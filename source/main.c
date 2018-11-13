#include <stdio.h>
#include <stdlib.h>
#include <switch.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

SDL_Window * 	window;
SDL_Renderer * 	renderer;
SDL_Surface *	surface;
SDL_Texture * txt_texture;
SDL_Surface * txt_surface;
SDL_Rect txt_rect;
TTF_Font* font;

typedef struct 
{
	SDL_Texture * texture;
	SDL_Rect SrcR;
	SDL_Rect DestR;
}

images;
images background[1];

int main()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	TTF_Init();
	romfsInit();

	// Create an SDL window & renderer
	window = SDL_CreateWindow("Main-Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

	//BG
	surface = IMG_Load("romfs:/resources/main.png");
	background[0].texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	
	//Font
	font = TTF_OpenFont("romfs:/resources/small_font.ttf", 24);
	SDL_Color color = {0, 0, 0}; 

	//Rendering TTF_Font
	txt_surface = TTF_RenderText_Solid(font, "finally for me is june 15!", color);
	txt_texture = SDL_CreateTextureFromSurface(renderer, txt_surface);
	txt_rect.x = 10; 
	txt_rect.y = 10;
	txt_rect.w = txt_surface->w;
	txt_rect.h = txt_surface->h;

	while (appletMainLoop())
	{
		hidScanInput();
		u32 kDown = hidKeysDown(CONTROLLER_P1_AUTO);
		if (kDown & KEY_PLUS) break;

		//CLEAR
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, background[0].texture, NULL, NULL);
		SDL_RenderCopy(renderer, txt_texture, NULL, &txt_rect);
		//REFRESH
		SDL_RenderPresent(renderer);
	}
	
	TTF_Quit()				//Font cleanup
	romfsExit();				//romfs cleanup
	IMG_Quit();				//BG cleanup
	SDL_Quit();				// SDL cleanup
	return EXIT_SUCCESS; 	// Clean exit to HBMenu
	
}
