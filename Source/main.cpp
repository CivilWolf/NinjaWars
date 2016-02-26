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

#include "tank.h"
#include "turret.h"


#if defined(__APPLE__)
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include "SDL2_mixer/SDL_mixer.h"
#include "SDL2_ttf/SDL_ttf.h"
string currentWorkingDirectory(getcwd(NULL,0));
string images_dir = currentWorkingDirectory +"/Resources/Images/";
string audio_dir = currentWorkingDirectory +"/Resources/Audio/";

#endif
#if defined(_WIN32)||(_WIN64)
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <direct.h>
#define getcwd _getcwd

string currentWorkingDirectory(getcwd(NULL,0));
string images_dir = currentWorkingDirectory + "\\Resources\\Images\\";
string audio_dir = currentWorkingDirectory +"\\Resources\\Audio\\";




#endif
#if defined(__linux__)
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"

#include <unistd.h>

string currentWorkingDirectory(getcwd(NULL,0));
string images_dir = currentWorkingDirectory +"/Resources/Images/";
string audio_dir = currentWorkingDirectory + "/Resources/Audio/";

#endif

int main(int argc, char *argv[])
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
	Mix_Music *bgm = Mix_LoadMUS((audio_dir + "background.wav").c_str());

	if(!Mix_PlayingMusic())
	{
		Mix_PlayMusic(bgm,-1);
	}

	//Create Players - Start
	Tank tank1 = Tank(renderer,0,images_dir.c_str(),audio_dir.c_str(),50.0f,50.0f);

	//CreateTurrets - Start
	Turret turret1 = Turret(renderer,images_dir.c_str(),audio_dir.c_str(),800.0f,500.0f);

	Turret turret2 = Turret(renderer,images_dir.c_str(),audio_dir.c_str(),1600.0f,250.0f);
	Turret turret2 = Turret(renderer,images_dir.c_str(),audio_dir.c_str(),400.0f,1000.0f);
	Turret turret2 = Turret(renderer,images_dir.c_str(),audio_dir.c_str(),1600.0f,1250.0f);

	SDL_Texture *bkgd = IMG_LoadTexture(renderer)
	//

	while(!quit)
	{
		thisTime = SDL_GetTicks();
		deltaTime= (float)(thisTime - lastTime)/ 1000;
		lastTime = thisTime;

		//cout << currentWorkingDirectory;
		while(SDL_PollEvent(&e) !=0)
		{
			if(e.type == SDL_QUIT)
			{
				quit = true;
			}

			switch(e.type)
			{
			case SDL_CONTROLLERBUTTONDOWN:
				if(e.cdevice.which == 0)
				{
					if(e.cbutton.button == SDL_CONTROLLER_BUTTON_A)
					{
						tank1.OnControllerButton(e.cbutton);
						break;
					}
				}
			break;

			case SDL_CONTROLLERAXISMOTION:
				tank1.OnControllerAxis(e.caxis);
				break;
			}

		} // end Poll Events
		// ********** Start Update Process**************
		tank1.Update(deltaTime);

		// *********** Start the SDL Draw Process **************
		SDL_RenderClear(renderer);
		//draw the player's tank
		tank1.Draw(renderer);
		//cout << audio_dir << endl;
		//Draw Turret
		turret1.Draw(renderer);
		//present new buffer to the screen
		SDL_RenderPresent(renderer);
	}// end Main Loop
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}


