#include <SDL/SDL_config.h>
#include <SDL/SDL.h>
#include <os.h>
#include "../drivers/rtc.cpp"
#include "../ressources.h"

#ifndef APPS_SETTINGS_INCLUDED
#define APPS_SETTINGS_INCLUDED

class AppSettings {
	public:
		AppSettings(SDL_Surface *s) {
			rtc = new RTC();
			screen = s;
		}

		void init() {
			if(isinit) return;
		}

		void close() {
			if(!isinit) return;
		}

		void setDateUI() {
			time_t t = rtc->read_rtc();
			tm* your_tm = localtime(&t);


			int hour    = your_tm->tm_hour;
			int minutes = your_tm->tm_min;
			int seconds = your_tm->tm_sec;

			int day     = your_tm->tm_mday;
			int month   = your_tm->tm_mon +1;
			int year    = your_tm->tm_year + 1900;

			int result  = 1;

			result = show_msgbox_2b("Choose", "Are you sure to change de date / time", "YES", "NO");
			if(result == 2) return;
			result = show_1numeric_input("What date is it?", "Enter the year", "Year: ", &year, 1970, 9999);
			if(result == 0) return;
			result = show_2numeric_input("What date is it?", "Enter the date", "Month: ", &month, -2, 24, "Day: ", &day, -2, 59);
			if(result == 0) return;
			result = show_2numeric_input("What time is it?", "Enter the time", "Hours: ", &hour, -2, 24, "Minutes: ", &minutes, -2, 59);
			if(result == 0) return;

			rtc->write_rtc(hour, minutes, seconds, day, month, year);
		}

		void handle_key_down_event(SDLKey key) {
			switch(key) {
				case SDLK_UP:
					break;
				case SDLK_DOWN:
					break;
				case SDLK_LEFT:
					current_selection--;
					if(current_selection<0) current_selection = 0;
					break;
				case SDLK_RIGHT:
					current_selection++;
					if(current_selection>1) current_selection = 1;
					break;
				case SDLK_KP_ENTER: /* This corresponds to the "click button" on the TI-Nspire. */
				case SDLK_RETURN:
					switch(current_selection) {
						case 0:
							setDateUI();
							break;
						default:
							break;
					}
					break;
				case SDLK_ESCAPE:
					break;
				default:
					break;
			}
		}

		void draw_selection() {
			SDL_Rect pos;
			SDL_Rect rec;
			SDL_Rect rec2;
			Sint16 sep = 16;
			Sint16 y = 24 + sep/2;
			Sint16 x = sep/2;

			pos = {x, y, 48, 48};
			rec = {x-2, y-2, 52, 52};
			rec2 = {x-1, y-1, 50, 50};
			if(current_selection == 0) SDL_FillRect(screen, &rec2, SDL_MapRGB(screen->format, 0, 0, 0));
			if(current_selection == 0) SDL_FillRect(screen, &rec,  SDL_MapRGB(screen->format, 255, 255, 255));
			else                       SDL_FillRect(screen, &rec,  SDL_MapRGB(screen->format, 0, 0, 0));
			SDL_BlitSurface(nSDL_LoadImage(image_clock), NULL, screen, &pos);
			x += 48 + sep;
		}

		void draw() {
			draw_selection();
		}
	private:
		RTC *rtc;
		SDL_Surface* screen;
		bool isinit = false;
		int current_selection = 0;
};

#endif