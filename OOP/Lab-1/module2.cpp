#include "framework.h"
#include "resource2.h"

static WCHAR buffer[256];
static int posCount;
static HWND hWnd;

static INT_PTR CALLBACK Work2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)

{
    static HWND Scroll_Label;
    static int count_m = 1; int count_M = 100;

    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        Scroll_Label = GetDlgItem(hDlg, IDC_SCROLLBAR1);
        SetScrollRange(Scroll_Label, SB_CTL, count_m, count_M, TRUE);
        SetDlgItemInt(hDlg, IDC_STATIC1, posCount, TRUE); 
        return (INT_PTR)TRUE;

    case WM_HSCROLL:


        posCount = GetScrollPos(GetDlgItem(hDlg, IDC_SCROLLBAR1), SB_CTL);

        switch (LOWORD(wParam))
        {
        case SB_LINELEFT: //натиснуто кнопку ліворуч
            posCount--;
            SetDlgItemInt(hDlg, IDC_STATIC1, posCount, TRUE);
            break;
        case SB_LINERIGHT: //натиснуто кнопку праворуч
            posCount++;
            SetDlgItemInt(hDlg, IDC_STATIC1, posCount, TRUE);
            break;
        case SB_THUMBPOSITION: //фіксована позиція повзуна
        case SB_THUMBTRACK: //поточна позиція повзуна
            posCount = HIWORD(wParam);
            SetDlgItemInt(hDlg, IDC_STATIC1, posCount, TRUE);
            break;
        default: break;
        }

        SetScrollPos(Scroll_Label, SB_CTL, posCount, TRUE); //фіксація повзуна
        SetDlgItemInt(hDlg, IDC_STATIC1, posCount, TRUE);
        break;

    default: break;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK)
        {
            GetDlgItemTextW(hDlg, IDC_STATIC1, buffer, 255);
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

int MyFunc2(HINSTANCE hInst, HWND hWnd, WCHAR* dest) {
    if (DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG2), hWnd, Work2) == 1) {
        lstrcpyW(dest, buffer);
        return 1;
    }
    return 0;
}