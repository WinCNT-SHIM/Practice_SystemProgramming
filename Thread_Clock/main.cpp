/// <summary>
/// 1���� �����ؼ� ȭ�鿡 ������ִ� (1�� �� �˶�) �Լ��� ������ ������� ����
/// </summary>
#include <windows.h> // HANDLE
#include <process.h> // THREAD
#include <time.h>
#include <iostream>

// ���� ����
UINT WINAPI TimerFunc(LPVOID lpParam);

int main()
{
	HANDLE hThread;
	unsigned int threadID;

	// �˶��� Ƚ�� ����(���� ���� ����)
	int alarmCnt = 5;

	hThread = (HANDLE)_beginthreadex(nullptr, 0, TimerFunc, &alarmCnt, 0, &threadID);

	WaitForSingleObject(hThread, INFINITE);

	CloseHandle(hThread);
	system("pause");
	return 0;
}

/// <summary>
/// 1���� �����ؼ� ȭ�鿡 ����ϴ� �Լ�
/// </summary>
UINT WINAPI TimerFunc(LPVOID lpParam)
{
	// �˶� �ݺ� Ƚ��
	int alarmCnt = *((int*) lpParam);
	// ���� �ݺ��� �˶� ��
	int curCnt = 0;

	LARGE_INTEGER timer, start, end;
	__int64 elapsed;
	double duringtime, deltaTime = 0;

	// Ÿ�̸��� ���ļ��� ȹ��
	QueryPerformanceFrequency(&timer);
	
	// ���� ������ CPU Ŭ�� ��
	QueryPerformanceCounter(&start);

	while (curCnt < alarmCnt)
	{
		// ���� ������ CPU Ŭ�� ��
		QueryPerformanceCounter(&end);

		// �ɸ� �ð� ���
		elapsed = end.QuadPart - start.QuadPart;
		deltaTime = (double)elapsed / (double)timer.QuadPart;
		deltaTime *= 1000; //ms�� ��ȯ

		// 1���� �Ǹ� ���
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