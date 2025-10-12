/*
 * main.h
 *
 *  Created on: 12 окт. 2025 г.
 *      Author: admin
 */

#ifndef INC_MAIN_H_
#define INC_MAIN_H_


#include <plib015.h>
#include <system_k1921vg015.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "retarget.h"

#define NSSPin GPIO_Pin_6
#define NSSPort GPIOB

#define DIO1Pin	 GPIO_Pin_8
#define DIO1Port GPIOB

#define BUSYPin	GPIO_Pin_9
#define BUSYPort GPIOB


#endif /* INC_MAIN_H_ */
