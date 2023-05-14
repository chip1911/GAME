#ifndef CHARACTER_H_
#define CHARACTER_H_

#include"fun.h"
#include"LTexture.h"

#define ON_THE_GROUND 0
#define JUMP 1
#define JUMP_DOWN -1

class Character
{
public:
	
    Character();
	
	bool onGround();

	void handleEvent( SDL_Event& e);

	void move();

	void render(LTexture characterTexture , SDL_Rect* currentClip, SDL_Renderer *gRenderer);
	
	void resetCharacter();

	int getPosX() {return posX;}
	int getPosY() {return posY;}


private:
	int posX, posY;

	int velY;

	int status; 
	


};

#endif