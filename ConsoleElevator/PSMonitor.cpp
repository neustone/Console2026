#include "PSMonitor.h"
///.
#include <iostream>
#include <chrono>
#include <ctime>   // localtime
#include <iomanip> // put_time

/***
"\033[y;xH" is an ANSI escape sequence that moves your terminal cursor to a specific row (y) and column (x).
The coordinate system is 1-based, meaning 033[1;1H moves the cursor to the top-left corner.
https://github.com/alfishe/amiga-bootcamp/blob/main/10_devices/console.md
***/
//#define cursup    "\033[A"
//#define curshome  "\033[0;0H"
#define cursorCmd       "\033[2;54H"
#define cursorTimer     "\033[3;0H"

PSMonitor::PSMonitor()
{
    std::cout << "*** Console Elevator: Hello World! ***\n";

}

PSMonitor::~PSMonitor()
{
    std::cout << "*** Console Elevator: End! ***\n";
}

int PSMonitor::turnOn(PSElevator& elevator)
{
    int nRet = 0, floor = 0;
    
    elevator.start();

    std::cout << "Please select floor number (0...9, otherwise exit): ";
    bool bContinue = true;
    do
    {
        std::cin >> floor;

        bContinue = elevator.request(floor);

    } while (bContinue);

    elevator.stop();

    return nRet;
}

int PSMonitor::notify(int floor, ElevatorState state)
{
    auto currTime = std::chrono::system_clock::now();
    auto rawTime = std::chrono::system_clock::to_time_t(currTime);
    struct tm timeInfo;
    localtime_s(&timeInfo, &rawTime);
    std::cout << cursorTimer;
    std::cout << std::put_time(&timeInfo, "%Y-%m-%d %X") << std::endl;

    switch (state)
    {
    case ElevatorState::Unknown:
        break;
    case ElevatorState::Idle:
        std::cout << "Elevator Idle at " << floor << std::endl;
        break;
    case ElevatorState::Up:
        std::cout << "Elevator Up at " << floor << std::endl;
        break;
    case ElevatorState::Down:
        std::cout << "Elevator Down at " << floor << std::endl;
        break;
    case ElevatorState::DoorOpen:
        break;
    case ElevatorState::DoorClose:
        break;
    case ElevatorState::ShutDown:
        std::cout << "Elevator turn off at " << floor << std::endl;
        break;
    default:
        break;
    }
    std::cout << cursorCmd;

    return 0;
}
