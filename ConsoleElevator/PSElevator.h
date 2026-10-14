#pragma once
#include <thread>
#include <set>
#include <mutex>

enum class ElevatorState
{
	Unknown = 0, Idle, Up, Down, DoorOpen, DoorClose, ShutDown,
};

class ElevatorObserver
{
public:
	ElevatorObserver() {};
	~ElevatorObserver() {};
	virtual int notify(int floor, ElevatorState state) = 0;
};

class PSElevator
{
	ElevatorObserver* pObserver;
	const int minFloor, maxFloor;
	int currFloor;
	ElevatorState currState;
	std::set<int> requests;

	std::thread* pThread;
	bool bRunning;
	std::timed_mutex mutex;
	const int timeOut;//ms

	/// <summary>
	/// 
	/// </summary>
	void processRequests();
	int step();
//	int updateDirection();

public:

	PSElevator();
	~PSElevator();
	int getMinFloor() const { return minFloor; };
	int getMaxFloor() const { return maxFloor; };

	void setObserver(ElevatorObserver* pt);
	bool request(int floor);
	int start();
	void stop();
};

