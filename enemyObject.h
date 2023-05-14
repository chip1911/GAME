#ifndef ENEMY_H_
#define ENEMY_H_

#include"fun.h"
#include"LTexture.h"

#define RANGE_POSX 150
#define FLY_MAX_HEIGHT 235  
#define RANGE_FLY_Y 75 //pham vi bay y

class enemy
{
public:
	enemy();

	~enemy();

	void renderE1(LTexture enemy1Texture, SDL_Renderer* gRenderer);

	void renderE2(LTexture enemy2Texture, SDL_Renderer* gRenderer, SDL_Rect* currentClip);

	void move(const int &speedPlus);

	void resetEnemy1();

	void resetEnemy2();

	int getPosX1();

	int getPosY1();

	int getPosX2();

	int getPosY2();


	// int GetWidth();

	// int GetHeight();
private:

	//catus
	int posX1, posY1;
	int e1Width, e1Height;

	//fly
	int posX2, posY2;
	int e2Width, e2Height;

};
#endif
