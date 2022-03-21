/// <summary>
/// 스레드를 이용한 에라토스테네스의 체를 구하는 알고리즘
/// </summary>
#include <iostream>
#include <windows.h>
#include <process.h>
#include <time.h>

// 소수를 찾기 위한 최대 범위
const int g_MaxRange = 10000000;
// 스레드 함수
UINT WINAPI MyThreadFunction(LPVOID lpParam);
// 소수인지 아닌지를 판별한 결과를 저장하는 변수(인덱스가 곧 판단한 숫자)
bool Result[g_MaxRange + 1];

int main()
{
	// 스레드의 개수
	const int _ThreadNum = 32;

	//// 사용할 스레드의 개수를 입력받음
	//std::cout << "사용할 스레드 개수 입력: ";
	//std::cin >> g_ThreadNum;

	HANDLE hThread[_ThreadNum] = { nullptr, };
	UINT threadID[_ThreadNum] = { 0, };

	// 성능 측정을 위한 시간 변수
	clock_t _StartTime, _EndTime;
	double _PerformanceTime;

	// 0과 1은 소수에서 제외
	Result[0] = true;
	Result[1] = true;

	// 스레드가 소수를 찾을 범위
	// 0: 시작 숫자, 1: 마지막 숫자
	int _TargetRange[2];
	_TargetRange[0] = 3;
	_TargetRange[1] = g_MaxRange;

	// 시간 측정 시작
	_StartTime = clock();

	for (int i = 0; i < _ThreadNum; i++)
	{
		// 스레드가 검색할 대상 숫자 범위의 시작 숫자를 설정
		if (i == 0)
		{
			// 소수의 검색 범위의 처음 시작 숫자를 2로 둔다
			_TargetRange[0] = 3;
		}
		else
		{
			_TargetRange[0] = (g_MaxRange / _ThreadNum) * i + 1;
		}

		// 소수의 검색 범위의 마지막 숫자를 설정한다
		_TargetRange[1] = (g_MaxRange / _ThreadNum) * (i + 1);

		hThread[i] = (HANDLE)_beginthreadex(nullptr, 0, MyThreadFunction, (LPVOID)_TargetRange, 0, &threadID[i]);

		if (hThread[i] != NULL)
		{
			WaitForSingleObject(hThread[i], INFINITE);
		}
	}

	// 걸린 시간 측정
	_EndTime = clock();
	_PerformanceTime = (double)_EndTime - _StartTime;

	// ==================== 결과 출력 ====================
	//// 남아있는 수를 모두 출력 (배열에서 false인 index) 
	//for (int i = 0; i <= g_MaxRange; i++)
	//{
	//	if (!Result[i]) printf("%d ", i);
	//}
	//std::cout << std::endl;
	std::cout << "탐색 범위: " << "1 ~ " << g_MaxRange << std::endl;
	std::cout << "사용 스레드 수: " << _ThreadNum << "개" << std::endl;
	std::cout << "걸린 시간: " << _PerformanceTime << "ms" << std::endl;

	// 스레드 삭제
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

// 스레드 함수 구현부
UINT WINAPI MyThreadFunction(LPVOID lpParam)
{
	int* _TargetRange = (int*)lpParam;

	// 에라토스테네스의 체로 1~n까지의 소수를 찾기 위해서는 루트 n의 배수까지만 찾으면 된다
	int _MultipleRange = sqrt(_TargetRange[1]);

	// 2부터 특정 수의 배수에 해당하는 수를 모두 지움
	for (int i = _TargetRange[0]; i <= _TargetRange[1]; i++)
	{
		// 이미 지워진 수라면 건너뜀
		if (Result[i])
			continue;

		// 해당 숫자의 배수를 모두 true로 만듦
		for (int j = 2; j <= _MultipleRange; j++)
		{
			// 이미 지워진 수거나 루트 n의 배수보다 크면 스킵
			if (Result[j] || j > _TargetRange[1]) continue;

			if(i != j && i % j == 0)
			{
				Result[i] = true;
			}
		}
	}
	return 0;
}
