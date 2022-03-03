#pragma once

struct fPoint {
	float x;
	float y;
	fPoint()	:
		x(0.f),
		y(0.f)
	{}
	fPoint(float _x,float _y) :
		x(_x),
		y(_y)
	{}
	fPoint(int _x,int _y)	:
		x(float(_x)),
		y(float(_y))
	{}
	fPoint(POINT pt) :
		x((float)pt.x),
		y((float)pt.y)
	{}
};
