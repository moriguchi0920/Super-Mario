#pragma once

#ifndef __SOUND_MANAGER_H__
#define __SOUND_MANAGER_H__

#include"const.h"

const int SOUND_INFO_LENGTH = 256;

struct SoundInfo
{

	int soundHandle;

	const char* soundPath;
};

class SoundManager
{
private:
	SoundManager();
	SoundManager& operator = (SoundManager& other) = delete;
	SoundManager(const SoundManager& other) = delete;
	SoundInfo soundInfoArray[SOUND_INFO_LENGTH];

public:
	enum SOUNDNAME
	{
		PB_PLAY_BGM,
		SE_JUMP,
		SE_BREAK,
		SE_FALLBALL,
		SE_SHOT,
	};

	static SoundManager* getInstance();

	void initSoundManager();
	bool setSoundInfo(int soundId, const char* soundPath);
	void loadSoundAll();
	int getSoundHandle(int soundId);
	void clearSoundManager();
	void setSoundVolume(int volume);
};



#endif
