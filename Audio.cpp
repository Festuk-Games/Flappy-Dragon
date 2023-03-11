#include "Audio.h"

Audio::Audio()
{
	for (int i = 0; i < MAX_FX; ++i)
		fx[i] = nullptr;
}

Audio::~Audio()
{

}

bool Audio::Init()
{
	SDL_Log("Loading Audio Mixer");
	bool ret = true;


	//todo 2: Init SDL audio subsystem.

	if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
	{
		SDL_Log("SDL EVENTS Could not initialize. SDL_Error %s\n", Mix_GetError());
		ret = false;
	}

	// load support for the OGG format
	int flags = MIX_INIT_OGG;
	int init = Mix_Init(flags);

	if ((init & flags) != flags)
	{
		SDL_Log("Could not initialize Mixer lib. Mix_Init: %s", Mix_GetError());
		ret = false;
	}

	//todo 3: Take a look at this code.
	if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		SDL_Log("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		ret = false;
	}

	return ret;
}

bool Audio::PlayMusic(const char* path, float fade_time)
{
	bool ret = true;

	if (music != NULL)
	{
		if (fade_time > 0.0f)
		{
			Mix_FadeOutMusic((int)(fade_time * 1000.0f));
		}
		else
		{
			Mix_HaltMusic();
		}

		// this call blocks until fade out is done
		Mix_FreeMusic(music);
	}

	music = Mix_LoadMUS(path);

	if (music == NULL)
	{
		SDL_Log("Cannot load music %s. Mix_GetError(): %s\n", path, Mix_GetError());
		ret = false;
	}
	else
	{
		if (fade_time > 0.0f)
		{
			if (Mix_FadeInMusic(music, -1, (int)(fade_time * 1000.0f)) < 0)
			{
				SDL_Log("Cannot fade in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
		else
		{
			if (Mix_PlayMusic(music, -1) < 0)
			{
				SDL_Log("Cannot play in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
	}

	SDL_Log("Successfully playing %s", path);
	return ret;
}

bool Audio::CleanUp()
{
	SDL_Log("Freeing sound FX, closing Mixer and Audio subsystem");

	if (music != NULL)
	{
		Mix_FreeMusic(music);
	}

	for (int i = 0; i < MAX_FX; ++i)
		if (fx[i] != nullptr)
			Mix_FreeChunk(fx[i]);

	Mix_CloseAudio();
	Mix_Quit();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
	return true;
}

// Load WAV
int Audio::LoadFx(const char* path)
{
	int ret = 0;
	Mix_Chunk* chunk = Mix_LoadWAV(path);

	if (chunk == nullptr)
	{
		SDL_Log("Cannot load wav %s. Mix_GetError(): %s", path, Mix_GetError());
	}
	else
	{
		fx[last_fx] = chunk;
		ret = last_fx++;
	}

	return ret;
}

// UnLoad WAV
bool Audio::UnLoadFx(int id)
{
	bool ret = false;

	if (fx[id] != nullptr)
	{
		Mix_FreeChunk(fx[id]);
		fx[id] = nullptr;
		ret = true;
	}

	return ret;
}

// Play WAV
bool Audio::PlayFx(unsigned int id, int repeat)
{
	bool ret = false;

	if (fx[id] != nullptr)
	{
		Mix_PlayChannel(-1, fx[id], repeat);
		ret = true;
	}

	return ret;
}