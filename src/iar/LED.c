#include "LED.h"
enum LED_Pin {
  LED_Pin_GREEN = GPIO_Pin_12,
  LED_Pin_RED = GPIO_Pin_13,
  LED_Pin_ORANGE = GPIO_Pin_14,
  LED_Pin_BLUE = GPIO_Pin_15,
} LED_Pin;

LED_InitStructure LEDS;
void LED_Init(void) {
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  LEDS.IO_PORT_LEDS = GPIOD;
  LEDS.IO_PIN_LED_RED = LED_Pin_RED;
  LEDS.IO_PIN_LED_GREEN = LED_Pin_GREEN;
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = LEDS.IO_PIN_LED_RED | LEDS.IO_PIN_LED_GREEN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_Init(LEDS.IO_PORT_LEDS, &GPIO_InitStructure);
}

void LED_GreenOn(void) {
  GPIO_SetBits(LEDS.IO_PORT_LEDS, LEDS.IO_PIN_LED_GREEN);
}
void LED_GreenOff(void) {
  GPIO_ResetBits(LEDS.IO_PORT_LEDS, LEDS.IO_PIN_LED_GREEN);
}

void LED_RedOn(void) { LED_Set_RED(&LEDS); }

void LED_RedOff(void) { LED_Reset_RED(&LEDS); }

void LED_OrangeOn(void) {}

void LED_OrangeOff(void) {}

void LED_BlueOn(void) {}

void LED_BlueOff(void) {}

void KT1On(void) { GPIO_SetBits(GPIOC, GPIO_Pin_9); }

void KT1Off(void) { GPIO_ResetBits(GPIOC, GPIO_Pin_9); }

void LED_Reset_RED(LED_InitStructure *Init) {
  GPIO_ResetBits(Init->IO_PORT_LEDS, Init->IO_PIN_LED_RED);
}

void LED_Set_RED(LED_InitStructure *Init) {
  GPIO_SetBits(Init->IO_PORT_LEDS, Init->IO_PIN_LED_RED);
}
