#pragma once


#include"entityObject.h"
#include"StateMachine.h"

class KoopaTroopa : public Object
{
private :
	StateMachine<KoopaTroopa> shellStateMachine;
	int resurrectionWait;

public:
	enum TROOPASTATE
	{
		WALK,
		SHELL
	};

	KoopaTroopa(Rect rect);
	virtual ~KoopaTroopa();


public:

	void update() override;

	void eventProc(int from, std::string name, std::vector<Event::DataMap> datas) override;

	void activateProc() override;

	void deactivateProc() override;

	void deathProc() override;

	void walkUpdate();

	void shellUpdate();

};