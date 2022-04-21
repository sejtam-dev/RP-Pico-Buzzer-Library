#include "buzzer_test.h"

Buzzer buzzer;

int main()
{
	buzzer.begin(17);

	while(true)
	{
		buzzer.play(NOTE_E5);
		sleep_ms(500);

		buzzer.play(NOTE_A1);
		sleep_ms(500);

		buzzer.stop();

		sleep_ms(500);
		buzzer.play(NOTE_G6);
		sleep_ms(500);

		buzzer.play(NOTE_A6);
		sleep_ms(500);

		buzzer.play(NOTE_C6);
		sleep_ms(500);
	}
}