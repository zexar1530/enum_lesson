#define _USE_MATH_DEFINES
#include"shape.h"
#include<cmath>

double Shape::getVolume() const
{
	return volume;
}

double Shape::getSquare() const
{
	return square;
}

double Shape::getHeight() const
{
	return height;
}

double Shape::getRadius() const
{
	return radius;
}

Line::Line(int _x1, int _y1, int _x2, int _y2)   //конструктор класса Line
{
	coor.x1 = _x1; coor.y1 = _y1;
	coor.x2 = cos.x2 = _x2; coor.y2 = _y2;
}

Sqr::Sqr(int _x1, int _y1, int _x2, int _y2, int _x3, int _y3, int _x4, int _y4)
{
	coor.x1 = _x1; coor.y1 = _y1;
	coor.x2 = _x2; coor.y2 = _y2;
	coor.x3 = _x3; coor.y3 = _y3;
	coor.x4 = _x4; coor.y4 = _y4;
	square = pow((coor.x1 - coor.x2), 2) + pow((coor.y1 - coor.y2), 2);
}



Cube::Cube(int _x1, int _y1, int _z1, int _x2, int _y2, int _z2, int _x3, int _y3, int _z3, int _x4, int _y4, int _z4, int _x5, int _y5, int _z5, int _x6, int _y6, int _z6, int _x7, int _y7, int _z7, int _x8, int _y8, int _z8)
{
	coor.x1 = _x1; coor.y1 = _y1; coor.z1 = _z1;
	coor.x2 = _x2; coor.y2 = _y2; coor.z2 = _z2;
	coor.x3 = _x3; coor.y3 = _y3; coor.z3 = _z3;
	coor.x4 = _x4; coor.y4 = _y4; coor.z4 = _z4;
	coor.x5 = _x5; coor.y5 = _y5; coor.z5 = _z5;
	coor.x6 = _x6; coor.y6 = _y6; coor.z6 = _z6;
	coor.x7 = _x7; coor.y7 = _y7; coor.z7 = _z7;
	coor.x8 = _x8; coor.y8 = _y8; coor.z8 = _z8;
	square = 6 * (pow((coor.x1 - coor.x2), 2) + pow((coor.y1 - coor.y2), 2));
	volume = 2 * (pow((coor.x1 - coor.x2), 2) + pow((coor.y1 - coor.y2), 2));
}

Circle::Circle(int _x1, int _y1, double _R)
{
	coor.x1 = _x1; coor.y1 = _y1;
	radius = _R;
	square = M_PI * _R * _R;
}

Cylinder::Cylinder(int _x1, int _y1, double _R, double _H)
{
	coor.x1 = _x1; coor.y1 = _y1;
	radius = _R;
	height = _H;
	square = 2 * M_PI * _R * (_R + _H);
	volume = M_PI * _R * _R * _H;
}

//----------разбираем трансформации по Override функциям--------------

void Line::shift(int _m, int _n)
{
	coor.x1 += _m; coor.y1 += _n;
	coor.x2 += _m; coor.y2 += _n;
}

void Line::scaleX(int _a)
{
	coor.x1 *= _a;
	coor.x2 *= _a;
}

void Line::scaleY(int _d)
{
	coor.y1 *= _d;
	coor.y2 *= _d;
}

void Line::scaleZ(int _e)
{
	coor.z1 *= _e;
	coor.z2 *= _e;
}

void Line::scale(int _s)
{
	coor.x1 /= _s; coor.y1 /= _s;
	coor.x2 /= _s; coor.y2 /= _s;
}

void Sqr::shift(int _m, int _n)
{
	coor.x1 += _m; coor.y1 += _n;
	coor.x2 += _m; coor.y2 += _n;
	coor.x3 += _m; coor.y3 += _n;
	coor.x4 += _m; coor.y4 += _n;
}

void Sqr::scaleX(int _a)
{
	coor.x1 *= _a;
	coor.x2 *= _a;
	coor.x3 *= _a;
	coor.x4 *= _a;
}

void Sqr::scaleY(int _d)
{
	coor.y1 *= _d;
	coor.y2 *= _d;
	coor.y3 *= _d;
	coor.y4 *= _d;
}

void Sqr::scaleZ(int _e)
{
	coor.z1 *= _e;
	coor.z2 *= _e;
	coor.z3 *= _e;
	coor.z4 *= _e;
}

void Sqr::scale(int _s)
{
	coor.x1 /= _s; coor.y1 /= _s;
	coor.x2 /= _s; coor.y2 /= _s;
	coor.x3 /= _s; coor.y3 /= _s;
	coor.x4 /= _s; coor.y4 /= _s;
}

void Cube::shift(int _m, int _n, int _k)
{
	coor.x1 += _m; coor.y1 += _n; coor.z1 += _k;
	coor.x2 += _m; coor.y2 += _n; coor.z2 += _k;
	coor.x3 += _m; coor.y3 += _n; coor.z3 += _k;
	coor.x4 += _m; coor.y4 += _n; coor.z4 += _k;
	coor.x5 += _m; coor.y5 += _n; coor.z5 += _k;
	coor.x6 += _m; coor.y6 += _n; coor.z6 += _k;
	coor.x7 += _m; coor.y7 += _n; coor.z7 += _k;
	coor.x8 += _m; coor.y8 += _n; coor.z8 += _k;
}

