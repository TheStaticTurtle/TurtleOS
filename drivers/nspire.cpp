#include <os.h>
#include "gpio.cpp"

#ifndef NSPIRE_INCLUDED
#define NSPIRE_INCLUDED


// #define RTC_READ  (uint32_t) 0x90090000
#define POWMAN_WTF (uint32_t) 0x900B0028  
#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))


class NSPIRE {
	public:
		GPIO *gpios;
		NSPIRE() {
			gpios = new GPIO();
		}

		bool is_charging() {
			return false;
		}
		int get_charge_percentage() {
			return volt_to_percentage(gpios->analogRead(2));
			// return batteryAvgCalc(volt_to_percentage(gpios->analogRead(2)));
		}

	private:
		int batteryAvg;
		size_t batteryAvg_count;
		int batteryAvgCalc(int newVal) {
			double scaling = 1. / (double)(batteryAvg_count + 1);
			double tmp = newVal * scaling + batteryAvg * (1. - scaling);
			batteryAvg_count++;
			if(batteryAvg_count > 200) batteryAvg_count =0;
			return (int)tmp;
		}

		// THIS IS A CALULATION FOR LIPOs (See. https://blog.ampow.com/lipo-voltage-chart/)
		int volt_to_percentage(double value) {
			if(value >= 4.18) return 100;
			if(value >= 4.15) return  95;
			if(value >= 4.11) return  90;
			if(value >= 4.08) return  85;
			if(value >= 4.02) return  80;
			if(value >= 3.98) return  75;
			if(value >= 3.95) return  70;
			if(value >= 3.91) return  65;
			if(value >= 3.87) return  60;
			if(value >= 3.85) return  55;
			if(value >= 3.84) return  50;
			if(value >= 3.82) return  45;
			if(value >= 3.80) return  40;
			if(value >= 3.79) return  35;
			if(value >= 3.77) return  30;
			if(value >= 3.75) return  25;
			if(value >= 3.73) return  20;
			if(value >= 3.71) return  15;
			if(value >= 3.69) return  10;
			if(value >= 3.61) return   5;
			return 0;
		}
};

#endif