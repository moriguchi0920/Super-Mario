#pragma once
#include"entityObject.h"
#include"StateMachine.h"
class Circle;

class Mario : public Object
{
private:
	// 移動状態変更用ステートマシン
	StateMachine<Mario> moveStateMachine;
	// デカマリオ、ファイヤーマリオ変更用ステートマシン
	StateMachine<Mario> varyStateMachine;
	// スター取得時の無敵判定用ステートマシン
	StateMachine<Mario> starStateMachine;

	float jumpTranslationY;

	int jumpHoldCount;

	bool isLeft;

public:
	Mario();
	~Mario();

	void update() override;

	void eventProc(int from, std::string name, std::vector<Event::DataMap> datas) override;

	void activateProc() override;

	void deactivateProc() override;

	void deathProc() override;

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

	int marioImages[7];
	int walkAnim[3];
	int jumpAnim[1];
	int idleAnim[1];

	int walkStart = 1;
	int walkCount = 3;
	int jumpStart = 5;
	int jumpCount = 1;

	int idleStart = 0;
	int idleCount = 1;

	// アニメーション用変数
	int animFrame = 0;
	int animTimer = 0;

};