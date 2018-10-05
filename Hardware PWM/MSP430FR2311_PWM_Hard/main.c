/*Author: Eric Schroeder
 * Written: October 2, 2018
 * Last Updated: October 5, 2018
 */

#include <msp430.h>

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;           // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;
    P1DIR |= BIT0;                      // set pin 1.0 direction to output
    P2DIR |= BIT0;                      // set pin 2.0 direction to output
    P2SEL0 |= (BIT0);                   //sets pin 2.0 as output
    P2SEL1 &= ~BIT0;
    TB1CTL = TBSSEL_2 + MC_1 + ID_1;    // set Timer B to SMLCK in up mode with a clock divider
    TB1CCR0 = 1000;                     // set period
    TB1CCR1 = 500;                      // set duty cycle to 50%
    TB1CCTL1 = OUTMOD_7;                // set timer to set/reset mode
    TB0CCTL0 = CCIE;                    //enable CCR interrupt
    TB0CCR0 = 10000;                    //set timer overflow
    TB0CTL = TBSSEL_2 + MC_0;           // connects timer b to SMCLK and turn off
    P1DIR &= ~BIT1;                     //set pin 1.3 direction to input
    P1REN |= BIT1;                      //enable resistor on pin 1.3
    P1OUT |= BIT1;                      //set resistor to pull up
    P1IE |= BIT1;                       //enable interrupt on button
    P1IES |= BIT1;                      //set interrupt edge to low
    P1IFG &= ~BIT1;                     //clear interrupt flags

    __bis_SR_register(GIE);             // LPM0 with general interrupts enabled
    while(1);
}


#pragma vector=PORT1_VECTOR         //indicate interrupt vector being used
__interrupt void Port_1(void)
{
    P1IE &= ~BIT1;                          //disable button interrupt
    if(P1IES & BIT1){
            if (TB1CCR1<1000) {             //if duty cycle did not overflow
                TB1CCR1+=100;               //increment duty cycle by 10%
            } else if (TB1CCR1 >=1000) {    //if the duty cycle overflows (goes over 100%)
                TB1CCR1 = 0;                //reset duty cycle
            }
    }
           P1IES ^= BIT1;                   //toggle edge
           P1OUT ^= BIT0;                   //toggle pin 1.0 LED
           P1IFG &= ~BIT1;                  //clear flags
           TB0CTL = TBSSEL_2 + MC_1;        // connect timer b0 to SMCLK in up mode
}

//timer B0 interrupt for debounce
#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer_B (void) {
    TB0CTL = MC_0;                          //stops the timer
    TB0R = 0;                               //resets the timer
    P1IE |= BIT1;                           //enable button interrupt
    P1IFG &= ~BIT1;                         //clear interrupt flag
}
