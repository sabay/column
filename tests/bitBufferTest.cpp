#include"src/bitBuffer.h"

#include <stdio.h>

int main(){
    BitBuffer bb;
    bb.append(1);
    bb.append(1);
    bb.append(0);
    bb.append(0);
    bb.append(1);
    bb.append(1);
    bb.append(1);
    bb.append(0);
    bb.append(0);
    bb.appendInterval(0b11110101110000011111, 21	);
    bb.append(0);
    bb.debug();
    return 0;
}