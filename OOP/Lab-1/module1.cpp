#include "framework.h"
#include "resource1.h"

static WCHAR buffer[256];
static HWND hWnd;

INT_PTR CALLBACK Work1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK)
        {
            GetDlgItemTextW(hDlg, IDC_EDIT1, buffer, 255);
            EndDialog(hDlg, 1);
            return (INT_PTR)TRUE;
        }

        if (LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, 0);
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;


}

int MyFunc1(HINSTANCE hInst, HWND hWnd, WCHAR* dest) {
    if (DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Work1) == 1) {
        lstrcpyW(dest, buffer);
        return 1;
    }
    return 0;
}
