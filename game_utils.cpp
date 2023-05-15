#include"game_utils.h"

void renderBackground(int& speed, LTexture backgroundTexture, SDL_Renderer* gRenderer)
{
	speed -= BACKGROUND_SPEED;
	if(speed < -backgroundTexture.getWidth())
	{
		speed = 0;
	}
	backgroundTexture.render(speed, 0 , gRenderer);
	backgroundTexture.render(speed + backgroundTexture.getWidth(), 0, gRenderer);
}

void renderGround(int& speed, LTexture groundTexture, SDL_Renderer* gRenderer, const int speedPlus)
{
	speed -= GROUND_SPEED + speedPlus;
	if(speed < - groundTexture.getWidth())
	{
		speed = 0;
	}
	groundTexture.render(speed, GROUND_POSY , gRenderer);
	groundTexture.render(speed +groundTexture.getWidth(), GROUND_POSY, gRenderer);
}

bool checkCollisionE1(Character character, SDL_Rect* characCurrentClip, enemy enemy1)
{

	bool collide = false;

	int leftA = character.getPosX() + 30 ;
	int rightA = character.getPosX() + characCurrentClip->w - 25;
	int topA = character.getPosY();
	int bottomA = character.getPosY() + characCurrentClip->h - 20;

	int leftB = enemy1.getPosX1();
	int rightB = enemy1.getPosX1() + ENEMY_1_WIDTH;
	int topB = enemy1.getPosY1();
	int bottomB = enemy1.getPosY1() + ENEMY_1_HEIGHT;
	
    if (rightA >= leftB && leftA  <= rightB)
    {
    	if(bottomA >= topB)
    	{
    		collide = true;
    	}
    }
    return collide;
}

bool checkCollisionE2(Character character, SDL_Rect* characCurrentClip, enemy enemy2, SDL_Rect* eCurrentClip)
{
	bool collide = false;

	int leftA = character.getPosX() + 19; //14
    int rightA = character.getPosX() + characCurrentClip->w - 20 ;//20
    int topA = character.getPosY() + 12;
    int bottomA = character.getPosY() + characCurrentClip->h -15; //10

    int leftB = enemy2.getPosX2() + 9;
	int rightB = enemy2.getPosX2() + eCurrentClip->w - 1;
	int topB = enemy2.getPosY2() + 6;
	int bottomB = enemy2.getPosY2() + eCurrentClip->h - 1;

	//SDL_HasIntersection( SDL_Rect a,  SDL_Rect b)

	if(rightA >= leftB && leftA <= rightB)
	{
		
		if(topA <= bottomB && bottomA >= topB)
		{
			collide = true;
		}
	}
	return collide;
}

bool checkEnemyCollision(Character character, 
						 enemy enemy1, 
					  	 enemy enemy2, 
						 SDL_Rect* characCurrentClip, 
						 SDL_Rect* eCurrentClip)
{
	if(checkCollisionE1(character, characCurrentClip, enemy1) )
	{
		return true;
	}

	if(checkCollisionE2(character, characCurrentClip, enemy2, eCurrentClip))
	{
		return true;
	}
	return false;

}

void drawWhenLose(LTexture gameOver,LTexture endSelectionText, SDL_Event *e, SDL_Renderer *gRenderer, bool &startGame) 
{	
	bool endGame = false;
	if(!startGame) return ;
			
	while(!endGame)//vong lap de doi lua chon
	{
		while(SDL_PollEvent(e) != 0)
		{
			if(e->type == SDL_QUIT)
			{
				endGame = true;
				startGame = false;
			}
			if(e->type == SDL_KEYDOWN && e->key.repeat == 0)
			{
				if(e->key.keysym.sym == SDLK_r) 
				{   endGame = true;
					 
					startGame = true;
						 
				}	
				else if (e->key.keysym.sym == SDLK_ESCAPE)
				{
					endGame = true;
					startGame = false;
						
				}
			}
		
		}	gameOver.render( 285, 75, gRenderer);
			endSelectionText.render(170, 130, gRenderer);
			SDL_RenderPresent(gRenderer);
	}
	
}						 


