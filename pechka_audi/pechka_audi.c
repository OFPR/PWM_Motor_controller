/*
 * pechka_audi.c
 *
 * Created: 26.10.2016 2:52:40
 *  Author: OFPR
 *	MCU: Attiny13
 *  4.8MHZ, Fuses: lf=0x79 hf=ff
 */ 

#include <avr/io.h>
#include <avr/iotn13.h>
void setup(void)
{
	DDRB = 0x01;
	PORTB = 0x1F;
	// Set to 'Fast PWM' mode
	TCCR0A = (1 << WGM01) | (1 << WGM00);
	
}

void PWM(uint8_t val)
{
	if (val != 0)
	{
		// Set OC0A output on compare match, upwards counting.
		TCCR0A |= (1 << COM0A1)|(1 << COM0A0);
		OCR0A = val;
		TCCR0B = 1<<CS00; // PWM freq 18750Hz 
	} 
	else
	{
		OCR0A = 0;
		TCCR0A &= ~((1 << COM0A1)| (1<< COM0A0));
		TCCR0B = 0x00;
	}
}
void delay(uint16_t de)
{
	while (!(de == 0))
	{
		de--;
	}
}

int main(void)
{
	setup();
    while(1)
    {
		if (!(PINB & 0x10)){
			PWM(255); // 100%
		}
		else if (!(PINB & 0x08)){
			PWM(192); // 75%
		}
		else if (!(PINB & 0x04)){
			PWM(128); // 50%
		}
		else if (!(PINB & 0x02)){
			PWM(64); // 25%
		}
		else{
			PWM(0); //Off
			PORTB |= 1<<0;
		};		
		delay(16318);
    }
}