#include"bitBuffer.h"
#include <stdio.h>
#include <cstdlib>

BitBuffer::BitBuffer(){
    bufferSize = 8;
    buffer = (uint8_t *) malloc(bufferSize);
    bitCount = 0;
};

BitBuffer::~BitBuffer(){
    free(buffer);
}

void BitBuffer::append(bool bit){
    uint64_t byteNumber = bitCount >> 3;
    if(bufferSize <= byteNumber ){
        bufferSize = byteNumber*2;
    buffer = (uint8_t *) realloc(buffer, bufferSize);
    }
    uint8_t bitNumber = bitCount & 0x7;
    if(bit){
        *(buffer + byteNumber) |= (1 << bitNumber);
    } else {
        *(buffer + byteNumber) &= 0xff ^ (1 << bitNumber);
    }
    ++bitCount;
};

void BitBuffer::appendInterval(uint64_t index, int count){
    uint64_t mask = 1 << (count-1);
    for(;count>0; --count){
        append(index & mask); index <<= 1;
    }
}

uint8_t BitBuffer::get( bool &eof ){
   if( index < bitCount) {
       uint64_t byteNumber = index >> 3;
       uint8_t bitNumber = index & 0x7;
       eof = false;
       ++index;
       return (*(buffer + byteNumber) >>bitNumber) & 1;
   } else {
       eof = true;
   }
   return 0;
}

uint64_t BitBuffer::getInterval(bool &eof, int count){
    uint64_t ret=0;
    for(int i=0; i<count; i++){
        ret <<= 1;
        ret |= this->get( eof );
        if(eof) break;
    }
    return ret;
}

uint8_t *BitBuffer::serialize( uint64_t &bitCnt){
    bitCnt=bitCount;
    return buffer;
}

void BitBuffer::debug(){
    bool eof;
    index =0;
    printf("\n|");
    for(uint64_t i=0; i<bitCount; i++){
        printf("%u", this->get(eof));
    }
    printf("|\n");
}
