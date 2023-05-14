#include"LTexture.h"
#include"fun.h"

LTexture::LTexture()
{
	mTexture = NULL;

	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	free();
}

void LTexture::free()
{
	if(mTexture != NULL)
	{
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

bool LTexture::loadFromRenderedText(std::string textureText, TTF_Font *gFont, SDL_Color textColor, SDL_Renderer *gRenderer)
{
	free();

	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor );

	if(textSurface != NULL)
	{
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if(mTexture == NULL)
		{
			std::cout << "Unabled to create texture from text surface! SDl Error: " << SDL_GetError() << std::endl;

		}
		
		else
		{
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
	}
	return mTexture != NULL;
}

bool LTexture::loadFromFile(std::string path, SDL_Renderer* gRenderer)
{
	SDL_Texture *newTexture = NULL;

	SDL_Surface *loadedSurface = IMG_Load(path.c_str());
	if(loadedSurface == NULL )
	{
		std::cout << "Could not load image! SDL_image Error: " << IMG_GetError() << std::endl;
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 255, 255));

		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if(newTexture == NULL)
		{
			std::cout << "Could not create texture from image! SDL Error: " << SDL_GetError() << std::endl;

		}
		else
		{
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}


	mTexture = newTexture;
	return mTexture != NULL;
		
}

void LTexture::render(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip )
{
	SDL_Rect renderQuad = {x, y, mWidth, mHeight};

	if(clip != NULL)
		{
			renderQuad.w = clip->w;
			renderQuad.h = clip->h;
		}

		SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}