void Cube::scaleX(int _a)
{
	coor.x1 *= _a;
	coor.x2 *= _a;
	coor.x3 *= _a;
	coor.x4 *= _a;
	coor.x5 *= _a;
	coor.x6 *= _a;
	coor.x7 *= _a;
	coor.x8 *= _a;
}

void Cube::scaleY(int _d)
{
	coor.y1 *= _d;
	coor.y2 *= _d;
	coor.y3 *= _d;
	coor.y4 *= _d;
	coor.y5 *= _d;
	coor.y6 *= _d;
	coor.y7 *= _d;
	coor.y8 *= _d;
}

void Cube::scaleZ(int _e)
{
	coor.z1 *= _e;
	coor.z2 *= _e;
	coor.z3 *= _e;
	coor.z4 *= _e;
	coor.z5 *= _e;
	coor.z6 *= _e;
	coor.z7 *= _e;
	coor.z8 *= _e;
}

void Cube::scale(int _s)
{
	coor.x1 /= _s; coor.y1 /= _s; coor.z1 /= _s;
	coor.x2 /= _s; coor.y2 /= _s; coor.z2 /= _s;
	coor.x3 /= _s; coor.y3 /= _s; coor.z3 /= _s;
	coor.x4 /= _s; coor.y4 /= _s; coor.z4 /= _s;
	coor.x5 /= _s; coor.y5 /= _s; coor.z5 /= _s;
	coor.x6 /= _s; coor.y6 /= _s; coor.z6 /= _s;
	coor.x7 /= _s; coor.y7 /= _s; coor.z7 /= _s;
	coor.x8 /= _s; coor.y8 /= _s; coor.z8 /= _s;
}




//все очень упрощаем)))) включая мат выражения-------------------------------------------

//Shape::Shape(int _type, int _x1, int _y1, int _z1, int _x2, int _y2, int _z2, int _x3, int _y3, int _z3, int _x4, int _y4, int _z4, int _x5, int _y5, int _z5, int _x6, int _y6, int _z6, int _x7, int _y7, int _z7, int _x8, int _y8, int _z8)
//{
//	type = _type;
//	// заполн¤ем координаты фигуры
//	switch (type)
//	{
//	case line:
//		x1 = _x1; y1 = _y1;
//		x2 = _x2; y2 = _y2;
//		break;
//	case sqr:
//		x1 = _x1; y1 = _y1;
//		x2 = _x2; y2 = _y2;
//		x3 = _x3; y3 = _y3;
//		x4 = _x4; y4 = _y4;
//		break;
//	case cube:
//		x1 = _x1; y1 = _y1; z1 = _z1;
//		x2 = _x2; y2 = _y2; z2 = _z2;
//		x3 = _x3; y3 = _y3; z3 = _z3;
//		x4 = _x4; y4 = _y4; z4 = _z4;
//		x5 = _x5; y5 = _y5; z5 = _z5;
//		x6 = _x6; y6 = _y6; z6 = _z6;
//		x7 = _x7; y7 = _y7; z7 = _z7;
//		x8 = _x8; y8 = _y8; z8 = _z8;
//		break;
//	default:
//		break;
//	}
//
//	// стороны фигуры
//	int a = abs(x1 - x2);
//	int b = abs(y1 - y2);
//	int c = abs(z1 - z2);
//	// считаем площадь фигуры
//	switch (type)
//	{
//	case line:
//		square = 0;
//		break;
//	case sqr:
//		square = a * b;
//		break;
//	case cube:
//		square = 2 * a * b + 2 * a * c + 2 * b * c;
//		break;
//	default:
//		break;
//	}
//
//	// считаем объем фигуры
//	switch (type)
//	{
//	case line:
//		volume = 0;
//		break;
//	case sqr:
//		volume = 0;
//		break;
//	case cube:
//		volume = a * b * c;
//		break;
//	default:
//		break;
//	}
//
//}
//
//Shape::Shape(int type, int _x1, int _y1, double R, double H)
//{
//	// заполн¤ем координаты фигуры
//	switch (type)
//	{
//	case circle:
//		x1 = _x1; y1 = _y1;
//		radius = R;
//		break;
//	case cylinder:
//		x1 = _x1; y1 = _y1;
//		radius = R;
//		height = H;
//		break;
//	default:
//		break;
//	}
//
//	// считаем площадь фигуры
//	switch (type)
//	{
//	case circle:
//		square = M_PI * R * R;
//		break;
//	case cylinder:
//		square = M_PI * R * R + 2 * R * height;
//		break;
//	default:
//		break;
//	}
//
//	// считаем объем фигуры
//	switch (type)
//	{
//	case circle:
//		volume = 0;
//		break;
//	case cylinder:
//		volume = M_PI * R * R * height;
//		break;
//	default:
//		break;
//	}
//
//}