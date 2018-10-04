/*Author: Eric Schroeder
 * Written: October 1, 2018
 * Last updated October 4, 2018
 */

#include <msp430.h>

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;           // stop watchdog timer
    P1DIR |= BIT0;                      //set pin 1.0 direction to output
    P1DIR |= BIT6;                      //set pin 1.6 direction to output
    P1SEL |= (BIT6);                    //sets port 1 for output
    P1OUT &= ~BIT0;
    TA0CTL = TASSEL_2 + MC_1 + ID_1;    //set Timer A to up mode divided by 2
    TA0CCR0 = 1000;                     //set period
    TA0CCR1 = 100;                      //set duty cycle
    TA0CCTL1 = OUTMOD_7;                //set timer to set/reset mode
    P1DIR &= ~BIT3;                     //set pin 1.3 direction to input
    P1REN |= BIT3;                      //enable resistor on pin 1.3
    P1OUT |= BIT3;                      //set resistor to pull up
    P1IE |= BIT3;                       //enable interrupt on button
    P1IES |= BIT3;                      //set interrupt edge
    P1IFG &= ~BIT3;                     //clear interrupt flags
    __enable_interrupt();
    while(1);
}
#pragma vector=PORT1_VECTOR             //indicate interrupt vector being used
__interrupt void Port_1(void)
{
    if(P1IES & BIT3){
            if (TA0CCR1<1000) {             //if duty cycle did not overflow
                TA0CCR1+=100;               //increment duty cycle by 10%
            } else if (TA0CCR1 >=1000) {    //if the duty cycle does overflow
                TA0CCR1 = 0;                //reset duty cycle
            }
    }
           P1IES ^= BIT3;                   //toggle interrupt edge
           P1OUT ^= BIT0;                   //toggle LED(green) on pin 1.0
           P1IFG &= ~BIT3;                  //clear flags on button interrupt
}
