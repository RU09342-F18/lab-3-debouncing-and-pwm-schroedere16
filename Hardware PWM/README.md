# Hardware PWM
These codes utlizize the hardware in the microcontrollers to control the duty cycle of a pulse in an LED. These codes start an LED at 50% duty cycle. While each button press will increase the duty cycle all the way to 100% at which point it will loop around and begin at 0% then starting the loop over. These codes depend on the <msp430.h> library.

## MSP430G2553
The code for this processor works as described above it starts with the red LED at 50% duty cycle and whenever the button is pressed the green LED will flash to let the user know the duty cycle has been increased. The green LED was implemented as the higher duty cycles 80, 90, and 100% have very little difference to the human eye. This code also takes the debouncing mentioned in a previous code to ensure the user's input is only counted a single time with each button press.

## MSP430FR2311


 * Author: Eric Schroeder
 * Written: October 4, 2018
 * Last Updated: October 4, 2018
