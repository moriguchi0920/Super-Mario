#include"task.h"


Task::Task(int id) : isHit(false), isDead(false)
{
	taskId = id;
	taskState = TaskState::READY;

}

Task::~Task()
{
	taskState = TaskState::READY;

}


int Task::getTaskState()
{
	return taskState;
}

int Task::getTaskId()
{
	return taskId;
}

void Task::activateProc()
{
	taskState = TaskState::ACTIVE;
}

bool Task::activate()
{
	if (!(taskState < TaskState::ACTIVE))
	{
		return false;
	}
	activateProc();
}

void Task::deactivateProc()
{
	taskState = TaskState::INACTIVE;
}

bool Task::deactivate()
{
	if (!(taskState < TaskState::INACTIVE))
	{
		return false;
	}
	deactivateProc();
}


