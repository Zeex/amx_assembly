amx_assembly amx
==========================================
AMX Assembly Library: `AMX*` struct pointer determination.
------------------------------------------

`struct AMX` is the structure in the server/VM that holds information about a loaded script - next instruction, segment addresses, etc.  This library, through an expoit in certain versions of the VM, allows scripts to access their own server-internal data, to read and write to it.  This makes it very easy to corrupt the currently running script.  The functions provided only give very low-level access to reading and writing offsets.  To find where in the structure you need to read certain data from check *amx.h* in the pawn runtime source.  This include uses both *phys_memory.inc* and *shellcode.inc* to execute arbitrary *x86* machine code, which sounds scary, but that code can only be defined in a script explicitly executed.  Furthermore the exploit in question only works on Windows, and is disabled by any VM without code relocation (notably, *open.mp*).

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

