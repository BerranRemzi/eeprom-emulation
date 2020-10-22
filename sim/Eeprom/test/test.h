#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <stdint.h>

void Test_PrintBufferAsWord(const uint16_t* _arr, uint8_t _size);
void Test_PrintBufferAsByte(const uint8_t* _arr, uint8_t _size);
uint16_t Test_GetErrorCount(const uint8_t _dataA[], const uint8_t _dataB[], uint16_t _size);

#endif /* TEST_H */