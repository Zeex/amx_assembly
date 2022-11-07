amx_assembly dynamic_call
==========================================
AMX Assembly; Call arbitrary functions by name.
------------------------------------------



## Variables


### `g_args`:


### `g_nargs`:


## Functions


### `Pop`:


#### Syntax


```pawn
Pop(&arg)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`arg`	 | 	` & `	 |

#### Tag
`bool:`


#### Depends on
* [`false`](#false)
* [`g_args`](#g_args)
* [`g_nargs`](#g_nargs)
* [`true`](#true)
#### Estimated stack usage
1 cells



### `Push`:


#### Syntax


```pawn
Push(arg)
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`arg`	 | 		 |

#### Tag
`bool:`


#### Depends on
* [`false`](#false)
* [`g_args`](#g_args)
* [`g_nargs`](#g_nargs)
* [`true`](#true)
#### Estimated stack usage
1 cells



### `PushString`:


#### Syntax


```pawn
PushString(string[])
```


#### Parameters


| 	**Name**	 | 	**Info**	 |
|	---	|	---	|
| 	`string`	 | 	` [] `	 |

#### Tag
`bool:`


#### Depends on
* [`Push`](#Push)
#### Estimated stack usage
5 cells

