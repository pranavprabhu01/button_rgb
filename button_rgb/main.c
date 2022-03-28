/*This program changes the color when the button is pressed. An interrupt is attached to the button.*/
//Author: Pranav Prabhu

#include "msp.h"


/**
 * P1.1 will be used as button(input).
 * P2.0,P2.1,P2.2 will be used as LED(output).
 */

void main(void)
{
    P1->SEL0=0;             //Configure as GPIO
    P1->SEL1=0;

    P1->DIR=~(uint8_t)BIT1;  //Configure as Input
    P1->OUT=BIT1;
    P1->REN=BIT1;           //Pull up resistor is high

    P1->IES=BIT1;           //High to low
    P1->IE=BIT1;            //Enable interrupt
    P1->IFG=0;              //Setting Interrupt Flag as zero

    NVIC->ISER[1]=1 << ((PORT1_IRQn) & 31);

    P2->SEL0=0;             //Configure as GPIO
    P2->SEL1=0;
    P2->DIR=0b00000111;     //Configure RGB as output
    P2->OUT=BIT0;           //Turning on red LED High

   //Disabling unused ports
        P3->DIR |= 0xFF; P3->OUT = 0;
        P4->DIR |= 0xFF; P4->OUT = 0;
        P5->DIR |= 0xFF; P5->OUT = 0;
        P6->DIR |= 0xFF; P6->OUT = 0;
        P7->DIR |= 0xFF; P7->OUT = 0;
        P8->DIR |= 0xFF; P8->OUT = 0;
        P9->DIR |= 0xFF; P9->OUT = 0;
        P10->DIR |= 0xFF; P10->OUT = 0;

    __enable_irq();
}

void PORT1_IRQHandler(void)
{
    volatile uint32_t i;

    if(P1->IFG & BIT1)
    {
        if(P2->OUT & BIT0)
        {
            P2->OUT=BIT1;
        }

        else if(P2->OUT & BIT1)
        {
            P2->OUT=BIT2;
        }

        else
        {
            P2->OUT=BIT0;
        }

    }

    for(i=0;i<10000;i++);               //Debounce


    P1->IFG&=~BIT1;                     //Clear interrupt flag
}
