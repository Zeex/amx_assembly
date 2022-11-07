amx_assembly frame_info
==========================================
AMX Assembly; Function call frame information.
------------------------------------------



## Functions


### `GetCurrentFrame`:


#### Syntax


```pawn
GetCurrentFrame()
```

#### Estimated stack usage
1 cells



### `GetCurrentFrameFunction`:


#### Syntax


```pawn
GetCurrentFrameFunction()
```

#### Depends on
* [`GetCallerFrame`](#GetCallerFrame)
* [`GetFrameFunction`](#GetFrameFunction)
#### Estimated stack usage
4 cells



### `GetCurrentFrameHeaderCount`:


#### Syntax


```pawn
GetCurrentFrameHeaderCount()
```

#### Depends on
* [`GetCallerFrame`](#GetCallerFrame)
* [`GetFrameHeaderCount`](#GetFrameHeaderCount)
#### Estimated stack usage
4 cells



### `GetCurrentFrameHeaderSize`:


#### Syntax


```pawn
GetCurrentFrameHeaderSize()
```

#### Depends on
* [`GetCallerFrame`](#GetCallerFrame)
* [`GetFrameHeaderSize`](#GetFrameHeaderSize)
#### Estimated stack usage
4 cells



### `GetCurrentFrameLocal`:


#### Syntax


```pawn
GetCurrentFrameLocal(param)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`param`	 | 		 |

#### Depends on
* [`GetCallerFrame`](#GetCallerFrame)
* [`GetFrameLocal`](#GetFrameLocal)
#### Estimated stack usage
5 cells



### `GetCurrentFrameLocalCount`:


#### Syntax


```pawn
GetCurrentFrameLocalCount()
```

#### Depends on
* [`GetCallerFrame`](#GetCallerFrame)
* [`GetFrameLocalCount`](#GetFrameLocalCount)
#### Estimated stack usage
4 cells



### `GetCurrentFrameLocalSize`:


#### Syntax


```pawn
GetCurrentFrameLocalSize()
```

#### Depends on
* [`GetCallerFrame`](#GetCallerFrame)
* [`GetFrameLocalSize`](#GetFrameLocalSize)
#### Estimated stack usage
4 cells



### `GetCurrentFrameParameter`:


#### Syntax


```pawn
GetCurrentFrameParameter(param, idx)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`param`	 | 		 |
| 	`idx`	 | 		 |

#### Depends on
* [`GetCallerFrame`](#GetCallerFrame)
* [`GetFrameParameter`](#GetFrameParameter)
#### Estimated stack usage
6 cells



### `GetCurrentFrameParameterCount`:


#### Syntax


```pawn
GetCurrentFrameParameterCount()
```

#### Depends on
* [`GetCallerFrame`](#GetCallerFrame)
* [`GetFrameParameterCount`](#GetFrameParameterCount)
#### Estimated stack usage
4 cells



### `GetCurrentFrameParameterSize`:


#### Syntax


```pawn
GetCurrentFrameParameterSize()
```

#### Depends on
* [`GetCallerFrame`](#GetCallerFrame)
* [`GetFrameParameterSize`](#GetFrameParameterSize)
#### Estimated stack usage
4 cells



### `GetCurrentFramePreviousFrame`:


#### Syntax


```pawn
GetCurrentFramePreviousFrame()
```

#### Depends on
* [`GetCallerFrame`](#GetCallerFrame)
* [`GetFramePreviousFrame`](#GetFramePreviousFrame)
#### Estimated stack usage
4 cells



### `GetCurrentFrameReturn`:


#### Syntax


```pawn
GetCurrentFrameReturn()
```

#### Depends on
* [`GetCallerFrame`](#GetCallerFrame)
* [`GetFrameReturn`](#GetFrameReturn)
#### Estimated stack usage
4 cells



### `GetCurrentFrameTotalCount`:


#### Syntax


```pawn
GetCurrentFrameTotalCount()
```

#### Depends on
* [`GetCallerFrame`](#GetCallerFrame)
* [`GetFrameTotalCount`](#GetFrameTotalCount)
#### Estimated stack usage
4 cells



### `GetCurrentFrameTotalSize`:


#### Syntax


```pawn
GetCurrentFrameTotalSize()
```

#### Depends on
* [`GetCallerFrame`](#GetCallerFrame)
* [`GetFrameTotalSize`](#GetFrameTotalSize)
#### Estimated stack usage
4 cells



### `GetFrameFunction`:


#### Syntax


```pawn
GetFrameFunction(frm_addr)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`frm_addr`	 | 		 |

#### Depends on
* [`AMX_HDR`](#AMX_HDR)
* [`AMX_HDR_CIP`](#AMX_HDR_CIP)
* [`AMX_HDR_COD`](#AMX_HDR_COD)
* [`AMX_HDR_DAT`](#AMX_HDR_DAT)
* [`AMX_HDR_DEFSIZE`](#AMX_HDR_DEFSIZE)
* [`AMX_HDR_NATIVES`](#AMX_HDR_NATIVES)
* [`AMX_HDR_PUBLICS`](#AMX_HDR_PUBLICS)
* [`GetAmxBaseAddress`](#GetAmxBaseAddress)
* [`GetAmxHeader`](#GetAmxHeader)
* [`GetFrameNextFrame`](#GetFrameNextFrame)
* [`GetFramePreviousFrame`](#GetFramePreviousFrame)
* [`GetFrameReturn`](#GetFrameReturn)
* [`GetFrameVariable`](#GetFrameVariable)
* [`OP_CALL`](#OP_CALL)
* [`OP_CONST_PRI`](#OP_CONST_PRI)
* [`OP_LOAD_PRI`](#OP_LOAD_PRI)
* [`OP_LOAD_S_PRI`](#OP_LOAD_S_PRI)
* [`OP_PROC`](#OP_PROC)
* [`OP_RETN`](#OP_RETN)
* [`OP_SCTRL`](#OP_SCTRL)
* [`RelocateOpcode`](#RelocateOpcode)
* [`UnrelocateOpcode`](#UnrelocateOpcode)
* [`cellbytes`](#cellbytes)
* [`gAmxAssemblyAddress_`](#gAmxAssemblyAddress_)
#### Estimated stack usage
26 cells



### `GetFrameHeaderCount`:


#### Syntax


```pawn
GetFrameHeaderCount(frm_addr)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`frm_addr`	 | 		 |

#### Depends on
* [`GetFrameHeaderSize`](#GetFrameHeaderSize)
* [`cellbytes`](#cellbytes)
#### Estimated stack usage
4 cells



### `GetFrameHeaderSize`:


#### Syntax


```pawn
GetFrameHeaderSize(frm_addr)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`frm_addr`	 | 		 |

#### Depends on
* [`cellbytes`](#cellbytes)
#### Estimated stack usage
1 cells



### `GetFrameLocalCount`:


#### Syntax


```pawn
GetFrameLocalCount(frm_addr)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`frm_addr`	 | 		 |

#### Depends on
* [`GetFrameLocalSize`](#GetFrameLocalSize)
* [`cellbytes`](#cellbytes)
#### Estimated stack usage
4 cells



### `GetFrameLocalSize`:


#### Syntax


```pawn
GetFrameLocalSize(frm_addr)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`frm_addr`	 | 		 |

#### Depends on
* [`GetFrameHeaderSize`](#GetFrameHeaderSize)
* [`GetFrameNextFrame`](#GetFrameNextFrame)
* [`GetFrameParameterSize`](#GetFrameParameterSize)
#### Estimated stack usage
6 cells



### `GetFrameNextFrame`:


#### Syntax


```pawn
GetFrameNextFrame(frm_addr)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`frm_addr`	 | 		 |

#### Depends on
* [`GetCurrentFrame`](#GetCurrentFrame)
* [`GetFramePreviousFrame`](#GetFramePreviousFrame)
#### Estimated stack usage
6 cells



### `GetFrameParameterCount`:


#### Syntax


```pawn
GetFrameParameterCount(frm_addr)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`frm_addr`	 | 		 |

#### Depends on
* [`GetFrameParameterSize`](#GetFrameParameterSize)
* [`cellbytes`](#cellbytes)
#### Estimated stack usage
4 cells



### `GetFramePreviousFrame`:


#### Syntax


```pawn
GetFramePreviousFrame(frm_addr)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`frm_addr`	 | 		 |

#### Estimated stack usage
1 cells



### `GetFrameTotalCount`:


#### Syntax


```pawn
GetFrameTotalCount(frm_addr)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`frm_addr`	 | 		 |

#### Depends on
* [`GetFrameTotalSize`](#GetFrameTotalSize)
* [`cellbytes`](#cellbytes)
#### Estimated stack usage
4 cells



### `GetFrameTotalSize`:


#### Syntax


```pawn
GetFrameTotalSize(frm_addr)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`frm_addr`	 | 		 |

#### Depends on
* [`GetFrameHeaderSize`](#GetFrameHeaderSize)
* [`GetFrameLocalSize`](#GetFrameLocalSize)
* [`GetFrameParameterSize`](#GetFrameParameterSize)
#### Estimated stack usage
4 cells



### `SetCurrentFramePreviousFrame`:


#### Syntax


```pawn
SetCurrentFramePreviousFrame(addr)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`addr`	 | 		 |

#### Depends on
* [`GetCallerFrame`](#GetCallerFrame)
* [`SetFramePreviousFrame`](#SetFramePreviousFrame)
#### Estimated stack usage
5 cells



### `SetCurrentFrameReturn`:


#### Syntax


```pawn
SetCurrentFrameReturn(addr)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`addr`	 | 		 |

#### Depends on
* [`GetCallerFrame`](#GetCallerFrame)
* [`SetFrameReturn`](#SetFrameReturn)
#### Estimated stack usage
5 cells



### `SetCurrentParameterCount`:


#### Syntax


```pawn
SetCurrentParameterCount(count)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`count`	 | 		 |

#### Depends on
* [`GetCallerFrame`](#GetCallerFrame)
* [`SetFrameParameterCount`](#SetFrameParameterCount)
#### Estimated stack usage
5 cells



### `SetCurrentParameterSize`:


#### Syntax


```pawn
SetCurrentParameterSize(size)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`size`	 | 		 |

#### Depends on
* [`GetCallerFrame`](#GetCallerFrame)
* [`SetFrameParameterSize`](#SetFrameParameterSize)
#### Estimated stack usage
5 cells



### `SetFrameParameterCount`:


#### Syntax


```pawn
SetFrameParameterCount(frm_addr, count)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`frm_addr`	 | 		 |
| 	`count`	 | 		 |

#### Depends on
* [`SetFrameParameterSize`](#SetFrameParameterSize)
* [`cellbytes`](#cellbytes)
#### Estimated stack usage
5 cells



### `SetFramePreviousFrame`:


#### Syntax


```pawn
SetFramePreviousFrame(frm_addr, addr)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`frm_addr`	 | 		 |
| 	`addr`	 | 		 |

#### Estimated stack usage
1 cells

