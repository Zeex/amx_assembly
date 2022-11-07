amx_assembly asm
==========================================
AMX Assembly Library: Assembly code generation.
------------------------------------------



## Enums


### `AsmContext`:

#### Members

* `AsmContext_buffer = 0`
* `AsmContext_buffer_size = 1`
* `AsmContext_buffer_offset = 2`
* `AsmContext_error = 3`
* `AsmContext_error_handler = 4`
* `AsmContext_label_names = 5`
* `AsmContext_labels = 13`

### `AsmError`:

#### Members

* `ASM_ERROR_NONE = 0`
* `ASM_ERROR_OPCODE = 1`
* `ASM_ERROR_OPERAND = 2`
* `ASM_ERROR_SPACE = 3`
* `ASM_ERROR_LABEL_OVERFLOW = 4`
* `ASM_ERROR_LABEL_DUPLICATE = 5`

## Variables


### `ASM_ARGUMENTS_OFFSET`:


### `ASM_CALLER_FRAME_OFFSET`:


### `ASM_CTRL_CIP`:


### `ASM_CTRL_COD`:


### `ASM_CTRL_DAT`:


### `ASM_CTRL_FRM`:


### `ASM_CTRL_HEA`:


### `ASM_CTRL_JIT`:


### `ASM_CTRL_JMP`:


### `ASM_CTRL_STK`:


### `ASM_CTRL_STP`:


### `ASM_LOCALS_OFFSET`:


### `ASM_RETURN_ADDR_OFFSET`:


### `gPreviousWriteOffset`:


## Functions


### `AsmClearError`:


#### Syntax


