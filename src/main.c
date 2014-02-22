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

int main(void) {
	// GPIOドメインの電源を入れる
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6);
	// LED用のGPIOピンを出力に設定
	LPC_GPIO->DIR[LED_PORT] |= (1 << LED_PIN);

	// LEDの次の出力状態を保持する変数
	int led_on = 0;
    // Enter an infinite loop, just incrementing a counter
    while(1) {
        // led_onに合わせてLEDを点灯したり消灯したりする
        if (led_on) {
        	// 点灯する
        	LPC_GPIO->SET[LED_PORT] = (1 << LED_PIN);
        } else {
        	// 消灯する
        	LPC_GPIO->CLR[LED_PORT] = (1 << LED_PIN);
        }
        // led_onの状態を反転する
        led_on = !led_on;

        // ちょっと待つ
        for (long i = 0; i < 1000000; i++) {
        }
    }
    return 0;
}
