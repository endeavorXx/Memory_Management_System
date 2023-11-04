#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <math.h>
typedef unsigned long ulong;
#define PAGE_SIZE 4096

/*
Initializes all the required parameters for the MeMS system. The main parameters to be initialized are:
1. the head of the free list i.e. the pointer that points to the head of the free list
2. the starting MeMS virtual address from which the heap in our MeMS virtual address space will start.
3. any other global variable that you want for the MeMS implementation can be initialized here.
Input Parameter: Nothing
Returns: Nothing
*/

struct mainNode{
    struct subNode* subn;
    struct mainNode* parent;
    struct mainNode* child;
    void* start_virt_add;
    void* end_virt_add;
    void* start_add;        // physical address
    int pages;
};

struct subNode{
    struct mainNode* mainnode;
    struct subNode* prev;
    struct subNode* next;
    int status;                 // status-1(for process and 0 for hole)
    void* start_sub;
    void* end_sub;
};

struct mainNode* head=NULL;
struct mainNode* tail=NULL;
void* p = NULL;
void* last_virt_add = NULL;

void mems_init(){
    //Initialize main chain node
    head = (struct mainNode*)mmap(NULL, PAGE_SIZE, PROT_READ, MAP_PRIVATE, -1, 0);
    // p = p + (int*)sizeof(head);
    head->parent=NULL;
    head->child=NULL;
    head->end_virt_add = NULL;
    head->subn=NULL;
    head->pages = 0;
    head->start_add = head;
    tail = head;
    printf("%p",head);

}

// function for creating a new Node in Main chain
struct mainNode* getNewNode(size_t size){
    int No_of_pages =  ceil(size/PAGE_SIZE);
    struct mainNode* newNode = (struct mainNode*)mmap(NULL, No_of_pages*PAGE_SIZE, PROT_READ, MAP_PRIVATE, -1, 0);
    if (newNode == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }
    newNode->pages = No_of_pages;
    newNode->parent = NULL;
    newNode->child = NULL;
    newNode->subn = NULL;
    newNode->start_virt_add = NULL;
    newNode->end_virt_add = NULL;
    newNode->start_add = newNode;
    return newNode;
}

/*
This function will be called at the end of the MeMS system and its main job is to unmap the 
allocated memory using the munmap system call.
Input Parameter: Nothing
Returns: Nothing
*/
void mems_finish(){
}


/*
Allocates memory of the specified size by reusing a segment from the free list if 
a sufficiently large segment is available. 

Else, uses the mmap system call to allocate more memory on the heap and updates 
the free list accordingly.

Note that while mapping using mmap do not forget to reuse the unused space from mapping
by adding it to the free list.
Parameter: The size of the memory the user program wants
Returns: MeMS Virtual address (that is created by MeMS)
*/ 


void* mems_malloc(size_t size){

}
    



/*
this function print the stats of the MeMS system like
1. How many pages are utilised by using the mems_malloc
2. how much memory is unused i.e. the memory that is in freelist and is not used.
3. It also prints details about each node in the main chain and each segment (PROCESS or HOLE) in the subn-chain.
Parameter: Nothing
Returns: Nothing but should print the necessary information on STDOUT
*/
void mems_print_stats(){

}


/*
Returns the MeMS physical address mapped to ptr ( ptr is MeMS virtual address).
Parameter: MeMS Virtual address (that is created by MeMS)
Returns: MeMS physical address mapped to the passed ptr (MeMS virtual address).
*/
void *mems_get(void*v_ptr){
    
}


/*
this function free up the memory pointed by our virtual_address and add it to the free list
Parameter: MeMS Virtual address (that is created by MeMS) 
Returns: nothing
*/
void mems_free(void *v_ptr){
    
}


int main(){

    
    mems_init();
    
    return 0;
}