```pawn
AsmClearError(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Depends on
* [`ASM_ERROR_NONE`](#ASM_ERROR_NONE)
* [`AsmSetError`](#AsmSetError)
#### Estimated stack usage
5 cells



### `AsmEmitAdd`:


#### Syntax


```pawn
AsmEmitAdd(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_ADD`](#OP_ADD)
#### Estimated stack usage
5 cells



### `AsmEmitAddC`:


#### Syntax


```pawn
AsmEmitAddC(ctx[], value)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`value`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_ADD_C`](#OP_ADD_C)
#### Estimated stack usage
6 cells



### `AsmEmitAddrAlt`:


#### Syntax


```pawn
AsmEmitAddrAlt(ctx[], offset)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`offset`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_ADDR_ALT`](#OP_ADDR_ALT)
#### Estimated stack usage
6 cells



### `AsmEmitAddrPri`:


#### Syntax


```pawn
AsmEmitAddrPri(ctx[], offset)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`offset`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_ADDR_PRI`](#OP_ADDR_PRI)
#### Estimated stack usage
6 cells



### `AsmEmitAlignAlt`:


#### Syntax


```pawn
AsmEmitAlignAlt(ctx[], number)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`number`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_ALIGN_ALT`](#OP_ALIGN_ALT)
#### Estimated stack usage
6 cells



### `AsmEmitAlignPri`:


#### Syntax


```pawn
AsmEmitAlignPri(ctx[], number)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`number`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_ALIGN_PRI`](#OP_ALIGN_PRI)
#### Estimated stack usage
6 cells



### `AsmEmitAnd`:


#### Syntax


```pawn
AsmEmitAnd(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_AND`](#OP_AND)
#### Estimated stack usage
5 cells



### `AsmEmitBounds`:


#### Syntax


```pawn
AsmEmitBounds(ctx[], bound)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`bound`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_BOUNDS`](#OP_BOUNDS)
#### Estimated stack usage
6 cells



### `AsmEmitBreak`:


#### Syntax


```pawn
AsmEmitBreak(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_BREAK`](#OP_BREAK)
#### Estimated stack usage
5 cells



### `AsmEmitCall`:


#### Syntax


```pawn
AsmEmitCall(ctx[], address)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`address`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_CALL`](#OP_CALL)
#### Estimated stack usage
6 cells



### `AsmEmitCallAbs`:


#### Syntax


```pawn
AsmEmitCallAbs(ctx[], address)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`address`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AMX_HDR`](#AMX_HDR)
* [`AMX_HDR_COD`](#AMX_HDR_COD)
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`GetAmxBaseAddress`](#GetAmxBaseAddress)
* [`GetAmxHeader`](#GetAmxHeader)
* [`OP_CALL`](#OP_CALL)
#### Estimated stack usage
24 cells



### `AsmEmitCallLabelStringize`:


#### Syntax


```pawn
AsmEmitCallLabelStringize(ctx[], label[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`label`	 | 	` [] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitJumpLabelInstruction`](#AsmEmitJumpLabelInstruction)
* [`OP_CALL`](#OP_CALL)
#### Estimated stack usage
7 cells



### `AsmEmitCell`:


#### Syntax


```pawn
AsmEmitCell(ctx[], value)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`value`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`ASM_ERROR_NONE`](#ASM_ERROR_NONE)
* [`ASM_ERROR_SPACE`](#ASM_ERROR_SPACE)
* [`AsmContext_buffer`](#AsmContext_buffer)
* [`AsmContext_buffer_offset`](#AsmContext_buffer_offset)
* [`AsmContext_buffer_size`](#AsmContext_buffer_size)
* [`AsmRaiseError`](#AsmRaiseError)
* [`cellbytes`](#cellbytes)
* [`gAmxAssemblyAddress_`](#gAmxAssemblyAddress_)
#### Estimated stack usage
5 cells



### `AsmEmitCmps`:


#### Syntax


```pawn
AsmEmitCmps(ctx[], nbytes)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`nbytes`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_CMPS`](#OP_CMPS)
#### Estimated stack usage
6 cells



### `AsmEmitConstAlt`:


#### Syntax


```pawn
AsmEmitConstAlt(ctx[], value)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`value`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_CONST_ALT`](#OP_CONST_ALT)
#### Estimated stack usage
6 cells



### `AsmEmitConstPri`:


#### Syntax


```pawn
AsmEmitConstPri(ctx[], value)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`value`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_CONST_PRI`](#OP_CONST_PRI)
#### Estimated stack usage
6 cells



### `AsmEmitDec`:


#### Syntax


```pawn
AsmEmitDec(ctx[], address)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`address`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_DEC`](#OP_DEC)
#### Estimated stack usage
6 cells



### `AsmEmitDecAlt`:


#### Syntax


```pawn
AsmEmitDecAlt(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_DEC_ALT`](#OP_DEC_ALT)
#### Estimated stack usage
5 cells



### `AsmEmitDecI`:


#### Syntax


```pawn
AsmEmitDecI(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_DEC_I`](#OP_DEC_I)
#### Estimated stack usage
5 cells



### `AsmEmitDecPri`:


#### Syntax


```pawn
AsmEmitDecPri(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_DEC_PRI`](#OP_DEC_PRI)
#### Estimated stack usage
5 cells



### `AsmEmitDecS`:


#### Syntax


```pawn
AsmEmitDecS(ctx[], offset)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`offset`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_DEC_S`](#OP_DEC_S)
#### Estimated stack usage
6 cells



### `AsmEmitEq`:


#### Syntax


```pawn
AsmEmitEq(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_EQ`](#OP_EQ)
#### Estimated stack usage
5 cells



### `AsmEmitEqCAlt`:


#### Syntax


```pawn
AsmEmitEqCAlt(ctx[], value)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`value`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_EQ_C_ALT`](#OP_EQ_C_ALT)
#### Estimated stack usage
6 cells



### `AsmEmitEqCPri`:


#### Syntax


```pawn
AsmEmitEqCPri(ctx[], value)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`value`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_EQ_C_PRI`](#OP_EQ_C_PRI)
#### Estimated stack usage
6 cells



### `AsmEmitFill`:


#### Syntax


```pawn
AsmEmitFill(ctx[], nbytes)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`nbytes`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_FILL`](#OP_FILL)
#### Estimated stack usage
6 cells



### `AsmEmitGeq`:


#### Syntax


```pawn
AsmEmitGeq(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_GEQ`](#OP_GEQ)
#### Estimated stack usage
5 cells



### `AsmEmitGrtr`:


#### Syntax


```pawn
AsmEmitGrtr(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_GRTR`](#OP_GRTR)
#### Estimated stack usage
5 cells



### `AsmEmitHalt`:


#### Syntax


```pawn
AsmEmitHalt(ctx[], code)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`code`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_HALT`](#OP_HALT)
#### Estimated stack usage
6 cells



### `AsmEmitHeap`:


#### Syntax


```pawn
AsmEmitHeap(ctx[], nbytes)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`nbytes`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_HEAP`](#OP_HEAP)
#### Estimated stack usage
6 cells



### `AsmEmitIdxaddr`:


#### Syntax


```pawn
AsmEmitIdxaddr(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_IDXADDR`](#OP_IDXADDR)
#### Estimated stack usage
5 cells



### `AsmEmitIdxaddrB`:


#### Syntax


```pawn
AsmEmitIdxaddrB(ctx[], shift)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`shift`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_IDXADDR_B`](#OP_IDXADDR_B)
#### Estimated stack usage
6 cells



### `AsmEmitInc`:


#### Syntax


```pawn
AsmEmitInc(ctx[], address)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`address`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_INC`](#OP_INC)
#### Estimated stack usage
6 cells



### `AsmEmitIncAlt`:


#### Syntax


```pawn
AsmEmitIncAlt(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_INC_ALT`](#OP_INC_ALT)
#### Estimated stack usage
5 cells



### `AsmEmitIncI`:


#### Syntax


```pawn
AsmEmitIncI(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_INC_I`](#OP_INC_I)
#### Estimated stack usage
5 cells



### `AsmEmitIncPri`:


#### Syntax


```pawn
AsmEmitIncPri(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_INC_PRI`](#OP_INC_PRI)
#### Estimated stack usage
5 cells



### `AsmEmitIncS`:


#### Syntax


```pawn
AsmEmitIncS(ctx[], offset)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`offset`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_INC_S`](#OP_INC_S)
#### Estimated stack usage
6 cells



### `AsmEmitInstruction`:


#### Syntax


```pawn
AsmEmitInstruction(ctx[], opcode, ...)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`opcode`	 | 	`Opcode `	 |
| 	`...`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`ASM_ERROR_NONE`](#ASM_ERROR_NONE)
* [`AsmContext_buffer_offset`](#AsmContext_buffer_offset)
* [`AsmEmitOpcode`](#AsmEmitOpcode)
* [`AsmEmitOperand`](#AsmEmitOperand)
* [`__COMPILER_CELL_SHIFT`](#__COMPILER_CELL_SHIFT)
* [`__args_offset`](#__args_offset)
* [`gPreviousWriteOffset`](#gPreviousWriteOffset)
* [`getarg`](#getarg)
#### Estimated stack usage
8 cells



### `AsmEmitInvert`:


#### Syntax


```pawn
AsmEmitInvert(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_INVERT`](#OP_INVERT)
#### Estimated stack usage
5 cells



### `AsmEmitJeq`:


#### Syntax


```pawn
AsmEmitJeq(ctx[], address)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`address`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_JEQ`](#OP_JEQ)
#### Estimated stack usage
6 cells



### `AsmEmitJeqLabelStringize`:


#### Syntax


```pawn
AsmEmitJeqLabelStringize(ctx[], label[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`label`	 | 	` [] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitJumpLabelInstruction`](#AsmEmitJumpLabelInstruction)
* [`OP_JEQ`](#OP_JEQ)
#### Estimated stack usage
7 cells



### `AsmEmitJeqRel`:


#### Syntax


```pawn
AsmEmitJeqRel(ctx[], offset)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`offset`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitJumpInstruction`](#AsmEmitJumpInstruction)
* [`OP_JEQ`](#OP_JEQ)
#### Estimated stack usage
6 cells



### `AsmEmitJgeq`:


#### Syntax


```pawn
AsmEmitJgeq(ctx[], address)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`address`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_JGEQ`](#OP_JGEQ)
#### Estimated stack usage
6 cells



### `AsmEmitJgeqLabelStringize`:


#### Syntax


```pawn
AsmEmitJgeqLabelStringize(ctx[], label[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`label`	 | 	` [] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitJumpLabelInstruction`](#AsmEmitJumpLabelInstruction)
* [`OP_JGEQ`](#OP_JGEQ)
#### Estimated stack usage
7 cells



### `AsmEmitJgeqRel`:


#### Syntax


```pawn
AsmEmitJgeqRel(ctx[], offset)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`offset`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitJumpInstruction`](#AsmEmitJumpInstruction)
* [`OP_JGEQ`](#OP_JGEQ)
#### Estimated stack usage
6 cells



### `AsmEmitJgrtr`:


#### Syntax


```pawn
AsmEmitJgrtr(ctx[], address)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`address`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_JGRTR`](#OP_JGRTR)
#### Estimated stack usage
6 cells



### `AsmEmitJgrtrLabelStringize`:


#### Syntax


```pawn
AsmEmitJgrtrLabelStringize(ctx[], label[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`label`	 | 	` [] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitJumpLabelInstruction`](#AsmEmitJumpLabelInstruction)
* [`OP_JGRTR`](#OP_JGRTR)
#### Estimated stack usage
7 cells



### `AsmEmitJgrtrRel`:


#### Syntax


```pawn
AsmEmitJgrtrRel(ctx[], offset)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`offset`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitJumpInstruction`](#AsmEmitJumpInstruction)
* [`OP_JGRTR`](#OP_JGRTR)
#### Estimated stack usage
6 cells



### `AsmEmitJleq`:


#### Syntax


```pawn
AsmEmitJleq(ctx[], address)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`address`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_JLEQ`](#OP_JLEQ)
#### Estimated stack usage
6 cells



### `AsmEmitJleqLabelStringize`:


#### Syntax


```pawn
AsmEmitJleqLabelStringize(ctx[], label[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`label`	 | 	` [] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitJumpLabelInstruction`](#AsmEmitJumpLabelInstruction)
* [`OP_JLEQ`](#OP_JLEQ)
#### Estimated stack usage
7 cells



### `AsmEmitJleqRel`:


#### Syntax


```pawn
AsmEmitJleqRel(ctx[], offset)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`offset`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitJumpInstruction`](#AsmEmitJumpInstruction)
* [`OP_JLEQ`](#OP_JLEQ)
#### Estimated stack usage
6 cells



### `AsmEmitJless`:


#### Syntax


```pawn
AsmEmitJless(ctx[], address)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`address`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_JLESS`](#OP_JLESS)
#### Estimated stack usage
6 cells



### `AsmEmitJlessLabelStringize`:


#### Syntax


```pawn
AsmEmitJlessLabelStringize(ctx[], label[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`label`	 | 	` [] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitJumpLabelInstruction`](#AsmEmitJumpLabelInstruction)
* [`OP_JLESS`](#OP_JLESS)
#### Estimated stack usage
7 cells



### `AsmEmitJlessRel`:


#### Syntax


```pawn
AsmEmitJlessRel(ctx[], offset)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`offset`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitJumpInstruction`](#AsmEmitJumpInstruction)
* [`OP_JLESS`](#OP_JLESS)
#### Estimated stack usage
6 cells



### `AsmEmitJneq`:


#### Syntax


```pawn
AsmEmitJneq(ctx[], address)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`address`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_JNEQ`](#OP_JNEQ)
#### Estimated stack usage
6 cells



### `AsmEmitJneqLabelStringize`:


#### Syntax


```pawn
AsmEmitJneqLabelStringize(ctx[], label[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`label`	 | 	` [] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitJumpLabelInstruction`](#AsmEmitJumpLabelInstruction)
* [`OP_JNEQ`](#OP_JNEQ)
#### Estimated stack usage
7 cells



### `AsmEmitJneqRel`:


#### Syntax


```pawn
AsmEmitJneqRel(ctx[], offset)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`offset`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitJumpInstruction`](#AsmEmitJumpInstruction)
* [`OP_JNEQ`](#OP_JNEQ)
#### Estimated stack usage
6 cells



### `AsmEmitJnz`:


#### Syntax


```pawn
AsmEmitJnz(ctx[], address)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`address`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_JNZ`](#OP_JNZ)
#### Estimated stack usage
6 cells



### `AsmEmitJnzLabelStringize`:


#### Syntax


```pawn
AsmEmitJnzLabelStringize(ctx[], label[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`label`	 | 	` [] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitJumpLabelInstruction`](#AsmEmitJumpLabelInstruction)
* [`OP_JNZ`](#OP_JNZ)
#### Estimated stack usage
7 cells



### `AsmEmitJnzRel`:


#### Syntax


```pawn
AsmEmitJnzRel(ctx[], offset)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`offset`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitJumpInstruction`](#AsmEmitJumpInstruction)
* [`OP_JNZ`](#OP_JNZ)
#### Estimated stack usage
6 cells



### `AsmEmitJrel`:


#### Syntax


```pawn
AsmEmitJrel(ctx[], offset)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`offset`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitJumpInstruction`](#AsmEmitJumpInstruction)
* [`OP_JREL`](#OP_JREL)
#### Estimated stack usage
6 cells



### `AsmEmitJrelLabelStringize`:


#### Syntax


```pawn
AsmEmitJrelLabelStringize(ctx[], label[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`label`	 | 	` [] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitJumpLabelInstruction`](#AsmEmitJumpLabelInstruction)
* [`OP_JREL`](#OP_JREL)
* [`true`](#true)
#### Estimated stack usage
7 cells



### `AsmEmitJsgeq`:


#### Syntax


```pawn
AsmEmitJsgeq(ctx[], address)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`address`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_JSGEQ`](#OP_JSGEQ)
#### Estimated stack usage
6 cells



### `AsmEmitJsgeqLabelStringize`:


#### Syntax


```pawn
AsmEmitJsgeqLabelStringize(ctx[], label[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`label`	 | 	` [] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitJumpLabelInstruction`](#AsmEmitJumpLabelInstruction)
* [`OP_JSGEQ`](#OP_JSGEQ)
#### Estimated stack usage
7 cells



### `AsmEmitJsgeqRel`:


#### Syntax


```pawn
AsmEmitJsgeqRel(ctx[], offset)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`offset`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitJumpInstruction`](#AsmEmitJumpInstruction)
* [`OP_JSGEQ`](#OP_JSGEQ)
#### Estimated stack usage
6 cells



### `AsmEmitJsgrtr`:


#### Syntax


```pawn
AsmEmitJsgrtr(ctx[], address)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`address`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_JSGRTR`](#OP_JSGRTR)
#### Estimated stack usage
6 cells



### `AsmEmitJsgrtrLabelStringize`:


#### Syntax


```pawn
AsmEmitJsgrtrLabelStringize(ctx[], label[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`label`	 | 	` [] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitJumpLabelInstruction`](#AsmEmitJumpLabelInstruction)
* [`OP_JSGRTR`](#OP_JSGRTR)
#### Estimated stack usage
7 cells



### `AsmEmitJsgrtrRel`:


#### Syntax


```pawn
AsmEmitJsgrtrRel(ctx[], offset)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`offset`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitJumpInstruction`](#AsmEmitJumpInstruction)
* [`OP_JSGRTR`](#OP_JSGRTR)
#### Estimated stack usage
6 cells



### `AsmEmitJsleq`:


#### Syntax


```pawn
AsmEmitJsleq(ctx[], address)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`address`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_JSLEQ`](#OP_JSLEQ)
#### Estimated stack usage
6 cells



### `AsmEmitJsleqLabelStringize`:


#### Syntax


```pawn
AsmEmitJsleqLabelStringize(ctx[], label[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`label`	 | 	` [] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitJumpLabelInstruction`](#AsmEmitJumpLabelInstruction)
* [`OP_JSLEQ`](#OP_JSLEQ)
#### Estimated stack usage
7 cells



### `AsmEmitJsleqRel`:


#### Syntax


```pawn
AsmEmitJsleqRel(ctx[], offset)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`offset`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitJumpInstruction`](#AsmEmitJumpInstruction)
* [`OP_JSLEQ`](#OP_JSLEQ)
#### Estimated stack usage
6 cells



### `AsmEmitJsless`:


#### Syntax


```pawn
AsmEmitJsless(ctx[], address)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`address`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_JSLESS`](#OP_JSLESS)
#### Estimated stack usage
6 cells



### `AsmEmitJslessLabelStringize`:


#### Syntax


```pawn
AsmEmitJslessLabelStringize(ctx[], label[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`label`	 | 	` [] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitJumpLabelInstruction`](#AsmEmitJumpLabelInstruction)
* [`OP_JSLESS`](#OP_JSLESS)
#### Estimated stack usage
7 cells



### `AsmEmitJslessRel`:


#### Syntax


```pawn
AsmEmitJslessRel(ctx[], offset)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`offset`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitJumpInstruction`](#AsmEmitJumpInstruction)
* [`OP_JSLESS`](#OP_JSLESS)
#### Estimated stack usage
6 cells



### `AsmEmitJump`:


#### Syntax


```pawn
AsmEmitJump(ctx[], address)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`address`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_JUMP`](#OP_JUMP)
#### Estimated stack usage
6 cells



### `AsmEmitJumpInstruction`:


#### Syntax


```pawn
AsmEmitJumpInstruction(ctx[], opcode, offset)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`opcode`	 | 	`Opcode `	 |
| 	`offset`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`AsmGetJumpAddressFromOffset`](#AsmGetJumpAddressFromOffset)
#### Estimated stack usage
7 cells



### `AsmEmitJumpLabelInstruction`:


#### Syntax


```pawn
AsmEmitJumpLabelInstruction(ctx[], opcode, label[], relative)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`opcode`	 | 	`Opcode `	 |
| 	`label`	 | 	` [] `	 |
| 	`relative`	 | 	`bool `	 |

#### Tag
`AsmError:`


#### Depends on
* [`ASM_ERROR_NONE`](#ASM_ERROR_NONE)
* [`AsmContext_buffer_offset`](#AsmContext_buffer_offset)
* [`AsmEmitJumpStringize`](#AsmEmitJumpStringize)
* [`AsmEmitOpcode`](#AsmEmitOpcode)
* [`gPreviousWriteOffset`](#gPreviousWriteOffset)
#### Estimated stack usage
7 cells



### `AsmEmitJumpLabelStringize`:


#### Syntax


```pawn
AsmEmitJumpLabelStringize(ctx[], label[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`label`	 | 	` [] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitJumpLabelInstruction`](#AsmEmitJumpLabelInstruction)
* [`OP_JUMP`](#OP_JUMP)
#### Estimated stack usage
7 cells



### `AsmEmitJumpRel`:


#### Syntax


```pawn
AsmEmitJumpRel(ctx[], offset)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`offset`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitJumpInstruction`](#AsmEmitJumpInstruction)
* [`OP_JUMP`](#OP_JUMP)
#### Estimated stack usage
6 cells



### `AsmEmitJumpStringize`:


#### Syntax


```pawn
AsmEmitJumpStringize(ctx[], label[], relative)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`label`	 | 	` [] `	 |
| 	`relative`	 | 	`bool `	 |

#### Tag
`AsmError:`


#### Depends on
* [`ASM_ERROR_LABEL_OVERFLOW`](#ASM_ERROR_LABEL_OVERFLOW)
* [`ASM_ERROR_NONE`](#ASM_ERROR_NONE)
* [`AsmContext_buffer`](#AsmContext_buffer)
* [`AsmContext_buffer_offset`](#AsmContext_buffer_offset)
* [`AsmContext_label_names`](#AsmContext_label_names)
* [`AsmContext_labels`](#AsmContext_labels)
* [`AsmEmitCell`](#AsmEmitCell)
* [`AsmFindLabelIndex`](#AsmFindLabelIndex)
* [`AsmHashLabel`](#AsmHashLabel)
* [`AsmRaiseError`](#AsmRaiseError)
* [`cellbytes`](#cellbytes)
#### Estimated stack usage
10 cells



### `AsmEmitJzer`:


#### Syntax


```pawn
AsmEmitJzer(ctx[], address)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`address`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_JZER`](#OP_JZER)
#### Estimated stack usage
6 cells



### `AsmEmitJzerLabelStringize`:


#### Syntax


```pawn
AsmEmitJzerLabelStringize(ctx[], label[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`label`	 | 	` [] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitJumpLabelInstruction`](#AsmEmitJumpLabelInstruction)
* [`OP_JZER`](#OP_JZER)
#### Estimated stack usage
7 cells



### `AsmEmitJzerRel`:


#### Syntax


```pawn
AsmEmitJzerRel(ctx[], offset)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`offset`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitJumpInstruction`](#AsmEmitJumpInstruction)
* [`OP_JZER`](#OP_JZER)
#### Estimated stack usage
6 cells



### `AsmEmitLabelStringize`:


#### Syntax


```pawn
AsmEmitLabelStringize(ctx[], label[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`label`	 | 	` [] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`ASM_ERROR_LABEL_DUPLICATE`](#ASM_ERROR_LABEL_DUPLICATE)
* [`ASM_ERROR_LABEL_OVERFLOW`](#ASM_ERROR_LABEL_OVERFLOW)
* [`ASM_ERROR_NONE`](#ASM_ERROR_NONE)
* [`AsmContext_buffer`](#AsmContext_buffer)
* [`AsmContext_buffer_offset`](#AsmContext_buffer_offset)
* [`AsmContext_label_names`](#AsmContext_label_names)
* [`AsmContext_labels`](#AsmContext_labels)
* [`AsmFindLabelIndex`](#AsmFindLabelIndex)
* [`AsmGetJumpAddressFromOffset`](#AsmGetJumpAddressFromOffset)
* [`AsmHashLabel`](#AsmHashLabel)
* [`AsmRaiseError`](#AsmRaiseError)
* [`cellbytes`](#cellbytes)
* [`gAmxAssemblyAddress_`](#gAmxAssemblyAddress_)
#### Estimated stack usage
9 cells



### `AsmEmitLctrl`:


#### Syntax


```pawn
AsmEmitLctrl(ctx[], index)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`index`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_LCTRL`](#OP_LCTRL)
#### Estimated stack usage
6 cells



### `AsmEmitLeq`:


#### Syntax


```pawn
AsmEmitLeq(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_LEQ`](#OP_LEQ)
#### Estimated stack usage
5 cells



### `AsmEmitLess`:


#### Syntax


```pawn
AsmEmitLess(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_LESS`](#OP_LESS)
#### Estimated stack usage
5 cells



### `AsmEmitLidx`:


#### Syntax


```pawn
AsmEmitLidx(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_LIDX`](#OP_LIDX)
#### Estimated stack usage
5 cells



### `AsmEmitLidxB`:


#### Syntax


```pawn
AsmEmitLidxB(ctx[], shift)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`shift`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_LIDX_B`](#OP_LIDX_B)
#### Estimated stack usage
6 cells



### `AsmEmitLoad`:


#### Syntax


```pawn
AsmEmitLoad(ctx[], address)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`address`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_LOAD_ALT`](#OP_LOAD_ALT)
#### Estimated stack usage
6 cells



### `AsmEmitLoadAlt`:


#### Syntax


```pawn
AsmEmitLoadAlt(ctx[], address)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`address`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_LOAD_ALT`](#OP_LOAD_ALT)
#### Estimated stack usage
6 cells



### `AsmEmitLoadI`:


#### Syntax


```pawn
AsmEmitLoadI(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_LOAD_I`](#OP_LOAD_I)
#### Estimated stack usage
5 cells



### `AsmEmitLoadPri`:


#### Syntax


```pawn
AsmEmitLoadPri(ctx[], address)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`address`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_LOAD_PRI`](#OP_LOAD_PRI)
#### Estimated stack usage
6 cells



### `AsmEmitLoadSAlt`:


#### Syntax


```pawn
AsmEmitLoadSAlt(ctx[], offset)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`offset`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_LOAD_S_ALT`](#OP_LOAD_S_ALT)
#### Estimated stack usage
6 cells



### `AsmEmitLoadSPri`:


#### Syntax


```pawn
AsmEmitLoadSPri(ctx[], offset)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`offset`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_LOAD_S_PRI`](#OP_LOAD_S_PRI)
#### Estimated stack usage
6 cells



### `AsmEmitLodbI`:


#### Syntax


```pawn
AsmEmitLodbI(ctx[], nbytes)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`nbytes`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_LODB_I`](#OP_LODB_I)
#### Estimated stack usage
6 cells



### `AsmEmitLrefAlt`:


#### Syntax


```pawn
AsmEmitLrefAlt(ctx[], address)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`address`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_LREF_ALT`](#OP_LREF_ALT)
#### Estimated stack usage
6 cells



### `AsmEmitLrefPri`:


#### Syntax


```pawn
AsmEmitLrefPri(ctx[], address)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`address`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_LREF_PRI`](#OP_LREF_PRI)
#### Estimated stack usage
6 cells



### `AsmEmitLrefSAlt`:


#### Syntax


```pawn
AsmEmitLrefSAlt(ctx[], offset)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`offset`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_LREF_S_ALT`](#OP_LREF_S_ALT)
#### Estimated stack usage
6 cells



### `AsmEmitLrefSPri`:


#### Syntax


```pawn
AsmEmitLrefSPri(ctx[], offset)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`offset`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_LREF_S_PRI`](#OP_LREF_S_PRI)
#### Estimated stack usage
6 cells



### `AsmEmitMoveAlt`:


#### Syntax


```pawn
AsmEmitMoveAlt(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_MOVE_ALT`](#OP_MOVE_ALT)
#### Estimated stack usage
5 cells



### `AsmEmitMovePri`:


#### Syntax


```pawn
AsmEmitMovePri(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_MOVE_PRI`](#OP_MOVE_PRI)
#### Estimated stack usage
5 cells



### `AsmEmitMovs`:


#### Syntax


```pawn
AsmEmitMovs(ctx[], nbytes)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`nbytes`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_MOVS`](#OP_MOVS)
#### Estimated stack usage
6 cells



### `AsmEmitNeg`:


#### Syntax


```pawn
AsmEmitNeg(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_NEG`](#OP_NEG)
#### Estimated stack usage
5 cells



### `AsmEmitNeq`:


#### Syntax


```pawn
AsmEmitNeq(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_NEQ`](#OP_NEQ)
#### Estimated stack usage
5 cells



### `AsmEmitNop`:


#### Syntax


```pawn
AsmEmitNop(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_NOP`](#OP_NOP)
#### Estimated stack usage
5 cells



### `AsmEmitNot`:


#### Syntax


```pawn
AsmEmitNot(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_NOT`](#OP_NOT)
#### Estimated stack usage
5 cells



### `AsmEmitOpcode`:


#### Syntax


```pawn
AsmEmitOpcode(ctx[], opcode)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`opcode`	 | 	`Opcode `	 |

#### Tag
`AsmError:`


#### Depends on
* [`ASM_ERROR_OPCODE`](#ASM_ERROR_OPCODE)
* [`AsmEmitCell`](#AsmEmitCell)
* [`AsmRaiseError`](#AsmRaiseError)
* [`NUM_OPCODES`](#NUM_OPCODES)
* [`OP_NONE`](#OP_NONE)
* [`RelocateOpcode`](#RelocateOpcode)
#### Estimated stack usage
5 cells



### `AsmEmitOperand`:


#### Syntax


```pawn
AsmEmitOperand(ctx[], value)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`value`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitCell`](#AsmEmitCell)
#### Estimated stack usage
5 cells



### `AsmEmitOr`:


#### Syntax


```pawn
AsmEmitOr(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_OR`](#OP_OR)
#### Estimated stack usage
5 cells



### `AsmEmitPadding`:


#### Syntax


```pawn
AsmEmitPadding(ctx[], op)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`op`	 | 	`Opcode `	 |

#### Depends on
* [`AsmContext_buffer`](#AsmContext_buffer)
* [`AsmContext_buffer_offset`](#AsmContext_buffer_offset)
* [`AsmContext_buffer_size`](#AsmContext_buffer_size)
* [`IsOpcodeValid`](#IsOpcodeValid)
* [`OP_NOP`](#OP_NOP)
* [`RelocateOpcode`](#RelocateOpcode)
* [`cellbytes`](#cellbytes)
* [`gAMXOpcodeParameterCounts`](#gAMXOpcodeParameterCounts)
* [`gAmxAssemblyAddress_`](#gAmxAssemblyAddress_)
#### Estimated stack usage
4 cells



### `AsmEmitPopAlt`:


#### Syntax


```pawn
AsmEmitPopAlt(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_POP_ALT`](#OP_POP_ALT)
#### Estimated stack usage
5 cells



### `AsmEmitPopArgs`:


#### Syntax


```pawn
AsmEmitPopArgs(ctx[], n)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`n`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitStack`](#AsmEmitStack)
* [`cellbytes`](#cellbytes)
#### Estimated stack usage
5 cells



### `AsmEmitPopPri`:


#### Syntax


```pawn
AsmEmitPopPri(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_POP_PRI`](#OP_POP_PRI)
#### Estimated stack usage
5 cells



### `AsmEmitProc`:


#### Syntax


```pawn
AsmEmitProc(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_PROC`](#OP_PROC)
#### Estimated stack usage
5 cells



### `AsmEmitPush`:


#### Syntax


```pawn
AsmEmitPush(ctx[], address)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`address`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_PUSH`](#OP_PUSH)
#### Estimated stack usage
6 cells



### `AsmEmitPushAdr`:


#### Syntax


```pawn
AsmEmitPushAdr(ctx[], offset)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`offset`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_PUSH_ADR`](#OP_PUSH_ADR)
#### Estimated stack usage
6 cells



### `AsmEmitPushAlt`:


#### Syntax


```pawn
AsmEmitPushAlt(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_PUSH_ALT`](#OP_PUSH_ALT)
#### Estimated stack usage
5 cells



### `AsmEmitPushArg`:


#### Syntax


```pawn
AsmEmitPushArg(ctx[], n)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`n`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitPushS`](#AsmEmitPushS)
* [`AsmGetArgOffset`](#AsmGetArgOffset)
#### Estimated stack usage
5 cells



### `AsmEmitPushC`:


#### Syntax


```pawn
AsmEmitPushC(ctx[], value)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`value`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_PUSH_C`](#OP_PUSH_C)
#### Estimated stack usage
6 cells



### `AsmEmitPushNumArgs`:


#### Syntax


```pawn
AsmEmitPushNumArgs(ctx[], n)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`n`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitPushC`](#AsmEmitPushC)
* [`cellbytes`](#cellbytes)
#### Estimated stack usage
5 cells



### `AsmEmitPushPri`:


#### Syntax


```pawn
AsmEmitPushPri(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_PUSH_PRI`](#OP_PUSH_PRI)
#### Estimated stack usage
5 cells



### `AsmEmitPushS`:


#### Syntax


```pawn
AsmEmitPushS(ctx[], offset)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`offset`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_PUSH_S`](#OP_PUSH_S)
#### Estimated stack usage
6 cells



### `AsmEmitRet`:


#### Syntax


```pawn
AsmEmitRet(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_RET`](#OP_RET)
#### Estimated stack usage
5 cells



### `AsmEmitRetn`:


#### Syntax


```pawn
AsmEmitRetn(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_RETN`](#OP_RETN)
#### Estimated stack usage
5 cells



### `AsmEmitSctrl`:


#### Syntax


```pawn
AsmEmitSctrl(ctx[], index)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`index`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_SCTRL`](#OP_SCTRL)
#### Estimated stack usage
6 cells



### `AsmEmitSdiv`:


#### Syntax


```pawn
AsmEmitSdiv(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_SDIV`](#OP_SDIV)
#### Estimated stack usage
5 cells



### `AsmEmitSdivAlt`:


#### Syntax


```pawn
AsmEmitSdivAlt(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_SDIV_ALT`](#OP_SDIV_ALT)
#### Estimated stack usage
5 cells



### `AsmEmitSgeq`:


#### Syntax


```pawn
AsmEmitSgeq(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_SGEQ`](#OP_SGEQ)
#### Estimated stack usage
5 cells



### `AsmEmitSgrtr`:


#### Syntax


```pawn
AsmEmitSgrtr(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_SGRTR`](#OP_SGRTR)
#### Estimated stack usage
5 cells



### `AsmEmitShl`:


#### Syntax


```pawn
AsmEmitShl(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_SHL`](#OP_SHL)
#### Estimated stack usage
5 cells



### `AsmEmitShlCAlt`:


#### Syntax


```pawn
AsmEmitShlCAlt(ctx[], shift)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`shift`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_SHL_C_ALT`](#OP_SHL_C_ALT)
#### Estimated stack usage
6 cells



### `AsmEmitShlCPri`:


#### Syntax


```pawn
AsmEmitShlCPri(ctx[], shift)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`shift`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_SHL_C_PRI`](#OP_SHL_C_PRI)
#### Estimated stack usage
6 cells



### `AsmEmitShr`:


#### Syntax


```pawn
AsmEmitShr(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_SHR`](#OP_SHR)
#### Estimated stack usage
5 cells



### `AsmEmitShrCAlt`:


#### Syntax


```pawn
AsmEmitShrCAlt(ctx[], shift)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`shift`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_SHR_C_ALT`](#OP_SHR_C_ALT)
#### Estimated stack usage
6 cells



### `AsmEmitShrCPri`:


#### Syntax


```pawn
AsmEmitShrCPri(ctx[], shift)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`shift`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_SHR_C_PRI`](#OP_SHR_C_PRI)
#### Estimated stack usage
6 cells



### `AsmEmitSignAlt`:


#### Syntax


```pawn
AsmEmitSignAlt(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_SIGN_ALT`](#OP_SIGN_ALT)
#### Estimated stack usage
5 cells



### `AsmEmitSignPri`:


#### Syntax


```pawn
AsmEmitSignPri(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_SIGN_PRI`](#OP_SIGN_PRI)
#### Estimated stack usage
5 cells



### `AsmEmitSleq`:


#### Syntax


```pawn
AsmEmitSleq(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_SLEQ`](#OP_SLEQ)
#### Estimated stack usage
5 cells



### `AsmEmitSless`:


#### Syntax


```pawn
AsmEmitSless(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_SLESS`](#OP_SLESS)
#### Estimated stack usage
5 cells



### `AsmEmitSmul`:


#### Syntax


```pawn
AsmEmitSmul(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_SMUL`](#OP_SMUL)
#### Estimated stack usage
5 cells



### `AsmEmitSmulC`:


#### Syntax


```pawn
AsmEmitSmulC(ctx[], value)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`value`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_SMUL_C`](#OP_SMUL_C)
#### Estimated stack usage
6 cells



### `AsmEmitSrefAlt`:


#### Syntax


```pawn
AsmEmitSrefAlt(ctx[], address)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`address`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_SREF_ALT`](#OP_SREF_ALT)
#### Estimated stack usage
6 cells



### `AsmEmitSrefPri`:


#### Syntax


```pawn
AsmEmitSrefPri(ctx[], address)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`address`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_SREF_PRI`](#OP_SREF_PRI)
#### Estimated stack usage
6 cells



### `AsmEmitSrefSAlt`:


#### Syntax


```pawn
AsmEmitSrefSAlt(ctx[], offset)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`offset`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_SREF_S_ALT`](#OP_SREF_S_ALT)
#### Estimated stack usage
6 cells



### `AsmEmitSrefSPri`:


#### Syntax


```pawn
AsmEmitSrefSPri(ctx[], offset)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`offset`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_SREF_S_PRI`](#OP_SREF_S_PRI)
#### Estimated stack usage
6 cells



### `AsmEmitSshr`:


#### Syntax


```pawn
AsmEmitSshr(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_SSHR`](#OP_SSHR)
#### Estimated stack usage
5 cells



### `AsmEmitStack`:


#### Syntax


```pawn
AsmEmitStack(ctx[], nbytes)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`nbytes`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_STACK`](#OP_STACK)
#### Estimated stack usage
6 cells



### `AsmEmitStorAlt`:


#### Syntax


```pawn
AsmEmitStorAlt(ctx[], address)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`address`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_STOR_ALT`](#OP_STOR_ALT)
#### Estimated stack usage
6 cells



### `AsmEmitStorI`:


#### Syntax


```pawn
AsmEmitStorI(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_STOR_I`](#OP_STOR_I)
#### Estimated stack usage
5 cells



### `AsmEmitStorPri`:


#### Syntax


```pawn
AsmEmitStorPri(ctx[], address)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`address`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_STOR_PRI`](#OP_STOR_PRI)
#### Estimated stack usage
6 cells



### `AsmEmitStorSAlt`:


#### Syntax


```pawn
AsmEmitStorSAlt(ctx[], offset)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`offset`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_STOR_S_ALT`](#OP_STOR_S_ALT)
#### Estimated stack usage
6 cells



### `AsmEmitStorSPri`:


#### Syntax


```pawn
AsmEmitStorSPri(ctx[], offset)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`offset`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_STOR_S_PRI`](#OP_STOR_S_PRI)
#### Estimated stack usage
6 cells



### `AsmEmitStrbI`:


#### Syntax


```pawn
AsmEmitStrbI(ctx[], nbytes)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`nbytes`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_STRB_I`](#OP_STRB_I)
#### Estimated stack usage
6 cells



### `AsmEmitSub`:


#### Syntax


```pawn
AsmEmitSub(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_SUB`](#OP_SUB)
#### Estimated stack usage
5 cells



### `AsmEmitSubAlt`:


#### Syntax


```pawn
AsmEmitSubAlt(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_SUB_ALT`](#OP_SUB_ALT)
#### Estimated stack usage
5 cells



### `AsmEmitSwapAlt`:


#### Syntax


```pawn
AsmEmitSwapAlt(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_SWAP_ALT`](#OP_SWAP_ALT)
#### Estimated stack usage
5 cells



### `AsmEmitSwapPri`:


#### Syntax


```pawn
AsmEmitSwapPri(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_SWAP_PRI`](#OP_SWAP_PRI)
#### Estimated stack usage
5 cells



### `AsmEmitSysreq`:


#### Syntax


```pawn
AsmEmitSysreq(ctx[], name[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`name`	 | 	` [] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitSysreqC`](#AsmEmitSysreqC)
* [`GetNativeIndexFromName`](#GetNativeIndexFromName)
#### Estimated stack usage
5 cells



### `AsmEmitSysreqC`:


#### Syntax


```pawn
AsmEmitSysreqC(ctx[], index)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`index`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_SYSREQ_C`](#OP_SYSREQ_C)
#### Estimated stack usage
6 cells



### `AsmEmitSysreqD`:


#### Syntax


```pawn
AsmEmitSysreqD(ctx[], address)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`address`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`ASM_ERROR_OPCODE`](#ASM_ERROR_OPCODE)
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_SYSREQ_D`](#OP_SYSREQ_D)
#### Estimated stack usage
6 cells



### `AsmEmitSysreqPri`:


#### Syntax


```pawn
AsmEmitSysreqPri(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_SYSREQ_PRI`](#OP_SYSREQ_PRI)
#### Estimated stack usage
5 cells



### `AsmEmitUdiv`:


#### Syntax


```pawn
AsmEmitUdiv(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_UDIV`](#OP_UDIV)
#### Estimated stack usage
5 cells



### `AsmEmitUdivAlt`:


#### Syntax


```pawn
AsmEmitUdivAlt(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_UDIV_ALT`](#OP_UDIV_ALT)
#### Estimated stack usage
5 cells



### `AsmEmitUmul`:


#### Syntax


```pawn
AsmEmitUmul(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_UMUL`](#OP_UMUL)
#### Estimated stack usage
5 cells



### `AsmEmitXchg`:


#### Syntax


```pawn
AsmEmitXchg(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_XCHG`](#OP_XCHG)
#### Estimated stack usage
5 cells



### `AsmEmitXor`:


#### Syntax


```pawn
AsmEmitXor(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_XOR`](#OP_XOR)
#### Estimated stack usage
5 cells



### `AsmEmitZero`:


#### Syntax


```pawn
AsmEmitZero(ctx[], address)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`address`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_ZERO`](#OP_ZERO)
#### Estimated stack usage
6 cells



### `AsmEmitZeroAlt`:


#### Syntax


```pawn
AsmEmitZeroAlt(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_ZERO_ALT`](#OP_ZERO_ALT)
#### Estimated stack usage
5 cells



### `AsmEmitZeroPri`:


#### Syntax


```pawn
AsmEmitZeroPri(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_ZERO_PRI`](#OP_ZERO_PRI)
#### Estimated stack usage
5 cells



### `AsmEmitZeroS`:


#### Syntax


```pawn
AsmEmitZeroS(ctx[], offset)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`offset`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmEmitInstruction`](#AsmEmitInstruction)
* [`OP_ZERO_S`](#OP_ZERO_S)
#### Estimated stack usage
6 cells



### `AsmFindLabelIndex`:


#### Syntax


```pawn
AsmFindLabelIndex(ctx[], hash)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`hash`	 | 		 |

#### Depends on
* [`AsmContext_label_names`](#AsmContext_label_names)
#### Estimated stack usage
2 cells



### `AsmGetArgOffset`:


#### Syntax


```pawn
AsmGetArgOffset(n)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`n`	 | 		 |

#### Depends on
* [`ASM_ARGUMENTS_OFFSET`](#ASM_ARGUMENTS_OFFSET)
* [`cellbytes`](#cellbytes)
#### Estimated stack usage
1 cells



### `AsmGetBufferSize`:


#### Syntax


```pawn
AsmGetBufferSize(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Depends on
* [`AsmContext_buffer_offset`](#AsmContext_buffer_offset)
* [`AsmContext_buffer_size`](#AsmContext_buffer_size)
#### Estimated stack usage
1 cells



### `AsmGetCode`:


#### Syntax


```pawn
AsmGetCode(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Depends on
* [`AMX_HDR`](#AMX_HDR)
* [`AMX_HDR_COD`](#AMX_HDR_COD)
* [`AMX_HDR_DAT`](#AMX_HDR_DAT)
* [`AsmContext_buffer`](#AsmContext_buffer)
* [`GetAmxHeader`](#GetAmxHeader)
#### Estimated stack usage
21 cells



### `AsmGetCodeSize`:


#### Syntax


```pawn
AsmGetCodeSize(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Depends on
* [`AsmContext_buffer_offset`](#AsmContext_buffer_offset)
#### Estimated stack usage
1 cells



### `AsmGetError`:


#### Syntax


```pawn
AsmGetError(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmContext_error`](#AsmContext_error)
#### Estimated stack usage
1 cells



### `AsmGetErrorHandler`:


#### Syntax


```pawn
AsmGetErrorHandler(ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |

#### Depends on
* [`AsmContext_error_handler`](#AsmContext_error_handler)
#### Estimated stack usage
1 cells



### `AsmGetJumpAddressFromOffset`:


#### Syntax


```pawn
AsmGetJumpAddressFromOffset(ctx[], offset)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`offset`	 | 		 |

#### Depends on
* [`AMX_HDR`](#AMX_HDR)
* [`AMX_HDR_DAT`](#AMX_HDR_DAT)
* [`AsmContext_buffer`](#AsmContext_buffer)
* [`AsmContext_buffer_offset`](#AsmContext_buffer_offset)
* [`GetAmxBaseAddress`](#GetAmxBaseAddress)
* [`GetAmxHeader`](#GetAmxHeader)
* [`cellbytes`](#cellbytes)
#### Estimated stack usage
22 cells



### `AsmGetPreviousWriteOffset`:


#### Syntax


```pawn
AsmGetPreviousWriteOffset()
```

#### Depends on
* [`gPreviousWriteOffset`](#gPreviousWriteOffset)
#### Estimated stack usage
1 cells



### `AsmHashLabel`:


#### Syntax


```pawn
AsmHashLabel(label[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`label`	 | 	` [] `	 |

#### Estimated stack usage
4 cells



### `AsmInit`:


#### Syntax


```pawn
AsmInit(ctx[], buffer[], size)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`buffer`	 | 	` [] `	 |
| 	`size`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`AsmInitPtr`](#AsmInitPtr)
* [`cellbytes`](#cellbytes)
* [`ref`](#ref)
#### Estimated stack usage
6 cells



### `AsmInitPtr`:


#### Syntax


```pawn
AsmInitPtr(ctx[], buffer, size)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`buffer`	 | 		 |
| 	`size`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`ASM_ERROR_NONE`](#ASM_ERROR_NONE)
* [`AsmContext_buffer`](#AsmContext_buffer)
* [`AsmContext_buffer_offset`](#AsmContext_buffer_offset)
* [`AsmContext_buffer_size`](#AsmContext_buffer_size)
* [`AsmContext_error_handler`](#AsmContext_error_handler)
* [`AsmContext_label_names`](#AsmContext_label_names)
* [`AsmContext_labels`](#AsmContext_labels)
#### Estimated stack usage
2 cells



### `AsmRaiseError`:


#### Syntax


```pawn
AsmRaiseError(ctx[], error)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`error`	 | 	`AsmError `	 |

#### Tag
`AsmError:`


#### Depends on
* [`ASM_ERROR_NONE`](#ASM_ERROR_NONE)
* [`AsmContext_error_handler`](#AsmContext_error_handler)
* [`AsmSetError`](#AsmSetError)
* [`CallFunction`](#CallFunction)
* [`ref`](#ref)
#### Estimated stack usage
6 cells



### `AsmSetError`:


#### Syntax


```pawn
AsmSetError(ctx[], error)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`error`	 | 	`AsmError `	 |

#### Depends on
* [`AsmContext_error`](#AsmContext_error)
#### Estimated stack usage
1 cells



### `AsmSetErrorHandler`:


#### Syntax


```pawn
AsmSetErrorHandler(ctx[], error_handler)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`error_handler`	 | 		 |

#### Tag
`AsmError:`


#### Depends on
* [`ASM_ERROR_NONE`](#ASM_ERROR_NONE)
* [`AsmContext_error_handler`](#AsmContext_error_handler)
#### Estimated stack usage
1 cells



### `AsmSetErrorHandlerName`:


#### Syntax


```pawn
AsmSetErrorHandlerName(ctx[], error_handler[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ctx`	 | 	` [21] `	 |
| 	`error_handler`	 | 	` [] `	 |

#### Tag
`AsmError:`


#### Depends on
* [`ASM_ERROR_NONE`](#ASM_ERROR_NONE)
* [`AsmContext_error_handler`](#AsmContext_error_handler)
* [`O@A@`](#O@A@)
#### Estimated stack usage
4 cells

