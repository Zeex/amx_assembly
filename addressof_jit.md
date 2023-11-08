amx_assembly addressof_jit
==========================================
AMX Assembly Library: `addressof` JIT code.
------------------------------------------

`addressof` works by reading data directly out of the stack to get a return address, then reading information from that location in memory to get the next `CALL` OpCode.  This fails with the JIT because the return address is in the JITed code, not in the original p-code.  Instead this library uses *codescan.inc* to convert runtime `addressof` calls to startup-time resolutions (i.e. constants).  Despite being called "addressof-jit", this is useful in normal execution modes as well.  See [addressof.md](addressof.md) for more details.


## Functions


### `AddressofResolve`:


#### Syntax


```pawn
AddressofResolve()
```

#### Depends on
* [`AddressofResolveFoundEnd`](#AddressofResolveFoundEnd)
* [`AddressofResolveFoundStart`](#AddressofResolveFoundStart)
* [`CodeScanAddMatcher`](#CodeScanAddMatcher)
* [`CodeScanInit`](#CodeScanInit)
* [`CodeScanMatcher`](#CodeScanMatcher)
* [`CodeScanMatcherInit_`](#CodeScanMatcherInit_)
* [`CodeScanMatcherPattern_`](#CodeScanMatcherPattern_)
* [`CodeScanRunFast`](#CodeScanRunFast)
* [`CodeScanner`](#CodeScanner)
* [`GetAmxJITBaseAddress`](#GetAmxJITBaseAddress)
* [`O@A_`](#O@A_)
* [`O@V_`](#O@V_)
* [`OP_CALL`](#OP_CALL)
* [`OP_CONST_PRI`](#OP_CONST_PRI)
* [`OP_HEAP`](#OP_HEAP)
* [`OP_JUMP`](#OP_JUMP)
* [`OP_JZER`](#OP_JZER)
* [`OP_LOAD_PRI`](#OP_LOAD_PRI)
* [`OP_PUSH_C`](#OP_PUSH_C)
* [`false`](#false)
* [`gCodeScanCallback_match`](#gCodeScanCallback_match)
* [`ref`](#ref)
* [`true`](#true)
#### Estimated stack usage
761 cells



### `AddressofResolveFoundEnd`:


#### Syntax


```pawn
AddressofResolveFoundEnd(scanner[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`scanner`	 | 	` [172] `	 |

#### Depends on
* [`AsmContext`](#AsmContext)
* [`AsmEmitConstPri`](#AsmEmitConstPri)
* [`CodeScanGetMatchAsm`](#CodeScanGetMatchAsm)
* [`CodeScanGetMatchHole`](#CodeScanGetMatchHole)
* [`CodeScanGetMatchLength`](#CodeScanGetMatchLength)
* [`cellbytes`](#cellbytes)
#### Estimated stack usage
27 cells



### `AddressofResolveFoundStart`:


#### Syntax


```pawn
AddressofResolveFoundStart(scanner[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`scanner`	 | 	` [172] `	 |

#### Depends on
* [`AMX_HDR`](#AMX_HDR)
* [`AMX_HDR_COD`](#AMX_HDR_COD)
* [`AsmContext`](#AsmContext)
* [`AsmEmitJump`](#AsmEmitJump)
* [`CodeScanGetMatchAsm`](#CodeScanGetMatchAsm)
* [`CodeScanGetMatchHole`](#CodeScanGetMatchHole)
* [`GetAmxBaseAddress`](#GetAmxBaseAddress)
* [`GetAmxHeader`](#GetAmxHeader)
#### Estimated stack usage
44 cells

