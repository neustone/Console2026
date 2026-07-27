#pragma once
#include "PSElevator.h"

class PSMonitor : public ElevatorObserver
{
	virtual int notify(int floor, ElevatorState state);

public:
	PSMonitor();
	~PSMonitor();

	int turnOn(PSElevator& elevator);
};

