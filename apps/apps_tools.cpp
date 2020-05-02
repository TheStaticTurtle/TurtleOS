#include <SDL/SDL_config.h>
#include <SDL/SDL.h>
#include <os.h>
#include "../drivers/gpio.cpp"
#include "../ressources.h"

#ifndef APPS_TOOLS_INCLUDED
#define APPS_TOOLS_INCLUDED

class AppTools {
	public:
		AppTools(SDL_Surface *s) {
			gpios = new GPIO();
			screen = s;
		}

		void init() {
			if(isinit) return;
		}

		void close() {
			if(!isinit) return;
		}

		void writeText(int line, char* text) {
			nSDL_Font *font = nSDL_LoadFont(NSDL_FONT_TINYTYPE, 255, 255, 255);
			int h = nSDL_GetStringHeight(font, text);

			nSDL_DrawString(
				screen,
				font,
				5,
				(h+2)*line + 24,
				text
			);
		}
		void displayGPIOS() {
			char buf[24];

			sprintf(buf,"GPIO0  = %d",gpios->digitalRead(0));
			writeText(1,buf);
			sprintf(buf,"GPIO4  = %d",gpios->digitalRead(4));
			writeText(2,buf);
			sprintf(buf,"GPIO22 = %d",gpios->digitalRead(22));
			writeText(3,buf);
			sprintf(buf,"GPIO26 = %d",gpios->digitalRead(26));
			writeText(4,buf);
			sprintf(buf,"GPIO15 = %d",gpios->digitalRead(15));
			writeText(5,buf);
			sprintf(buf,"GPIO16 = %d",gpios->digitalRead(16));
			writeText(6,buf);

			for (int i = 0; i < 6; ++i) {
				sprintf(buf,"ADC%d = %4f",i,gpios->analogRead(i));
				writeText(8+i,buf);
			}
		}

		void handle_key_down_event(SDLKey key) {
			switch(key) {
				case SDLK_UP:
					break;
				case SDLK_DOWN:
					break;
				case SDLK_LEFT:
					break;
				case SDLK_RIGHT:
					break;
				case SDLK_KP_ENTER: /* This corresponds to the "click button" on the TI-Nspire. */
				case SDLK_RETURN:
					break;
				case SDLK_ESCAPE:
					break;
				default:
					break;
			}
		}

		void draw() {
			displayGPIOS();
		}
	private:
		GPIO *gpios;
		SDL_Surface* screen;
		bool isinit = false;
};

#endif