led_array_arm
=============
o An implementation of an RGB LED array driver for the LPC1769 microcontroller, using the LPCXpressor dev. kit.
o The RGB LED array that was used for this project can be obtained here: http://www.adafruit.com/products/420 .
o More information about the LPCeXpressor dev. kit is here: http://www.lpctools.com/lpc1768.lpcxpresso.aspx . This 
board is cheap ($30), has loads of GPIO, and has a fast ARM Cortex-M3 core (can clock up to 120 MHz).

Misc. notes
===========
o This project uses the uC/OS-II RTOS, which is *NOT* bundled due to licensing issues. In order for the project to compile, you must first sign-up for an account at http://micrium.com/ . I'll consider using FreeRTOS.
