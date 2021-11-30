#include "framework.h"
#include "pch.h"
#include "my_editor.h"
#include "toolbar.h"

MyEditor* MyEditor::p_instance = 0;

MyEditor* MyEditor::getInstance()
{
	if (!p_instance)
		p_instance = new MyEditor();
	return p_instance;
}

MyEditor::MyEditor() {

}

MyEditor::~MyEditor()
{
	delete[] pcshape;
}

void MyEditor::Start(Shape* shape)
{
	pcshape[size] = shape;
}

void MyEditor::OnLMBDown(HWND hWnd)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x1 = x2 = pt.x;
	y1 = y2 = pt.y;
	isPressed = true;
}

void MyEditor::OnLMBUp(HWND hWnd)
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	x2 = pt.x;
	y2 = pt.y;
	isPressed = false;
	pcshape[size]->Set(x1, y1, x2, y2);
	size++;
	InvalidateRect(hWnd, NULL, TRUE);
	pcshape[size] = pcshape[size - 1]->Duplicate();
}

void MyEditor::OnMouseMove(HWND hWnd)
{
	if (isPressed)
	{
		POINT pt;
		HDC hdc = GetDC(hWnd);
		SetROP2(hdc, R2_NOTXORPEN);
		MoveToEx(hdc, x1, y1, NULL);
		pcshape[size]->Set(x1, y1, x2, y2);
		pcshape[size]->Trace(hdc);
		GetCursorPos(&pt);
		ScreenToClient(hWnd, &pt);
		x2 = pt.x;
		y2 = pt.y;
		MoveToEx(hdc, x1, y1, NULL);
		pcshape[size]->Set(x1, y1, x2, y2);
		pcshape[size]->Trace(hdc);
		ReleaseDC(hWnd, hdc);
	}
}

void MyEditor::OnPaint(HWND hWnd, HDC hdc)
{
	for (int i = 0; i < size; i++)
	{
		if (pcshape[i])
		{
			pcshape[i]->Show(hdc);
		}
	}
}

int* MyEditor::getCoord()
{
	return pcshape[size - 1]->getCoord();
}

int MyEditor::getID()
{
	return pcshape[size - 1]->ID();
}