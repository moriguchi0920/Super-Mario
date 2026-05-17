#include"taskManager.h"


// コンストラクタの初期化リストでタスクのvectorの要素数を指定
TaskManager::TaskManager() : pTaskArray(ALL_OBJECT_MAX)
{

	// 現在のIDを初期化
	lastId = TASK_GENERATE_START_ID;
}

TaskManager::~TaskManager()
{
	pTaskArray.clear();
}

Task* TaskManager::search(int id)
{
	// とりあえずnullptrでTask*変数を定義
	Task* ret = nullptr;

	// 範囲forでpTaskArrayを見て回る
	for (std::shared_ptr<Task>& spTask : pTaskArray)
	{
		// 中身がnullptr(つまりポインタが入っていない)なら
		if (!spTask)
		{
			// 戻る
			continue;
		}
		// IDが一致するTaskが見つかったら
		if (spTask->getTaskId() == id)
		{
			// retに生ポインタをget()を通して入れる
			ret = spTask.get();
			break;
		}
	}
	// 結果をreturn 
	return ret;
}


bool TaskManager::addObject(std::shared_ptr<Task> _Object)
{


	// 同じIDのタスクが存在しないかチェック

	if (search(_Object->getTaskId()))
	{
		return false;
	}



	// vectorへの追加
	pTaskArray.push_back(_Object);


	return true;


}

void TaskManager::removeObject(Task* _pObject)
{

	// for文で走査(vectorの.size()はintでは不適なためsize_t)
	for (size_t i = 0; i < pTaskArray.size(); i++)
	{
		// vector要素の参照を取る
		std::shared_ptr<Task>& spTask = pTaskArray[i];

		// .get()で出した生ポインタと引数が一致したら
		if (spTask.get() == _pObject)
		{
			// vectorの.erase()で初期インデックス(.begin())にi(現在見ているインデックス)を足したインデックスの要素を削除
			pTaskArray.erase(pTaskArray.begin() + i);
			
			break;
		}

	}
}



void TaskManager::taskUpdateAll()
{
	for (std::shared_ptr<Task>& spTask : pTaskArray)
	{


		// NULLだったら
		if (!spTask)
		{
			// これ以上何もせず次の要素に
			continue;
		}

		
		int curState = spTask->getTaskState();

		// タスクが死亡状態か
		if (curState == Task::INACTIVE)
		{
			// 削除
			spTask.reset();

			// 次の要素へ
			continue;
		}
		if (curState == Task::READY)
		{
			spTask->activate();
		}
		spTask->Update();

	}
}
//void TaskManager::taskRenderAll()
//{
//	for (int i = 0; i < ALL_OBJECT_MAX; i++)
//	{
//		Task* pTask = pTaskArray[i];
//		if (pTask == NULL)
//		{
//			continue;
//		}
//
//		int state = pTask->getTaskState();
//
//		if (!(state == Task::ACTIVE))
//		{
//			continue;
//		}
//		pTask->Render();
//	}
//
//}

//void TaskManager::destroyUpdate()
//{
//	for (int i = 0; i < ALL_OBJECT_MAX; i++)
//	{
//		if (pTaskArray[i] != NULL && pTaskArray[i]->isDead == true)
//		{
//			CollisionManager* pColManager = CollisionManager::getInstance();
//			pColManager->removeObject(pTaskArray[i]->pColTask);
//			pColManager->removeInfoFromCol(pTaskArray[i]->pColTask);
//
//			delete(pTaskArray[i]);
//			pTaskArray[i] = NULL;
//		}
//	}
//}

void TaskManager::destroyAll()
{
	pTaskArray.clear();

}

int TaskManager::generateId()
{
	return lastId++;
}