std::string getHighScore()
{
	std::ifstream input;
	std::string highScore;

	input.open("best_score.txt");
	input >> highScore;

	return highScore;
}

void updateHighScore( const int& score, const std::string& oldHighScoreStringType)
{
	int oldHighScore = 0;

	std::ofstream output;
	std::string newHighScore;
	std::stringstream temp(oldHighScoreStringType);

	output.open("best_score.txt");

	temp  >> oldHighScore; // chuyen  sang int 
	if(score > oldHighScore)
	{
		oldHighScore = score;
	}
	newHighScore = std::to_string(oldHighScore);

	output << newHighScore;
	output.close();
	
}

int updateScoreAfterLoop(int& time, int& speedPlus, int& score)
{
	if(time == TIME_LIMIT )//60frame/s
	{
		speedPlus += SPEED_INCREASEMENT;
	}

	if(time > TIME_LIMIT)
	{
		time = 0;
	}
	if(time % 60 == 0)
	{
		score += SCORE_INCREASEMENT;
	}

	time += TIME_INCREASEMENT;

	return time;
}

void renderScore(LTexture gScore, LTexture scoreText, SDL_Color textColor, SDL_Renderer *gRenderer, TTF_Font *gFont1, const int& score )
{
	if(!scoreText.loadFromRenderedText("your score: ", gFont1, textColor, gRenderer));
	{
		std::cout <<"Unable to load!" << std::endl;
	}
	if(!gScore.loadFromRenderedText(std::to_string(score), gFont1, textColor, gRenderer));
	{
		std::cout <<"Unable to load!" << std::endl;
	}

	gScore.render(680, 0, gRenderer);
	scoreText.render(520, 0, gRenderer);
}

void renderHighScore(LTexture gHighScore, LTexture highScoreText, SDL_Color textColor, SDL_Renderer *gRenderer, TTF_Font *gFont1, const std::string& highScore)
{
	if(!highScoreText.loadFromRenderedText("high Score: ", gFont1, textColor, gRenderer))
	{
		std::cout <<"Unable to load!" << std::endl;
	}
	if(!gHighScore.loadFromRenderedText(highScore, gFont1, textColor, gRenderer))
	{
		std::cout <<"Unable to load!" << std::endl;
	}

	gHighScore.render(680, 25, gRenderer);
	highScoreText.render(520, 25, gRenderer);
}

bool checkInsideButton(SDL_Event* e1, const int buttonPosX, const int buttonPosY )
{
	bool inside = true;

	if(e1->type == SDL_MOUSEMOTION || e1->type == SDL_MOUSEBUTTONDOWN)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);

		if(x < buttonPosX)
		{
			inside = false;
		}

		else if( x > buttonPosX + BUTTON_WIDTH)
		{
			inside = false;
		}

		else if(y < buttonPosY)
		{
			inside = false;
		}

		else if( y > buttonPosY + BUTTON_HEIGHT)
		{
			inside = false;
		}
	}
	return inside;
}

void handleButtonPlay(SDL_Event* e1, bool &startGame, bool &quitMenu, Mix_Chunk *gClick)
{
	if(checkInsideButton(e1, buttonPosX1, buttonPosY1 ))
	{
		switch(e1->type)
		{
			case SDL_MOUSEBUTTONDOWN:
				Mix_PlayChannel(-1, gClick, 0);
				startGame = true;
				quitMenu = true;
				break;
		}
	}
}

void handleButtonExit(SDL_Event* e1, bool &startGame, bool &quitMenu, Mix_Chunk *gClick)
{
	if(checkInsideButton(e1, buttonPosX2, buttonPosY2))
	{
		switch(e1->type)
		{	
			case SDL_MOUSEBUTTONDOWN:
			Mix_PlayChannel(-1, gClick, 0);
			startGame = false;
			quitMenu = true;
			break;

		}
	}
}
