#pragma once
#include<string>

enum class NameShapes
{
	line = 0, sqr = 1, cube = 2, circle = 3, cylinder = 4
};

class Shape				//разбиваем класс shape на несколько классов
{
protected:
	struct Coordinate {
		int x1 = 0, y1 = 0, z1 = 0,
			x2 = 0, y2 = 0, z2 = 0,
			x3 = 0, y3 = 0, z3 = 0,
			x4 = 0, y4 = 0, z4 = 0,
			x5 = 0, y5 = 0, z5 = 0,
			x6 = 0, y6 = 0, z6 = 0,
			x7 = 0, y7 = 0, z7 = 0,
			x8 = 0, y8 = 0, z8 = 0;
	};
	double volume{};
	double square{};
	double height{};
	double radius{};

public:
	/*static const int line = 0;       static убираем и делаем enum
	static const int sqr = 1;
	static const int cube = 2;
	static const int circle = 3;
	static const int cylinder = 4;*/
	Shape() = default; //конструктор по умолчанию оставим, основные конструкторы будут у наследуемых классов
	/*Shape(int type, int _x1, int _y1, int _z1, int _x2, int _y2, int _z2, int _x3, int _y3, int _z3, int _x4, int _y4, int _z4, int _x5, int _y5, int _z5, int _x6, int _y6, int _z6, int _x7, int _y7, int _z7, int _x8, int _y8, int _z8);
	Shape(int type, int _x1, int _y1, double R, double H);
	int getType() { return type; }*/

	//int type;
	/*int x1 = 0, y1 = 0, z1 = 0,        А это переносим в структуру coordinate
		x2 = 0, y2 = 0, z2 = 0,
		x3 = 0, y3 = 0, z3 = 0,
		x4 = 0, y4 = 0, z4 = 0,
		x5 = 0, y5 = 0, z5 = 0,
		x6 = 0, y6 = 0, z6 = 0,
		x7 = 0, y7 = 0, z7 = 0,
		x8 = 0, y8 = 0, z8 = 0;*/
	/*double volume;
	double square;           переносим в секцию Protected и там инициализируем
	double height;
	double radius;*/
	double getVolume() const;          // создадим Геттеры
	double getSquare() const;
	double getHeight() const;
	double getRadius() const;
	Coordinate coor;
};

class Line : public Shape
{
public:
	Line(int _x1, int _y1, int _x2, int _y2);

	virtual void shift(int _m, int _n);
	virtual void scaleX(int _a);
	virtual void scaleY(int _d);
	virtual void scaleZ(int _e);
	virtual void scale(int _s);
};

class Sqr : public Line
{
public:
	Sqr(int _x1, int _y1, int _x2, int _y2, int _x3, int _y3, int _x4, int _y4);

	void shift(int _m, int _n) override;
	void scaleX(int _a) override;
	void scaleY(int _d) override;
	void scaleZ(int _e) override;
	void scale(int _s) override;
};

class Cube : public Line
{
public:
	Cube(int _x1, int _y1, int _z1, int _x2, int _y2, int _z2, int _x3, int _y3, int _z3, int _x4, int _y4, int _z4, int _x5, int _y5, int _z5, int _x6, int _y6, int _z6, int _x7, int _y7, int _z7, int _x8, int _y8, int _z8);

	void shift(int _m, int _n, int _k) override;
	void scaleX(int _a) override;
	void scaleY(int _d) override;
	void scaleZ(int _e) override;
	void scale(int _s) override;
};

class Circle : public Shape
{
public:
	Circle(int _x1, int _y1, double _R);
};

class Cylinder : public Circle
{
public:
	Cylinder(int _x1, int _y1, double _R, double _H);
};
