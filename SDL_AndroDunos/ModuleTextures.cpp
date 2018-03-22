#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"

#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )

ModuleTextures::ModuleTextures() : Module()
{
	for (int i = 0; i < MAX_TEXTURES; i++)
		textures[i] = nullptr;
}

// Destructor
ModuleTextures::~ModuleTextures()
{}

// Called before render is available
bool ModuleTextures::Init()
{
	LOG("Init Image library");
	bool ret = true;

	// load support for the PNG image format
	int flags = IMG_INIT_PNG;
	int init = IMG_Init(flags);

	if((init & flags) != flags)
	{
		LOG("Could not initialize Image lib. IMG_Init: %s", IMG_GetError());
		ret = false;
	}

	return ret;
}

// Called before quitting
bool ModuleTextures::CleanUp()
{
	LOG("Freeing textures and Image library");

	for (int i = 0; i < MAX_TEXTURES; i++) {
		if (textures[i] != nullptr)
			SDL_DestroyTexture(textures[i]);
	}

	IMG_Quit();
	return true;
}

// Load new texture from file path
SDL_Texture* const ModuleTextures::Load(const char* path)
{
	SDL_Surface* texture = IMG_Load(path);
	int i, j=0;
	bool loop = true;
	if (texture == 0) LOG("Error loading texture", IMG_GetError());

	for (i = 0; i < MAX_TEXTURES; ++i) { //search where can create a texture, when the texture is loaded leaves loop
		if (textures[i] == nullptr) {
			textures[i] = SDL_CreateTextureFromSurface(App->render->renderer, texture);
			j = i;
			i = MAX_TEXTURES;
		}
	}
	if (textures[j] == NULL) LOG("Error creating texture from surface", SDL_GetError());

	SDL_FreeSurface(texture);
	return textures[j];
}
