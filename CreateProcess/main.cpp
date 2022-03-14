#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <locale.h>

int _tmain(int argc, TCHAR* argv[])
{
#pragma region 간단한 프로세스(메모장) 실행
	//_tprintf(_T("Execute"));
	//// cmd에서 메모장 실행
	//_tsystem(_T("notepad.exe"));
	//_tprintf(_T("\n  OK\n"));
#pragma endregion

#pragma region CreateProcess 예제 코드
	// 시작 정보
	STARTUPINFO si; // 한 번에 초기화 하기: STARTUPINFO si = { sizeof(si) };
	// 프로세스 정보
	PROCESS_INFORMATION pi;

	// 시작 정보 초기화
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);	// STARTUPINFO의 구조체 바이트 크기
	// 프로세스 정보 초기화
	ZeroMemory(&pi, sizeof(pi));

	// cmd 입력 값 오류 시
	// 속성 --> 디버깅 --> 명령 인수에 작성할 수 있다
	if (argc != 2)
	{
		_tprintf(_T("Usage %s\n"), argv[0]);
	}
	else
	{
		if (
			CreateProcess(
				NULL,		// 모듈 이름
				argv[1],	// 실행하고자 하는 프로그램명(명령행의 첫 번째 원소)
				NULL,		// 프로세스 핸들 상속 여부
				NULL,		// 스레드 핸들 상속 여부
				FALSE,		// 호출 프로세스의 상속 가능한 핸들을 새 프로세스에 상속할지 여부
				0,			// 생성 플래그 --> MSDN에서 옵션 확인 가능
				NULL,		// 새 프로세스의 환경 블록에 대한 포인터
				NULL,		// 프로세스의 현재 디렉토리에 대한 전체 경로
				&si,		// 시작 정보
				&pi)		// 프로세스 정보
			)
		{
			_tprintf(_T("CreateProcess"));

			// %08x : 16진수 8자리 출력(공백은 0으로 패딩)
			_tprintf(_T("\n  Parent ID: 0x%08X"), GetCurrentProcessId());
			_tprintf(_T("\n  Child  ID: 0x%08X"), pi.dwProcessId); // dwProcessId: 프로세스를 식별 값

			// 지정된 프로세스의 우선 순위 클래스를 검색
			DWORD priority = GetPriorityClass(pi.hProcess); // hProcess: 새로 생성된 프로세스에 대한 핸들
			if (priority)
			{
				_tprintf(_T("\n  Priority Class: %d"), priority);
			}

			// 자식 프로세스의 종료를 대기
			WaitForSingleObject(pi.hProcess, INFINITE);

			// 핸들 닫기(안 하면 누수가 발생할 수 있음)
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
		}
		else
		{
			// 오류 발생 시, 에러 확인
			_tprintf(_T("CreateProcess Failed %d\n"), GetLastError());
		}
		
	}
#pragma endregion
	// 일시 정지
	_tsystem(_T("pause"));
	return 0;
}