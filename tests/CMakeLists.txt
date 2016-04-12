cmake_minimum_required (VERSION 2.6) 
set (PROJECT test.exe) 
project (${PROJECT}) 

message(STATUS ${PROJECT_ROOT_DIR})

set (HEADERS 
     ../src/bitBuffer.h
     )
 
set (SOURCES 
     bitBufferTest.cpp
     ../src/bitBuffer.cpp
     ) 

add_executable (${PROJECT} ${HEADERS} ${SOURCES} ${COMMON_HEADERS} ${COMMON_SOURCES})

add_executable (valueVectorTest.exe valueVectorTest.cpp ../src/dbColumn.cpp  ../src/bitBuffer.cpp ../src/bitBuffer.h ../src/dbColumn.h  ${COMMON_HEADERS} ${COMMON_SOURCES})

add_executable (dbColumnTest.exe dbColumnTest.cpp ../src/dbColumn.cpp  ../src/bitBuffer.cpp ../src/bitBuffer.h ../src/dbColumn.h  ${COMMON_HEADERS} ${COMMON_SOURCES})
