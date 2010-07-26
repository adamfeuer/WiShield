/* 
 * maple-util.c
 * 
 * various utility routines useful for debugging
 *
 */

#include "libmaple_types.h"
#include "usart.h"
#include "gpio.h"
#include "timers.h"

#define USART1_TX_PORT             GPIOA_BASE
#define USART1_TX_PIN              9
#define USART1_RX_PORT             GPIOA_BASE
#define USART1_RX_PIN              10

#define USART2_TX_PORT             GPIOA_BASE
#define USART2_TX_PIN              2
#define USART2_RX_PORT             GPIOA_BASE
#define USART2_RX_PIN              3

#define USART3_TX_PORT             GPIOB_BASE
#define USART3_TX_PIN              10
#define USART3_RX_PORT             GPIOB_BASE
#define USART3_RX_PIN              11

static uint8 usartNum;

void initSerial(uint8 usartNumIn, uint32 baud) {

    /* Set appropriate pin modes  */
    switch (usartNum) {
    case 1:
        gpio_set_mode(USART1_TX_PORT, USART1_TX_PIN, GPIO_MODE_AF_OUTPUT_PP);
        gpio_set_mode(USART1_RX_PORT, USART1_RX_PIN, GPIO_MODE_INPUT_FLOATING);
        /* Turn off any pwm  */
        timers_disable_channel(1, 2);
        break;
    case 2:
        gpio_set_mode(USART2_TX_PORT, USART2_TX_PIN, GPIO_MODE_AF_OUTPUT_PP);
        gpio_set_mode(USART2_RX_PORT, USART2_RX_PIN, GPIO_MODE_INPUT_FLOATING);
        /* Turn off any pwm  */
        timers_disable_channel(2, 3);
        break;
    case 3:
        gpio_set_mode(USART3_TX_PORT, USART3_TX_PIN, GPIO_MODE_AF_OUTPUT_PP);
        gpio_set_mode(USART3_RX_PORT, USART3_RX_PIN, GPIO_MODE_INPUT_FLOATING);
        break;
    default:
        ;
    }

    usart_init(usartNum, baud);

}

void writeSerialStr(const char *str) {
  while (*str)
    write(*str++);
}

void writeSerialChar(unsigned char ch) {
    usart_putc(usartNum, ch);
}

void printSerialNewline(void) {
  writeSerialChar('\r');
  writeSerialChar('\n');
}

void printlnSerialChar(char c) {
  writeSerialChar(c);
  printlnSerial();
}

void printlnSerial(const char c[]) {
  writeSerialStr(c);
  printSerialNewline();
}
