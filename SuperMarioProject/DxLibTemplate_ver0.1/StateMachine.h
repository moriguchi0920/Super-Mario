#ifndef __STATE_MACHINE_H__
#define __STATE_MACHINE_H__


#include<unordered_map>

// 状態を扱うクラス
template<typename _T_>
class StateMachine
{
protected:
	typedef void(_T_::* CallBackFuncPtr)();
	

	// 一つの状態を保存するクラス
	class State
	{
	public:
		CallBackFuncPtr pInit;
		CallBackFuncPtr pUpdate;
		CallBackFuncPtr pExit;
	};

public:

	StateMachine()
	{
		curState = -1;
		nextState = -1;
	}

	// 状態の追加
	void addState(int stateId, CallBackFuncPtr _pInit, CallBackFuncPtr _pUpdate, CallBackFuncPtr _pExit)
	{
		State* pState = &stateMap[stateId];
		pState->pInit = _pInit;
		pState->pUpdate = _pUpdate;
		pState->pExit = _pExit;
	}

	// 状態の変更
	void changeState(int nextStateId)
	{
		// 現在の状態と同じなら何もせず抜ける
		if (nextStateId == curState)
		{
			return;
		}
		// 次に移動するべき状態番号を保存して終了
		nextState = nextStateId;
	}

	// 状態に応じた更新処理の呼び出し
	void update(_T_* pObject)
	{
		// 次の状態が保存されているかチェック
		if (0 <= nextState)
		{
			// 現在の状態の終了処理を実行
			if (0 <= curState)
			{
				State* pPrevState = &stateMap[curState];
				if (pPrevState->pExit != nullptr)
				{
					CallBackFuncPtr pExit = pPrevState->pExit;
					(pObject->*pExit)();
				}
			}
			// 次の状態の初期化処理を実行
			State* pNextState = &stateMap[nextState];
			if (pNextState->pInit != nullptr)
			{
				CallBackFuncPtr pInit = pNextState->pInit;
				(pObject->*pInit)();
			}
			// 現在の状態を更新
			curState = nextState;
			nextState = -1;
		}

		// 更新処理
		State* pCurState = &stateMap[curState];
		if (pCurState->pUpdate != nullptr)
		{
			CallBackFuncPtr pUpdate = pCurState->pUpdate;
			(pObject->*pUpdate)();
		}

	}

	int getStateId()
	{
		return curState;
	}




private:
	// 各状態でどの関数ポインタを呼び出せばいいかの情報を保持する配列
	std::unordered_map<int, State> stateMap;


	// 現在の状態
	int curState;
	// 次に変更するべき状態(マイナスの値で状態変化をしない)
	int nextState;

};







#endif
