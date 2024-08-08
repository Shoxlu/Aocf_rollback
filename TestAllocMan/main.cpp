#include "AllocMan.h"
#include <iostream>
#include <synchapi.h>
#include <windows.h>
#include <vector>

size_t true_numberAllocs = 0;

struct MyList{
    std::vector<void*> vec;
    size_t total_size;
    void emplace_back(void* elm, size_t size){
        total_size += size;
        vec.emplace_back(elm);
    }
    void clear(){
        vec.clear();
        total_size = 0;
    }
};
MyList list;

void AllocSomething(){
    size_t size = 2000;
    void *alloc = my_malloc(size);
    printf("Alloc: %x \n", alloc);
    list.emplace_back(alloc, size);
    true_numberAllocs++;
}



int main(int argc, char* argv[])
{
    printf("Hi from testing\n");
    while (!(GetKeyState(VK_F9) & 0x8000))
    {
        Sleep(1);
    }

    srand(time(0));

    while (!(GetKeyState(VK_SHIFT) & 0x8000))
    {
        AllocSomething();
        if (GetKeyState(VK_ESCAPE) & 0x8000)
        {
            printf("Command  disabled \n");
            // rollback_allocs(1);
        }
        if (GetKeyState(VK_F1) & 0x8000)
        {
            printf("Free \n");
            size_t n = 0;
            for (void *elm : list.vec)
            {
                n++;
                printf("%x, %d\n", elm, n);
                my_free(elm);
            }
            printf("Freed %d bytes.\n", list.total_size);
            true_numberAllocs = 0;
            list.clear();
            reset_rollback_buffers();
            printf("Free end\n");
        }
        tick_allocs();
        // printAllocs();

        Sleep(1);
    }
    printf("Bye bye \n");
    Sleep(1000);
    return 0;
}


