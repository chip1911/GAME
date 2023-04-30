#include"fun.h"
#include"LTexture.h"

bool init();
bool loadMedia();
void close();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
LTexture loadbackground;

const std::string WINDOW_TITLE = "Dino game";

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

	if( !loadbackground.loadFromFile( "img/Full-Background.png" , gRenderer) )
	{
		printf( "Failed to load walking animation texture!\n" );
		success = false;
	}
	return success;
}

void close()
{
	loadbackground.free();

	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
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
			bool quit = false;

			SDL_Event e;

			while( !quit)
			{
				while( SDL_PollEvent( &e ) != 0)
				{
					if(e.type == SDL_QUIT )
					{
						quit = true;
					}
				}

				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				loadbackground.render(0, 0, gRenderer);

				SDL_RenderPresent( gRenderer );
			}
		}
	}
	close();
	return 0;
}