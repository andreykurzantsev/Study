#include "pch.h"
#include "colors.h"
#include "toolbar.h"

class Shape
{
protected:
	const int dumbComb = 20;
	int paralellComb;
	long x1, x2, y1, y2;
	long xs1, ys1, xs2, ys2;
public:
	void Set(long x1, long y1, long x2, long y2);
	virtual void Show(HDC) = 0;
	virtual void Trace(HDC) = 0;
	virtual Shape* Duplicate() = 0;
	~Shape();
};

class PointShape : public Shape
{
	virtual void Show(HDC);
	void Trace(HDC);
	virtual Shape* Duplicate();
};

class LineShape : public virtual Shape
{
public:
	virtual void Show(HDC);
	void Trace(HDC);
	virtual Shape* Duplicate();
};

class RectangleShape : public virtual Shape
{
public:
	virtual void Show(HDC);
	void Trace(HDC);
	virtual Shape* Duplicate();
};

class EllipseShape : public virtual Shape
{
public:
	virtual void Show(HDC);
	void Trace(HDC);
	virtual Shape* Duplicate();
};

class CubeShape : public RectangleShape, public LineShape
{
public:
	void Show(HDC);
	void Trace(HDC);
	virtual Shape* Duplicate();
};

class LineOOShape : public LineShape, public EllipseShape
{
public:
	void Show(HDC);
	void Trace(HDC);
	virtual Shape* Duplicate();
};
