#ifndef COMMON_BITBUFFER_H
#define COMMON_BITBUFFER_H

#include<stdint.h>
class BitBuffer{
    public:
        BitBuffer();
        ~BitBuffer();
        void append(bool bit);
        void appendInterval(uint64_t data, int count);
        void setIndex(uint64_t idx){ index=idx; };
        uint8_t get(bool &eof);
        uint64_t getInterval(bool &eof, int count);
        uint8_t *serialize( uint64_t &bitCount );
        uint64_t size(){ return bufferSize; }
        void debug();
    protected:
        uint8_t *buffer;
        uint64_t bufferSize;
        uint64_t bitCount;
        uint64_t index;
};
#endif
