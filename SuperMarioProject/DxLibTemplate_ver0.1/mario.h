#pragma once
#include"entityObject.h"
#include"StateMachine.h"
class Circle;

class Mario : public Object
{
private:
	StateMachine<Mario> moveStateMachine;

	StateMachine<Mario> varyStateMachine;

	StateMachine<Mario> starStateMachine;

	float jumpTranslationY;

	int jumpHoldCount;

public:
	Mario();
	~Mario();

	void update() override;

	void eventProc(int from, std::string name, std::vector<Event::DataMap> datas) override;

	enum MOVESTATE
	{
		MOV_WALK,
		MOV_DASH,
		MOV_JUMP
	};

	enum VARYSTATE
	{
		VARY_DEFAULT,
		VARY_TALL,
		VARY_FIRE,
	};

	enum STARSTATE
	{
		STAR_DEFAULT,
		STAR_INVINCIBLE
	};

	// 歩き状態更新処理
	void walk();

	// ジャンプ状態更新処理
	void jump();

	// ダッシュ状態更新処理
	void dash();

	// スター状態更新処理
	void starStateUpdate();

	// ちびマリオ状態変化時処理
	void defaultStateInit();
	// ちびマリオ状態更新処理
	void defaultStateUpdate();

	// でかマリオ状態変化時処理
	void tallStateInit();
	// でかマリオ状態更新処理
	void tallStateUpdate();

	// ファイア状態変化時処理
	void fireBallStateInit();
	// ファイア状態更新処理
	void fireBallStateUpdate();

};