#ifndef _FASTIO_H
#define _FASTIO_H

#include <samd.h>

#include <samd21/include/samd21.h>

// 0/1 - UART (Serial)
#define DIO0_PORT PORTA
#define DIO0_PIN PORT_PA11

#define DIO1_PORT PORTA
#define DIO1_PIN PORT_PA10

// 2 .. 12
#define DIO2_PORT PORTA
#define DIO2_PIN PORT_PA14
#define DIO3_PORT PORTA
#define DIO3_PIN PORT_PA09
#define DIO4_PORT PORTA
#define DIO4_PIN PORT_PA08
#define DIO5_PORT PORTA
#define DIO5_PIN PORT_PA15
#define DIO6_PORT PORTA
#define DIO6_PIN PORT_PA20
#define DIO7_PORT PORTA
#define DIO7_PIN PORT_PA21
#define DIO8_PORT PORTA
#define DIO8_PIN PORT_PA06
#define DIO9_PORT PORTA
#define DIO9_PIN PORT_PA07
#define DIO10_PORT PORTA
#define DIO10_PIN PORT_PA18
#define DIO11_PORT PORTA
#define DIO11_PIN PORT_PA16
#define DIO12_PORT PORTA
#define DIO12_PIN PORT_PA19

// 13 - AMBER LED
#define DIO13_PORT PORTA
#define DIO13_PIN PORT_PA17

// 14 - 27
#define DIO14_PORT PORTB
#define DIO14_PIN PORT_PB04
#define DIO15_PORT PORTB
#define DIO15_PIN PORT_PB05
#define DIO16_PORT PORTB
#define DIO16_PIN PORT_PB06
#define DIO17_PORT PORTB
#define DIO17_PIN PORT_PB07
#define DIO18_PORT PORTA
#define DIO18_PIN PORT_PA12
#define DIO19_PORT PORTB
#define DIO19_PIN PORT_PB13
#define DIO20_PORT PORTB
#define DIO20_PIN PORT_PB14
#define DIO21_PORT PORTB
#define DIO21_PIN PORT_PB15
#define DIO22_PORT PORTB
#define DIO22_PIN PORT_PB16
#define DIO23_PORT PORTB
#define DIO23_PIN PORT_PB17
#define DIO24_PORT PORTB
#define DIO24_PIN PORT_PB30
#define DIO25_PORT PORTB
#define DIO25_PIN PORT_PB31
#define DIO26_PORT PORTB
#define DIO26_PIN PORT_PB00
#define DIO27_PORT PORTB
#define DIO27_PIN PORT_PB01

// 28 - 33 ANALOG

#define DIO28_PORT PORTA
#define DIO28_PIN PORT_PA02
#define DIO29_PORT PORTB
#define DIO29_PIN PORT_PB08
#define DIO30_PORT PORTB
#define DIO30_PIN PORT_PB09
#define DIO31_PORT PORTA
#define DIO31_PIN PORT_PA04
#define DIO32_PORT PORTA
#define DIO32_PIN PORT_PA05
#define DIO33_PORT PORTB
#define DIO33_PIN PORT_PB02

// 34 .. 35 I2C
#define DIO34_PORT PORTA
#define DIO34_PIN PORT_PA22
#define DIO35_PORT PORTA
#define DIO35_PIN PORT_PA23

//36 .. 38 SPI
#define DIO36_PORT PORTB
#define DIO36_PIN PORT_PB12
#define DIO37_PORT PORTB
#define DIO37_PIN PORT_PB10
#define DIO38_PORT PORTB
#define DIO38_PIN PORT_PB11

// 39 .. 40 LED RX TX
#define DIO39_PORT PORTB
#define DIO39_PIN PORT_PB03
#define DIO40_PORT PORTA
#define DIO40_PIN PORT_PA27

// 41 .. 43 USB
#define DIO41_PORT PORTA
#define DIO41_PIN PORT_PA28
#define DIO42_PORT PORTA
#define DIO42_PIN PORT_PA24
#define DIO43_PORT PORTA
#define DIO43_PIN PORT_PA25

// 44 ..45 EDBG

#define DIO44_PORT PORTB
#define DIO44_PIN PORT_PB22
#define DIO45_PORT PORTB
#define DIO45_PIN PORT_PB23

// 46 .. 47 I2C
#define DIO46_PORT PORTA
#define DIO46_PIN PORT_PA22
#define DIO47_PORT PORTA
#define DIO47_PIN PORT_PA23

// 48 .. 51 EDBG SPI
#define DIO48_PORT PORTA
#define DIO48_PIN PORT_PA19
#define DIO49_PORT PORTA
#define DIO49_PIN PORT_PA16
#define DIO50_PORT PORTA
#define DIO50_PIN PORT_PA18
#define DIO51_PORT PORTA
#define DIO51_PIN PORT_PA17

//52 .. 55
#define DIO52_PORT PORTA
#define DIO52_PIN PORT_PA13
#define DIO53_PORT PORTA
#define DIO53_PIN PORT_PA21
#define DIO54_PORT PORTA
#define DIO54_PIN PORT_PA06
#define DIO55_PORT PORTA
#define DIO55_PIN PORT_PA07

//56 AREF
#define DIO56_PORT PORTA
#define DIO56_PIN PORT_PA03

// 57 DAC
#define DIO57_PORT PORTA
#define DIO57_PIN PORT_PA02

#ifndef DIO0_PIN
#error pins for this chip not defined in arduino.h! If you write an appropriate pin definition and have this firmware work on your chip, please submit a pull request
#endif

#endif /* _FASTIO_H */
