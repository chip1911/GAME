#include"enemyObject.h"

enemy::enemy()
{
	//cactus
	posX1 =  850;
	posY1 = charGround - 7;
	e1Width = ENEMY_1_WIDTH;
	e1Height = ENEMY_1_HEIGHT;

	//fly
	 posX2 = 1100; 
	 posY2 =  rand() % RANGE_FLY_Y + FLY_MAX_HEIGHT;
	 e2Width = ENEMY_2_WIDTH;
	 e2Height = ENEMY_2_HEIGHT;
}

enemy::~enemy()
{
	posX1 = 0;
	posY1 = 0;
	e1Width = 0;
	e1Height = 0;

	posX2 = 0;
	posY2 = 0;
	e2Width = 0;
	e2Height = 0;


}

void enemy::renderE1(LTexture enemy1Texture, SDL_Renderer* gRenderer)
{
	enemy1Texture.render(posX1, posY1, gRenderer);
}

void enemy::renderE2(LTexture enemy2Texture, SDL_Renderer* gRenderer, SDL_Rect* currentClip)
{
	enemy2Texture.render(posX2, posY2, gRenderer,currentClip );
}

void enemy::move(const int &speedPlus)
{
	posX1 -=  (ENEMY_SPEED + speedPlus);
	posX2 -=  (ENEMY_SPEED + speedPlus);

	if(posX1 + ENEMY_1_WIDTH < 0 )
	{
		posX1 = rand() % RANGE_POSX + SCREEN_WIDTH; // screenWidth -> screenWidth + 100
	}

	if(posX2 + ENEMY_2_WIDTH < 0 )
	{
		posX2 = rand() % (SCREEN_WIDTH + RANGE_POSX) + SCREEN_WIDTH;
		posY2 =  rand() % RANGE_FLY_Y + FLY_MAX_HEIGHT ;
	}


} 

void enemy::resetEnemy1()
{
	posX1 =  850;
	posY1 = charGround - 7;
	e1Width = ENEMY_1_WIDTH;
	e1Height = ENEMY_1_HEIGHT;
}

void enemy::resetEnemy2()
{
	posX2 = 1100; 
	posY2 =  rand() % RANGE_FLY_Y + FLY_MAX_HEIGHT;
	e2Width = ENEMY_2_WIDTH;
	e2Height = ENEMY_2_HEIGHT;
}

int enemy::getPosX1()
{
	return posX1;
}

int enemy::getPosY1()
{
	return posY1;
}

int enemy::getPosX2()
{
	return posX2;
}

int enemy::getPosY2()
{
	return posY2;
}

