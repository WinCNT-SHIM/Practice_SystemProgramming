/// <summary>
/// 1���� �����ؼ� ȭ�鿡 ������ִ� (1�� �� �˶�) �Լ��� ������ ������� ����
/// </summary>
#include <windows.h> // HANDLE
#include <process.h> // THREAD
#include <time.h>
#include <iostream>

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