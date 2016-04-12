#include "../src/dbColumn.h"

#include <stdio.h>
#include <stdlib.h> 

int main(){
    dbColumn<uint64_t> c;
    uint64_t size=0;
    for(uint64_t i=0;i<10000000;i++){
        c.add(rand() % 10000, i);
        size+=sizeof(uint64_t);
    }
    printf("original size = %lu count %lu\n", size, c.serialize());
    c.calculateSize();
    return 0;
}