#ifndef __TASK_H__
#define __TASK_H__

#include "stdlib.h"
#include"common_func.h"
#include"collision.h"
#include"collisionManager.h"


// 全オブジェクトに使うオブジェクトの種類、更新関数、表示関数保存用のクラス
class Task
{
public:


	enum TaskState
	{
		READY,
		ACTIVE,
		INACTIVE
	};

	enum Priority
	{
		PR_BG,
		PR_GAMEOBJECT,
		PR_MAP,
		PR_UI
	};
protected: 
	// 当たっているか(CollisionManagerに権限を委譲したため使わない)
	bool isHit;
	// 死んだかどうか
	bool isDead;

	// TaskManagerでCollisionManagerのremoveObject()を動かすためのCollisionObjectのポインタ
	//CollisionObject* pColTask;

public:
	Task(int id);
	virtual ~Task();

	virtual void Update() = 0;

	//virtual void Render() = 0;

	virtual bool Destroy() = 0;

	//virtual void eventProc(const Event* event);

	int getTaskState();

	int getTaskId();

	bool activate();

	bool deactivate();

protected:
	virtual void activateProc();
	virtual void deactivateProc();

protected :
	// 識別管理用ID
	int taskId;
	int taskState;


};

void taskInit(Task* pTask, int objectType, void (*pFuncUpdate)(void*), void (*pFuncDisp)(void*), void(*pFuncDestroy)(void*));


#endif
