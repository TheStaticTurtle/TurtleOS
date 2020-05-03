#include <os.h>

#ifndef RTC_INCLUDED
#define RTC_INCLUDED


#define RTC_READ  (uint32_t) 0x90090000
#define RTC_WRITE (uint32_t) 0x90090008

class RTC {
	public:
		RTC() {
		}

		time_t read_rtc() {
			return *(volatile uint32_t*)(RTC_READ);
		}

		void write_rtc(int hour, int minutes, int seconds, int day, int month, int year) {
			struct tm  tm;
			time_t rawtime;
			time (&rawtime);
			tm = *localtime ( &rawtime );
			tm.tm_year = year - 1900;
			tm.tm_mon = month - 1;
			tm.tm_mday = day;
			tm.tm_hour = hour;
			tm.tm_min = minutes;
			tm.tm_sec = seconds;
			*(volatile uint32_t*)(RTC_WRITE) = mktime(&tm);
		}
};

#endif