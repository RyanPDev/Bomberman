#pragma once
#include <SDL_mixer.h>
#include "Types.h"

class AudioManager
{
private:
	static AudioManager* audio;
	AudioManager();

public:
	~AudioManager();

	static AudioManager* GetInstance() { if (audio == nullptr) { audio = new AudioManager; } return audio; }

	void LoadSoundtrack(const Soundtrack& audio);
	void PauseMusic();
	void ResumeMusic();
	int PausedMusic();
	void StopMusic();
};