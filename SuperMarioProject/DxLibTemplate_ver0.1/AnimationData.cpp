#include"AnimationData.h"
#include<stdlib.h>

AnimationData::AnimationData()
{
	// 登録されたアニメーションデータの個数を0に初期化
	dataLength = 0;
	// 終了コマンドで初期化を行い、誤動作を防止する
	for (int i = 0; i < DATA_ELEM_LENGTH; i++)
	{
		dataElemArray[i].command = AnimationCommand::AC_END;
	}
}

// アニメーションデータが満杯でないかチェック
bool AnimationData::isFull()
{
	bool ret = false;
	if (DATA_ELEM_LENGTH <= dataLength)
	{
		ret = true;
	}

	return ret;
}
// 指定した番号のアニメーションデータを取得
const AnimationDataElem* AnimationData::getData(int idx)
{
	AnimationDataElem* ret = NULL;
	if (0 <= idx && idx < dataLength)
	{
		ret = &dataElemArray[idx];
	}
	return ret;
}

void AnimationData::pushEnd()
{
	if (isFull())
	{
		return;
	}
	AnimationDataElem* pElem = &dataElemArray[dataLength];
	pElem->command = AnimationCommand::AC_END;
	dataLength++;
}


// アニメーションデータに画像変更命令を追加する
void AnimationData::pushSetImage(int imageId)
{
	// アニメーションデータが満杯ならこれ以上登録をしない
	if (isFull())
	{
		return;
	}
	AnimationDataElem* pElem = &dataElemArray[dataLength];
	pElem->command = AnimationCommand::AC_SET_IMAGE;
	pElem->data.imageHandle = imageId;
	dataLength++;
}

void AnimationData::pushSetWait(int wait)
{
	// アニメーションデータが満杯ならこれ以上登録をしない
	if (isFull())
	{
		return;
	}
	AnimationDataElem* pElem = &dataElemArray[dataLength];
	pElem->command = AnimationCommand::AC_SET_WAIT;
	pElem->data.wait = wait;
	dataLength++;
}

void AnimationData::pushJump(int idx)
{
	// アニメーションデータが満杯ならこれ以上登録をしない
	if (isFull())
	{
		return;
	}
	AnimationDataElem* pElem = &dataElemArray[dataLength];
	pElem->command = AnimationCommand::AC_JUMP;
	pElem->data.jumpDataIdx = idx;
	dataLength++;
}

void AnimationData::pushPlaySound(int soundId)
{
	// アニメーションデータが満杯ならこれ以上登録をしない
	if (isFull())
	{
		return;
	}
	AnimationDataElem* pElem = &dataElemArray[dataLength];
	pElem->command = AnimationCommand::AC_PLAYSOUND;
	pElem->data.soundHandle = soundId;
	dataLength++;

}

void AnimationData::pushSetCropBegin(int x, int y)
{
	// アニメーションデータが満杯ならこれ以上登録をしない
	if (isFull())
	{
		return;
	}
	AnimationDataElem* pElem = &dataElemArray[dataLength];
	pElem->command = AnimationCommand::AC_SET_CROP_BEGIN;
	pElem->data.crop_begin.x = x;
	pElem->data.crop_begin.y = y;
	dataLength++;

}

void AnimationData::pushSetCropSize(int w, int h)
{
	// アニメーションデータが満杯ならこれ以上登録をしない
	if (isFull())
	{
		return;
	}
	AnimationDataElem* pElem = &dataElemArray[dataLength];
	pElem->command = AnimationCommand::AC_SET_CROP_SIZE;
	pElem->data.crop_size.x = w;
	pElem->data.crop_size.y = h;
	dataLength++;

}

void AnimationData::pushSetReverseX(bool isReverse)
{
	// アニメーションデータが満杯ならこれ以上登録をしない
	if (isFull())
	{
		return;
	}
	AnimationDataElem* pElem = &dataElemArray[dataLength];
	pElem->command = AnimationCommand::AC_SET_REVERSE_X;
	pElem->data.reverseX = isReverse;
	dataLength++;

}

void AnimationData::pushSetReverseY(bool isReverse)
{
	// アニメーションデータが満杯ならこれ以上登録をしない
	if (isFull())
	{
		return;
	}
	AnimationDataElem* pElem = &dataElemArray[dataLength];
	pElem->command = AnimationCommand::AC_SET_REVERSE_Y;
	pElem->data.reverseY = isReverse;
	dataLength++;

}

