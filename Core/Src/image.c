/*
 * image.c
 *
 *  Created on: 2020. dec. 9.
 *      Author: iebal
 */

#include "image.h"

/* Figuring the technique and the size out */
void computeModeAndSize(uint8_t* pdata, uint8_t* psize, uint8_t* pmode){
	if((*pdata) > 128){
		*pmode = 1;
		*psize = (*pdata)-128;
	}
	else{
		*pmode = 0;
		*psize = *pdata;
	}
	*(psize+1) = *(pdata+1);
}

/* Computing the number of useful bytes in the image */
int computeNumOfBytes(uint8_t* pSize){
	  int mod = (pSize[0]*pSize[1])%8;
	  int numOfBytes;
	  if(mod==0){
		  numOfBytes = pSize[0] * pSize[1] / 8;
	  }
	  else{numOfBytes = (pSize[0]*pSize[1]+8-mod)/8;}
	  return numOfBytes;
}

/* Converting the decimal number to binary */
void decimalToBinary(uint8_t decimal, uint8_t* pbinary) {
	for (int j = 0; j < 8; j++)
		pbinary[j] = 0;
	int i = 7;
	while (decimal > 0) {
		pbinary[i] = decimal % 2;
		decimal = decimal / 2;
		i--;
	}
}

/* Filling the array with zeros */
void fillArrayWithZeros(uint8_t (* pData)[100]) {
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			*(pData[i] + j) = 0;
		}
	}
}

/* Counting dots in a line */
uint8_t countDots(uint8_t* pDot, uint8_t* dotsRemainInRow){
	uint8_t Dots = 0;
	while((*dotsRemainInRow) != 0 && *(pDot+1)==1){
		Dots += 1;
		(*dotsRemainInRow)--;
		pDot++;
	}
	if((*dotsRemainInRow) > 0)
		(*dotsRemainInRow)--;
	return Dots;
}

/* Filling the array with ones and zeros */
void fillArray(uint8_t* pDataByte, int NumOfBytes, uint8_t* pSize, uint8_t (*pData)[100]) {
	uint8_t Rows = *pSize;
	uint8_t Cols = *(pSize + 1);
	uint8_t StartRow = (100 - Rows) / 2;
	uint8_t StartCol = (100 - Cols) / 2;
	uint8_t CurrentRow = StartRow;
	uint8_t CurrentCol = StartCol;
	uint8_t binary[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

	for (int i = 2; i < NumOfBytes+2; i++) {
		decimalToBinary(pDataByte[i], binary);
		if(i==NumOfBytes+1){
			uint8_t rest = 8 - ((Rows*Cols)%8);
			for(int k = 0; k<rest; k++){
				*(pData[CurrentRow] + CurrentCol) = binary[k];
				CurrentCol++;
			}
			return;
		}
		for (int j = 0; j < 8; j++) {
			*(pData[CurrentRow] + CurrentCol) = binary[j];
			if (CurrentCol == StartCol + Cols - 1) {
				CurrentCol = StartCol;
				CurrentRow += 1;
			}
			else { CurrentCol++; }
		}
	}
}

/* Preparing array for linear drawing */
void prepareArrayAsLinear(uint8_t (*pData)[100]){
	for(int i=0; i<100; i++){
		uint8_t dotsRemainInRow = 99;
		while(dotsRemainInRow > 0){
			if(*(pData[i]+(100-dotsRemainInRow-1)) == 1){
				uint8_t* pTemp = pData[i]+(100-dotsRemainInRow-1);
				uint8_t NumOfDots = countDots(pData[i]+(100-dotsRemainInRow-1), &dotsRemainInRow);
				(*pTemp) += (2*NumOfDots);
			}
			else{
				dotsRemainInRow--;
			}
		}
	}
}
