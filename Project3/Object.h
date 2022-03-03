#pragma once
class Object
{
public: 
	fPoint m_pos;
	fPoint m_scale;
public:
	Object();
	~Object();
public:
	void SetPos(fPoint pos) { m_pos = pos; }
	void SetScale(fPoint scale) { m_scale = scale; }
	
	fPoint GetPos() { return m_pos; }
	fPoint GetScale() { return m_scale; }
};

