/// <summary>
/// 1분을 측정해서 화면에 출력해주는 (1분 뒤 알람) 함수를 별도의 스레드로 실행
/// </summary>
#include <windows.h> // HANDLE
#include <process.h> // THREAD
#include <time.h>
#include <iostream>

int main()
{
	HANDLE hThread;
	unsigned int threadID;

	// 알람의 횟수 설정(무한 루프 방지)
	int alarmCnt = 5;

	hThread = (HANDLE)_beginthreadex(nullptr, 0, TimerFunc, &alarmCnt, 0, &threadID);

	WaitForSingleObject(hThread, INFINITE);

	CloseHandle(hThread);
	system("pause");
	return 0;
}