#include"eventServer.h"
#include"objectManager.h"
#include<memory>

EventServer::EventServer()
{
	
}

void EventServer::enqueueEvent(const Event& event)
{
	events.push(event);
}

void EventServer::dequeueEventsAll()
{
	ObjectManager* pObjManager = ObjectManager::getInstance();
	while (!events.empty())
	{
		Event event = events.front();
		std::weak_ptr<Object> to = pObjManager->getObjectById(event.to);
		if (!to.expired())
		{
			to.lock()->eventProc(event.from, event.eventName, event.datas);
		}
		events.pop();
	}
		

}


