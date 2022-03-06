#include "pch.h"
#include "Timer.h"
#include "Core.h"

Timer::Timer() :
	m_curCount{},
	m_preCount{},
	m_frequency{},
	m_deltaTime(0),
	m_accumulateDT(0),
	m_callCount(0),
	m_fps(0)
{
}
Timer::~Timer()
{
}
void Timer::Init()
{
	QueryPerformanceCounter(&m_preCount);
	QueryPerformanceFrequency(&m_frequency);
}

void Timer::Update(double* dt, float* ft)
{
	QueryPerformanceCounter(&m_curCount);
	m_deltaTime = (double)(m_curCount.QuadPart - m_preCount.QuadPart) / (double)m_frequency.QuadPart;
	m_accumulateDT += m_deltaTime;
	m_callCount++;
	*dt = m_accumulateDT;
	if (1. <= m_accumulateDT) {
		m_fps = m_callCount;
		m_callCount = 0;
		m_accumulateDT = 0;
		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d DT : %f", m_fps, m_deltaTime);
		SetWindowText(Core::Get_Inst()->GetHwnd(), szBuffer);
	}

	m_preCount = m_curCount;
}
