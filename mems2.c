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
    void* start_virt;
    void* end_virt;
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
    // printf("size of head:%d\n",sizeof(head));
    // printf("size of structure is :%d\n",sizeof(struct mainNode));
    p = (void *)((char *)head->start_add + sizeof(struct mainNode));
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

struct subNode* createHole(struct mainNode* Node,void* p){
    struct subNode* hole = (struct subNode*)p;
        hole->main_chain_node = Node;
        hole->prev = NULL;
        hole->next = NULL;
        hole->status = 0;
        hole->start_virt = Node->start_virt_add;
        hole->end_virt = Node->end_virt_add;
}

void* mems_malloc(size_t size) {
    // Implement the function according to the requirements
    int tot_pages = 0;
    if (size%4096 == 0){
        tot_pages = (size/4096);
    }else{
        tot_pages = (size/4096) + 1;
    }
    // printf("%d\n",tot_pages);
    struct mainNode* Node = (struct mainNode*)p;
    if(count == 0){
        Node->parent = head;
        head->child = Node;
        Node->start_virt_add = 0;
        Node->end_virt_add = (char *)Node->start_virt_add + (tot_pages*4096) - 1;
        int sizeMain = sizeof(struct mainNode);
        p = (void *)((char*)p + sizeMain);
        Node->pages = tot_pages;
        printf("%ld\n",sizeof(Node));
        printf("%d\n",p);

        Node->start_add = mmap(NULL, (int)tot_pages * PAGE_SIZE , PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        if (Node->start_add == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
        }

        struct subNode* hole = createHole(&Node,&p);
        Node->subn = hole;
        int sizeSub = sizeof(struct subNode);
        printf("size of subNodes are:%d\n",sizeSub);
        p = (void *)((char*)p + sizeSub);
        printf("%d\n",p);
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
