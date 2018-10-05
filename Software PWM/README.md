# Software PWM
These two codes change the duty cycle of an LED in 10% increments after a user pushes a button. This is obviously implemented using software loops inside the interrupts. The code for these has two CCR registers when the timer counts up to the first value in the CCR the LED turns on and when the timer counts to the value in the second CCR is turns the LED off. The code for this will increase the second CCR value which will increase the time the LED is on until it reaches a 100% duty cycle. After this is will loop back to 0% duty cycle and begin again. The codes for these processors depend on the <msp430.h> library. 

## MSP430G2553
The code for this processor functions identically to the above mentioned code. The LED will start at a 50% duty cycle and begin to increase as the button is hit up until 100% and then reset. 

## MSP430F5529
The code for this processor functions identically to the one for the other board but implements port differences to interface with this board. 

 * Author: Eric Schroeder
 * Written: October 5, 2018
 * Last Updated: October 5, 2018
