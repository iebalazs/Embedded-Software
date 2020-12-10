/*
 * plotter.h
 *
 *  Created on: 2020. nov. 1.
 *      Author: iebal
 */

#ifndef PLOTTER_H_
#define PLOTTER_H_

#include "main.h"

void moveXY(uint8_t row, uint8_t col);

void moveZ();

void moveLinear(uint8_t row, uint8_t col, uint8_t NumOfBlackDots);

void print(uint8_t (*pData)[100]);

void printLinear(uint8_t (*pData)[100]);

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

#endif /* PLOTTER_H_ */
