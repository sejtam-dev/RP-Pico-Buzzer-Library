#include "buzzer.h"



Buzzer::~Buzzer()
{
    stop();
}

void Buzzer::begin(uint8_t pin)
{
    this->m_pin = pin;

    gpio_set_function(this->m_pin, GPIO_FUNC_PWM);

    this->m_slice = pwm_gpio_to_slice_num(this->m_pin);
    this->m_channel = pwm_gpio_to_channel(this->m_pin);

}

void Buzzer::play(uint16_t frequency)
{
    stop();

    pwm_set_freq(frequency);
    pwm_set_wrap(this->m_slice, this->m_top);
    set_pwm_duty(32767);
}

void Buzzer::stop()
{
    pwm_set_enabled(this->m_slice, false);
}

int Buzzer::pwm_set_freq(int freq)
{
    // Set the frequency, making "top" as large as possible for maximum resolution.
    this->m_div = (uint32_t)(16 * clock_get_hz(clk_sys) / (uint32_t)freq);
    this->m_top = 1;
    for (;;) {
        // Try a few small prime factors to get close to the desired frequency.
        if (this->m_div >= 16 * 5 && this->m_div % 5 == 0 && this->m_top * 5 <= TOP_MAX) {
            this->m_div /= 5;
            this->m_top *= 5;
        }
        else if (this->m_div >= 16 * 3 && this->m_div % 3 == 0 && this->m_top * 3 <= TOP_MAX) {
            this->m_div /= 3;
            this->m_top *= 3;
        }
        else if (this->m_div >= 16 * 2 && this->m_top * 2 <= TOP_MAX) {
            this->m_div /= 2;
            this->m_top *= 2;
        }
        else {
            break;
        }
    }

    if (this->m_div < 16) {
        this->m_div = 0;
        this->m_top = 0;
        return -1; // freq too large
    }

    if (this->m_div >= 256 * 16) {
        this->m_div = 0;
        this->m_top = 0;
        return -2; // freq too small
    }

    return 0;
}

int Buzzer::set_pwm_duty(uint32_t duty)
{
    // Set duty cycle.
    uint32_t cc = duty * (this->m_top + 1) / 65535;

    pwm_set_chan_level(this->m_slice, this->m_channel, cc);
    pwm_set_enabled(this->m_slice, true);

    return 0;
}