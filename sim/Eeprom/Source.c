#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "test.h"

#include "Eeprom.h"

#define EEPROM_SIZE (uint16_t)1024
#define START_FLASH (END_FLASH - EEPROM_SIZE)

uint8_t inputBuffer[EEPROM_SIZE];
uint8_t outputBuffer[EEPROM_SIZE];

int main() {
    printf("Data FLASH for an EEPROM Emulation #1\n\n");

    /* Fill with incrementing sequence */
    for (uint16_t i = 1; i < EEPROM_SIZE; i++) {
        outputBuffer[i] = outputBuffer[i - 1] + 1;
    }
    /* Init eeprom emulation */
    Eeprom_Init(START_FLASH, END_FLASH - 1);

    /* Write and read back to buffer */
    Eeprom_Write(outputBuffer, 0, EEPROM_SIZE);
    Eeprom_Read(inputBuffer, 0, EEPROM_SIZE);

    /* Test_PrintBufferAsByte input and output buffer content */
    printf("Write to EEPROM");
    Test_PrintBufferAsByte(outputBuffer, 64);
    printf("\nRead from EEPROM");
    Test_PrintBufferAsByte(inputBuffer, 64);

    /* Get count of non equal values in input-output buffers */
    uint16_t errorCount = Test_GetErrorCount(inputBuffer, outputBuffer, EEPROM_SIZE);

    /* Test_PrintBufferAsByte debug data */
    printf("\nUsed FlashWords  = %4d\n", Eeprom_GetUsedSize());
    printf("Flash writes     = %4d\n", FLASH_WriteCycles());
    printf("Used EepromBytes = %4d\n\n", (int)sizeof(outputBuffer));
    printf("Error count      = %4d\n", errorCount);

    return errorCount;
}