#include "shape.h"



void Shape::Set(long x1, long y1, long x2, long y2)
{
	xs1 = x1;
	ys1 = y1;
	xs2 = x2;
	ys2 = y2;
}

void PointShape::Show(HDC hdc)
{
	SetPixel(hdc, xs1, ys1, black);
}

void PointShape::Trail(HDC hdc) {}

Shape* PointShape::Duplicate()
{
	return new PointShape();
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

void LineShape::Trail(HDC hdc)
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

void RectangleShape::Show(HDC hdc)
{
	HPEN hPen, hPenOld;
	HBRUSH hBrush, hBrushOld;
	hPen = CreatePen(PS_SOLID, 1, black);
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	hBrush = CreateSolidBrush(NULL_BRUSH);
	hBrushOld = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));
	Rectangle(hdc, xs1, ys1, xs2, ys2);
	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

void RectangleShape::Trail(HDC hdc)
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

void EllipseShape::Trail(HDC hdc)
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

void LineOOShape::Show(HDC hdc)
{
	x1 = xs1;
	y1 = ys1;
	x2 = xs2;
	y2 = ys2;
	LineShape::Set(x1, y1, x2, y2);
	LineShape::Show(hdc);
	EllipseShape::Set(x1, y1,
		x1 - dumbComb, y1 - dumbComb);
	EllipseShape::Show(hdc);
	EllipseShape::Set(x2, y2,
		x2 - dumbComb, y2 - dumbComb);
	EllipseShape::Show(hdc);
	LineShape::Set(x1, y1, x2, y2);
}

void LineOOShape::Trail(HDC hdc)
{
	x1 = xs1;
	y1 = ys1;
	x2 = xs2;
	y2 = ys2;
	LineShape::Set(x1, y1, x2, y2);
	LineShape::Trail(hdc);
	EllipseShape::Set(x1, y1,
		x1 - dumbComb, y1 - dumbComb);
	EllipseShape::Trail(hdc);
	EllipseShape::Set(x2, y2,
		x2 - dumbComb, y2 - dumbComb);
	EllipseShape::Trail(hdc);
	LineShape::Set(x1, y1, x2, y2);
}

Shape* LineOOShape::Duplicate()
{
	return new LineOOShape();
}

void CubeShape::Show(HDC hdc)
{
	x1 = xs1; 
	y1 = ys1; 
	x2 = xs2; 
	y2 = ys2;
	RectangleShape::Set(x1 - paralellComb, y1 - paralellComb,
		x1 + paralellComb, y1 + paralellComb);
	RectangleShape::Show(hdc);
	RectangleShape::Set(x2 - paralellComb, y2 - paralellComb,
		x2 + paralellComb, y2 + paralellComb);
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
	LineShape::Set(x1, y1, x2, y2);
}

void CubeShape::Trail(HDC hdc)
{
	x1 = xs1; y1 = ys1; x2 = xs2; y2 = ys2;
	RectangleShape::Set(x1 - paralellComb, y1 - paralellComb,
		x1 + paralellComb, y1 + paralellComb);
	RectangleShape::Trail(hdc);
	RectangleShape::Set(x2 - paralellComb, y2 - paralellComb,
		x2 + paralellComb, y2 + paralellComb);
	RectangleShape::Trail(hdc);
	LineShape::Set(x1 - paralellComb, y1 - paralellComb,
		x2 - paralellComb, y2 - paralellComb);
	LineShape::Trail(hdc);
	LineShape::Set(x1 - paralellComb, y1 + paralellComb,
		x2 - paralellComb, y2 + paralellComb);
	LineShape::Trail(hdc);
	LineShape::Set(x1 + paralellComb, y1 + paralellComb,
		x2 + paralellComb, y2 + paralellComb);
	LineShape::Trail(hdc);
	LineShape::Set(x1 + paralellComb, y1 - paralellComb,
		x2 + paralellComb, y2 - paralellComb);
	LineShape::Trail(hdc);
	LineShape::Set(x1, y1, x2, y2);
}

Shape* CubeShape::Duplicate()
{
	return new CubeShape();
}

Shape::~Shape() {};