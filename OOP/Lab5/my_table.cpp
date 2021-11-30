#include "my_table.h"
#include "Resource.h"
#include "resource1.h"

MyTable::MyTable()
{
}

std::string MyTable::ParseType(int type)
{
	int types[6] = { IDM_POINT, IDM_LINE, IDM_RECTANGLE, IDM_ELLIPSE, IDM_LINEOO, IDM_CUBE };
	std::string types_names[6] = { "Точка\t\t", "Лінія\t\t", "Прямокутник\t", "Еліпс\t\t", "Лінія з точками\t", "Паралелепіпід\t" };

	std::string temp;
	for (int i = 0; i < 6; i++)
	{
		if (type == types[i])
		{
			temp = types_names[i];
		}
	}
	return temp;
}


void MyTable::FileManage()
{
	file.open(path, std::ios::out);
	file.close();
}

void MyTable::AddToTable(int type, int* coord)
{
	AddToFile(type, coord);
	std::vector<int> temp;

	temp.push_back(type);
	for (int i = 0; i < 4; i++)
	{
		temp.push_back(coord[i]);
	}

	someTable.push_back(temp);
}

void MyTable::AddToFile(int type, int* coord)
{
	std::string temp = ParseType(type);
	file.open(path, std::ios::app);
	file << temp << std::endl;

	for (int i = 0; i < 4; i++)
	{
		file << coord[i] << '\t';
	}
	file << std::endl;
	file.close();
}


HWND dlghWnd;
MyTable* auxTable;
int selCursel = -1;

INT_PTR CALLBACK dlgProcedure(HWND, UINT, WPARAM, LPARAM);

INT_PTR CALLBACK dlgProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_INITDIALOG:
		{
			DisplayTable(hWnd);
			break;
		}
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case ID_CANCEL:
				DestroyWindow(hWnd);
				return 0;
			}
		}
		case WM_LBUTTONDOWN:
		case WM_LBUTTONUP:
		{
			break;
		}
		case WM_CLOSE:
		{
			DestroyWindow(hWnd);
			break;
		}
		case WM_DESTROY:
		{
			dlghWnd = NULL;
			break;
		}
	}
	return (INT_PTR)FALSE;
}

void DialogMain(HINSTANCE hInst, HWND hWnd, MyTable& sTable)
{
	if (!dlghWnd)
	{
		auxTable = &sTable;
		dlghWnd = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, (DLGPROC)dlgProcedure);
		ShowWindow(dlghWnd, SW_SHOW);
	}
}

void DisplayTable(HWND hWnd)
{
	std::vector<std::vector<int>> someTable = auxTable->getInfo();
	std::string info;
	std::string first_row = "Name\t\tx1\ty1\tx2\ty2";
	SendDlgItemMessage(hWnd, IDC_LIST1, LB_INSERTSTRING, 0, (LPARAM)first_row.c_str());
	int curr = 1;
	for (std::vector<int> i : someTable)
	{
		info += auxTable->ParseType(i[0]);
		for (int j = 1; j < i.size(); j++)
		{
			info += std::to_string(i[j]) + '\t';
		}
		SendDlgItemMessage(hWnd, IDC_LIST1, LB_INSERTSTRING, curr, (LPARAM)info.c_str());
		curr++;
		info = "";
	}
}

void RefreshTable(MyTable& sTable)
{
	auxTable = &sTable;
	SendDlgItemMessage(dlghWnd, IDC_LIST1, LB_RESETCONTENT, 0, 0);
	DisplayTable(dlghWnd);
}
