#include "AudioManager.h"

AudioManager* AudioManager::audio = nullptr;

AudioManager::AudioManager()
{
	const Uint8 mixFlags{ MIX_INIT_MP3 | MIX_INIT_OGG };
	if (!(Mix_Init(mixFlags) & mixFlags)) throw "Error: SDL:MixerInit";
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1) throw "SDL_Mixer wasn't able to initialize";
}

AudioManager::~AudioManager()
{
	Mix_CloseAudio();
	Mix_Quit();
}

void AudioManager::LoadSoundtrack(const Soundtrack& audio)
{
	Mix_Music* soundtrack{ Mix_LoadMUS(audio.path.c_str()) };
	if (!soundtrack) throw "Audio was unable to load correctly";

	Mix_FadeInMusic(soundtrack, -1, 5000);
	Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
}

void AudioManager::PauseMusic()
{
	Mix_PauseMusic();
}

void AudioManager::ResumeMusic()
{
	Mix_ResumeMusic();
}

int AudioManager::PausedMusic()
{
	return Mix_PausedMusic();
}

void AudioManager::StopMusic()
{
	Mix_HaltMusic();
}