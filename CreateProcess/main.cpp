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
	//// 일시 정지
	//_tsystem(_T("pause"));
#pragma endregion

	// 시작 정보
	STARTUPINFO si;
	// 프로세스 정보
	PROCESS_INFORMATION pi;




	return 0;
}