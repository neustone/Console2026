#include "PSElevator.h"

PSElevator::PSElevator()
	: pObserver(nullptr), minFloor(0), maxFloor(10)
	, currFloor(0), currState(ElevatorState::Idle)
	, requests()
	, pThread(nullptr), bRunning(false)
	, mutex(), timeOut(300)
{
	;
}

PSElevator::~PSElevator()
{
	stop();
}

void PSElevator::setObserver(ElevatorObserver* pt)
{
	pObserver = pt;
}

bool PSElevator::request(int floor)
{
	bool ret = false;
	if (minFloor > floor || maxFloor < floor)
		return ret;

	if (currFloor == floor)
		return ret;

	if (mutex.try_lock_for(std::chrono::milliseconds()))
	{
		requests.insert(floor);
		mutex.unlock();
		ret = true;
	}
	return ret;
}

int PSElevator::start()
{
	int nRet = -1;
	if (nullptr == pThread)
	{
		bRunning = true;
		pThread = new std::thread(
			[ this ](){
				processRequests();
			}
			);
		nRet = 0;
	}
	return nRet;
}

void PSElevator::stop()
{
	bRunning = false;
	if (pThread)
	{
		pThread->join();
		delete pThread;
		pThread = nullptr;
	}
}

void PSElevator::processRequests()
{
	if (pObserver)
		pObserver->notify(currFloor, ElevatorState::Idle);

	do
	{
		step();
		std::this_thread::sleep_for( std::chrono::milliseconds(500) );

	} while (bRunning);

	if (pObserver)
		pObserver->notify(currFloor, ElevatorState::ShutDown);
}

int PSElevator::step()
{
	int nRet = 0;
	if (!requests.empty())
	{
		// determine, or maintain direction
		if (currState == ElevatorState::Idle)
		{
			currState = currFloor < *requests.begin() ? ElevatorState::Up : ElevatorState::Down;
		}
		else if (currState == ElevatorState::Up
			&& *requests.rbegin() <= currFloor)
		{
			currState = *requests.begin() <= currFloor ? ElevatorState::Down : ElevatorState::Idle;
		}
		else if (currState == ElevatorState::Down
			&& *requests.begin() >= currFloor)
		{
			currState = *requests.rbegin() >= currFloor ? ElevatorState::Up : ElevatorState::Idle;
		}

		// Simulate the travel between floors;
		if (currState == ElevatorState::Up)
			++currFloor;
		else if (currState == ElevatorState::Down)
			--currFloor;
//		std::this_thread::sleep_for(std::chrono::milliseconds(600)); // Simulates travel time
		
		// check if the elevator nneds to stop at current floor
		if (mutex.try_lock_for( std::chrono::milliseconds( timeOut ) ) )
		{
			if (requests.count(currFloor))
			{
				// Clear completed request
				requests.erase(currFloor);
				// Update Direction
	//			updateDirection();
			}
			mutex.unlock();
		}
	}
	else
	{
		currState = ElevatorState::Idle;
	}
	if (pObserver)
		pObserver->notify(currFloor, currState);

	return 0;
}

//int PSElevator::updateDirection()
//{
//	if (requests.empty())
//	{
//		currState = ElevatorState::Idle;
//	}
//	else
//	{
//		// Look for any remaining requests in the direction we were heading
////		bool hasRequestsAbove = false;
////		bool hasRequestsBelow = false;
////		for (int floor : requests)
////		{
////			if (floor > currFloor)
////				hasRequestsAbove = true;
////			if (floor < currFloor)
////				hasRequestsBelow = true;
////		}
//		bool hasRequestsAbove = *requests.rbegin() > currFloor ? true : false;
//		bool hasRequestsBelow = *requests.begin() < currFloor ? true : false;
//
//		if (currState == ElevatorState::Up && !hasRequestsAbove)
//		{
//			currState = hasRequestsBelow ? ElevatorState::Down : ElevatorState::Idle;
//		}
//		else if (currState == ElevatorState::Down && !hasRequestsBelow)
//		{
//			currState = hasRequestsAbove ? ElevatorState::Up : ElevatorState::Idle;
//		}
//	}
//	return (int)currState;
//}