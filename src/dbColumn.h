#ifndef COMMON_DB_COLUMN_H
#define COMMON_DB_COLUMN_H

#include <stdint.h>
#include <map>
#include "bitBuffer.h"

class ValueVector {
  enum Method { AND, NOT };

public:
  ValueVector();
  void append(uint64_t index);
  uint64_t get(bool &eof);
  void resetIterate();
  void debug();
  uint8_t * serialize(uint64_t &bitCount);
protected:
  uint64_t lastIndex;
  BitBuffer bitBuffer;
};


template <class TYPE>
using Storage = std::map<TYPE , ValueVector>;

template <class TYPE> class dbColumn {
public:
    void add(TYPE value, uint64_t rowNumber){
//        typename std::map<TYPE , ValueVector>::iterator it = storage.find(value);
        auto it = storage.find(value);
        if( it == storage.end()){
//            auto newIt = storage.emplace(std::piecewise_construct, std::forward_as_tuple(value),std::forward_as_tuple(0));
            auto newIt = storage.emplace(std::piecewise_construct, std::forward_as_tuple(value),std::forward_as_tuple());
            newIt.first->second.append(rowNumber);
        } else {
            it->second.append(rowNumber);
        }
    };

    uint64_t calculateSize(){
        uint64_t size=0;
        for(auto it = storage.begin(); it != storage.end(); it++){
//        for(typename std::map<TYPE , ValueVector>::iterator it = storage.begin(); it != storage.end(); it++){
            uint64_t s;
            it->second.serialize(s);
            size+=s/8+3*sizeof(uint64_t);
        }
        return size;
    };

    uint64_t serialize(){
        uint64_t size=0;
        for(auto it = storage.begin(); it != storage.end(); it++){
            uint64_t s;
            it->second.serialize(s);
            size+=s/8+3*sizeof(uint64_t);
        }
        return size;
    };
protected:
//  std::map<TYPE , ValueVector> storage;
  Storage<TYPE> storage;
};




#endif