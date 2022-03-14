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

#pragma region CreateProcess ���� �ڵ�
	// ���� ����
	STARTUPINFO si; // �� ���� �ʱ�ȭ �ϱ�: STARTUPINFO si = { sizeof(si) };
	// ���μ��� ����
	PROCESS_INFORMATION pi;

	// ���� ���� �ʱ�ȭ
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);	// STARTUPINFO�� ����ü ����Ʈ ũ��
	// ���μ��� ���� �ʱ�ȭ
	ZeroMemory(&pi, sizeof(pi));

	// cmd �Է� �� ����
	if (argc != 2)
	{
		_tprintf(_T("Usage %s"), argv[0]);
	}
	else
	{
		if (
			CreateProcess(
				NULL,		// ��� �̸�
				argv[1],	// �����ϰ��� �ϴ� ���α׷���(������� ù ��° ����)
				NULL,		// ���μ��� �ڵ� ��� ����
				NULL,		// ������ �ڵ� ��� ����
				FALSE,		// ȣ�� ���μ����� ��� ������ �ڵ��� �� ���μ����� ������� ����
				0,			// ���� �÷��� --> MSDN���� �ɼ� Ȯ�� ����
				NULL,		// �� ���μ����� ȯ�� ��Ͽ� ���� ������
				NULL,		// ���μ����� ���� ���丮�� ���� ��ü ���
				&si,		// ���� ����
				&pi)		// ���μ��� ����
			)
		{
			_tprintf(_T("CreateProcess\n"));

			// %08x : 16���� 8�ڸ� ���(������ 0���� �е�)
			_tprintf(_T("\n  Parent ID: 0x%08X"), GetCurrentProcessId());
			_tprintf(_T("\n  Child  ID: 0x%08X"), pi.dwProcessId); // dwProcessId: ���μ����� �ĺ� ��

			// hProcess: ���� ������ ���μ����� ���� �ڵ�
			DWORD priority = GetPriorityClass(pi.hProcess);
			if (priority)
			{
				_tprintf(_T("\n  Priority Class: %d"), priority);
			}

			// 


		}
		
	}
#pragma endregion

	return 0;
}