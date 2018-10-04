# Software Debouncing
These codes are button interrupts that implement button debouncing. Mechanical switches like most things are not perfect and can sometimes "bounce". A button "bounce" is when the button interprets a single quick button input as multiple inputs which is usually undesired. The simple fix for this is to implement debouncing into codes that may encounter this problem. Debouncing allows the button to only read one input when the button is pressed. Theses codes both depend on two different libraries <msp430.h> for the MSP430G2553 and <msp432.h> for the MSP432P401R.

## MSP430G2553
The code for this processor has an interrupt for when the button is pressed. Although once this interrupt begins the code inside runs which disables the button's interrupt which prevents the debouncing of the button. One the interrupt is disabled a timer begins to count which when reached will allow the interrupt to be activated again.

## MSP432P401R
The code for this processor runs identically to the code mentioned for the other processor. Some changes were made to the ports and sytanx to allow the code to interface with this processor. 

 * Author: Eric Schroeder
 * Written: October 4, 2018
 * Last Updated: October 4, 2018
