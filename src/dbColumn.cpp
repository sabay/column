#include"dbColumn.h"
#include <stdio.h>

ValueVector::ValueVector():lastIndex(0){
}

void ValueVector::resetIterate(){
    bitBuffer.setIndex(0);
    lastIndex=0;
}

void ValueVector::debug(){ printf("size()=%lu\n", bitBuffer.size());/* bitBuffer.debug();*/ };

void ValueVector::append(uint64_t index){
    ++index;
    uint64_t diff = index - lastIndex;
    lastIndex = index;
    if( diff == 1 ){         // 0b00
        bitBuffer.appendInterval(0b00, 2);
    } else if( diff < 64 ){ //0b01    6-bit | 1 -byte
        bitBuffer.appendInterval(0b01, 2);
        bitBuffer.appendInterval(diff, 6);
    } else if( diff < 16384 ){    //0b10   14-bit | 2 -byte
        bitBuffer.appendInterval(0b10, 2);
        bitBuffer.appendInterval(diff, 14);
    } else if( diff < 2097152){    //0b110  21-bit | 3 -byte
        bitBuffer.appendInterval(0b110, 3);
        bitBuffer.appendInterval(diff, 21);
    } else if( diff < 268435456){    //0b1110 28-bit | 4 -byte
        bitBuffer.appendInterval(0b1110, 4);
        bitBuffer.appendInterval(diff, 28);
    } else {                //0b1111 60-bit | 8 -byte
        bitBuffer.appendInterval(0b1111, 4);
        bitBuffer.appendInterval(diff, 60);
    }
}

uint64_t ValueVector::get( bool &eof ){
    uint64_t diff=0, flag=0;
    flag = bitBuffer.getInterval(eof, 2);
    if(eof) return 0;
    switch(flag){
        case 0b00:
            diff = 1;
            break;
        case 0b01:
            diff = bitBuffer.getInterval(eof, 6);
            if(eof) return 0;
            break;
        case 0b10:
            diff = bitBuffer.getInterval(eof, 14);
            if(eof) return 0;
            break;
        case 0b11:
            uint8_t subflag = bitBuffer.get(eof);
            switch( subflag ){
                case 0:
                    diff = bitBuffer.getInterval(eof, 21);
                    if(eof) return 0;
                    break;
                case 1:
                    subflag = bitBuffer.get(eof);
                    switch( subflag ){
                        case 0:
                            diff = bitBuffer.getInterval(eof, 28);
                            if(eof) return 0;
                            break;
                        case 1:
                            diff = bitBuffer.getInterval(eof, 60);
                            if(eof) return 0;
                            break;
                    }
                    break;
            }
    }
    lastIndex+=diff;
    return (lastIndex - 1) ;
}



uint8_t * ValueVector::serialize(uint64_t &bitCount){
    return bitBuffer.serialize( bitCount );
};