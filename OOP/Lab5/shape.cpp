#include "shape.h"
#include "Resource.h"

Shape::~Shape() {};

void Shape::Set(long x1, long y1, long x2, long y2)
{
	xs1 = x1;
	ys1 = y1;
	xs2 = x2;
	ys2 = y2;
}

int* Shape::getCoord()
{
	static int arr[4];
	arr[0] = xs1;
	arr[1] = ys1;
	arr[2] = xs2;
	arr[3] = ys2;
	return arr;
}

void PointShape::Show(HDC hdc)
{
	SetPixel(hdc, xs1, ys1, black);
}

void PointShape::Trace(HDC hdc) {}

Shape* PointShape::Duplicate()
{
	return new PointShape();
}

int PointShape::ID()
{
	return IDM_POINT;
}

void LineShape::Show(HDC hdc)
{
	HPEN hPen, hPenOld;
	hPen = CreatePen(PS_SOLID, 1, black);
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	MoveToEx(hdc, xs1, ys1, NULL);
	LineTo(hdc, xs2, ys2);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

void LineShape::Trace(HDC hdc)
{
	HPEN hPen, hPenOld;
	hPen = CreatePen(PS_DOT, 1, black);
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	MoveToEx(hdc, xs1, ys1, NULL);
	LineTo(hdc, xs2, ys2);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

Shape* LineShape::Duplicate()
{
	return new LineShape();
}

int LineShape::ID()
{
	return IDM_LINE;
}

void RectangleShape::Show(HDC hdc)
{
	HPEN hPen, hPenOld;
	HBRUSH hBrush, hBrushOld;
	hPen = CreatePen(PS_SOLID, 1, black);
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	hBrush = CreateSolidBrush(RGB(192, 192, 192));
	hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);
	Rectangle(hdc, xs1, ys1, xs2, ys2);
	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

void RectangleShape::Trace(HDC hdc)
{
	HPEN hPen, hPenOld;
	hPen = CreatePen(PS_DOT, 1, black);
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	MoveToEx(hdc, xs1, ys1, NULL);
	LineTo(hdc, xs1, ys2);
	LineTo(hdc, xs2, ys2);
	LineTo(hdc, xs2, ys1);
	LineTo(hdc, xs1, ys1);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

Shape* RectangleShape::Duplicate()
{
	return new RectangleShape();
}

int RectangleShape::ID()
{
	return IDM_RECTANGLE;
}

void EllipseShape::Show(HDC hdc)
{
	HPEN hPen, hPenOld;
	HBRUSH hBrush, hBrushOld;
	hPen = CreatePen(PS_SOLID, 1, black);
	hPenOld = (HPEN)SelectObject(hdc, hPen);

	hBrush = CreateSolidBrush(RGB(192, 192, 192));
	hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);
	Ellipse(hdc, 2 * xs1 - xs2, 2 * ys1 - ys2, xs2, ys2);
	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
};

void EllipseShape::Trace(HDC hdc)
{
	HPEN hPen, hPenOld;
	hPen = CreatePen(PS_DOT, 1, black);
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	MoveToEx(hdc, xs1, ys1, NULL);
	Arc(hdc, 2 * xs1 - xs2, 2 * ys1 - ys2, xs2, ys2, 0, 0, 0, 0);

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

Shape* EllipseShape::Duplicate()
{
	return new EllipseShape();
}

int EllipseShape::ID()
{
	return IDM_ELLIPSE;
}

void LineOOShape::Show(HDC hdc)
{
	x1 = xs1;
	y1 = ys1;
	x2 = xs2;
	y2 = ys2;
	LineShape::Set(x1, y1, x2, y2);
	LineShape::Show(hdc);
	EllipseShape::Set(x1, y1, x1 - dumbComb, y1 - dumbComb);
	EllipseShape::Show(hdc);
	EllipseShape::Set(x2, y2, x2 - dumbComb, y2 - dumbComb);
	EllipseShape::Show(hdc);
	LineShape::Set(x1, y1, x2, y2);
}

void LineOOShape::Trace(HDC hdc)
{
	x1 = xs1;
	y1 = ys1;
	x2 = xs2;
	y2 = ys2;
	LineShape::Set(x1, y1, x2, y2);
	LineShape::Trace(hdc);
	EllipseShape::Set(x1, y1, x1 - dumbComb, y1 - dumbComb);
	EllipseShape::Trace(hdc);
	EllipseShape::Set(x2, y2, x2 - dumbComb, y2 - dumbComb);
	EllipseShape::Trace(hdc);
	LineShape::Set(x1, y1, x2, y2);
}

Shape* LineOOShape::Duplicate()
{
	return new LineOOShape();
}

int LineOOShape::ID()
{
	return IDM_LINEOO;
}

void CubeShape::Show(HDC hdc)
{
	RectangleShape::Set(x1 - paralellComb, y1 - paralellComb,
		x1 + paralellComb, y1 + paralellComb);
	RectangleShape::Show(hdc);
	LineShape::Set(x1 - paralellComb, y1 - paralellComb,
		x2 - paralellComb, y2 - paralellComb);
	LineShape::Show(hdc);
	LineShape::Set(x1 - paralellComb, y1 + paralellComb,
		x2 - paralellComb, y2 + paralellComb);
	LineShape::Show(hdc);
	LineShape::Set(x1 + paralellComb, y1 + paralellComb,
		x2 + paralellComb, y2 + paralellComb);
	LineShape::Show(hdc);
	LineShape::Set(x1 + paralellComb, y1 - paralellComb,
		x2 + paralellComb, y2 - paralellComb);
	LineShape::Show(hdc);
	//LineShape::Set(x1, y1, x2, y2);
	RectangleShape::Set(x2 - paralellComb, y2 - paralellComb,
		x2 + paralellComb, y2 + paralellComb);
	RectangleShape::Show(hdc);
}

void CubeShape::Trace(HDC hdc)
{
	x1 = xs1;
	y1 = ys1;
	x2 = xs2;
	y2 = ys2;
	paralellComb = x2 - x1;
	RectangleShape::Set(x1 - paralellComb, y1 - paralellComb,
		x1 + paralellComb, y1 + paralellComb);
	RectangleShape::Trace(hdc);
	RectangleShape::Set(x2 - paralellComb, y2 - paralellComb,
		x2 + paralellComb, y2 + paralellComb);
	RectangleShape::Trace(hdc);
	LineShape::Set(x1 - paralellComb, y1 - paralellComb,
		x2 - paralellComb, y2 - paralellComb);
	LineShape::Trace(hdc);
	LineShape::Set(x1 - paralellComb, y1 + paralellComb,
		x2 - paralellComb, y2 + paralellComb);
	LineShape::Trace(hdc);
	LineShape::Set(x1 + paralellComb, y1 + paralellComb,
		x2 + paralellComb, y2 + paralellComb);
	LineShape::Trace(hdc);
	LineShape::Set(x1 + paralellComb, y1 - paralellComb,
		x2 + paralellComb, y2 - paralellComb);
	LineShape::Trace(hdc);
	//LineShape::Set(x1, y1, x2, y2);
}

Shape* CubeShape::Duplicate()
{
	return new CubeShape();
}

int CubeShape::ID()
{
	return IDM_CUBE;
}