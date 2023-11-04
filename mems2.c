#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <math.h>

#define PAGE_SIZE 4096

typedef unsigned long ulong;

// Define the structure for the main chain node
struct mainNode {
    struct subNode* subn;
    struct mainNode* parent;
    struct mainNode* child;
    void* start_virt_add;
    void* end_virt_add;
    void* start_add; // physical address
    int pages;
};

// Define the structure for the sub-chain node
struct subNode {
    struct mainNode* main_chain_node;
    struct subNode* prev;
    struct subNode* next;
    int status; // status-1(for process and 0 for hole)
    void* start_sub;
    void* end_sub;
    void* phy_add;
};

// Global variables
struct mainNode* head = NULL;
struct mainNode* tail = NULL;
void* last_virt_add = NULL;
void* p = NULL;
int count = 0;                      //count no of nodes in the main chain
/*
Initializes all the required parameters for the MeMS system.
*/
void mems_init() {
    head = (struct mainNode*)mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (head == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }
    head->parent = NULL;
    head->child = NULL;
    head->end_virt_add = NULL;
    head->subn = NULL;
    head->pages = 0;
    head->start_add = (void *)head;
    // tail = head;
    printf("Head Physical address is:%d\n", head->start_add);
    printf("size of head:%d\n",sizeof(head));
    p = (void *)((char *)head->start_add + sizeof(head));
    printf("%d\n",p);
}

/*
This function will be called at the end of the MeMS system and its main job is to unmap the 
allocated memory using the munmap system call.
*/
void mems_finish() {
    // Implement the function according to the requirements
}

/*
Allocates memory of the specified size by reusing a segment from the free list if 
a sufficiently large segment is available.
*/
void* mems_malloc(size_t size) {
    // Implement the function according to the requirements
    

    int tot_pages = ceil(size/4096);
    struct mainNode* Node = (struct mainNode*)p;
    if(count == 0){
        Node->parent = head;
        head->child = Node;
        Node->start_virt_add = 0;
        Node->end_virt_add = (char *)Node->start_virt_add + (tot_pages*4096) - 1;
        Node->start_add = p;
        int sizeMain = sizeof(Node);
        p = (void *)((char*)p + sizeMain);
        Node->pages = tot_pages;
        printf("%ld\n",sizeof(Node));
        printf("%d\n",p);
        struct subNode* hole = (struct subNode*)p;
        hole->main_chain_node = Node;
        hole->prev = NULL;
        hole->next = NULL;
        hole->status = 0;
        hole->start_sub = Node->start_virt_add;
        hole->end_sub = Node->end_virt_add;
        hole->phy_add = (void*)mmap(NULL, tot_pages * PAGE_SIZE , PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        if (hole->phy_add == MAP_FAILED) {
            perror("mmap");
            exit(EXIT_FAILURE);
        }
        int sizeSub = sizeof(hole);
        p = (void *)((char*)p + sizeSub);
        count ++;
        return NULL;
    }else{

    }
    return NULL; // Update the return value
}

/*
Prints the stats of the MeMS system.
*/
void mems_print_stats() {
    // Implement the function according to the requirements
}

/*
Returns the MeMS physical address mapped to ptr ( ptr is MeMS virtual address).
*/
void* mems_get(void* v_ptr) {
    // Implement the function according to the requirements



    return NULL; // Update the return value
}

/*
Frees up the memory pointed by our virtual_address and adds it to the free list.
*/
void mems_free(void* v_ptr) {
    // Implement the function according to the requirements
}

int main() {
    mems_init();
    mems_malloc(1000);
    return 0;
}
