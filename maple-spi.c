
/******************************************************************************

  Filename:	maple-spi.c
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

#include "nvic.h"
#include "exti.h"
#include "wirish.h"
#include "maple-spi.h"
#include "maple-util.h"

void enable_interrupt(uint8 channel) {

    // copied from exti_attach_interrupt() in libmaple/exti.c
    // TODO: refactor exti_attach_interrupt() to separate this into a separate function and eliminate duplication

    /* Configure the enable interrupt bits for the NVIC  */
    switch (channel) {
    case EXTI0:
    case EXTI1:
    case EXTI2:
    case EXTI3:
    case EXTI4:
        REG_SET(NVIC_ISER0, BIT(channel + 6));
        break;

    /* EXTI5-9 map to the same isr */
    case EXTI5:
    case EXTI6:
    case EXTI7:
    case EXTI8:
    case EXTI9:
        REG_SET(NVIC_ISER0, BIT(23));
        break;

    /* EXTI10-15 map to the same isr */
    case EXTI10:
    case EXTI11:
    case EXTI12:
    case EXTI13:
    case EXTI14:
    case EXTI15:
        REG_SET(NVIC_ISER1, BIT(8));
        break;
    }

}

void zg2100_isr_enable(uint8 channel) {
   enable_interrupt(channel);

   // enable USB interrupts so the bootloader will continue to work
   nvic_enable_interrupt(NVIC_INT_USBHP);
   nvic_enable_interrupt(NVIC_INT_USBLP);
}

/*
#define SPI1_Init()  DDRB  |= SPI0_SS_BIT|SPI0_SCLK_BIT|SPI0_MOSI_BIT|LEDConn_BIT;\
	DDRB  &= ~SPI0_MISO_BIT;\
	PORTB = SPI0_SS_BIT;\
	SPCR  = 0x50;\
	SPSR  = 0x01
*/

// Maple SPI

static const uint32 prescaleFactors[MAPLE_MAX_SPI_FREQS] = {
   MAPLE_SPI_PRESCALE_2,               // SPI_18MHZ
   MAPLE_SPI_PRESCALE_4,               // SPI_9MHZ
   MAPLE_SPI_PRESCALE_8,               // SPI_4_5MHZ
   MAPLE_SPI_PRESCALE_16,              // SPI_2_25MHZ
   MAPLE_SPI_PRESCALE_32,              // SPI_1_125MHZ
   MAPLE_SPI_PRESCALE_64,              // SPI_562_500KHZ
   MAPLE_SPI_PRESCALE_128,             // SPI_281_250KHZ
   MAPLE_SPI_PRESCALE_256,             // SPI_140_625KHZ
};

void SPI1_Init() {
  MapleSPIFrequency freq;
  uint32 spi_num, endian, prescale;

  //serialUsbPrintlnWaitForInput("***In SPI1_Init()");
  serialUsbPrintln("***In SPI1_Init()");

  // set up CS pin
  ZG2100_CSInit();
  ZG2100_CSoff();

  pinMode(D2, INPUT);

  // init SPI
  spi_num = 1;
  endian = MSBFIRST;
  freq = MAPLE_SPI_4_5MHZ;
  prescale = prescaleFactors[freq]; // only valid for SPI1
  spi_init(spi_num, prescale, endian, 0);

  //serialUsbPrintlnWaitForInput("*** Done with spi_init.");
  serialUsbPrintln("*** Done with spi_init.");
}

// ZG2100 SPI HAL

int led0_bit = 0;
int led1_bit = 0;
int led2_bit = 0;
int led3_bit = 0;
int led_conn_bit = 0;

