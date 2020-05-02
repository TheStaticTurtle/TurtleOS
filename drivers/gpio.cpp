#include <os.h>

#ifndef GPIO_INCLUDED
#define GPIO_INCLUDED

#define GPIO_SEC_0 (uint32_t) 0x90000000
#define GPIO_SEC_1 (uint32_t) 0x90000040
#define GPIO_SEC_2 (uint32_t) 0x90000080
#define GPIO_SEC_3 (uint32_t) 0x900000C0
#define GPIO_DIRECTION_BIT (uint32_t) 0x10
#define GPIO_OUT_BIT (uint32_t) 0x14
#define GPIO_IN_BIT (uint32_t) 0x18

#define ADC_RAW_INT (uint32_t) 0xC4000004
#define ADC_ENA_INT (uint32_t) 0xC4000008

#define ADC_CHAN_0 (uint32_t) 0xC4000100
#define ADC_CHAN_1 (uint32_t) 0xC4000120
#define ADC_CHAN_2 (uint32_t) 0xC4000140
#define ADC_CHAN_3 (uint32_t) 0xC4000160
#define ADC_CHAN_4 (uint32_t) 0xC4000180
#define ADC_CHAN_5 (uint32_t) 0xC40001A0
#define ADC_CHAN_6 (uint32_t) 0xC40001C0

class GPIO {
	public:
		static const int INPUT = 0;
		static const int OUTPUT = 1;

		static const bool HIGH = true;
		static const bool LOW  = false;

		GPIO() {
		}

		void pinMode(int pin, int dir) {
			if(pin<0 || pin>31) return;
			if(dir > 1 || dir <0) return;

			volatile uint32_t* ptr = get_section_ptr_from_pin(pin,GPIO_DIRECTION_BIT);
			int BIT = get_bit_from_pin(pin);

			if(dir == GPIO::OUTPUT){
				*ptr &= ~(1<<BIT);
			}

			if(dir == GPIO::INPUT){
				*ptr |= 1<<BIT;
			}

		}

		void digitalWrite(int pin, bool value) {
			if(pin<0 || pin>31) return;
			pinMode(pin,GPIO::OUTPUT);

			volatile  uint32_t* ptr = get_section_ptr_from_pin(pin,GPIO_OUT_BIT);
			uint32_t BIT = get_bit_from_pin(pin);

			if(value){
				*ptr |= 1<<BIT;
			} else {
				*ptr &= ~(1<<BIT);
			}

		}

		bool digitalRead(int pin) {
			if(pin<0 || pin>31) return false;
			pinMode(pin,GPIO::INPUT);

			volatile  uint32_t* ptr = get_section_ptr_from_pin(pin,GPIO_IN_BIT);
			uint32_t BIT = get_bit_from_pin(pin);

			return (*ptr>>BIT)&0x1;
		}

		double analogRead(int channel) {
			if(channel<0 || channel>4) return false;

			volatile unsigned int *rawinterrupt = (volatile unsigned int*) 0xC4000004; // https://hackspire.org/index.php?title=Memory-mapped_I/O_ports_on_CX#C4000000_-_Analog-to-Digital_Converter_.28ADC.29
			volatile unsigned int *enableinterrupts = (volatile unsigned int*) 0xC4000008;


			volatile uint32_t* start_ptr = get_section_ptr_from_analog_channel(channel,0x00);
			volatile uint32_t* read_ptr  = get_section_ptr_from_analog_channel(channel,0x10);

			// volatile unsigned int *start_ptr = (volatile unsigned int*) 0xC4000140;
			// volatile unsigned int *read_ptr = (volatile unsigned int*) 0xC4000150;

			volatile uint32_t* peripherals  = (volatile uint32_t*) 0x900B0018; 
			volatile uint32_t* peripherals2 = (volatile uint32_t*) 0x900B0020;
			*peripherals = 0;
			*peripherals2 = 0;


			unsigned int intmask = *enableinterrupts;
			
			*enableinterrupts = 0x0;
			*rawinterrupt = 0xFFFFFFFF;
			
			unsigned int prevstart = *start_ptr;
			
			msleep(5);
			
			*peripherals = 0;
			*peripherals2 = 0;
			*rawinterrupt = 0xFFFFFFFF;
			*start_ptr = 0b1;
			
			msleep(5);
			
			*rawinterrupt = 0xFFFFFFFF;
			unsigned int tmp = *read_ptr;

			*peripherals = 0;
			*peripherals2 = 0;
			
			*enableinterrupts = intmask;
			
			*start_ptr = prevstart;


			return convert_adc_to_volt(channel,tmp); 
		}

	private:
		double convert_adc_to_volt(int channel, uint32_t value) {
			switch(channel) {
				case 1:
					return (double) value / (double) 155;
				case 2:
					return (double) value / (double) 155;
				default:
					return (double) value / (double) 310;
			}

		}
		uint32_t* get_section_ptr_from_analog_channel(int channel,int offset) {
			switch(channel) {
				case 0:
					return (uint32_t*)(ADC_CHAN_0+offset);
				case 1:
					return (uint32_t*)(ADC_CHAN_1+offset);
				case 2:
					return (uint32_t*)(ADC_CHAN_2+offset);
				case 3:
					return (uint32_t*)(ADC_CHAN_3+offset);
				case 4:
					return (uint32_t*)(ADC_CHAN_4+offset);
				case 5:
					return (uint32_t*)(ADC_CHAN_5+offset);
				case 6:
					return (uint32_t*)(ADC_CHAN_6+offset);
			}
			return (uint32_t*)(ADC_CHAN_0+offset);
		}

		uint32_t* get_section_ptr_from_pin(int pin,int offset) {
			switch((int)floor(pin/8)) {
				case 0:
					return (uint32_t*)(GPIO_SEC_0+offset);
				case 1:
					return (uint32_t*)(GPIO_SEC_1+offset);
				case 2:
					return (uint32_t*)(GPIO_SEC_2+offset);
				case 3:
					return (uint32_t*)(GPIO_SEC_3+offset);
			}
			return (uint32_t*)(GPIO_SEC_2+offset);
		}
		uint32_t get_bit_from_pin(int pin) {
			return pin % 8;
		}
};

#endif