#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <locale.h>

int _tmain(int argc, TCHAR* argv[])
{
#pragma region ������ ���μ���(�޸���) ����
	//_tprintf(_T("Execute"));
	//// cmd���� �޸��� ����
	//_tsystem(_T("notepad.exe"));
	//_tprintf(_T("\n  OK\n"));
	//// �Ͻ� ����
	//_tsystem(_T("pause"));
#pragma endregion

	// ���� ����
	STARTUPINFO si;
	// ���μ��� ����
	PROCESS_INFORMATION pi;




	return 0;
}