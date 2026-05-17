#pragma once
#include"AnimationDataSet.h"
#include"ImageManager.h"

class AnimationRepository
{
private :
	AnimationRepository();
	AnimationRepository(const AnimationRepository& other) = delete;
	AnimationRepository& operator = (const AnimationRepository& other) = delete;

public :
	static AnimationRepository* getInstance();

	static enum AnimationObjectType
	{
		AOT_NUM
	};




private :
	AnimationDataSet ads[AOT_NUM];

public :
	void initAnimationRepository();
	AnimationDataSet* getAds(int AnimobjectType);

};