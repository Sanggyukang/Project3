#pragma once
class Object
{
	SINGLE(Object)
public:
	enum class Direction
	{
		RIGHT,
		LEFT,
		UP,
		DOWN
	};
private:
	vector<POINT> m_snakePoint;
	POINT m_applePoint;
	Direction m_direction;
	int m_width;
	int m_height;
	BOOL m_Life;
	int m_nCount;
public:
	void Init(int,int);
public:
	void Update();
	void moveSnake();
	void reset();
	void setApple();
	void CollectApple();
	void gameover();
public:
	vector<POINT> GetSnakePoint() const { return m_snakePoint; }
	POINT GetApplePoint() const { return m_applePoint; }
	void SetDirection(Direction dir) { m_direction = dir; }
};

