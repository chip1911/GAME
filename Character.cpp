#include"Character.h"

Character::Character() 
{
	posX = 200;
	posY = charGround;

	velY = 7;
	status = ON_THE_GROUND; // on the ground = 0 jump = 1
}

bool Character::onGround()
{
	return posY == charGround;
}


void Character::handleEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0 && e.key.keysym.sym == SDLK_SPACE)
	{
		if (onGround())
		{
					
		    status = JUMP;
		    return ;
		}
			
		
	}
}


void Character::move()
{
	if(status == JUMP && posY >= JUMP_MAX_HEIGHT )
	{
		posY += -velY ;
	}
	if(posY <= JUMP_MAX_HEIGHT)
	{
		status = JUMP_DOWN; //jump down = -1
	}

	if(status == JUMP_DOWN && posY < charGround)
	{
		posY += velY;
	}
}

void Character::render(LTexture characterTexture, SDL_Rect* currentClip, SDL_Renderer *gRenderer)
{
	characterTexture.render(posX, posY, gRenderer, currentClip);
}
void Character::resetCharacter()
{
	posX = 200;
	posY = charGround;

	status = ON_THE_GROUND;
}

