#pragma once
#include<string>
#include<queue>
#include"Float2.h"
#include<vector>

struct Event
{
	int from;
	int to;

	std::string eventName;

	enum DATA_TYPE
	{
		DATA_POS,
		DATA_ROT,
		DATA_FLAG,
	};

	union EventData
	{
		Float2 position;
		float rotation;
		bool flag;
		EventData() : position() {}
		~EventData() {}
	};

	struct DataMap
	{
		int dataType;
		EventData data;
	};


	std::vector<DataMap> datas;
};


class EventServer
{
private:
	std::queue<Event> events;

private:
	EventServer();
	EventServer& operator = (const EventServer& other) = delete;
	EventServer(const EventServer& other) = delete;

public:
	static EventServer* getInstance();

	void enqueueEvent(const Event& event);

	void dequeueEventsAll();


};