#pragma once
#include <windows.h>
#include <time.h>
#include <chrono>

#pragma comment(lib, "winmm.lib")

using namespace std;
using namespace chrono;

class Timer
{
public:
	Timer();
	~Timer();

public:
	void StartTimer_GetTickCount64();
	void EndTimer_GetTickCount64();
	double ReturnDeltaTime_GetTickCount64();
	
	void StartTimer_timeGetTime();
	void EndTimer_timeGetTime();
	double ReturnDeltaTime_timeGetTime();
	
	void StartTimer_SystemClock();
	void EndTimer_SystemClock();
	double ReturnDeltaTime_SystemClock();
	
	void StartTimer_QueryPerformence();
	void EndTimer_QueryPerformence();
	double ReturnDeltaTime_QueryPerformence();

private:
	// GetTickCount64용 변수
	DWORD m_StartTime_GetTickCount64;
	DWORD m_EndTime_GetTickCount64;
	double m_DeltaTime_GetTickCount64;

	// timeGetTime용 변수
	DWORD m_StartTime_timeGetTime;
	DWORD m_EndTime_timeGetTime;
	double m_DeltaTime_timeGetTime;

	// SystemClock용 변수
	system_clock::time_point m_StartTime_SystemClock;
	system_clock::time_point m_EndTime_SystemClock;
	double m_DeltaTime_SystemClock;

	// QueryPerformence용 변수
	LARGE_INTEGER m_Timer_QueryPerformence;
	LARGE_INTEGER m_StartTime_QueryPerformence;
	LARGE_INTEGER m_EndTime_QueryPerformence;
	__int64 m_Elapsed_QueryPerformence;
	double m_DeltaTime_QueryPerformence;
};

