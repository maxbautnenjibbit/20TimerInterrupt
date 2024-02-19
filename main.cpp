/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

DigitalOut ledA(PC_0);
DigitalOut ledB(PC_1);

float getSecFromHz(float hz) {
    return 1 / hz;
}

void blinkA() {
    TIM6->SR = 0;
    ledA = !ledA;
}

void blinkB() {
    TIM7->SR = 0;
    ledB = !ledB;
}

void initATimer() {    
    RCC->APB1ENR |= 0b10000;
    TIM6->PSC = 31999;
    TIM6->ARR = 1000 * getSecFromHz(1);
    TIM6->CNT = 0;
    TIM6->SR = 0;
    TIM6->CR1 = 1;
    
    TIM6->DIER = 1;

    NVIC_SetVector(TIM6_IRQn, (uint32_t)&blinkA);
    HAL_NVIC_EnableIRQ(TIM6_IRQn);
}

void initBTimer() {    
    RCC->APB1ENR |= 0b100000;
    TIM7->PSC = 31999;
    TIM7->ARR = 1000 * getSecFromHz(3);
    TIM7->CNT = 0;
    TIM7->SR = 0;
    TIM7->CR1 = 1;
    
    TIM7->DIER = 1;

    NVIC_SetVector(TIM7_IRQn, (uint32_t)&blinkB);
    HAL_NVIC_EnableIRQ(TIM7_IRQn);
}

int main()
{
    ledA = 0;
    ledB = 0;
    initATimer();
    initBTimer();
    while (true) {

    }
}
