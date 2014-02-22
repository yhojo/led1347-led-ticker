/*
===============================================================================
 Name        : main.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC13Uxx.h"
#endif

#include <cr_section_macros.h>

// LEDのポート番号と、ピン番号を定義
#define LED_PORT 0
#define LED_PIN 1

void gpio_init() {
	// GPIOドメインの電源を入れる
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6);
}

/**
 * GPIOのピンの入出力方向を設定する。
 */
void gpio_set_dir(int port, int pin, int do_output) {
	if (do_output) {
		LPC_GPIO->DIR[port] |= (1 << pin);
	} else {
		LPC_GPIO->DIR[port] &= ~(1 << pin);
	}
}

/**
 * GPIOの特定ピンの出力内容を設定する。
 */
void gpio_set_output(int port, int pin, int enable) {
    if (enable) {
    	LPC_GPIO->SET[port] = (1 << pin);
    } else {
    	LPC_GPIO->CLR[port] = (1 << pin);
    }
}

int main(void) {
	// GPIOの初期化
	gpio_init();
	// LED用のGPIOピンを出力に設定
	gpio_set_dir(LED_PORT, LED_PIN, 1);

	// LEDの次の出力状態を保持する変数
	int led_on = 0;
    // Enter an infinite loop
    while(1) {
        // led_onに合わせてLEDを点灯したり消灯したりする
    	gpio_set_output(LED_PORT, LED_PIN, led_on);
        // led_onの状態を反転する
        led_on = !led_on;

        // ちょっと待つ
        for (long i = 0; i < 1000000; i++) {
        }
    }
    return 0;
}
