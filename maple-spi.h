
/******************************************************************************

  Filename:		maple-spi.h
  Description:	SPI bus configuration for the WiShield 1.0 and Leaf Labs Maple board

 ******************************************************************************

  TCP/IP stack and driver for the WiShield 1.0 wireless devices

  Copyright(c) 2010 Adam Feuer All rights reserved.

  This program is free software; you can redistribute it and/or modify it
  under the terms of version 2 of the GNU General Public License as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
  more details.

  You should have received a copy of the GNU General Public License along with
  this program; if not, write to the Free Software Foundation, Inc., 59
  Temple Place - Suite 330, Boston, MA  02111-1307, USA.

   Author               Date        Comment
  ---------------------------------------------------------------
   Adam Feuer        19-Jul-2010   initial revision

 *****************************************************************************/

#ifndef MAPLE_SPI_H_
#define MAPLE_SPI_H_

#include "nvic.h"
#include "util.h"
#include "spi.h"

// Uncomment one line below to
// specify which Arduino pin
// to use as WiShield interrupt
#define USE_DIG0_INTR		// use digital pin 0
//#define USE_DIG8_INTR		// use digital pin 8

#ifdef USE_DIG0_INTR
#define ZG2100_ISR_ENABLE()		zg2100_isr_enable(EXTI3)   // Maple: digital pin D0 corresponds to interrupt EXTI3
#endif

#ifdef USE_DIG8_INTR
#define ZG2100_ISR_ENABLE()		zg2100_isr_enable(EXTI10)   // Maple: digital pin D8 corresponds to interrupt EXTI10
#endif

/* Maple: only pin D0 is supported for now
#ifdef USE_DIG8_INTR
#define ZG2100_INTR						BIT0
#endif
*/

#define HIGH 0x1
#define LOW  0x0

enum {
   MAPLE_SPI_PRESCALE_2       = (0x0 << 3),
   MAPLE_SPI_PRESCALE_4       = (0x1 << 3),
   MAPLE_SPI_PRESCALE_8       = (0x2 << 3),
   MAPLE_SPI_PRESCALE_16      = (0x3 << 3),
   MAPLE_SPI_PRESCALE_32      = (0x4 << 3),
   MAPLE_SPI_PRESCALE_64      = (0x5 << 3),
   MAPLE_SPI_PRESCALE_128     = (0x6 << 3),
   MAPLE_SPI_PRESCALE_256     = (0x7 << 3)
};

typedef enum 
MapleSPIFrequency {
   MAPLE_SPI_18MHZ       = 0,
   MAPLE_SPI_9MHZ        = 1,
   MAPLE_SPI_4_5MHZ      = 2,
   MAPLE_SPI_2_25MHZ     = 3,
   MAPLE_SPI_1_125MHZ    = 4,
   MAPLE_SPI_562_500KHZ  = 5,
   MAPLE_SPI_281_250KHZ  = 6,
   MAPLE_SPI_140_625KHZ  = 7,
   MAPLE_MAX_SPI_FREQS   = 8,
} MapleSPIFrequency;

#define SPI1                                    1
#define SPI1_SendByte(Data)		        spi_tx_byte(SPI1, Data); 
#define SPI1_RecvByte()				spi_rx(SPI1)

// ZG2100 SPI HAL

void zg2100_isr_enable(uint8 channel);

#define ZG2100_ISR_DISABLE()                    nvic_disable_interrupts();
#define ZG2100_SpiInit				SPI1_Init
#define ZG2100_SpiSendData	                SPI1_SendByte
#define ZG2100_SpiRecvData	                SPI1_RecvByte

#define ZG2100_CS_PIN                           10
#define ZG2100_CSInit()                         pinMode(ZG2100_CS_PIN, OUTPUT)
#define ZG2100_CSon()                           digitalWrite(ZG2100_CS_PIN, LOW)
#define ZG2100_CSoff()                          digitalWrite(ZG2100_CS_PIN, HIGH)

#define NUMBER_OF_ZG_LEDS                       4
#define LED0_PIN                                15
#define LED1_PIN                                16
#define LED2_PIN                                17
#define LED3_PIN                                18
#define LED_CONN_PIN                            8

extern int led0_bit;
extern int led1_bit;
extern int led2_bit;
extern int led3_bit;
extern int led_conn_bit;

#define LEDConn_on()                            led_on(LED_CONN_PIN, led_conn_bit)
#define LED0_on()                               led_on(LED0_PIN, led0_bit)
#define LED1_on()                               led_on(LED1_PIN, led1_bit)
#define LED2_on()                               led_on(LED2_PIN, led2_bit)
#define LED3_on()                               led_on(LED3_PIN, led3_bit)

#define LEDConn_off()                           led_off(LED_CONN_PIN, led_conn_bit)
#define LED0_off()                              led_off(LED0_PIN, led0_bit)
#define LED1_off()                              led_off(LED1_PIN, led1_bit)
#define LED2_off()                              led_off(LED2_PIN, led2_bit)
#define LED3_off()                              led_off(LED3_PIN, led3_bit)

#define LED0_toggle()                           led_toggle(LED0_PIN, led0_bit)
#define LED1_toggle()                           led_toggle(LED1_PIN, led1_bit)
#define LED3_toggle()                           led_toggle(LED3_PIN, led3_bit)

#endif /* MAPLE_SPI_H_ */
