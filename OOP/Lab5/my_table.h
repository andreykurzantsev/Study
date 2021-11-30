#pragma once
#include "framework.h"
#include <fstream>
class MyTable {
private:
	std::vector<std::vector<int>> someTable;
	std::string path = "table.txt";
	std::fstream file;
	void AddToFile(int, int*);

public:
	MyTable();
	std::string ParseType(int);
	void FileManage();
	void AddToTable(int, int*);
	std::vector<std::vector<int>> getInfo() { return someTable; }
};

void DialogMain(HINSTANCE, HWND, MyTable&);
void DisplayTable(HWND);
void RefreshTable(MyTable&);