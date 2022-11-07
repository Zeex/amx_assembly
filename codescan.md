amx_assembly codescan
==========================================
AMX Assembly Library: Compiled code scanning and pattern matching.
------------------------------------------



## Enums


### `CodeScanMatcher`:

#### Members

* `CodeScanMatcher_func = 0`
* `CodeScanMatcher_user_data = 1`
* `CodeScanMatcher_type = 2`
* `CodeScanMatcher_code = 66`
* `CodeScanMatcher_len = 130`
* `CodeScanMatcher_offset = 131`
* `CodeScanMatcher_start = 133`
* `CodeScanMatcher_holeidx = 135`
* `CodeScanMatcher_holes = 137`
* `CodeScanMatcher_next = 169`
* `CodeScanMatcher_flags = 170`

### `CodeScanner`:

#### Members

* `CodeScanMatch_func = 0`
* `CodeScanMatch_size = 1`
* `CodeScanMatch_type = 2`
* `CodeScanMatch_heap = 3`
* `CodeScanMatch_stack = 4`
* `CodeScanMatch_params = 5`
* `CodeScanMatch_cip = 6`
* `CodeScanMatch_holes = 7`
* `CodeScanMatch_hole_count = 23`
* `CodeScanMatch_name = 24`
* `CodeScanner_first = 40`
* `CodeScanner_minn = 41`
* `CodeScanner_jump_switch = 42`
* `CodeScanner_jump_target = 74`
* `CodeScanner_jump_stack = 106`
* `CodeScanner_jump_heap = 138`
* `CodeScanner_state = 170`
* `CodeScanner_param = 171`

## Variables


### `gBase`:


### `gCodBase`:


### `gCodeScanCallback_match`:


### `gDat`:


### `gFakeMatcher`:


### `gHdr`:


### `gOP_CASETBL`:


### `gOP_NOP`:


### `gRelocateRequired`:

#### Tag
`bool:`



## Functions


### `CodeScanAddJumpTarget`:


#### Syntax


