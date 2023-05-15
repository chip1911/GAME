#include"enemyObject.h"

enemy::enemy()
{
	//cactus
	posX1 =  850;
	posY1 = charGround - 7;
	

	//fly
	 posX2 = 1100; 
	 posY2 =  rand() % RANGE_FLY_Y + FLY_MAX_HEIGHT;

	 posX3 = SCREEN_WIDTH + 3500;
	 posY3 = 318 ;
	 
}

enemy::~enemy()
{
	posX1 = 0;
	posY1 = 0;
	

	posX2 = 0;
	posY2 = 0;
	
	posX3 = 0;
	posY3 = 0;

}

void enemy::renderE1(LTexture enemy1Texture, SDL_Renderer* gRenderer)
{
	enemy1Texture.render(posX1, posY1, gRenderer);
}

void enemy::renderE2(LTexture enemy2Texture, SDL_Renderer* gRenderer, SDL_Rect* currentClip)
{
	enemy2Texture.render(posX2, posY2, gRenderer,currentClip );
}

void enemy::renderE3(LTexture enemy3Texture, SDL_Renderer* gRenderer)
{
	enemy3Texture.render(posX3, posY3, gRenderer);
}

void enemy::move(const int &speedPlus)
{
	posX1 -=  (ENEMY_SPEED + speedPlus);
	posX2 -=  (ENEMY_SPEED + speedPlus);
	

	if(posX1 + ENEMY_1_WIDTH < 0 )
	{
		posX1 = rand() % RANDOM_POSX_CACTUS + SCREEN_WIDTH; // screenWidth -> screenWidth + 50
	}

	if(posX2 + ENEMY_2_WIDTH < 0 )
	{
		posX2 = rand() % RANDOM_POSX_FLY + SCREEN_WIDTH;
		posY2 =  rand() % RANGE_FLY_Y + FLY_MAX_HEIGHT ;
	}

	

} 

void enemy::moveE3(const int &speedPlus)
{
	posX3 -=  2*ENEMY_SPEED + speedPlus / 2;

	if(posX3 +  ENEMY_3_WIDTH < 0)
	{
		posX3 = rand() % (2500 + SCREEN_WIDTH) + (SCREEN_WIDTH + 1500) ;
		posY3 = 318 ;
	}

}

void enemy::resetEnemy1()
{
	posX1 =  850;
	posY1 = charGround - 7;
	
}

void enemy::resetEnemy2()
{
	posX2 = 1100; 
	posY2 =  rand() % RANGE_FLY_Y + FLY_MAX_HEIGHT;
	
}

void enemy::resetEnemy3()
{
	 posX3 = SCREEN_WIDTH + 3500;
	 posY3 = posY3 = 318 ;
	
}


