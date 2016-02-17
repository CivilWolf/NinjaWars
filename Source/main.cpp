#include <iostream>
#include <stdio.h>
#include <string>
#include <stdint.h>

using namespace std;
const int SCREEN_WIDTH = 1024;

const int SCREEN_HEIGHT = 768;

float deltaTime = 0.0;
int thisTime = 0;
int lastTime = 0;


#if defined(__APPLE__)
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "SDL2_mixer/SDL_mixer.h"
#include "SDL2_ttf/SDL_ttf.h"
string currentWorkingDirectory(getcwd(NULL,0));
string images_dir = currentWorkingDirectory +"/source/";
string audio_dir = currentWorkingDirectory +"/source/";

#endif
#if defined(_WIN32)||(_WIN64)
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <direct.h>
#define getcwd _getcwd

string currentWorkingDirectory(getcwd(NULL,0));
string images_dir = currentWorkingDirectory + "\\source\\";
string audio_dir = currentWorkingDirectory +"\\source\\";




#endif
#if defined(__linux__)
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"

#include <unistd.h>

string currentWorkingDirectory(getcwd(NULL,0));
string images_dir = currentWorkingDirectory +"/source/";
string audio_dir = currentWorkingDirectory +"/source/";

#endif

int main()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *window = NULL;
	SDL_Renderer*renderer = NULL;
	window = SDL_CreateWindow("Tank Wars!",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			SCREEN_WIDTH,SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

	//********Create SDL WINDOW
	bool quit = false;

	SDL_Event e;

	//****** variable creation -end****

	SDL_GameControllerEventState(SDL_ENABLE);
	SDL_GameController* gGameController0 = NULL;
	gGameController0 = SDL_GameControllerOpen(0);
	Mix_OpenAudio(4410,MIX_DEFAULT_FORMAT,2,2048);
	Mix_Music *bgm = Mix_LoadMUS((audio_dir + "background.mp3").c_str());

	if(!Mix_PlayingMusic())
	{
		Mix_PlayMusic(bgm,-1);
	}
	while(!quit)
	{
		thisTime = SDL_GetTicks();
		deltaTime= (float)(thisTime - lastTime)/ 1000;
		lastTime = thisTime;


		while(SDL_PollEvent(&e) !=0)
		{
			if(e.type == SDL_QUIT)
			{
				quit = true;
			}
		} // end Poll Events
		// ********** Start Update Process**************
		// *********** Start the SDL Draw Process **************


	}// end Main Loop
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;



	return 0;
}


