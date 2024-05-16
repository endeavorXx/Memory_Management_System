## Traditionally, malloc() library is used in C for the allocation of the memory.The work is about implemting an efficient Memory Management system in C, Given space input by the user it efficiently allocates memory to the user in the memory. 

Function Definitions - 

## mems_init() initializes the memory management system.
## mems_finish() frees all allocated memory at the end of the program execution.
## mems_malloc(size_t size) allocates memory for a specified size.
## mems_print_stats() prints the statistics of the memory management system.
## mems_get(void* v_ptr) returns the physical address mapped to the virtual address.
## mems_free(void* v_ptr) frees up memory pointed to by the virtual address.
Main Function
The main function demonstrates the usage of the MeMS system by allocating and freeing memory, printing statistics, and finishing the program execution.

### Global Variables used--
In the provided C program, several global variables are used to maintain and manage the MeMS (Memory Management System) and its associated data structures. Here is an explanation of the global variables used in your program:

1. **`head`**:
   - These variables point to the head of the main chain of the MeMS system, respectively.
   - They help in keeping track of the main nodes in the MeMS system.

2. **`last_virt_add`**:
   - This variable is used to store the last virtual address that was allocated in the MeMS system.
   - It helps in tracking the virtual addresses of allocated memory segments.

3. **`p`**:
   - This variable serves as a pointer to manage memory allocation within the MeMS system.
   - It keeps track of the current position in the memory where the next allocation can be made.

4. **`No_of_pages`** and **`count`**:
   - These variables keep track of the total number of pages and the total number of main nodes in the MeMS system, respectively.
   - They aid in managing and monitoring the allocation and deallocation of memory segments.

These global variables play a crucial role in managing the MeMS system and ensuring the efficient allocation, deallocation, and utilization of memory resources within the program. They help in maintaining the state of the data structures and facilitate the tracking of allocated memory segments and available memory segments (holes) within the MeMS system.

The provided C program defines two main structures: `struct mainNode` and `struct subNode`. These structures serve as the backbone for managing memory allocation and deallocation within the custom memory management system.

### `struct mainNode`
- This structure represents the main chain node in the memory management system.
- It contains the following members:
  - `struct subNode* subn`: A pointer to the sub-chain node associated with the main node.
  - `struct mainNode* prev`: A pointer to the previous main chain node.
  - `struct mainNode* next`: A pointer to the next main chain node.
  - `void* start_virt_add`: The starting virtual address of the main chain node.
  - `void* end_virt_add`: The ending virtual address of the main chain node.
  - `void* start_add`: The physical address associated with the main chain node.
  - `int pages`: The number of pages allocated for the main chain node.
  - `int no_of_subnodes`: The count of sub-chain nodes associated with the main chain node.

### `struct subNode`
- This structure represents the sub-chain node in the memory management system.
- It includes the following members:
  - `struct mainNode* main_chain_node`: A pointer to the main chain node associated with the sub-chain node.
  - `struct subNode* prev`: A pointer to the previous sub-chain node.
  - `struct subNode* next`: A pointer to the next sub-chain node.
  - `int status`: An integer indicating the status of the node, where 1 represents a process and 0 represents a hole.
  - `void* start_virt`: The starting virtual address of the sub-chain node.
  - `void* end_virt`: The ending virtual address of the sub-chain node.
  - `void* phy_add`: The physical address associated with the sub-chain node.

The `mems_init()` function initializes the MeMS (Memory Management System) by setting up the necessary data structures and memory regions. Here is a summary of its key actions:

### `mems_init()`
- Allocates memory using the `mmap()` system call to set up the initial main node.
- Initializes the `head` pointer to the allocated memory.
- Sets the various attributes of the `head` node, such as `prev`, `next`, `end_virt_add`, `subn`, `pages`, and `start_add`.
- Sets the global variable `p` to the start address of the allocated memory, which is used to keep track of memory allocation for subsequent nodes.
- Prepares the initial data structures required for memory allocation and deallocation within the MeMS system.

Overall, the `mems_init()` function serves as the starting point for the MeMS system, initializing the primary data structures and memory regions necessary for managing memory allocation and deallocation operations.


The `mems_malloc()` function in the provided C program is responsible for allocating memory of a specified size within the MeMS (Memory Management System). It efficiently manages the allocation of memory by reusing available segments from the free list if a sufficiently large segment is available. Here is a summary of its key actions:

### `mems_malloc(size_t size)`
- Calculates the total number of pages required for the allocation based on the given size.
- Handles the initial allocation when there are no existing main nodes in the system.
- Creates a new main chain node if the existing nodes cannot accommodate the requested memory size.
- Implements logic to create a new sub-chain node for the allocated memory segment within the main chain node.
- Manages the allocation and splitting of memory segments in the system to ensure efficient memory utilization.
- Updates the pointers and attributes of the data structures to reflect the newly allocated memory segments.

