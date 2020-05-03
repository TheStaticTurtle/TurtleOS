#include <SDL/SDL_config.h>
#include <SDL/SDL.h>
#include <os.h>

#include "drivers/rtc.cpp"
#include "drivers/nspire.cpp"
#include "drivers/gpio.cpp"
#include "ressources.h"

#include "apps/apps_menu.cpp"
#include "apps/apps_settings.cpp"
#include "apps/apps_tools.cpp"



#define min(a,b) a<b?a:b
#define max(a,b) a>b?a:b

class UI {
	public:
		UI() {
		}

		SDL_Surface *screen;
		nSDL_Font *font_large;
		nSDL_Font *font_normal;

		RTC *rtc;
		NSPIRE *nspire;

		AppMenu     *appMenu;
		AppSettings *appSettings;
		AppTools	*appTools;

		void init() {
			if(SDL_Init(SDL_INIT_VIDEO) ==-1) {
				printf("Couldn't initialize SDL: %s\n", SDL_GetError());
				exit(EXIT_FAILURE);
			}

			screen = SDL_SetVideoMode(320, 240, has_colors ? 16 : 8, SDL_SWSURFACE);
			if(screen == NULL) {
				printf("Couldn't initialize display: %s\n", SDL_GetError());
				SDL_Quit();
				exit(EXIT_FAILURE);
			}

			rtc = new RTC();
			nspire = new NSPIRE();

			font_large = nSDL_LoadFont(NSDL_FONT_THIN, 200, 200, 200);
			font_normal = nSDL_LoadFont(NSDL_FONT_TINYTYPE, 25, 43, 61);

			appMenu = new AppMenu(screen);
			appSettings = new AppSettings(screen);
			appTools = new AppTools(screen);
			// SDL_ShowCursor(SDL_DISABLE);

		}

		void draw_top_bar() {
			Uint16 barHeight = 24;

			/* 
			 *	Title
			 */
			char title[10] = "TurtleOS";
			SDL_Rect rect = {0, 0, 320, barHeight};
			SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 35, 35, 35));
			nSDL_DrawString(
				screen,
				font_large,
				SCREEN_WIDTH/2 - nSDL_GetStringWidth(font_large, title)/2,
				barHeight/2 - nSDL_GetStringHeight(font_large, title)/2,
				title
			);

			/* 
			 *	Time
			 */
			char current_time[10];
			time_t t = rtc->read_rtc();
			tm* your_tm = localtime(&t);
			strftime(current_time, sizeof(current_time), "%H:%M:%S", your_tm);
			nSDL_DrawString(
				screen,
				font_large,
				SCREEN_WIDTH - nSDL_GetStringWidth(font_normal, current_time) - 24,
				barHeight/2 - nSDL_GetStringHeight(font_normal, current_time)/2,
				current_time
			);

			/* 
			 *	Battery
			 */

			if(nspire->is_charging()) {
				SDL_Rect pos = {304, (Sint16)(barHeight/2 - 8), 16, 16};
				SDL_BlitSurface(nSDL_LoadImage(image_charging), NULL, screen, &pos);

			} else {
				int percentage = nspire->get_charge_percentage();

				SDL_Rect batrect = {310, 4, 7, (Uint16)(barHeight-4-4)};
				SDL_FillRect(screen, &batrect, SDL_MapRGB(screen->format, 255, 255, 255));

				SDL_Rect batirect = {311, 5, 5, (Uint16)(barHeight-5-5)};
				SDL_FillRect(screen, &batirect, SDL_MapRGB(screen->format, 0, 0, 0));

				int k = (barHeight-6-6) * percentage / 100;
				int h = 6 + (barHeight-6*2) - k;
				SDL_Rect lvelrect = {312, (Sint16)h, 3, (Uint16)k};

				if(percentage>80) {
					SDL_FillRect(screen, &lvelrect, SDL_MapRGB(screen->format, 0, 255, 0));
				} else if(percentage<=80 && percentage>15) {
					SDL_FillRect(screen, &lvelrect, SDL_MapRGB(screen->format, 255, 255, 0));
				} else if(percentage<=15 && percentage>0) {
					SDL_FillRect(screen, &lvelrect, SDL_MapRGB(screen->format, 255, 0, 0));
				}
			}
		}

		void handle_keydown(SDLKey key) {
			if(key == SDLK_MENU) {
				current_app = 0;
				clear_screen();
				re_init_apps();
			}
			switch(current_app) {
				case 4:
					appSettings -> handle_key_down_event(key);
					return;
				default:
					break;
			}
			switch(key) {
				case SDLK_UP:
					break;
				case SDLK_DOWN:
					break;
				case SDLK_LEFT:
					if(current_app==0) apps_menu_selection--;
					if(apps_menu_selection<0) apps_menu_selection = 0;
					break;
				case SDLK_RIGHT:
					if(current_app==0) apps_menu_selection++;
					if(apps_menu_selection>4) apps_menu_selection = 4;
					break;
				case SDLK_RETURN:
				case SDLK_KP_ENTER: /* This corresponds to the "click button" on the TI-Nspire. */
					if(current_app==0) current_app = apps_menu_selection;
					clear_screen();
					re_init_apps();
					break;
				case SDLK_MENU:
					current_app = 0;
					clear_screen();
					re_init_apps();
				default:
					break;
			}
		}

		void clear_screen() {
			SDL_Rect pos = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
			SDL_FillRect(screen, &pos, SDL_MapRGB(screen->format, 0,0,0));
		}

		void scratchpad() {
			((void(*)(void))0x1022FBE0)();
			void * t = ((void * (*)(void))0x10007368)();
			((void(*)(void *))0x1002EA20)(t);
		}

		void re_init_apps() {
			switch(current_app) {
				case 0:
					appSettings -> close();
					appTools    -> close();
					appMenu     -> init();
					break;
				case 1:
					scratchpad();
					break;
				case 3:
					appSettings -> close();
					appTools    -> init();
					appMenu     -> close();
					break;
				case 4:
					appMenu     -> close();
					appTools    -> close();
					appSettings -> init();
					break;
			}
		}

		void redraw() {
			clear_screen();
			draw_top_bar();
			switch(current_app) {
				case 0:
					appMenu->draw(apps_menu_selection);
					break;
				case 3:
					appTools->draw();
					break;
				case 4:
					appSettings->draw();
					break;
			}
			SDL_Flip(screen);
		}

	private:
		int current_app = 0; //0=Main menu
		int apps_menu_selection = 0;

		uint16_t map(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max) {
			return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
		}
};