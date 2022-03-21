/// <summary>
/// �����带 �̿��� �����佺�׳׽��� ü�� ���ϴ� �˰���
/// </summary>
#include <iostream>
#include <windows.h>
#include <process.h>
#include <time.h>

// �Ҽ��� ã�� ���� �ִ� ����
const int g_MaxRange = 10000000;
// ������ �Լ�
UINT WINAPI MyThreadFunction(LPVOID lpParam);
// �Ҽ����� �ƴ����� �Ǻ��� ����� �����ϴ� ����(�ε����� �� �Ǵ��� ����)
bool Result[g_MaxRange + 1];

int main()
{
	// �������� ����
	const int _ThreadNum = 32;

	//// ����� �������� ������ �Է¹���
	//std::cout << "����� ������ ���� �Է�: ";
	//std::cin >> g_ThreadNum;

	HANDLE hThread[_ThreadNum] = { nullptr, };
	UINT threadID[_ThreadNum] = { 0, };

	// ���� ������ ���� �ð� ����
	clock_t _StartTime, _EndTime;
	double _PerformanceTime;

	// 0�� 1�� �Ҽ����� ����
	Result[0] = true;
	Result[1] = true;

	// �����尡 �Ҽ��� ã�� ����
	// 0: ���� ����, 1: ������ ����
	int _TargetRange[2];
	_TargetRange[0] = 3;
	_TargetRange[1] = g_MaxRange;

	// �ð� ���� ����
	_StartTime = clock();

	for (int i = 0; i < _ThreadNum; i++)
	{
		// �����尡 �˻��� ��� ���� ������ ���� ���ڸ� ����
		if (i == 0)
		{
			// �Ҽ��� �˻� ������ ó�� ���� ���ڸ� 2�� �д�
			_TargetRange[0] = 3;
		}
		else
		{
			_TargetRange[0] = (g_MaxRange / _ThreadNum) * i + 1;
		}

		// �Ҽ��� �˻� ������ ������ ���ڸ� �����Ѵ�
		_TargetRange[1] = (g_MaxRange / _ThreadNum) * (i + 1);

		hThread[i] = (HANDLE)_beginthreadex(nullptr, 0, MyThreadFunction, (LPVOID)_TargetRange, 0, &threadID[i]);

		if (hThread[i] != NULL)
		{
			WaitForSingleObject(hThread[i], INFINITE);
		}
	}

	// �ɸ� �ð� ����
	_EndTime = clock();
	_PerformanceTime = (double)_EndTime - _StartTime;

	// ==================== ��� ��� ====================
	//// �����ִ� ���� ��� ��� (�迭���� false�� index) 
	//for (int i = 0; i <= g_MaxRange; i++)
	//{
	//	if (!Result[i]) printf("%d ", i);
	//}
	//std::cout << std::endl;
	std::cout << "Ž�� ����: " << "1 ~ " << g_MaxRange << std::endl;
	std::cout << "��� ������ ��: " << _ThreadNum << "��" << std::endl;
	std::cout << "�ɸ� �ð�: " << _PerformanceTime << "ms" << std::endl;

	// ������ ����
	for (int i = 0; i < _ThreadNum; i++)
	{
		if (hThread[i] != NULL)
		{
			CloseHandle(hThread[i]);
		}
	}
	
	system("pause");
	return 0;
}

// ������ �Լ� ������
UINT WINAPI MyThreadFunction(LPVOID lpParam)
{
	int* _TargetRange = (int*)lpParam;

	// �����佺�׳׽��� ü�� 1~n������ �Ҽ��� ã�� ���ؼ��� ��Ʈ n�� ��������� ã���� �ȴ�
	int _MultipleRange = sqrt(_TargetRange[1]);

	// 2���� Ư�� ���� ����� �ش��ϴ� ���� ��� ����
	for (int i = _TargetRange[0]; i <= _TargetRange[1]; i++)
	{
		// �̹� ������ ����� �ǳʶ�
		if (Result[i])
			continue;

		// �ش� ������ ����� ��� true�� ����
		for (int j = 2; j <= _MultipleRange; j++)
		{
			// �̹� ������ ���ų� ��Ʈ n�� ������� ũ�� ��ŵ
			if (Result[j] || j > _TargetRange[1]) continue;

			if(i != j && i % j == 0)
			{
				Result[i] = true;
			}
		}
	}
	return 0;
}
