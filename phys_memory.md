amx_assembly phys_memory
==========================================
AMX Assembly Library: Read and write real server addresses.
------------------------------------------



## Functions


### `AbsToRel`:


#### Syntax


```pawn
AbsToRel(address)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`address`	 | 		 |

#### Depends on
* [`GetAmxBaseAddress`](#GetAmxBaseAddress)
* [`GetDat`](#GetDat)
#### Estimated stack usage
3 cells



### `GetDat`:


#### Syntax


```pawn
GetDat()
```

#### Estimated stack usage
1 cells



### `RelToAbs`:


#### Syntax


```pawn
RelToAbs(address)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`address`	 | 		 |

#### Depends on
* [`GetAmxBaseAddress`](#GetAmxBaseAddress)
* [`GetDat`](#GetDat)
#### Estimated stack usage
3 cells

