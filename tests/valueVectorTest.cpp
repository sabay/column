#include "../src/dbColumn.h"

#include <stdio.h>
#include <stdlib.h> 

int main(){

    ValueVector vv;
    uint64_t size=0;
    for(uint64_t i=0;i<1000000000;i+=rand() % 1000){
        vv.append(i);
        size+=sizeof(uint64_t);
//        printf("%lu\n", i);
       
    }
    printf("original size = %lu\n", size);
    vv.debug();
    uint64_t current;
    bool eof;
    vv.resetIterate();
    do{
         current = vv.get( eof );
//         if(!eof) fprintf(stderr,"%lu\n", current);
    } while(!eof);

    return 0;
}