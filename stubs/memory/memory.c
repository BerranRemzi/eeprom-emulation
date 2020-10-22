/**
  MEMORY Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    memory.c

  @Summary
    This is the generated driver implementation file for the MEMORY driver using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This file provides implementations of driver APIs for MEMORY.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.77
        Device            :  PIC16F1619
        Driver Version    :  2.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.05 and above
        MPLAB             :  MPLAB X 5.20
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip software and any
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party
    license terms applicable to your use of third party software (including open source software) that
    may accompany Microchip software.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS
    FOR A PARTICULAR PURPOSE.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS
    SOFTWARE.
*/

/**
  Section: Included Files
*/

//#include <xc.h>
#include "memory.h"

/**
  Section: Flash Module APIs
*/
uint16_t usedFlashWords = UINT16_MAX;
uint16_t flashContainer[END_FLASH];
uint16_t writeCycles = 0;

uint16_t FLASH_ReadWord(uint16_t flashAddr)
{
    return (flashContainer[flashAddr]);
}

void FLASH_WriteWord(uint16_t flashAddr, uint16_t* ramBuf, uint16_t word)
{
    uint16_t blockStartAddr = (uint16_t)(flashAddr & ((END_FLASH - 1) ^ (ERASE_FLASH_BLOCKSIZE - 1)));
    uint8_t offset = (uint8_t)(flashAddr & (ERASE_FLASH_BLOCKSIZE - 1));
    uint8_t i;

    // Entire row will be erased, read and save the existing data
    for (i = 0; i < ERASE_FLASH_BLOCKSIZE; i++)
    {
        ramBuf[i] = FLASH_ReadWord((blockStartAddr + i));
    }

    // Write at offset
    ramBuf[offset] = word;

    // Writes ramBuf to current block
    FLASH_WriteBlock(blockStartAddr, ramBuf);
}

int8_t FLASH_WriteBlock(uint16_t writeAddr, const uint16_t* flashWordArray)
{
    uint16_t    blockStartAddr = (uint16_t)(writeAddr & ((END_FLASH - 1) ^ (ERASE_FLASH_BLOCKSIZE - 1)));

    uint8_t i;

    // Flash write must start at the beginning of a row
    if (writeAddr != blockStartAddr)
    {
        return -1;
    }

    // Block erase sequence
    FLASH_EraseBlock(writeAddr);

    for (i = 0; i < WRITE_FLASH_BLOCKSIZE; i++)
    {
        flashContainer[writeAddr] = flashWordArray[i];

        writeAddr++;
    }

    writeCycles++;
    if (usedFlashWords == UINT16_MAX) {
        usedFlashWords = blockStartAddr;
    }

    return 0;
}

void FLASH_EraseBlock(uint16_t startAddr)
{
    uint16_t blockStartAddr = (uint16_t)(startAddr & ((END_FLASH - 1) ^ (ERASE_FLASH_BLOCKSIZE - 1)));

    for (uint8_t i = 0; i < ERASE_FLASH_BLOCKSIZE; i++) {
        flashContainer[blockStartAddr + i] = 0x3FFF;
    }
}
uint16_t FLASH_WriteCycles(void)
{
    return writeCycles;
}
/**
 End of File
*/