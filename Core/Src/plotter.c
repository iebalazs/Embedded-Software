/*
 * plotter.c
 *
 *  Created on: 2020. nov. 1.
 *      Author: iebal
 */

#include "plotter.h"

/* Setting the pen to the actual coloumn */
void moveXY(uint8_t row, uint8_t col){
	htim4.Instance->CCR1 = row + 25;
	htim3.Instance->CCR1 = 125 - col;
}

/* Putting the pen down and then lifting up */
void moveZ(){
	HAL_Delay(250);
	htim2.Instance->CCR1 = 27;
	HAL_Delay(250);
	htim2.Instance->CCR1 = 32;
	HAL_Delay(250);
}

/* Putting the pen down and moving to the end of the line */
void moveLinear(uint8_t row, uint8_t col, uint8_t NumOfBlackDots){
	htim4.Instance->CCR1 = row + 25;
	htim3.Instance->CCR1 = 125 - col;
	HAL_Delay(250);
	htim2.Instance->CCR1 = 27;
	HAL_Delay(250);
	htim3.Instance->CCR1 = 125 - col - NumOfBlackDots;
	HAL_Delay(250);
	htim2.Instance->CCR1 = 32;
	HAL_Delay(250);
}

/* Drawing the image as spotted */
void print(uint8_t (*pData)[100]){
	htim4.Instance->CCR1 = 25;
	htim3.Instance->CCR1 = 125;
	for(int i=0; i<100; i++){
		for(int j = 0; j<100; j++){
			if(*(pData[i]+j) == 1){
				moveXY(i, j);
				moveZ();
			}
		}
		HAL_Delay(250);
	}
	htim4.Instance->CCR1 = 25;
	htim3.Instance->CCR1 = 125;
}

/* Drawing the image as linear */
void printLinear(uint8_t (*pData)[100]){
	htim4.Instance->CCR1 = 25;
	htim3.Instance->CCR1 = 125;
	for(int i=0; i<100; i++){
		uint8_t dotsRemainInRow = 99;
		while(dotsRemainInRow > 0){
			if(*(pData[i]+(100-dotsRemainInRow-1)) == 1){
				moveXY(i, 100-dotsRemainInRow-1);
				moveZ();
				dotsRemainInRow--;
			}
			else if(*(pData[i]+(100-dotsRemainInRow-1)) > 1){
				moveLinear(i, 100-dotsRemainInRow-1, (*(pData[i]+(100-dotsRemainInRow-1))-1)/2);
				dotsRemainInRow -= (*(pData[i]+(100-dotsRemainInRow-1))-1)/2 + 1;
			}
			else {dotsRemainInRow--; continue;}
		}
		HAL_Delay(250);
	}
	htim4.Instance->CCR1 = 25;
	htim3.Instance->CCR1 = 125;
}
