amx_assembly addressof
==========================================
AMX Assembly Library: `addressof` function address lookup.
------------------------------------------

This library provides the `addressof` operator to get the position of a function in code (i.e the "address of" a function).  It also provides `nativeidxof` to get the index of a native function from the header (like `funcidx` does for public functions; which raises the question of why this has `of` in the name, for which there is no answer).

### `addressof`

This function takes a function and returns its address relative to the start of `COD`:

```pawn
MyFunc()
{
}

main()
{
	new addr = addressof(MyFunc);
	printf("`MyFunc` is at address 0x%08x", addr);
}
```

Because of limitations in the way the macro is implemented you must tell `addressof` how to call the function in question.  It *does not* call the function, so there are no unexpected side-effects, but a valid call to the function must appear in the generated code in order to get the address.  This is an unfortunate implementation detail leaked to users.  There are two ways to provide this information - either a `CALL@` macro for the function you're getting the address of:

```pawn
MyFunc(a, b)
{
}
#define CALL@MyFunc%8() MyFunc%8(0, 1) // Yes, the `%8`s are needed.

main()
{
	new addr = addressof(MyFunc);
	printf("`MyFunc` is at address 0x%08x", addr);
}
```

Or giving a specifier directly to `addressof`:

```pawn
MyFunc(a, b)
{
}

main()
{
	new addr = _:addressof(MyFunc<ii>);
	printf("`MyFunc` is at address 0x%08x", addr);
}
```

In the latter case the return value will have a tag representing how to call the function, so without the `_:` tag override as seen in the example above you would need to declare `addr` as `Func:addr<ii>`.

The *addressof-jit.inc* library will re-compile `addressof` calls to a single constant when `AddressofResolve()` is called.  It should really be a constant, but there's no (known) way of doing that at compile-time with only macros.  However, compiler version 3.10.11 introduced a native `__addressof` operator to do exactly this (but without the tag-type information, so still using `addressof` is better; with it using `__addressof` underneath where possible).  The original implementation of `addressof` used *disasm.inc* to find the fake function call and get the address from that.  The new version (ignoring any `__addressof` usage) does away with that fairly heavy dependency and is a single small function, defined in *addressof-light.inc*.

### `nativeidxof`

This function returns the address of a native function.  All natives are compiled to a number, this number is the index of the function name in the AMX header (basically an array), and calling a native becomes `SYSREQ.C <index>`.  The obvious implementation of `nativeidxof` would simply read this table from the header until the native was found, but there is no guarantee in that case that the native will have actually been used to appear in the table (`__nameof` *may* solve this).  Instead, in the same way as `addressof` has a fake call, so does `nativeidxof`, thus has the same limitations in use - i.e. you either need to provide `CALL@Name%8()` or the `<iisi>` specifier.  However, unlike `addressof` the return value is never tagged.

The index is currently read from the generated assembly, using `disasm` (thus bringing in that include when you use *addressof.inc* rather than *addressof-light.inc* directly).  Searching the header is possible, but with some care due to how name offsets are clobbered when running a 32-bit script on a 64-bit server (the `SYSREQ.D` pointers take up two cells instead of one).  This, however, is not information relevant to simply using the function.  *addressof-jit.inc* does not currently optimise this lookup, but can do.

## Variables


### `O@V_`:


## Functions


### `O@A_`:


#### Syntax


```pawn
O@A_()
```

#### Tag
`bool:`


#### Depends on
* [`DisasmContext`](#DisasmContext)
* [`DisasmContext_opcode`](#DisasmContext_opcode)
* [`DisasmGetOperandReloc`](#DisasmGetOperandReloc)
* [`DisasmInit`](#DisasmInit)
* [`DisasmNext`](#DisasmNext)
* [`GetCurrentFrameReturn`](#GetCurrentFrameReturn)
* [`O@V_`](#O@V_)
* [`OP_CALL`](#OP_CALL)
* [`false`](#false)
#### Estimated stack usage
11 cells



### `O@B_`:


#### Syntax


```pawn
O@B_()
```

#### Tag
`bool:`


#### Depends on
* [`DisasmContext`](#DisasmContext)
* [`DisasmContext_opcode`](#DisasmContext_opcode)
* [`DisasmGetOperand`](#DisasmGetOperand)
* [`DisasmInit`](#DisasmInit)
* [`DisasmNext`](#DisasmNext)
* [`GetCurrentFrameReturn`](#GetCurrentFrameReturn)
* [`O@V_`](#O@V_)
* [`OP_SYSREQ_C`](#OP_SYSREQ_C)
* [`false`](#false)
#### Estimated stack usage
11 cells

