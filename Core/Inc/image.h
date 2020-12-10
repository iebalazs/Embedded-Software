/*
 * image.h
 *
 *  Created on: 2020. dec. 9.
 *      Author: iebal
 */

#ifndef INC_IMAGE_H_
#define INC_IMAGE_H_

#include "main.h"

void computeModeAndSize(uint8_t* pdata, uint8_t* psize, uint8_t* pmode);

int computeNumOfBytes(uint8_t* pSize);

void decimalToBinary(uint8_t decimal, uint8_t* pbinary);

void fillArray(uint8_t* pDataByte, int NumOfBytes, uint8_t* pSize, uint8_t (*pData)[100]);

void fillArrayWithZeros(uint8_t (* pData)[100]);

uint8_t countDots(uint8_t* pDot, uint8_t* dotsRemainInRow);

void prepareArrayAsLinear(uint8_t (*pData)[100]);

#endif /* INC_IMAGE_H_ */
