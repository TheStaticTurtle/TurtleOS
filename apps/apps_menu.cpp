#include <SDL/SDL_config.h>
#include <SDL/SDL.h>
#include <os.h>
#include "../ressources.h"

#ifndef APPS_MENU_INCLUDED
#define APPS_MENU_INCLUDED

class AppMenu {
	public:
		AppMenu(SDL_Surface *s) {
			screen = s;
		}

		void init() {
			if(isinit) return;
		}
		
		void close() {
			if(!isinit) return;
		}
		
		void draw_app_bar(int apps_menu) {
			SDL_Rect pos;
			SDL_Rect rec;
			SDL_Rect rec2;
			Sint16 sep = 16;
			Sint16 y = 240 - 48 - sep/2;
			Sint16 x = sep/2;

			pos = {x, y, 48, 48};
			rec = {x-2, y-2, 52, 52};
			rec2 = {x-1, y-1, 50, 50};
			if(apps_menu == 0) SDL_FillRect(screen, &rec2, SDL_MapRGB(screen->format, 0, 0, 0));
			if(apps_menu == 0) SDL_FillRect(screen, &rec,  SDL_MapRGB(screen->format, 255, 255, 255));
			else               SDL_FillRect(screen, &rec,  SDL_MapRGB(screen->format, 0, 0, 0));

			SDL_BlitSurface(nSDL_LoadImage(image_calc), NULL, screen, &pos);
			x += 48 + sep;

			pos = {x, y, 48, 48};
			rec = {x-2, y-2, 52, 52};
			rec2 = {x-1, y-1, 50, 50};
			if(apps_menu == 1) SDL_FillRect(screen, &rec2, SDL_MapRGB(screen->format, 0, 0, 0));
			if(apps_menu == 1) SDL_FillRect(screen, &rec,  SDL_MapRGB(screen->format, 255, 255, 255));
			else               SDL_FillRect(screen, &rec,  SDL_MapRGB(screen->format, 0, 0, 0));
			SDL_BlitSurface(nSDL_LoadImage(image_internet), NULL, screen, &pos);
			x += 48 + sep;

			pos = {x, y, 48, 48};
			rec = {x-2, y-2, 52, 52};
			rec2 = {x-1, y-1, 50, 50};
			if(apps_menu == 2) SDL_FillRect(screen, &rec2, SDL_MapRGB(screen->format, 0, 0, 0));
			if(apps_menu == 2) SDL_FillRect(screen, &rec,  SDL_MapRGB(screen->format, 255, 255, 255));
			else               SDL_FillRect(screen, &rec,  SDL_MapRGB(screen->format, 0, 0, 0));
			SDL_BlitSurface(nSDL_LoadImage(image_messages), NULL, screen, &pos);
			x += 48 + sep;

			pos = {x, y, 48, 48};
			rec = {x-2, y-2, 52, 52};
			rec2 = {x-1, y-1, 50, 50};
			if(apps_menu == 3) SDL_FillRect(screen, &rec2, SDL_MapRGB(screen->format, 0, 0, 0));
			if(apps_menu == 3) SDL_FillRect(screen, &rec,  SDL_MapRGB(screen->format, 255, 255, 255));
			else               SDL_FillRect(screen, &rec,  SDL_MapRGB(screen->format, 0, 0, 0));
			SDL_BlitSurface(nSDL_LoadImage(image_tools), NULL, screen, &pos);
			x += 48 + sep;

			pos = {x, y, 48, 48};
			rec = {x-2, y-2, 52, 52};
			rec2 = {x-1, y-1, 50, 50};
			if(apps_menu == 4) SDL_FillRect(screen, &rec2, SDL_MapRGB(screen->format, 0, 0, 0));
			if(apps_menu == 4) SDL_FillRect(screen, &rec,  SDL_MapRGB(screen->format, 255, 255, 255));
			else               SDL_FillRect(screen, &rec,  SDL_MapRGB(screen->format, 0, 0, 0));
			SDL_BlitSurface(nSDL_LoadImage(image_settings), NULL, screen, &pos);
			x += 48 + sep;
		}

		void draw(int apps_menu) {
			draw_app_bar(apps_menu);
		}

	private:
		SDL_Surface* screen;
		bool isinit = false;
};

#endif