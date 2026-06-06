#include "blockBase.h"
#include"componentCollision.h"
#include"componentRenderable.h"
#include"componentTransform.h"
#include"objectManager.h"
#include"collisionManager.h"

BlockBase::BlockBase(const Rect& rect) : Object(ObjectManager::makeId())
{
	this->addComponent<ComponentTransform>(this->id);
	auto transform = getComponent<ComponentTransform>();
	transform.lock()->setPosition(rect.begin);
	this->addComponent<ComponentCollisionRect>(this->id, rect);

}

BlockBase::~BlockBase()
{
}

void BlockBase::update()
{
	auto comCR = getComponent<ComponentCollisionRect>();
	auto comT = getComponent<ComponentTransform>();

	if (!comCR.expired() && !comT.expired())
	{
		if (comCR.lock()->getStayByTag(ICollisionTag::MARIO))
		{
			CollisionManager* pColManager = CollisionManager::getInstance();
			std::vector<int> infoIds = comCR.lock()->getInfoId();
			for (int i = 0; i < infoIds.size(); i++)
			{
				auto wpColInfo = pColManager->getColInfoFromId(infoIds[i]);
				if (!wpColInfo.expired())
				{
					auto target = wpColInfo.lock()->getTarget(id);
					if (!target.expired())
					{
						if (target.lock()->getTag()->tag == ICollisionTag::MARIO)
						{
							Rect colRect = comCR.lock()->get();
							Event event;
							if(fabsf(wpColInfo.lock()->getIntersection().y - colRect.begin.y) <= 0.01f)
							{

								Event::EventData dataPos;
								dataPos.position = wpColInfo.lock()->getIntersection();
								int dataTypePos = Event::DATA_POS;
								Event::DataMap dataMapPos(dataTypePos, dataPos);
								event.datas.push_back(dataMapPos);
								event.eventName = "HitTop";
								event.to = target.lock()->getParentId();
								event.from = id;
							}
							else if(fabsf(wpColInfo.lock()->getIntersection().y - colRect.begin.y + colRect.size.y) <= 0.01f)
							{
								Event::EventData dataPos;
								dataPos.position = wpColInfo.lock()->getIntersection();
								int dataTypePos = Event::DATA_POS;
								Event::DataMap dataMapPos(dataTypePos, dataPos);
								event.datas.push_back(dataMapPos);
								event.eventName = "HitBottom";
								event.to = target.lock()->getParentId();
								event.from = id;
							}
							else if (fabsf(wpColInfo.lock()->getIntersection().x - colRect.begin.x ) <= 0.01f)
							{
								Event::EventData dataPos;
								dataPos.position = wpColInfo.lock()->getIntersection();
								int dataTypePos = Event::DATA_POS;
								Event::DataMap dataMapPos(dataTypePos, dataPos);
								event.datas.push_back(dataMapPos);
								event.eventName = "HitLeft";
								event.to = target.lock()->getParentId();
								event.from = id;
							}
							else if (fabsf(wpColInfo.lock()->getIntersection().x - colRect.begin.x + colRect.size.x) <= 0.01f)
							{
								Event::EventData dataPos;
								dataPos.position = wpColInfo.lock()->getIntersection();
								int dataTypePos = Event::DATA_POS;
								Event::DataMap dataMapPos(dataTypePos, dataPos);
								event.datas.push_back(dataMapPos);
								event.eventName = "HitRight";
								event.to = target.lock()->getParentId();
								event.from = id;
							}

							EventServer::getInstance()->enqueueEvent(event);
						}

					}
				}
			}
		}
	}
}

void BlockBase::eventProc(int from, std::string name, std::vector<Event::DataMap> datas)
{
}
