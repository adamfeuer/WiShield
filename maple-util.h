/*
 * maple-util.h
 *
 */

#ifndef MAPLE_UTIL_H_
#define MAPLE_UTIL_H_

#define USART1    1
#define USART2    2
#define USART3    3

#ifdef __cplusplus
extern "C"{
#endif

void initSerial(uint8 usartNumIn, uint32 baud);
void writeSerialStr(const char *str);
void writeSerialChar(unsigned char ch);
void printSerial(const char str[]);
void printSerialNewline(void);
void printlnSerialChar(char c);
void printlnSerial(const char c[]);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* MAPLE_UTIL_H_ */
