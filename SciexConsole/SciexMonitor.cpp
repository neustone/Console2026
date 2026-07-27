#include "SciexMonitor.h"

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
#define cursorTemp      "\033[3;21H"
#define cursorTarget    "\033[4;22H"
#define cursorDoor      "\033[6;13H"
#define cursorTimer     "\033[8;7H"
#define cursorToCmd     "\033[11;27H"

CSciexMonitor::CSciexMonitor()
    : CObserver()
    , m_pThread(nullptr)
    , m_bRunning(false)
    , m_pFridge(nullptr)
{
    //line 1
	std::cout << "*** SciexMonitor ***\n";
    std::cout << "\nCurrent Temperature:\n";
    std::cout << "Target Temperature:\n";
    std::cout << "\nFridge Door:\n";
    std::cout << "\nTimer:\n";
    //std::cout << cursup;
    //std::cout << cursup;
    //std::cout << "4 new";
    //std::cout << curshome;
    std::cout << "\nExit: 0, Temp[up|down]: 1|2, Target[up|down]: 3|4, Door[open|close]: 5\n";
    std::cout << "Please enter your command:";
}

CSciexMonitor::~CSciexMonitor()
{
    if (m_pThread)
    {
        m_bRunning = false;
        m_pThread->join();
        delete m_pThread;
        m_pThread = nullptr;
    }
    m_pFridge = nullptr;
}

int CSciexMonitor::notify(CSciexMessage_ nMsg, long lData)
{
    int nRet = 0;
    switch (nMsg)
    {
    case CSciexMessage_Initialize:
        if (nullptr == m_pThread)
        {
            m_pThread = new std::thread(
                CSciexMonitor::startThread, this);
        }
        break;
    default:
        break;
    }
    return nRet;
}

void CSciexMonitor::updateData()
{
    m_bRunning = true;
    do
    {
        if (m_pFridge)
        {
            float fTemp = m_pFridge->getCurrentTemperature() / 100.0f;
            float fTarget = m_pFridge->getTargetTemperature() / 100.0f;
            bool bDoorOpened = m_pFridge->isDoorOpened();

            std::cout << cursorTemp;
            std::cout << fTemp;
            std::cout << cursorTarget;
            std::cout << fTarget;
            std::cout << cursorDoor;
            std::cout << (bDoorOpened ? "open" : "close");
        }
        // 1. Get the current system time point
        auto now = std::chrono::system_clock::now();
        // 2. Convert to a C-style time_t object
        auto rawTime = std::chrono::system_clock::to_time_t(now);
        // 3. Print local time using a clean layout format (YYYY-MM-DD HH:MM:SS)
        struct tm timeInfo;
        errno_t result = localtime_s(&timeInfo, &rawTime);
        std::cout << cursorTimer;
        std::cout << std::put_time(&timeInfo, "%Y-%m-%d %X");

        std::cout << cursorToCmd;

        //Sleep(500);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));

    } while (m_bRunning);

    std::cout << "*** End ***" << std::endl;
}

void CSciexMonitor::startThread(CSciexMonitor* pt)
{
    if (pt)
        pt->updateData();
}