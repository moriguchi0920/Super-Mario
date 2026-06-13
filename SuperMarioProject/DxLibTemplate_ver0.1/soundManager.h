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
		PB_PLAY_BGM,//BGM
		SE_JUMP,//ジャンプ
		SE_BREAK,//ブロック破壊音
		SE_PUSH,//ブロック押す
		SE_DEATH,//死亡
		SE_COIN,//コイン
		SE_STEPON,//踏む
		SE_NOKO01,//ノコノコ蹴る音
		SE_NOKO02,//ノコノコが跳ね返る音
		SE_GOALPOLE,//ポール
		SE_GOAL,//ゴールSE
		SE_KINOKO,//キノコ
		SE_BIGMARIO,//でかくなる時の音
		SE_FIREBALL,//ファイヤーボール
		SE_STAR,//スター
		SE_1UP,//１UPキノコ

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
