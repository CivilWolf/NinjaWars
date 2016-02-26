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
		TankBullet tmpBullet(renderer,bulletPath,-1000,-1000,0,0);
		///add to bulletlist
		bulletList.push_back(tmpBullet);
	}


}

void Tank::Draw(SDL_Renderer*renderer)
{

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
	pos_X += (speed*xDir)*deltaTime;
	pos_Y += (speed *yDir)*deltaTime;
	posRect.x = (int)(pos_X + 0.5f);
	posRect.y = (int)(pos_Y + 0.5f);


	if(posRect.x < 0)
	{
		posRect.x < 0;
		pos_X = posRect.x;
	}

	if(posRect.x > 1024 - posRect.w)
	{
		posRect.x = 1024 - posRect.w;
		pos_X = posRect.x;
	}
	if(posRect.y < 0)
	{
		posRect.y = 0;
		pos_Y = posRect.y;
	}
	if(posRect.y > 768 - posRect.h)
	{
		posRect.y = 768 - posRect.h;
		pos_Y = posRect.y;
	}
	//Update the tank's bullets
	for(int i = 0; i < bulletList.size();i++)
	{
		if(bulletList[i].active)
		{
			bulletList[i].Update(deltaTime);
		}
	}

}
void Tank::OnControllerAxis(const SDL_ControllerAxisEvent event)
{
	if(event.which == 0 && playerNum == 0)
		{
			if(event.axis == 0)
			{
				if(event.value < -JOYSTICK_DEAD_ZONE)
				{
					xDir = -1.0f;
				}
				else if(event.value > JOYSTICK_DEAD_ZONE)
				{
					xDir = 1.0f;
				}
				else
				{
					xDir = 0.0f;
				}
			}
			if(event.axis == 1)
			{
				if(event.value < -JOYSTICK_DEAD_ZONE)
				{
					yDir = -1.0f;
				}
				else if(event.value > JOYSTICK_DEAD_ZONE)
				{
					yDir = 1.0f;
				}
				else
				{
					yDir = 0.0f;
				}
			}
		}
	if(event.which == 1 && playerNum == 1)
	{
		if(event.axis == 0)
		{
			if(event.value < -JOYSTICK_DEAD_ZONE)
			{
				xDir = -1.0f;
			}
			else if(event.value > JOYSTICK_DEAD_ZONE)
			{
				xDir = 1.0f;
			}
			else
			{
				xDir = 0.0f;
			}
		}
		if(event.axis == 1)
		{
			if(event.value < -JOYSTICK_DEAD_ZONE)
			{
				yDir = -1.0f;
			}
			else if(event.value > JOYSTICK_DEAD_ZONE)
			{
				yDir = 1.0f;
			}
			else
			{
				yDir = 0.0f;
			}
		}
	}

}
void Tank::OnControllerButton(const SDL_ControllerButtonEvent event)
{
	if(event.which == 0 && playerNum == 0)
	{
		if(event.button == 0)
		{
			CreateBullet();
		}
	}
	if(event.which == 1 && playerNum == 1)
	{
		if(event.button == 0)
		{
			CreateBullet();
		}
	}
}
void Tank::CreateBullet()
{
	for(int i = 0; i< bulletList.size();i++)
	{
		if(bulletList[i].active == false)
		{
			Mix_PlayChannel(-1,fire,0);

			bulletList[i].active = true;

			bulletList[i].posRect.x = (posRect.x + (posRect.w/2));
			bulletList[i].posRect.y = (posRect.y + (posRect.h/2));
			bulletList[i].posRect.x = bulletList[i].posRect.x - (bulletList[i].posRect.w/2);
			bulletList[i].posRect.y = bulletList[i].posRect.y - (bulletList[i].posRect.h/2);
			bulletList[i].pos_X = bulletList[i].posRect.x;
			bulletList[i].pos_Y = bulletList[i].posRect.y;

			if(xDir != 0 || yDir != 0)
			{
				bulletList[i].xDir = xDirOld;
				bulletList[i].yDir = yDirOld;
			}
			else
			{
				bulletList[i].xDir = xDirOld;
				bulletList[i].yDir = yDirOld;
			}
			break;
		}
	}
}
