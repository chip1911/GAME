#include"fun.h"
#include"LTexture.h"
#include"Character.h"
#include"enemyObject.h"
#include"game_utils.h"


bool init();
bool loadMedia();
void close();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
TTF_Font* gFont = NULL;
TTF_Font* gFont1 = NULL;
SDL_Color textColor = { 0, 0, 0 , 255};

LTexture menuTexture;
LTexture backgroundTexture;
LTexture groundTexture;
LTexture characterTexture;
LTexture enemy1Texture;
LTexture enemy2Texture;//fly
LTexture enemy3Texture; //ufo
LTexture gameOverText;
LTexture endSelectionText;
LTexture gScore;
LTexture scoreText ;
LTexture gHighScore;
LTexture highScoreText;

Mix_Music *gMusic = NULL;

Mix_Chunk *gJump = NULL;
Mix_Chunk *gGameOver = NULL;
Mix_Chunk *gClick = NULL;

SDL_Rect e2Clips[ FLY_FRAMES ];
SDL_Rect characterClips[ RUN_FRAMES ];

Character character;
enemy enemy1;
enemy enemy2;
enemy enemy3;

const std::string WINDOW_TITLE = "DINO GAME";

bool init()
{
	bool success = true;
	if( SDL_Init(SDL_INIT_VIDEO || SDL_INIT_AUDIO ) < 0)
	{
		std::cout << "Could not initialize SDL and SDL_mixer! SDL Error: " << SDL_GetError() << std::endl;
		success = false;
	}
	else
	{
		//create window
		if( !SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			std::cout << "Warning: Linear texture filtering not enabled! " << std::endl;	
		}	

		//create window
		gWindow = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(gWindow == NULL)
		{
			std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if(gRenderer == NULL)
			{
				std::cout<< "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if( !(IMG_Init( imgFlags ) & imgFlags ) )
				{
					std::cout << "Can not initialize SDL_image! SDL_image Error: " << IMG_GetError() << std::endl;
					success = false;
				}

				if( Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError()<< std::endl ;
					success = false;
				}

				if(TTF_Init() == -1 )
				{
					std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
					success = false;
				}

			}
		}		   
	}
	return success;
}

bool loadMedia()
{
	bool success = true;
	if( !menuTexture.loadFromFile( "img/menu.png" , gRenderer) )
	{
		std::cout << "Failed to load image!\n" ;
		success = false;
	}


	if( !backgroundTexture.loadFromFile( "img/pre.png" , gRenderer) )
	{
		std::cout << "Failed to load image!\n" ;
		success = false;
	}

	if( !characterTexture.loadFromFile( "img/char.png" , gRenderer) )
	{
		std::cout << "Failed to load image!\n" ;
		success = false;
	}
	else
	{
				characterClips[0].x = 57 * 0;
				characterClips[0].y = 0;
				characterClips[0].w = 57;
				characterClips[0].h = 57;

				characterClips[1].x = 57 * 1;
				characterClips[1].y = 0;
				characterClips[1].w = 57;
				characterClips[1].h = 57;

				characterClips[2].x = 57 * 2;
				characterClips[2].y = 0;
				characterClips[2].w = 57;
				characterClips[2].h = 57;

				characterClips[3].x = 57 * 3;
				characterClips[3].y = 0;
				characterClips[3].w = 57;
				characterClips[3].h = 57;

				characterClips[4].x = 57 * 4;
				characterClips[4].y = 0;
				characterClips[4].w = 57;
				characterClips[4].h = 57;

				characterClips[5].x = 57 * 5;
				characterClips[5].y = 0;
				characterClips[5].w = 57;
				characterClips[5].h = 57;

	}

	if( !enemy1Texture.loadFromFile( "img/cactus.png" , gRenderer) )
	{
		std::cout << "Failed to load image!\n" ;
		success = false;
	}

	

	if( !enemy2Texture.loadFromFile( "img/fly.png", gRenderer ) )
	{
		std::cout << "Failed to load image!\n" ;
		success = false;
	}
	else
	{
		//Set sprite clips
		e2Clips[ 0 ].x =   0;
		e2Clips[ 0 ].y =   0;
		e2Clips[ 0 ].w =  36;
		e2Clips[ 0 ].h = 30;

		e2Clips[ 1 ].x =  36;
		e2Clips[ 1 ].y =   0;
		e2Clips[ 1 ].w =  36;
		e2Clips[ 1 ].h = 30;
		
	}

	if( !enemy3Texture.loadFromFile( "img/ufo.png" , gRenderer) )
	{
		std::cout << "Failed to load image!\n" ;
		success = false;
	}

	if( !groundTexture.loadFromFile( "img/ground.png", gRenderer ) )
	{
		std::cout << "Failed to load image!\n" ;
		success = false;
	}

	gFont = TTF_OpenFont("font/fontgame.ttf", 50);
	if(gFont == NULL)
	{
		std::cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() <<std::endl;
		success = false;
	}
	else
	{
		 
		if(!gameOverText.loadFromRenderedText("game over",  gFont, textColor, gRenderer))
		{
			std::cout <<"Unable to render!" << std::endl;
			success = false;
		}
		

	}

	gFont1 = TTF_OpenFont("font/fontgame.ttf", 30);
	if(gFont1 == NULL)
	{
		std::cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() <<std::endl;
		success = false;
	}
	else
	{
		
		if(!endSelectionText.loadFromRenderedText("press esc to exit or r to continue!",  gFont1, textColor, gRenderer))
		{
			std::cout <<"Unable to load!" << std::endl;
			success = false;
		}
		
	}

	gMusic = Mix_LoadMUS("music/music.wav");
	if(gMusic == NULL)
	{
		std::cout << "Failed to load music! SDL_mixer Error: " << Mix_GetError() << std::endl;
		success = false;
	}

	gJump = Mix_LoadWAV("music/Jump.wav");
	if(gJump == NULL)
	{
		std::cout << "Failed to load sound effect! SDL_mixer Error: " << Mix_GetError() << std::endl;
		success = false;
	}


	gGameOver = Mix_LoadWAV("music/Cat_Meow.wav");
	if(gGameOver == NULL)
	{
		std::cout << "Failed to load sound effect! SDL_mixer Error: " << Mix_GetError() << std::endl;
		success = false;
	}

	gClick = Mix_LoadWAV("music/click.wav");
	if(gClick == NULL)
	{
		std::cout << "Failed to load sound effect! SDL_mixer Error: " << Mix_GetError() << std::endl;
		success = false;
	}

	

	return success;
}

