/*******************

Example program showcasing the appropriate usage
sfw features. This library is SUPER TINY and
NOT featureful. It is intended for education
use only.

It attempts to provide the simplest openGL
context and drawing options possible.

author: Esmeralda Salamone, esmes@aie.edu.au

********************/
#include <iostream>
#include "Box.h"
#include "sfwdraw.h"

const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 800;
const float PLAYER_SPEED = 1000;
int Score[2];

void main()
{

	Score[1] = 0;
	Score[2] = 0;
	bool Xflip = false;
	bool Yflip = false;
	//first we need to initialize our graphics context- or window.
	sfw::initContext(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong 2.0");
	struct Player
	{
		float tempX;
		float tempY;
	};
	
	Player you;
	you.tempX = 50;
	you.tempY = 400;// Player position
	Player him;
	him.tempX = 1120;
	him.tempY = 400;
	float ball_tempX = 600, ball_tempY = 400; // position
	float Bxacc = 0, Byacc = 0;	  // Ball acceleration
	float Bxvel = 0, Byvel = 0;	  // Ball velocity
	float speed = 100;

	// then we need to update our buffers, poll for input, etc.
	while (sfw::stepContext())
	{
		// we haven't covered frame independent movement yet,
		// but we'll use some euler integration
		// we also haven't gotten into vector math yet,
		// so we'll use cardinal speeds 
		ball_tempX += Bxvel * sfw::getDeltaTime();
		ball_tempY += Byvel * sfw::getDeltaTime();

		//Player collision / input

		if (sfw::getKey('w')) you.tempY -= PLAYER_SPEED*sfw::getDeltaTime();
		if (sfw::getKey('s')) you.tempY += PLAYER_SPEED*sfw::getDeltaTime();

		if (sfw::getKey('i')) him.tempY -= PLAYER_SPEED*sfw::getDeltaTime();
		if (sfw::getKey('k')) him.tempY += PLAYER_SPEED*sfw::getDeltaTime();

		if (ball_tempX < you.tempX + PADDLE_WIDTH && ball_tempX > you.tempX && 
			ball_tempY < you.tempY + PADDLE_HEIGHT && ball_tempY > you.tempY)
		{
			ball_tempX = you.tempX + PADDLE_WIDTH + 5;
			Bxvel = -Bxvel;
			Xflip = !Xflip;

		}
		
		if (ball_tempX < him.tempX + PADDLE_WIDTH && ball_tempX > him.tempX &&
			ball_tempY < him.tempY + PADDLE_HEIGHT && ball_tempY > him.tempY)
		{
			ball_tempX = him.tempX - 5;
			Bxvel = -Bxvel;
			Xflip = !Xflip;

		}
		
		


		//Borders
		if (ball_tempY < 0)
		{
			ball_tempY = 10;
			Byvel = -Byvel;
			Yflip = !Yflip;
		}
		if (ball_tempY > 800) 
		{
			ball_tempY = 790;
			Byvel = -Byvel;
			Yflip = !Yflip;
		}
		if (ball_tempX > 1200)
		{
			ball_tempX = 600;
			ball_tempY = 400;
			Bxvel = -Bxvel;
			Xflip = !Xflip;
			Score[2] += 1;
		}
		if (ball_tempX < 0) 
		{
			ball_tempX = 600;
			ball_tempY = 400;
			Bxvel = -Bxvel;
			Xflip = !Xflip;
			Score[1] += 1;
		}
		if (you.tempY < 0) you.tempY = 1;
		if (you.tempY + PADDLE_HEIGHT > 800) you.tempY = 799 - PADDLE_HEIGHT;

		if (him.tempY < 0) him.tempY = 1;
		if (him.tempY + PADDLE_HEIGHT > 800) him.tempY = 799 - PADDLE_HEIGHT;
		// base acceleration on the keypress
		Byacc = Bxacc = 0;
		if (Xflip == true)
		{
			Bxacc = speed;
		}
		else
		{
			Bxacc = -speed;
		}
		if (Yflip == true)
		{
			Byacc = speed;
		}
		else
		{
			Byacc = -speed;
		}

		// end game
		if (Score[1] == 5 || Score[2] == 5)
		{
			sfw::termContext();
		}

		// more euler integration 
		Bxvel += Bxacc * sfw::getDeltaTime();
		Byvel += Byacc * sfw::getDeltaTime();
		

		Box::drawPlayer(you.tempX, you.tempY);
		Box::drawPlayer(him.tempX, him.tempY);
		sfw::drawCircle(ball_tempX, ball_tempY, 10);

		sfw::drawLine(5, 5, 5, SCREEN_HEIGHT - 5);
		sfw::drawLine(5, 5, SCREEN_WIDTH - 5, 5);

		sfw::drawLine(SCREEN_WIDTH - 5, SCREEN_HEIGHT - 5, 5, SCREEN_HEIGHT - 5);
		sfw::drawLine(SCREEN_WIDTH - 5, SCREEN_HEIGHT - 5, SCREEN_WIDTH - 5, 5);
	}
	
	//finally, we need to properly shut stuff down.
	sfw::termContext();
}