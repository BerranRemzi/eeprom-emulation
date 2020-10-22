#include "test.h"

void Test_PrintBufferAsWord(const uint16_t* _arr, uint8_t _size) {
    for (int i = 0; i < _size; i++) {
        printf("%04X ", _arr[i]);
    }
    printf("\n");
}

void Test_PrintBufferAsByte(const uint8_t* _arr, uint8_t _size) {
    for (int i = 0; i < _size; i++) {
        if (i % 16 == 0) {
            printf("\n");
        }
        printf("%02X ", _arr[i]);
    }
    printf("\n");
}

uint16_t Test_GetErrorCount(const uint8_t _dataA[], const uint8_t _dataB[], uint16_t _size) {
    uint16_t errorCount = 0;

    for (uint16_t i = 0; i < _size; i++) {
        if (_dataA[i] != _dataB[i]) {
            errorCount++;
        }
    }

    return errorCount;
}