void close()
{
	backgroundTexture.free();
	groundTexture.free();
	characterTexture.free();
	enemy1Texture.free();
	enemy2Texture.free();
	enemy3Texture.free();
	gameOverText.free();
	endSelectionText.free();
	gScore.free();
	scoreText.free() ;
	gHighScore.free();
	highScoreText.free();

	Mix_FreeChunk(gJump);
	Mix_FreeChunk(gGameOver);
	Mix_FreeChunk(gClick);
	gJump = NULL;
	gGameOver = NULL;
	gClick = NULL;

	Mix_FreeMusic(gMusic);
	gMusic = NULL;

	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	Mix_Quit();
}


int main( int argc, char* args[])
{
	if(!init())
	{
		std::cout << "Failed to initialize!\n";
	}
	else
	{

		if(!loadMedia())
		{
			std::cout << "Failed to load media!\n";
		}
		else
		{
			bool startGame = false;
			bool quitMenu = false;
			SDL_Event e1;
			while(!quitMenu)
			{
				
				while(SDL_PollEvent(&e1) != 0)
				{
					if(e1.type == SDL_QUIT)
					{
						quitMenu = true;
						startGame = false;
					}
					
					handleButtonPlay(&e1, startGame, quitMenu, gClick);
					handleButtonExit(&e1, startGame, quitMenu, gClick);
				}

				menuTexture.render(0, 0, gRenderer);
				SDL_RenderPresent(gRenderer);
			}

			while(startGame)
			{
				bool quit = false;

				srand(time(NULL));
				SDL_Event e;
				int frame = 0;
				int frame1 = 0;
				
				int speedBackground = 0;
				int speedGround = 0;
				int time = 0;
				int score = 0;
				int speedPlus = 0;
				std::string highScore = getHighScore();
				enemy1.resetEnemy1();
				enemy2.resetEnemy2();
				enemy3.resetEnemy3();
				character.resetCharacter();
				
			
				while( !quit)
				{	
					updateScoreAfterLoop(time, speedPlus, score);
					if( Mix_PlayingMusic() == 0 )
						{
							//Play the music
							Mix_PlayMusic( gMusic, -1 );
						}
					while( SDL_PollEvent( &e ) != 0)
					{
						if(e.type == SDL_QUIT )
						{
							quit = true;
							startGame = false;
						}

						if(e.type == SDL_KEYDOWN && e.key.repeat == 0)
					    {
						   switch(e.key.keysym.sym)
						   {
						   		case SDLK_SPACE:
						   		Mix_PlayChannel(-1, gJump, 0);
						   		break;
						   }
					    }
						character.handleEvent(e);
					}

					SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
					SDL_RenderClear( gRenderer );
					
					renderBackground(speedBackground, backgroundTexture,  gRenderer);

					renderGround(speedGround, groundTexture, gRenderer, speedPlus);

					
					enemy1.move(speedPlus);
					enemy1.renderE1(enemy1Texture, gRenderer);

					SDL_Rect* eCurrentClip = &e2Clips[frame1 / 8];
					enemy2.move(speedPlus);
					enemy2.renderE2(enemy2Texture, gRenderer, eCurrentClip);

					
					enemy3.moveE3(speedPlus);
					enemy3.renderE3(enemy3Texture, gRenderer);

					//enemy3Texture.render(300, 315, gRenderer);
					character.move();
					SDL_Rect* characCurrentClip = &characterClips[ frame / 4];

					if(character.onGround())
					{
						characCurrentClip = &characterClips[frame / 4];
						character.render(characterTexture, characCurrentClip, gRenderer);
					}

					else
					{
						characCurrentClip = &characterClips[0];
						character.render(characterTexture, characCurrentClip, gRenderer);
					}
					//renderScore(timeText, timer,  gRenderer, gFont1, scoreText );
					//renderScore(  timer,  gRenderer,  gFont1,  scoreText ,  bestScoreText);
					 renderScore( gScore,  scoreText,  textColor, gRenderer, gFont1, score );
					 renderHighScore( gHighScore,  highScoreText, textColor, gRenderer, gFont1, highScore);

					if(checkEnemyCollision(character, 
						 enemy1, 
					  	 enemy2,
					  	 enemy3, 
						 characCurrentClip, 
						 eCurrentClip))
					{
						
						
						updateHighScore( score, highScore);
						Mix_HaltMusic();
						Mix_PlayChannel(-1, gGameOver, 0);
						quit = true;
					}
					
					
					
					SDL_RenderPresent( gRenderer );

					++frame;
					++frame1;
					if(frame / 4 >= RUN_FRAMES )
					{
						frame = 0;
					}
					if(frame1 / 8 >= FLY_FRAMES)
					{
						frame1 = 0;
					}
			
				}
				
				drawWhenLose( gameOverText,endSelectionText, &e, gRenderer, startGame );
			}
			
		}
	}		
			

		
			
	close();
	return 0;
}


