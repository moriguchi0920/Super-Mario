#pragma once
#include<string>
#include<queue>

struct Event
{
	int from;
	int to;

	std::string eventName;
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