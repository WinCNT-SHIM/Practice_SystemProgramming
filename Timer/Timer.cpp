#include "Timer.h"

Timer::Timer()
{
	m_DeltaTime_GetTickCount64 = -1;
	m_DeltaTime_timeGetTime = -1;
	m_DeltaTime_SystemClock = -1;
	m_Elapsed_QueryPerformence = -1;
	m_DeltaTime_QueryPerformence = -1;
	// QueryPerformence�� Ÿ�̸��� ���ļ��� ȹ��
	QueryPerformanceFrequency(&m_Timer_QueryPerformence);
}

Timer::~Timer()
{

}

void Timer::StartTimer_GetTickCount64()
{
	m_StartTime_GetTickCount64 = GetTickCount64();
	// �ð� ���� ���� �ʱ�ȭ
	m_DeltaTime_GetTickCount64 = -1;
}

void Timer::EndTimer_GetTickCount64()
{
	m_EndTime_GetTickCount64 = GetTickCount64();
	m_DeltaTime_GetTickCount64 = (double)(m_EndTime_GetTickCount64 - m_StartTime_GetTickCount64);
}

double Timer::ReturnDeltaTime_GetTickCount64()
{
	return m_DeltaTime_GetTickCount64;
}

void Timer::StartTimer_timeGetTime()
{
	m_StartTime_timeGetTime = timeGetTime();
	// �ð� ���� ���� �ʱ�ȭ
	m_DeltaTime_timeGetTime = -1;
}

void Timer::EndTimer_timeGetTime()
{
	m_EndTime_timeGetTime = timeGetTime();
	m_DeltaTime_timeGetTime = (double)(m_EndTime_timeGetTime - m_StartTime_timeGetTime);
}

double Timer::ReturnDeltaTime_timeGetTime()
{
	return m_DeltaTime_timeGetTime;
}

void Timer::StartTimer_SystemClock()
{
	m_StartTime_SystemClock = system_clock::now();
	// �ð� ���� ���� �ʱ�ȭ
	m_DeltaTime_SystemClock = -1;
}

void Timer::EndTimer_SystemClock()
{
	m_EndTime_SystemClock = system_clock::now();
	
	milliseconds _milliSec = duration_cast<milliseconds>(m_EndTime_SystemClock - m_StartTime_SystemClock);

	m_DeltaTime_SystemClock = _milliSec.count();
}

double Timer::ReturnDeltaTime_SystemClock()
{
	return m_DeltaTime_SystemClock;
}

void Timer::StartTimer_QueryPerformence()
{
	// ���� ������ CPU Ŭ�� ��
	QueryPerformanceCounter(&m_StartTime_QueryPerformence);
	// �ð� ���� ���� �ʱ�ȭ
	m_Elapsed_QueryPerformence = -1;
	m_DeltaTime_QueryPerformence = -1;
}

void Timer::EndTimer_QueryPerformence()
{
	// ���� ������ CPU Ŭ�� ��
	QueryPerformanceCounter(&m_EndTime_QueryPerformence);

	// �ɸ� �ð� ���
	m_Elapsed_QueryPerformence = m_EndTime_QueryPerformence.QuadPart - m_StartTime_QueryPerformence.QuadPart;
	m_DeltaTime_QueryPerformence = (double)m_Elapsed_QueryPerformence / (double)m_Timer_QueryPerformence.QuadPart;
	m_DeltaTime_QueryPerformence *= 1000; //ms�� ��ȯ
}

double Timer::ReturnDeltaTime_QueryPerformence()
{
	return m_DeltaTime_QueryPerformence;
}
