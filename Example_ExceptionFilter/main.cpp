#include <Windows.h>
#include <tchar.h>
#include "dbghelp.h"
#pragma comment(lib, "Dbghelp.lib")

LONG WINAPI MyExceptionFilter(struct _EXCEPTION_POINTERS* pExceptionInfo);

int main()
{
	// 함수 포인터를 등록해준는 함수
	SetUnhandledExceptionFilter(MyExceptionFilter);

	// 예외를 발생 시키는 코드
	int* pInt = nullptr;
	int n = *pInt;
}

LONG WINAPI MyExceptionFilter(struct _EXCEPTION_POINTERS* pExceptionInfo)
{
	// test.dmp라는 파일을 만들 것
	HANDLE hFile = CreateFile(_T("test.dmp"), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	// 밑의 구조체를 서술한다
	MINIDUMP_EXCEPTION_INFORMATION stExceptionParam;
	stExceptionParam.ThreadId = GetCurrentThreadId();		// GetCurrentThreadId()가 쓰인다
	stExceptionParam.ExceptionPointers = pExceptionInfo;
	stExceptionParam.ClientPointers = FALSE;

	// 
	MiniDumpWriteDump(
		GetCurrentProcess(),		// 현재 프로세스의 핸들(슈도 핸들)
		GetCurrentProcessId(),		// 현재 프로세스의 ID
		hFile,
		MiniDumpWithFullMemory,
		&stExceptionParam,
		NULL, NULL
	);
	CloseHandle(hFile);

	return EXCEPTION_EXECUTE_HANDLER;
}
