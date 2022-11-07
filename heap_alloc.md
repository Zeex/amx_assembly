amx_assembly heap_alloc
==========================================
AMX Assembly Library: Allocate space in the heap.
------------------------------------------



## Functions


### `HeapAllocBytes`:

Allocates a block of (uninitialized) memory on the heap.



#### Syntax


```pawn
HeapAllocBytes(nbytes)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`nbytes`	 | 		 |

#### Estimated stack usage
2 cells



### `HeapAllocCells`:

Same as HeapAllocBytes() but operates on cells.



#### Syntax


```pawn
HeapAllocCells(ncells)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`ncells`	 | 		 |

#### Depends on
* [`HeapAllocBytes`](#HeapAllocBytes)
* [`cellbytes`](#cellbytes)
#### Estimated stack usage
4 cells



### `HeapRelease`:

Releases memory allocated with HeapAlloc().



#### Syntax


```pawn
HeapRelease(address)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`address`	 | 		 |

#### Estimated stack usage
1 cells

