/*
 * adc.c
 *
 *  Created on: Nov. 5, 2020
 *      Author: James
 */

#include "msp.h"
#include "adc.h"

void adcInit(int channel)
{
    ADC14->CTL0 &= ~ADC14_CTL0_ENC;

    //turn on ADC14 and use sample/hold timer with minimum 4 sample cycles and modclk as clock source
    ADC14->CTL0 = ADC14_CTL0_ON | ADC14_CTL0_SHP;

    //select the input channel to be sampled
    ADC14->MCTL[0] = channel;


    ADC14->CTL0 |= ADC14_CTL0_ENC; // enable conversion
}

int adcSample()
{
    while(1)
    {
        ADC14->CTL0 |= ADC14_CTL0_SC;  // start conversion
        while ((ADC14->IFGR0 & ADC14_IFGR0_IFG0) == 0) {}  // wait for conversion to complete
        return ADC14->MEM[0];
    }
}


