#ifndef GAME_UTILS_H_
#define GAME_UTILS_H_

#include"fun.h"
#include"enemyObject.h"
#include"Character.h"
#include"LTexture.h"
#include"LTimer.h"

void renderBackground(int& speed, LTexture backgroundTexture, SDL_Renderer* gRenderer);

void renderGround(int& speed, LTexture groundTexture, SDL_Renderer* gRenderer, const int speedPlus);

bool checkCollisionE1(Character character, SDL_Rect* characCurrentClip, enemy enemy1);

bool checkCollisionE2(Character character, SDL_Rect* characCurrentClip, enemy enemy2, SDL_Rect* eCurrentClip);

bool checkEnemyCollision(Character character, 
						 enemy enemy1, 
					  	 enemy enemy2, 
						 SDL_Rect* characCurrentClip, 
						 SDL_Rect* eCurrentClip);
void drawWhenLose(LTexture gameOver, LTexture endSelectionText,SDL_Event *e,SDL_Renderer *gRenderer, bool &startGame);	

std::string getHighScore(std::string path);

void updateHighScore(std::string path, const int& score, const std::string& oldHighScore1);

int updateScoreAfterLoop(int& time, int& speedPlus, int& score);

void renderScore(LTexture gScore, LTexture scoreText, SDL_Color textColor, SDL_Renderer *gRenderer, TTF_Font *gFont1, const int& score );
void renderHighScore(LTexture gHighScore, LTexture highScoreText, SDL_Color textColor, SDL_Renderer *gRenderer, TTF_Font *gFont1, const std::string& highScore);

bool checkInsideButton(SDL_Event* e1, const int buttonPosX, const int buttonPosY );

void handleButtonPlay(SDL_Event* e1, bool &startGame, bool &quitMenu, Mix_Chunk *gClick);
void handleButtonExit(SDL_Event* e1, bool &startGame, bool &quitMenu, Mix_Chunk *gClick);


#endif