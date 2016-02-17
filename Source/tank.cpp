#include "tank.h"

const int JOYSTICK_DEAD_ZONE = 8000;

Tank::Tank(SDL_Renderer*renderer,int pNum, string filePath,string audioPath, float x, float y)
{
	active = true;
	playerNum = pNum;
	speed = 200.0f;
	fire = Mix_LoadWAV((audioPath + "fire.wav").c_str());
	if(playerNum == 0)
	{
		playerPath = filePath +"redTank.png";
	}
	else
	{
		playerPath = filePath + "blueTank.png";
	}
	texture = IMG_LoadTexture(renderer,playerPath.c_str());

	posRect.x = x;
	posRect.y = y;

	int w,h;
	SDL_QueryTexture(texture,NULL,NULL,&w,&h);
	posRect.w = w;
	posRect.h = h;

	pos_X = x;
	pos_Y = y;

	xDir = 0;
	yDir = 0;

	xDirOld = 1;
	yDirOld = 0;

	center.x = posRect.w/2;
	center.y = posRect.h/2;

	string bulletPath;
	if(playerNum == 0)
	{
		bulletPath = filePath +"redBullet.png";
	}else
	{
		bulletPath = filePath + "blueBullet.png";
	}

	for(int i = 0; i < 10; i++)
	{
		//TankBullet tmpBullet(renderer,bulletPath,,,);
		//add to bulletlist
		//bulletList.push_back(tmpBullet);
	}


}

void Tank::Draw(SDL_Renderer*renderer)
{
	/*
	 //draw the player's bullets
	 for(int i = 0; i < bulletList.size(); i++)
	 {
	 	 //check to see if the bullet is active
	 	   if(bulletList[i].active)
	 	   {
	 	   //Draw Bullet
	 	    bulletList[i].Draw(renderer);
	 	   }
	 }

	*/

	SDL_RenderCopyEx(renderer,texture,NULL,&posRect,tankangle,&center,SDL_FLIP_NONE);

}

void Tank::Update(float deltaTime)
{
	if(xDir != 0 || yDir != 0)
	{
		x = posRect.x - xDir;
		y = posRect.y - yDir;
		tankangle = atan2(yDir,xDir) *180/3.14;
		oldAngle = tankangle;
		xDirOld = xDir;
		yDirOld = yDir;
	}
	else
	{
		tankangle = oldAngle;
	}
}
