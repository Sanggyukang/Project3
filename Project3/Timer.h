#pragma once
class Timer
{
	SINGLE(Timer);
private:
	LARGE_INTEGER m_curCount;
	LARGE_INTEGER m_preCount;
	LARGE_INTEGER m_frequency;
	double		  m_deltaTime;
	double		  m_accumulateDT;
	UINT		  m_callCount;
	UINT		  m_fps;
public:
	void Init();
	void Update(double* dt,float* ft);
public:
	double GetDeltaTime() { return m_deltaTime; }
	float GetfDeltaTime() { return (float)m_deltaTime; }
	double GetFPS() { return m_fps; }
	float GetfFps() { return (float)m_fps; }
	
};