```pawn
CodeScanAddJumpTarget(cip, target, stk, hea, jumpTargets[], num)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`cip`	 | 		 |
| 	`target`	 | 		 |
| 	`stk`	 | 		 |
| 	`hea`	 | 		 |
| 	`jumpTargets`	 | 	` [172] `	 |
| 	`num`	 | 		 |

#### Depends on
* [`CodeScanner_jump_heap`](#CodeScanner_jump_heap)
* [`CodeScanner_jump_stack`](#CodeScanner_jump_stack)
* [`CodeScanner_jump_switch`](#CodeScanner_jump_switch)
* [`CodeScanner_jump_target`](#CodeScanner_jump_target)
* [`CodeScanner_minn`](#CodeScanner_minn)
* [`min`](#min)
#### Estimated stack usage
4 cells



### `CodeScanAddMatcher`:


#### Syntax


```pawn
CodeScanAddMatcher(scanner[], searcher[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`scanner`	 | 	` [172] `	 |
| 	`searcher`	 | 	` [171] `	 |

#### Depends on
* [`CodeScanMatcher_next`](#CodeScanMatcher_next)
* [`CodeScanner_first`](#CodeScanner_first)
* [`ref`](#ref)
#### Estimated stack usage
4 cells



### `CodeScanAddSwitchTarget`:


#### Syntax


```pawn
CodeScanAddSwitchTarget(cip, stk, hea, jumpTargets[], num)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`cip`	 | 		 |
| 	`stk`	 | 		 |
| 	`hea`	 | 		 |
| 	`jumpTargets`	 | 	` [172] `	 |
| 	`num`	 | 		 |

#### Depends on
* [`AMX_HDR_COD`](#AMX_HDR_COD)
* [`AMX_HDR_DAT`](#AMX_HDR_DAT)
* [`CodeScanner_jump_heap`](#CodeScanner_jump_heap)
* [`CodeScanner_jump_stack`](#CodeScanner_jump_stack)
* [`CodeScanner_jump_switch`](#CodeScanner_jump_switch)
* [`CodeScanner_jump_target`](#CodeScanner_jump_target)
* [`CodeScanner_minn`](#CodeScanner_minn)
* [`cellbytes`](#cellbytes)
* [`cellmin`](#cellmin)
* [`gAmxAssemblyAddress_`](#gAmxAssemblyAddress_)
* [`gBase`](#gBase)
* [`gHdr`](#gHdr)
* [`gOP_CASETBL`](#gOP_CASETBL)
* [`min`](#min)
#### Estimated stack usage
8 cells



### `CodeScanCheck`:


#### Syntax


```pawn
CodeScanCheck(op, dctx[], cs[], matcher__, fctx[], &next)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`op`	 | 	`Opcode `	 |
| 	`dctx`	 | 	` [5] `	 |
| 	`cs`	 | 	` [171] `	 |
| 	`matcher__`	 | 		 |
| 	`fctx`	 | 	` [172] `	 |
| 	`next`	 | 	` & `	 |

#### Tag
`bool:`


#### Depends on
* [`CodeScanMatch_cip`](#CodeScanMatch_cip)
* [`CodeScanMatch_hole_count`](#CodeScanMatch_hole_count)
* [`CodeScanMatch_holes`](#CodeScanMatch_holes)
* [`CodeScanMatch_size`](#CodeScanMatch_size)
* [`CodeScanMatcher_code`](#CodeScanMatcher_code)
* [`CodeScanMatcher_holeidx`](#CodeScanMatcher_holeidx)
* [`CodeScanMatcher_holes`](#CodeScanMatcher_holes)
* [`CodeScanMatcher_len`](#CodeScanMatcher_len)
* [`CodeScanMatcher_next`](#CodeScanMatcher_next)
* [`CodeScanMatcher_offset`](#CodeScanMatcher_offset)
* [`CodeScanMatcher_start`](#CodeScanMatcher_start)
* [`CodeScanMatcher_type`](#CodeScanMatcher_type)
* [`DisasmContext_cip`](#DisasmContext_cip)
* [`DisasmContext_nip`](#DisasmContext_nip)
* [`DisasmGetOperandReloc`](#DisasmGetOperandReloc)
* [`FIXES_memcpy`](#FIXES_memcpy)
* [`OP_CASETBL`](#OP_CASETBL)
* [`cellbytes`](#cellbytes)
* [`false`](#false)
* [`gAMXOpcodeParameterCounts`](#gAMXOpcodeParameterCounts)
* [`gAmxAssemblyAddress_`](#gAmxAssemblyAddress_)
* [`true`](#true)
#### Estimated stack usage
13 cells



### `CodeScanCheckJumpTarget`:


#### Syntax


```pawn
CodeScanCheckJumpTarget(cip, deloc, &stk, &hea, jumpTargets[], num)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`cip`	 | 		 |
| 	`deloc`	 | 		 |
| 	`stk`	 | 	` & `	 |
| 	`hea`	 | 	` & `	 |
| 	`jumpTargets`	 | 	` [172] `	 |
| 	`num`	 | 		 |

#### Tag
`bool:`


#### Depends on
* [`CodeScanner_jump_heap`](#CodeScanner_jump_heap)
* [`CodeScanner_jump_stack`](#CodeScanner_jump_stack)
* [`CodeScanner_jump_switch`](#CodeScanner_jump_switch)
* [`CodeScanner_jump_target`](#CodeScanner_jump_target)
* [`CodeScanner_minn`](#CodeScanner_minn)
* [`cellbytes`](#cellbytes)
* [`cellmin`](#cellmin)
* [`false`](#false)
* [`gAmxAssemblyAddress_`](#gAmxAssemblyAddress_)
* [`true`](#true)
#### Estimated stack usage
4 cells



### `CodeScanClone`:


#### Syntax


```pawn
CodeScanClone(dest[], src[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`dest`	 | 	` [172] `	 |
| 	`src`	 | 	` [172] `	 |

#### Depends on
* [`CodeScanner_first`](#CodeScanner_first)
#### Estimated stack usage
1 cells



### `CodeScanFindOneFastPattern2`:


#### Syntax


```pawn
CodeScanFindOneFastPattern2(matcher[], matcher__, &addr)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`matcher`	 | 	` [171] `	 |
| 	`matcher__`	 | 		 |
| 	`addr`	 | 	` & `	 |

#### Tag
`bool:`


#### Depends on
* [`CodeScanFindOneFastPattern3`](#CodeScanFindOneFastPattern3)
* [`CodeScanMatcher_code`](#CodeScanMatcher_code)
* [`CodeScanMatcher_len`](#CodeScanMatcher_len)
* [`CodeScanMatcher_next`](#CodeScanMatcher_next)
* [`CodeScanMatcher_type`](#CodeScanMatcher_type)
* [`OP_CALL`](#OP_CALL)
* [`false`](#false)
* [`gFakeMatcher`](#gFakeMatcher)
* [`true`](#true)
#### Estimated stack usage
10 cells



### `CodeScanFindOneFastPattern3`:


#### Syntax


```pawn
CodeScanFindOneFastPattern3(matcher[], matcher__, addr, &cur)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`matcher`	 | 	` [171] `	 |
| 	`matcher__`	 | 		 |
| 	`addr`	 | 		 |
| 	`cur`	 | 	` & `	 |

#### Tag
`bool:`


#### Depends on
* [`CodeScanMatcher_code`](#CodeScanMatcher_code)
* [`CodeScanMatcher_len`](#CodeScanMatcher_len)
* [`CodeScanMatcher_next`](#CodeScanMatcher_next)
* [`CodeScanMatcher_type`](#CodeScanMatcher_type)
* [`OP_CALL`](#OP_CALL)
* [`false`](#false)
* [`true`](#true)
#### Estimated stack usage
3 cells



### `CodeScanGetFuncName`:


#### Syntax


```pawn
CodeScanGetFuncName(addr, name[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`addr`	 | 		 |
| 	`name`	 | 	` [] `	 |

#### Tag
`bool:`


#### Depends on
* [`GetPublicIndexFromAddress`](#GetPublicIndexFromAddress)
* [`GetPublicNameFromIndex`](#GetPublicNameFromIndex)
* [`false`](#false)
* [`true`](#true)
#### Estimated stack usage
7 cells



### `CodeScanGetFunctionAsm`:


#### Syntax


```pawn
CodeScanGetFunctionAsm(csm[], ctx[], offset)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`csm`	 | 	` [172] `	 |
| 	`ctx`	 | 	` [21] `	 |
| 	`offset`	 | 		 |

#### Depends on
* [`AsmInitPtr`](#AsmInitPtr)
* [`CodeScanMatch_func`](#CodeScanMatch_func)
* [`cellmax`](#cellmax)
#### Estimated stack usage
6 cells



### `CodeScanGetFunctionDisasm`:


#### Syntax


```pawn
CodeScanGetFunctionDisasm(csm[], ctx[], offset)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`csm`	 | 	` [172] `	 |
| 	`ctx`	 | 	` [5] `	 |
| 	`offset`	 | 		 |

#### Depends on
* [`CodeScanMatch_func`](#CodeScanMatch_func)
* [`DisasmContext_cip`](#DisasmContext_cip)
* [`DisasmContext_end_ip`](#DisasmContext_end_ip)
* [`DisasmContext_nip`](#DisasmContext_nip)
* [`DisasmContext_start_ip`](#DisasmContext_start_ip)
#### Estimated stack usage
1 cells



### `CodeScanGetFunctionScanner`:


#### Syntax


```pawn
CodeScanGetFunctionScanner(csm[], ret[], ctx[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`csm`	 | 	` [172] `	 |
| 	`ret`	 | 	` [172] `	 |
| 	`ctx`	 | 	` [5] `	 |

#### Depends on
* [`CodeScanInit`](#CodeScanInit)
* [`CodeScanMatch_func`](#CodeScanMatch_func)
* [`CodeScanMatch_type`](#CodeScanMatch_type)
* [`CodeScanner_state`](#CodeScanner_state)
* [`DisasmContext_cip`](#DisasmContext_cip)
* [`DisasmContext_end_ip`](#DisasmContext_end_ip)
* [`DisasmContext_nip`](#DisasmContext_nip)
* [`DisasmContext_start_ip`](#DisasmContext_start_ip)
#### Estimated stack usage
4 cells



### `CodeScanGetHoleCount`:


#### Syntax


```pawn
CodeScanGetHoleCount(csm[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`csm`	 | 	` [172] `	 |

#### Depends on
* [`CodeScanMatch_hole_count`](#CodeScanMatch_hole_count)
#### Estimated stack usage
1 cells



### `CodeScanGetMatchAddress`:


#### Syntax


```pawn
CodeScanGetMatchAddress(csm[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`csm`	 | 	` [172] `	 |

#### Depends on
* [`CodeScanMatch_cip`](#CodeScanMatch_cip)
* [`gDat`](#gDat)
#### Estimated stack usage
1 cells



### `CodeScanGetMatchAddressData`:


#### Syntax


```pawn
CodeScanGetMatchAddressData(csm[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`csm`	 | 	` [172] `	 |

#### Depends on
* [`CodeScanMatch_cip`](#CodeScanMatch_cip)
#### Estimated stack usage
1 cells



### `CodeScanGetMatchAsm`:


#### Syntax


```pawn
CodeScanGetMatchAsm(csm[], ctx[], offset)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`csm`	 | 	` [172] `	 |
| 	`ctx`	 | 	` [21] `	 |
| 	`offset`	 | 		 |

#### Depends on
* [`AsmInitPtr`](#AsmInitPtr)
* [`CodeScanMatch_cip`](#CodeScanMatch_cip)
* [`cellmax`](#cellmax)
#### Estimated stack usage
6 cells



### `CodeScanGetMatchDisasm`:


#### Syntax


```pawn
CodeScanGetMatchDisasm(csm[], ctx[], offset)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`csm`	 | 	` [172] `	 |
| 	`ctx`	 | 	` [5] `	 |
| 	`offset`	 | 		 |

#### Depends on
* [`CodeScanMatch_cip`](#CodeScanMatch_cip)
* [`DisasmContext_cip`](#DisasmContext_cip)
* [`DisasmContext_end_ip`](#DisasmContext_end_ip)
* [`DisasmContext_nip`](#DisasmContext_nip)
* [`DisasmContext_start_ip`](#DisasmContext_start_ip)
#### Estimated stack usage
1 cells



### `CodeScanGetMatchFunc`:


#### Syntax


```pawn
CodeScanGetMatchFunc(csm[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`csm`	 | 	` [172] `	 |

#### Depends on
* [`CodeScanMatch_func`](#CodeScanMatch_func)
* [`gDat`](#gDat)
#### Estimated stack usage
1 cells



### `CodeScanGetMatchFuncData`:


#### Syntax


```pawn
CodeScanGetMatchFuncData(csm[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`csm`	 | 	` [172] `	 |

#### Depends on
* [`CodeScanMatch_func`](#CodeScanMatch_func)
#### Estimated stack usage
1 cells



### `CodeScanGetMatchHeap`:


#### Syntax


```pawn
CodeScanGetMatchHeap(csm[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`csm`	 | 	` [172] `	 |

#### Depends on
* [`CodeScanMatch_heap`](#CodeScanMatch_heap)
#### Estimated stack usage
1 cells



### `CodeScanGetMatchHole`:


#### Syntax


```pawn
CodeScanGetMatchHole(csm[], idx)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`csm`	 | 	` [172] `	 |
| 	`idx`	 | 		 |

#### Depends on
* [`CodeScanMatch_holes`](#CodeScanMatch_holes)
#### Estimated stack usage
1 cells



### `CodeScanGetMatchLength`:


#### Syntax


```pawn
CodeScanGetMatchLength(csm[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`csm`	 | 	` [172] `	 |

#### Depends on
* [`CodeScanMatch_size`](#CodeScanMatch_size)
#### Estimated stack usage
1 cells



### `CodeScanGetMatchName`:


#### Syntax


```pawn
CodeScanGetMatchName(csm[], name[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`csm`	 | 	` [172] `	 |
| 	`name`	 | 	` [] `	 |

#### Depends on
* [`CodeScanGetMatchType`](#CodeScanGetMatchType)
* [`CodeScanMatch_name`](#CodeScanMatch_name)
* [`CodeScanMatch_type`](#CodeScanMatch_type)
* [`strcat`](#strcat)
#### Estimated stack usage
5 cells



### `CodeScanGetMatchScanner`:


#### Syntax


```pawn
CodeScanGetMatchScanner(csm[], ret[], ctx[], accurate)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`csm`	 | 	` [172] `	 |
| 	`ret`	 | 	` [172] `	 |
| 	`ctx`	 | 	` [5] `	 |
| 	`accurate`	 | 	`bool `	 |

#### Depends on
* [`CodeScanGetFunctionScanner`](#CodeScanGetFunctionScanner)
* [`CodeScanMatch_cip`](#CodeScanMatch_cip)
* [`CodeScanStepInternal`](#CodeScanStepInternal)
* [`CodeScanner_param`](#CodeScanner_param)
* [`CodeScanner_state`](#CodeScanner_state)
* [`DisasmContext_cip`](#DisasmContext_cip)
* [`DisasmContext_nip`](#DisasmContext_nip)
* [`DisasmContext_start_ip`](#DisasmContext_start_ip)
* [`cellmin`](#cellmin)
#### Estimated stack usage
8 cells



### `CodeScanGetMatchStack`:


#### Syntax


```pawn
CodeScanGetMatchStack(csm[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`csm`	 | 	` [172] `	 |

#### Depends on
* [`CodeScanMatch_stack`](#CodeScanMatch_stack)
#### Estimated stack usage
1 cells



### `CodeScanGetMatchType`:


#### Syntax


```pawn
CodeScanGetMatchType(csm[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`csm`	 | 	` [172] `	 |

#### Depends on
* [`CodeScanGetFuncName`](#CodeScanGetFuncName)
* [`CodeScanMatch_func`](#CodeScanMatch_func)
* [`CodeScanMatch_name`](#CodeScanMatch_name)
* [`CodeScanMatch_type`](#CodeScanMatch_type)
#### Estimated stack usage
5 cells



### `CodeScanInit`:


#### Syntax


```pawn
CodeScanInit(scanner[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`scanner`	 | 	` [172] `	 |

#### Depends on
* [`AMX_HDR_COD`](#AMX_HDR_COD)
* [`AMX_HDR_DAT`](#AMX_HDR_DAT)
* [`CodeScanMatch_cip`](#CodeScanMatch_cip)
* [`CodeScanMatch_heap`](#CodeScanMatch_heap)
* [`CodeScanMatch_name`](#CodeScanMatch_name)
* [`CodeScanMatch_params`](#CodeScanMatch_params)
* [`CodeScanMatch_stack`](#CodeScanMatch_stack)
* [`CodeScanMatch_type`](#CodeScanMatch_type)
* [`CodeScanResetJumpTargets`](#CodeScanResetJumpTargets)
* [`CodeScanner_first`](#CodeScanner_first)
* [`CodeScanner_param`](#CodeScanner_param)
* [`CodeScanner_state`](#CodeScanner_state)
* [`GetAmxBaseAddress`](#GetAmxBaseAddress)
* [`GetAmxHeader`](#GetAmxHeader)
* [`OP_CASETBL`](#OP_CASETBL)
* [`OP_NOP`](#OP_NOP)
* [`RelocateOpcode`](#RelocateOpcode)
* [`cellmin`](#cellmin)
* [`gBase`](#gBase)
* [`gCodBase`](#gCodBase)
* [`gDat`](#gDat)
* [`gHdr`](#gHdr)
* [`gOP_CASETBL`](#gOP_CASETBL)
* [`gOP_NOP`](#gOP_NOP)
#### Estimated stack usage
5 cells



### `CodeScanMatcherData`:


#### Syntax


```pawn
CodeScanMatcherData(searcher[], val)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`searcher`	 | 	` [171] `	 |
| 	`val`	 | 		 |

#### Depends on
* [`CodeScanMatcher_flags`](#CodeScanMatcher_flags)
* [`CodeScanMatcher_user_data`](#CodeScanMatcher_user_data)
#### Estimated stack usage
1 cells



### `CodeScanMatcherInit_`:


#### Syntax


```pawn
CodeScanMatcherInit_(searcher[], address, flags)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`searcher`	 | 	` [171] `	 |
| 	`address`	 | 		 |
| 	`flags`	 | 		 |

#### Depends on
* [`CodeScanMatcher_flags`](#CodeScanMatcher_flags)
* [`CodeScanMatcher_func`](#CodeScanMatcher_func)
* [`CodeScanMatcher_holeidx`](#CodeScanMatcher_holeidx)
* [`CodeScanMatcher_len`](#CodeScanMatcher_len)
* [`CodeScanMatcher_next`](#CodeScanMatcher_next)
* [`CodeScanMatcher_offset`](#CodeScanMatcher_offset)
* [`CodeScanMatcher_user_data`](#CodeScanMatcher_user_data)
* [`IsOpcodeRelocationRequired`](#IsOpcodeRelocationRequired)
* [`OP_NOP`](#OP_NOP)
* [`RelocateOpcode`](#RelocateOpcode)
* [`gRelocateRequired`](#gRelocateRequired)
* [`printf`](#printf)
#### Estimated stack usage
4 cells



### `CodeScanMatcherPattern_`:


#### Syntax


```pawn
CodeScanMatcherPattern_(searcher[], ...)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`searcher`	 | 	` [171] `	 |
| 	`...`	 | 	` {Opcode,Float,_} `	 |

#### Depends on
* [`CodeScanMatcher_code`](#CodeScanMatcher_code)
* [`CodeScanMatcher_len`](#CodeScanMatcher_len)
* [`CodeScanMatcher_type`](#CodeScanMatcher_type)
* [`__COMPILER_CELL_SHIFT`](#__COMPILER_CELL_SHIFT)
* [`__args_offset`](#__args_offset)
* [`gAMXOpcodeParameterCounts`](#gAMXOpcodeParameterCounts)
* [`getarg`](#getarg)
#### Estimated stack usage
11 cells



### `CodeScanNOPMatch`:


#### Syntax


```pawn
CodeScanNOPMatch(csm[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`csm`	 | 	` [172] `	 |

#### Depends on
* [`CodeScanMatch_cip`](#CodeScanMatch_cip)
* [`CodeScanMatch_size`](#CodeScanMatch_size)
* [`cellbytes`](#cellbytes)
* [`gOP_NOP`](#gOP_NOP)
#### Estimated stack usage
3 cells



### `CodeScanReset`:


#### Syntax


```pawn
CodeScanReset(cs[], matcher__, &next)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`cs`	 | 	` [171] `	 |
| 	`matcher__`	 | 		 |
| 	`next`	 | 	` & `	 |

#### Depends on
* [`CodeScanMatcher_func`](#CodeScanMatcher_func)
* [`CodeScanMatcher_holeidx`](#CodeScanMatcher_holeidx)
* [`CodeScanMatcher_len`](#CodeScanMatcher_len)
* [`CodeScanMatcher_next`](#CodeScanMatcher_next)
* [`CodeScanMatcher_offset`](#CodeScanMatcher_offset)
#### Estimated stack usage
1 cells



### `CodeScanResetJumpTargets`:


#### Syntax


```pawn
CodeScanResetJumpTargets(jumpTargets[], num)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`jumpTargets`	 | 	` [172] `	 |
| 	`num`	 | 		 |

#### Depends on
* [`CodeScanner_jump_target`](#CodeScanner_jump_target)
* [`CodeScanner_minn`](#CodeScanner_minn)
* [`cellmin`](#cellmin)
#### Estimated stack usage
1 cells



### `CodeScanRun`:


#### Syntax


```pawn
CodeScanRun(csState[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`csState`	 | 	` [172] `	 |

#### Tag
`bool:`


#### Depends on
* [`CodeScanCall`](#CodeScanCall)
* [`CodeScanCheck`](#CodeScanCheck)
* [`CodeScanMatch_cip`](#CodeScanMatch_cip)
* [`CodeScanMatch_func`](#CodeScanMatch_func)
* [`CodeScanReset`](#CodeScanReset)
* [`CodeScanStepInternal`](#CodeScanStepInternal)
* [`CodeScanner_first`](#CodeScanner_first)
* [`DisasmContext`](#DisasmContext)
* [`DisasmContext_cip`](#DisasmContext_cip)
* [`DisasmContext_end_ip`](#DisasmContext_end_ip)
* [`DisasmContext_nip`](#DisasmContext_nip)
* [`DisasmContext_opcode`](#DisasmContext_opcode)
* [`DisasmContext_start_ip`](#DisasmContext_start_ip)
* [`OP_NONE`](#OP_NONE)
* [`cellmin`](#cellmin)
* [`gFakeMatcher`](#gFakeMatcher)
* [`true`](#true)
#### Estimated stack usage
18 cells



### `CodeScanRunFast`:


#### Syntax


```pawn
CodeScanRunFast(csState[], searchFuncAddr)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`csState`	 | 	` [172] `	 |
| 	`searchFuncAddr`	 | 		 |

#### Tag
`bool:`


#### Depends on
* [`CodeScanCall`](#CodeScanCall)
* [`CodeScanCheck`](#CodeScanCheck)
* [`CodeScanFindOneFastPattern2`](#CodeScanFindOneFastPattern2)
* [`CodeScanMatch_cip`](#CodeScanMatch_cip)
* [`CodeScanReset`](#CodeScanReset)
* [`CodeScanRun`](#CodeScanRun)
* [`CodeScanRunFastPrescanLocated`](#CodeScanRunFastPrescanLocated)
* [`CodeScanRunFastPrescanRelocate`](#CodeScanRunFastPrescanRelocate)
* [`CodeScanStepInternal`](#CodeScanStepInternal)
* [`CodeScanner_first`](#CodeScanner_first)
* [`DisasmContext`](#DisasmContext)
* [`DisasmContext_cip`](#DisasmContext_cip)
* [`DisasmContext_end_ip`](#DisasmContext_end_ip)
* [`DisasmContext_nip`](#DisasmContext_nip)
* [`DisasmContext_opcode`](#DisasmContext_opcode)
* [`DisasmContext_start_ip`](#DisasmContext_start_ip)
* [`DisasmGetOpcode`](#DisasmGetOpcode)
* [`OP_NONE`](#OP_NONE)
* [`OP_PROC`](#OP_PROC)
* [`cellbytes`](#cellbytes)
* [`cellmin`](#cellmin)
* [`false`](#false)
* [`gDat`](#gDat)
* [`gFakeMatcher`](#gFakeMatcher)
* [`gRelocateRequired`](#gRelocateRequired)
* [`print`](#print)
* [`true`](#true)
#### Estimated stack usage
21 cells



### `CodeScanRunFastPrescanLocated`:


#### Syntax


```pawn
CodeScanRunFastPrescanLocated(&proc, &nextaddr, searchFuncAddr)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`proc`	 | 	` & `	 |
| 	`nextaddr`	 | 	` & `	 |
| 	`searchFuncAddr`	 | 		 |

#### Depends on
* [`OP_CALL`](#OP_CALL)
* [`OP_CASETBL`](#OP_CASETBL)
* [`OP_NONE`](#OP_NONE)
* [`OP_PROC`](#OP_PROC)
* [`cellbytes`](#cellbytes)
* [`cellmin`](#cellmin)
* [`false`](#false)
* [`gAMXOpcodeBaseSizes`](#gAMXOpcodeBaseSizes)
* [`gAmxAssemblyAddress_`](#gAmxAssemblyAddress_)
* [`gCodBase`](#gCodBase)
* [`true`](#true)
#### Estimated stack usage
3 cells



### `CodeScanRunFastPrescanRelocate`:


#### Syntax


```pawn
CodeScanRunFastPrescanRelocate(&proc, &nextaddr, searchFuncAddr)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`proc`	 | 	` & `	 |
| 	`nextaddr`	 | 	` & `	 |
| 	`searchFuncAddr`	 | 		 |

#### Depends on
* [`OP_CALL`](#OP_CALL)
* [`OP_CASETBL`](#OP_CASETBL)
* [`OP_NONE`](#OP_NONE)
* [`OP_PROC`](#OP_PROC)
* [`UnrelocateOpcode`](#UnrelocateOpcode)
* [`cellbytes`](#cellbytes)
* [`cellmin`](#cellmin)
* [`false`](#false)
* [`gAMXOpcodeBaseSizes`](#gAMXOpcodeBaseSizes)
* [`gAmxAssemblyAddress_`](#gAmxAssemblyAddress_)
* [`gCodBase`](#gCodBase)
* [`true`](#true)
#### Estimated stack usage
6 cells



### `CodeScanStep`:


#### Syntax


```pawn
CodeScanStep(dctx[], csState[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`dctx`	 | 	` [5] `	 |
| 	`csState`	 | 	` [172] `	 |

#### Tag
`bool:`


#### Depends on
* [`CodeScanStepInternal`](#CodeScanStepInternal)
* [`CodeScanner_param`](#CodeScanner_param)
* [`CodeScanner_state`](#CodeScanner_state)
* [`cellmin`](#cellmin)
#### Estimated stack usage
8 cells



### `CodeScanStepInternal`:


#### Syntax


```pawn
CodeScanStepInternal(dctx[], csState[], &parseState, &parseParam)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`dctx`	 | 	` [5] `	 |
| 	`csState`	 | 	` [172] `	 |
| 	`parseState`	 | 	` & `	 |
| 	`parseParam`	 | 	` & `	 |

#### Tag
`bool:`


#### Depends on
* [`CodeScanAddJumpTarget`](#CodeScanAddJumpTarget)
* [`CodeScanAddSwitchTarget`](#CodeScanAddSwitchTarget)
* [`CodeScanCheckJumpTarget`](#CodeScanCheckJumpTarget)
* [`CodeScanMatch_func`](#CodeScanMatch_func)
* [`CodeScanMatch_heap`](#CodeScanMatch_heap)
* [`CodeScanMatch_stack`](#CodeScanMatch_stack)
* [`CodeScanMatch_type`](#CodeScanMatch_type)
* [`CodeScanResetJumpTargets`](#CodeScanResetJumpTargets)
* [`DisasmContext_cip`](#DisasmContext_cip)
* [`DisasmContext_end_ip`](#DisasmContext_end_ip)
* [`DisasmContext_nip`](#DisasmContext_nip)
* [`DisasmContext_opcode`](#DisasmContext_opcode)
* [`NUM_OPCODES`](#NUM_OPCODES)
* [`OP_ADD_C`](#OP_ADD_C)
* [`OP_BOUNDS`](#OP_BOUNDS)
* [`OP_BREAK`](#OP_BREAK)
* [`OP_CALL`](#OP_CALL)
* [`OP_CALL_PRI`](#OP_CALL_PRI)
* [`OP_CASETBL`](#OP_CASETBL)
* [`OP_HALT`](#OP_HALT)
* [`OP_HEAP`](#OP_HEAP)
* [`OP_JEQ`](#OP_JEQ)
* [`OP_JGEQ`](#OP_JGEQ)
* [`OP_JGRTR`](#OP_JGRTR)
* [`OP_JLEQ`](#OP_JLEQ)
* [`OP_JLESS`](#OP_JLESS)
* [`OP_JNEQ`](#OP_JNEQ)
* [`OP_JNZ`](#OP_JNZ)
* [`OP_JREL`](#OP_JREL)
* [`OP_JSGEQ`](#OP_JSGEQ)
* [`OP_JSGRTR`](#OP_JSGRTR)
* [`OP_JSLEQ`](#OP_JSLEQ)
* [`OP_JSLESS`](#OP_JSLESS)
* [`OP_JUMP`](#OP_JUMP)
* [`OP_JZER`](#OP_JZER)
* [`OP_LCTRL`](#OP_LCTRL)
* [`OP_LOAD_PRI`](#OP_LOAD_PRI)
* [`OP_NONE`](#OP_NONE)
* [`OP_NOP`](#OP_NOP)
* [`OP_POP_ALT`](#OP_POP_ALT)
* [`OP_POP_PRI`](#OP_POP_PRI)
* [`OP_PROC`](#OP_PROC)
* [`OP_PUSH`](#OP_PUSH)
* [`OP_PUSH_ADR`](#OP_PUSH_ADR)
* [`OP_PUSH_ALT`](#OP_PUSH_ALT)
* [`OP_PUSH_C`](#OP_PUSH_C)
* [`OP_PUSH_PRI`](#OP_PUSH_PRI)
* [`OP_PUSH_R`](#OP_PUSH_R)
* [`OP_PUSH_S`](#OP_PUSH_S)
* [`OP_RETN`](#OP_RETN)
* [`OP_SCTRL`](#OP_SCTRL)
* [`OP_STACK`](#OP_STACK)
* [`OP_SWITCH`](#OP_SWITCH)
* [`UnsafeUnrelocateOpcode`](#UnsafeUnrelocateOpcode)
* [`cellbytes`](#cellbytes)
* [`cellmin`](#cellmin)
* [`false`](#false)
* [`gAMXOpcodeBaseSizes`](#gAMXOpcodeBaseSizes)
* [`gAmxAssemblyAddress_`](#gAmxAssemblyAddress_)
* [`gBase`](#gBase)
* [`true`](#true)
#### Estimated stack usage
13 cells

