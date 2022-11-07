amx_assembly amx
==========================================
AMX Assembly Library: `AMX*` struct pointer determination.
------------------------------------------



## Functions


### `GetAmxAddress`:

Returns the address of the AMX struct instance in memory that corresponds to this script. This function works only on Windows!



#### Syntax


```pawn
GetAmxAddress()
```

#### Depends on
* [`RunShellcode`](#RunShellcode)
* [`cellbits`](#cellbits)
* [`refabs`](#refabs)
#### Estimated stack usage
5 cells



### `ReadAmxCell`:

Reads a cell from the AMX struct.



#### Syntax


```pawn
ReadAmxCell(offset)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`offset`	 | 		 |

#### Depends on
* [`GetAmxAddress`](#GetAmxAddress)
* [`ReadPhysMemoryCell`](#ReadPhysMemoryCell)
#### Estimated stack usage
5 cells



### `WriteAmxCell`:

Writes a cell to the AMX struct.



#### Syntax


```pawn
WriteAmxCell(offset, value)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`offset`	 | 		 |
| 	`value`	 | 		 |

#### Depends on
* [`GetAmxAddress`](#GetAmxAddress)
* [`WritePhysMemoryCell`](#WritePhysMemoryCell)
#### Estimated stack usage
6 cells

