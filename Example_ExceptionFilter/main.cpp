#include <Windows.h>
#include <tchar.h>
#include "dbghelp.h"
#pragma comment(lib, "Dbghelp.lib")

LONG WINAPI MyExceptionFilter(struct _EXCEPTION_POINTERS* pExceptionInfo);

int main()
{
	// �Լ� �����͸� ������ش� �Լ�
	SetUnhandledExceptionFilter(MyExceptionFilter);

	// ���ܸ� �߻� ��Ű�� �ڵ�
	int* pInt = nullptr;
	int n = *pInt;
}

LONG WINAPI MyExceptionFilter(struct _EXCEPTION_POINTERS* pExceptionInfo)
{
	// test.dmp��� ������ ���� ��
	HANDLE hFile = CreateFile(_T("test.dmp"), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	// ���� ����ü�� �����Ѵ�
	MINIDUMP_EXCEPTION_INFORMATION stExceptionParam;
	stExceptionParam.ThreadId = GetCurrentThreadId();		// GetCurrentThreadId()�� ���δ�
	stExceptionParam.ExceptionPointers = pExceptionInfo;
	stExceptionParam.ClientPointers = FALSE;

	// 
	MiniDumpWriteDump(
		GetCurrentProcess(),		// ���� ���μ����� �ڵ�(���� �ڵ�)
		GetCurrentProcessId(),		// ���� ���μ����� ID
		hFile,
		MiniDumpWithFullMemory,
		&stExceptionParam,
		NULL, NULL
	);
	CloseHandle(hFile);

	return EXCEPTION_EXECUTE_HANDLER;
}
