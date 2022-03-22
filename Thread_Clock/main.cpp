/// <summary>
/// 1분을 측정해서 화면에 출력해주는 (1분 뒤 알람) 함수를 별도의 스레드로 실행
/// </summary>
#include <windows.h> // HANDLE
#include <process.h> // THREAD
#include <time.h>
#include <iostream>

// 전방 선언
UINT WINAPI TimerFunc(LPVOID lpParam);

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

/// <summary>
/// 1분을 측정해서 화면에 출력하는 함수
/// </summary>
UINT WINAPI TimerFunc(LPVOID lpParam)
{
	// 알람 반복 횟수
	int alarmCnt = *((int*) lpParam);
	// 현재 반복한 알람 수
	int curCnt = 0;

	LARGE_INTEGER timer, start, end;
	__int64 elapsed;
	double duringtime, deltaTime = 0;

	// 타이머의 주파수를 획득
	QueryPerformanceFrequency(&timer);
	
	// 시작 시점의 CPU 클럭 수
	QueryPerformanceCounter(&start);

	while (curCnt < alarmCnt)
	{
		// 종료 시점의 CPU 클럭 수
		QueryPerformanceCounter(&end);

		// 걸린 시간 계산
		elapsed = end.QuadPart - start.QuadPart;
		deltaTime = (double)elapsed / (double)timer.QuadPart;
		deltaTime *= 1000; //ms로 변환

		// 1분이 되면 출력
		if (deltaTime > 1000)
		{
			std::cout << deltaTime << std::endl;
			deltaTime = 0;
			curCnt++;
			QueryPerformanceCounter(&start);
		}
	}
	return 0;
}