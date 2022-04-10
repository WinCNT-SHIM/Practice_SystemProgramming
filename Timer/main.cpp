#include <windows.h>
#include <iostream>
#include "Timer.h"

using namespace std;

int main()
{
	Timer* timer = new Timer();


	cout << "측정 시작" << endl;

	//timer->StartTimer_QueryPerformence();
	//timer->StartTimer_GetTickCount64();
	//timer->StartTimer_timeGetTime();
	timer->StartTimer_SystemClock();
	Sleep(2000);
	//timer->EndTimer_QueryPerformence();
	//timer->EndTimer_GetTickCount64();
	//timer->EndTimer_timeGetTime();
	timer->EndTimer_SystemClock();

	//cout <<	timer->ReturnDeltaTime_QueryPerformence();
	//cout <<	timer->ReturnDeltaTime_GetTickCount64() << endl;
	//cout <<	timer->ReturnDeltaTime_timeGetTime() << endl;
	cout <<	timer->ReturnDeltaTime_SystemClock() << endl;

	cout << "측정 종료" << endl;
	//system("pause");
	return 0;
}