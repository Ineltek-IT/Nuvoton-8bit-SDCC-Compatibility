/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2020 nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

/***********************************************************************************************************/
/* Website: http://www.nuvoton.com                                                                         */
/*  E-Mail : MicroC-8bit@nuvoton.com                                                                       */
/*  Date   : June/21/2020                                                                                   */
/***********************************************************************************************************/

/************************************************************************************************************/
/*  File Function: MS51 ADC / Bandgap input demo code                                                       */
/************************************************************************************************************/
#include "MS51_32K.h"

/************************************************************************************************************/
/*   PWM interrupt subroutine                                                                               */
/************************************************************************************************************/
void PWM0_ISR (void) interrupt 13

{
    _push_(SFRS);
  
    clr_PWM0CON0_PWMF;               // clear PWM interrupt flag
  
    _pop_(SFRS);
}

/************************************************************************************************************
*    Main function 
************************************************************************************************************/
void main(void)
{

/**********************************************************************
  PWM frequency = Fpwm/((PWMPH,PWMPL) + 1) <Fpwm = Fsys/PWM_CLOCK_DIV> 
                = (16MHz/8)/(0x3FF + 1)
                = 2.7KHz
***********************************************************************/
    ENABLE_PWM0_CH2_P05_OUTPUT;
    P05_PUSHPULL_MODE;
    PWM0_CH2_INTERRUPT_SELECT;    

    PWM0_CLOCK_DIV_8;
    PWM0PH = 0x03;                     /*Setting PWM period  */
    PWM0PL = 0xFF;
    PWM0C2H = 0x0;                      /*PWM0 high duty = 1/2 PWM period */
    PWM0C2L = 0xFF;  

    ENABLE_PWM0_INTERRUPT;                     /*Enable PWM interrupt  */
    ENABLE_GLOBAL_INTERRUPT;
    set_PWM0CON0_LOAD;
    set_PWM0CON0_PWM0RUN;
    while(1);
}