Overall, the `mems_malloc()` function efficiently manages memory allocation within the MeMS system, ensuring optimal utilization of available memory segments and facilitating the allocation of memory for various application requirements.


The `mems_malloc()` function in the provided C program is responsible for allocating memory within the MeMS (Memory Management System) based on the specified size. Here is a more detailed explanation of its key actions:

1. **Size Calculation:**
   - Determines the total number of pages required for the memory allocation based on the given size.

2. **Handling Initial Allocation:**
   - Manages the initial allocation when there are no existing main nodes in the system.
   - Creates a new main chain node if the existing nodes cannot accommodate the requested memory size. 
   - This is done by keeping a tracking pointer p which keep tracks of mems physical address which is used by Nodes and subNode(i.e freelist).
   - Initializes the necessary attributes of the new main chain node, including its virtual and physical addresses and the number of pages allocated.
   - virtual address of first node has been intialised to 1000.

3. **Sub-Chain Node Creation:**
   - Implements logic to create a new sub-chain node for the allocated memory segment within the main chain node.
   - First a subNode is created as Hole(using createHole()) and then memory is divided between hole and process.
   Simultaneously,Updates the pointers and attributes of the data structures to reflect the newly allocated memory segments and their corresponding virtual and physical addresses.
   - Handles the splitting of memory segments to facilitate the allocation of the requested memory size.
   

4. **Memory Management:**
   - Tracks the allocation and status of memory segments within the MeMS system, distinguishing between allocated memory segments (processes) and available memory segments (holes).
   - Ensures efficient memory utilization by managing the allocation and splitting of memory segments to meet application requirements.

Overall, the `mems_malloc()` function serves as a crucial component of the MeMS system, facilitating the efficient allocation and management of memory resources based on the specified size and memory requirements of various processes within the system.

Certainly, here is a summary of the `mems_free()` function in the provided C program:

### `mems_free(void* v_ptr)`
1. **Input:**
   - Takes a virtual address `v_ptr` as an input to identify the memory segment to be freed.

2. **Error Handling:**
   - Checks whether the provided virtual address is within the allocated memory space.
   - Generates a "Segmentation Fault" error and exits the program if an invalid memory segment is attempted to be freed.

3. **Memory Deallocation:**
   - Marks the identified memory segment as unallocated or "free" in the MeMS system.
   - Updates the status of the sub-chain node associated with the freed memory segment to indicate that it is available for future allocations.

4. **Memory Consolidation:**
   - Checks for adjacent free memory segments (holes) and merges them to create larger contiguous memory blocks, thus preventing memory fragmentation.

5. **Data Structure Management:**
   - Updates the pointers and attributes of the data structures to reflect the changes in the memory status after the deallocation operation.

The `mems_free()` function plays a crucial role in managing the deallocation of memory segments within the MeMS system, effectively maintaining the balance between allocated and available memory resources and preventing memory fragmentation.


The `mems_get()` function in the provided C program is designed to retrieve the physical memory address associated with a given virtual memory address within the MeMS (Memory Management System). Here is a summary of its key features:
# Assumption - If user wants to access physical address of a process but the user provides the virtual address which is not starting address of the process but is the address which lies in the range of [start_virt,end_virt] then mems_get will return starting physical address. No error will be casted on the screen.

### `mems_get(void* v_ptr)`
1. **Input:**
   - Accepts a virtual memory address `v_ptr` as an input to find its corresponding physical memory address.

2. **Memory Address Verification:**
   - Validates whether the provided virtual address falls within the allocated memory space managed by the MeMS system.
   - Performs boundary checks to ensure that the virtual address is within the range of the allocated memory.

3. **Retrieval of Physical Address:**
   - Calculates the physical memory address associated with the provided virtual address based on the memory mapping maintained within the MeMS system.

4. **Error Handling:**
   - Generates a "Segmentation Fault" error and exits the program if an invalid virtual address is passed to the function.

### `mems_get()` 
function serves as a critical component in the MeMS system, facilitating the mapping between virtual and physical memory addresses and ensuring the efficient retrieval of the physical memory address associated with a given virtual memory address.

The `mems_finish()` function in the provided C program is responsible for clearing all the allocated memory and freeing the resources used by the MeMS (Memory Management System) at the end of the program's execution. Here is a summary of its key actions:

### `mems_finish()`
- Frees all the allocated memory in the MeMS system.
- Uses the `munmap()` system call to release the allocated memory regions and handles error simultaneously.
- Clears the main chain nodes and their associated sub-chain nodes.
- Sets the `head` pointer and other related variables to `NULL` to indicate that the memory has been deallocated.
- Set the `count` variable = 0 The main Node count is the free list.

Overall, the `mems_finish()` function ensures that all the allocated memory within the MeMS system is properly deallocated, preventing memory leaks and freeing up resources for other system operations.
## Edge cases Handled - 
>> Merging of Holes, right holes and left hole both 
>> Customized segmentation faults
>> allocating more pages to store free list if required,by checking conditions on p(what is p? given in definition of global variables).
