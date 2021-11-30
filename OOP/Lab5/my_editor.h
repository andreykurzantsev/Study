#pragma once
#include "pch.h"
#include "Resource.h"
#include "shape.h"
#include "editor.h"

class MyEditor : public Editor 
{
private:
	const int Size_Of_Array = 103;
	Shape** pcshape = new Shape * [Size_Of_Array];
	int size = 0;
	bool isPressed;
	int allMenus[6] = { IDM_POINT, IDM_LINE, IDM_RECTANGLE, IDM_ELLIPSE, IDM_LINEOO, IDM_CUBE };


	//Sing

	static MyEditor* p_instance;
	MyEditor();
	MyEditor(const MyEditor&);
	MyEditor& operator= (MyEditor&);

public:
	static MyEditor* getInstance();
	void Start(Shape*);
	void OnLMBDown(HWND);
	void OnLMBUp(HWND);
	void OnMouseMove(HWND);
	void OnPaint(HWND, HDC);
	~MyEditor();
	long x1, y1, x2, y2;

	int* getCoord();
	int getID();
};