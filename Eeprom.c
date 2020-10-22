#include "Eeprom.h"

static uint16_t buff[ERASE_FLASH_BLOCKSIZE];

static uint16_t usedEeprom = 0;

/* local variables */
static uint16_t flashStart;
static uint16_t flashEnd;

void Eeprom_Init(uint16_t _flashStart, uint16_t _flashEnd) {
    flashStart = _flashStart;
    flashEnd = _flashEnd;
}

void Eeprom_Read(uint8_t* _dest, uint16_t _address, uint16_t _size) {
    for (uint16_t i = 0; i < _size; i++) {
        uint16_t flashAddress = flashStart + _address + i;

        if (flashAddress <= flashEnd) {
            _dest[i] = (uint8_t)FLASH_ReadWord(flashAddress);
        }
        else {
            _dest[i] = 0xFF;
        }        
    }
}

void Eeprom_Write(const uint8_t* _src, uint16_t _address, uint16_t _size) {
    for (uint16_t i = 0; i < _size; i++) {
        uint16_t flashAddress = flashStart + _address + i;

        if (flashAddress <= flashEnd) {
            FLASH_WriteWord(flashAddress, buff, (uint16_t)_src[i]);
        }
        
        if (flashAddress - flashStart > usedEeprom) {
            usedEeprom = flashAddress - flashStart+1;
        }
    }
}

uint16_t Eeprom_GetUsedSize(void) {
    return usedEeprom;
}