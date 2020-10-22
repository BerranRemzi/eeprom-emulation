#ifndef EEPROM_H
#define EEPROM_H

#include <stdint.h>
#include <stdbool.h>

#include "memory.h"

#ifdef __cplusplus
extern "C" {
#endif

    void Eeprom_Init(uint16_t _flashStart, uint16_t _flashEnd);
    void Eeprom_Read(uint8_t* _dest, uint16_t _address, uint16_t _size);
    void Eeprom_Write(const uint8_t* _src, uint16_t _address, uint16_t _size);

    uint16_t Eeprom_GetUsedSize(void);

#ifdef __cplusplus
}
#endif

#endif /* EEPROM_H */