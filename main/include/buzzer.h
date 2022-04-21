#pragma once

#include "pico.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"

#define TOP_MAX 65534

class Buzzer {

private:
	uint8_t m_pin;

	uint m_slice, m_channel;
	uint32_t m_div = 0, m_top = 0;

	int pwm_set_freq(int freq);
	int set_pwm_duty(uint32_t duty);

public:
	~Buzzer();

	void begin(uint8_t pin);
	void play(uint16_t frequency);
	void stop();

};