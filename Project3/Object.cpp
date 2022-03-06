#include "pch.h"
#include "Object.h"
#include "Timer.h"

Object::Object()	:
	m_applePoint{},
	m_direction(),
	m_height(0),
	m_width(0),
	m_Life(FALSE),
	m_nCount(0)
{
}

Object::~Object()
{
}

void Object::Init(int widthPoint, int heightPoint)
{
	m_width = widthPoint;
	m_height = heightPoint;
}

void Object::Update()
{
	if (m_Life == TRUE) {
		moveSnake();

		if (m_snakePoint[0].x == m_applePoint.x && m_snakePoint[0].y == m_applePoint.y)
			CollectApple();

		for (int i = 1; i < m_snakePoint.size(); ++i) {
			if (m_snakePoint[0].x == m_snakePoint[i].x && m_snakePoint[0].y == m_snakePoint[i].y)
				gameover();
		}
	}
	else if (m_Life == FALSE) {
		m_nCount += 1;
		if (m_nCount == m_height) {
			reset();
			return;
		}
		POINT newp = {};
		for (int i = 0; i < m_width; ++i) {
			newp.x = i;
			newp.y = m_nCount;
			m_snakePoint.push_back(newp);
		}
	}
}

void Object::moveSnake()
{
	POINT temp = {};
	POINT lastPoint = {};
	for (int i = 0; i < m_snakePoint.size(); ++i) {
		temp = m_snakePoint[i];
		if (i == 0) {
			if (m_direction == Direction::RIGHT) {
				m_snakePoint[i].x +=1;
				if (m_snakePoint[i].x > m_width-1)
					m_snakePoint[i].x = 0;
			}
			else if (m_direction == Direction::LEFT) {
				m_snakePoint[i].x -= 1;
				if (m_snakePoint[i].x < 1)
					m_snakePoint[i].x = m_width-1;
			}
			else if (m_direction == Direction::DOWN){
				m_snakePoint[i].y += 1;
				if (m_snakePoint[i].y > m_height-1)
					m_snakePoint[i].y = 0;
			}
			else if (m_direction == Direction::UP) {
				m_snakePoint[i].y -= 1;
				if (m_snakePoint[i].y < 1)
					m_snakePoint[i].y = m_height-1;
			}
			if (m_snakePoint[i].x == temp.x && m_snakePoint[i].y == temp.y)
				break;
		}
		else {
			m_snakePoint[i] = lastPoint;
		}
		lastPoint = temp;
	}

}

void Object::reset()
{
	m_snakePoint.clear();
	m_Life = TRUE;
	m_direction = Direction::RIGHT;

	for (int i = 4; i > 0; --i) {
		POINT newSnake = { i,0 };
		m_snakePoint.push_back(newSnake);
	}

	setApple();
}

void Object::setApple()
{
	m_applePoint = {};
	m_applePoint.x = rand() % m_width;
	m_applePoint.y = rand() % m_height;

	for (int i = 0; i < m_snakePoint.size(); ++i) {
		if (m_snakePoint[i].x == m_applePoint.x && m_snakePoint[i].y == m_applePoint.y)
			setApple();
	}
}

void Object::CollectApple()
{
	POINT newSnake = {};
	newSnake.x = m_snakePoint[m_snakePoint.size() - 1].x;
	newSnake.y = m_snakePoint[m_snakePoint.size() - 1].y;
	m_snakePoint.push_back(newSnake);

	moveSnake();
	setApple();
}

void Object::gameover()
{
	m_Life = FALSE;
	m_nCount = 0;
	m_snakePoint.clear();
}
