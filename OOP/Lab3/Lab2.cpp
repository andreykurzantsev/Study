#include "framework.h"
#include "pch.h"
#include "Lab2.h"
#include "Resource.h"
#include "shape_editor.h"
#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")

#define MAX_LOADSTRING 100

HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

HWND hwndToolBar = NULL;
#define IDC_MY_TOOLBAR 1
#define ID_TOOL_POINT 1
#define ID_TOOL_LINE 2
#define ID_TOOL_RECTANGLE 3
#define ID_TOOL_ELLIPSE 4
int toolbarButtons[4] = { ID_TOOL_POINT, ID_TOOL_LINE , ID_TOOL_RECTANGLE , ID_TOOL_ELLIPSE };
int isToolbarPressed = 0;

ShapeObjectsEditor shapeobjeditor;

void createToolbar(HWND hWnd);
void resizeToolbar(HWND hWnd);
void notifyToolbar(HWND hWnd, WPARAM wParam, LPARAM lParam);
void pressToolbar(HWND hWnd, int id);

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    InitCommonControls(); // Toolbar init

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LAB2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LAB2));

    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB2));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LAB2);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_LAB2));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance;

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_CREATE:
        createToolbar(hWnd); //тут створимо Toolbar
        break;
    case WM_SIZE: //це повідомлення надсилається, якщо вікно змінить розмір
        resizeToolbar(hWnd);
        break;
    case WM_NOTIFY: //повідомлення від кнопок
        notifyToolbar(hWnd, wParam, lParam);
        break;

    case WM_LBUTTONDOWN:
        shapeobjeditor.OnLMBdown(hWnd); //натиснуто ліву кнопку миші у клієнтській частині вікна
        break;
    case WM_LBUTTONUP:
        shapeobjeditor.OnLMBup(hWnd); //відпущено ліву кнопку миші у клієнтській частині вікна
        break;
    case WM_MOUSEMOVE:
        shapeobjeditor.OnMouseMove(hWnd); //пересунуто мишу у клієнтській частині вікна
        break;
    case WM_PAINT:
        shapeobjeditor.OnPaint(hWnd); //потрібно оновлення зображення клієнтської частині вікна
        break;
    case WM_COMMAND: {
        int wmId = LOWORD(wParam);
        switch (wmId) {
            // Point
        case ID_TOOL_POINT:
        case IDM_POINT:
            pressToolbar(hWnd, ID_TOOL_POINT);
            shapeobjeditor.StartPointEditor(hWnd); //початок вводу точкових об’єктів
            break;

            // LINE
        case ID_TOOL_LINE:
        case IDM_LINE:
            pressToolbar(hWnd, ID_TOOL_LINE);
            shapeobjeditor.StartLineEditor(hWnd); //початок вводу об’єктів-ліній
            break;

            // RECTANGLE
        case ID_TOOL_RECTANGLE:
        case IDM_RECTANGLE:
            pressToolbar(hWnd, ID_TOOL_RECTANGLE);
            shapeobjeditor.StartRectangleEditor(hWnd); //початок вводу прямокутників
            break;

            // ELLIPSE
        case ID_TOOL_ELLIPSE:
        case IDM_ELLIPSE:
            pressToolbar(hWnd, ID_TOOL_ELLIPSE);
            shapeobjeditor.StartEllipseEditor(hWnd); //початок вводу еліпсів
            break;

        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProcW(hWnd, message, wParam, lParam);
        }
    }
                   break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProcW(hWnd, message, wParam, lParam);
    }
    return 0;
}

void createToolbar(HWND hWnd) {
    TBBUTTON tbb[4];

    ZeroMemory(tbb, sizeof(tbb));

    tbb[0].iBitmap = 0; //стандартне зображення
    tbb[0].fsState = TBSTATE_ENABLED;
    tbb[0].fsStyle = TBSTYLE_BUTTON; //тип елементу - кнопка
    tbb[0].idCommand = ID_TOOL_POINT; //цей ID буде у повідомленні WM_COMMAND

    tbb[1].iBitmap = 1;
    tbb[1].fsState = TBSTATE_ENABLED;
    tbb[1].fsStyle = TBSTYLE_BUTTON;
    tbb[1].idCommand = ID_TOOL_LINE;

    tbb[2].iBitmap = 2;
    tbb[2].fsState = TBSTATE_ENABLED;
    tbb[2].fsStyle = TBSTYLE_BUTTON;
    tbb[2].idCommand = ID_TOOL_RECTANGLE;

    tbb[3].iBitmap = 3;
    tbb[3].fsState = TBSTATE_ENABLED;
    tbb[3].fsStyle = TBSTYLE_BUTTON;
    tbb[3].idCommand = ID_TOOL_ELLIPSE;

    hwndToolBar = CreateToolbarEx(hWnd,
        WS_CHILD | WS_VISIBLE | WS_BORDER |
        WS_CLIPSIBLINGS | CCS_TOP |
        TBSTYLE_TOOLTIPS,
        IDC_MY_TOOLBAR,
        4,
        hInst,
        IDB_BITMAP1,
        tbb,
        4,
        24, 24, 24, 24,
        sizeof(TBBUTTON));
}

void resizeToolbar(HWND hWnd) {
    RECT rc, rw;

    if (hwndToolBar) {
        GetClientRect(hWnd, &rc); //нові розміри головного вікна
        GetWindowRect(hwndToolBar, &rw); //нам потрібно знати висоту Toolbar
        MoveWindow(hwndToolBar, 0, 0, rc.right - rc.left, rw.bottom - rw.top, FALSE);
    }
}

void notifyToolbar(HWND hWnd, WPARAM wParam, LPARAM lParam) {
    LPNMHDR pnmh = (LPNMHDR)lParam;

    if (pnmh->code == TTN_NEEDTEXT) {
        LPTOOLTIPTEXT lpttt = (LPTOOLTIPTEXT)lParam;
        switch (lpttt->hdr.idFrom) {
        case ID_TOOL_POINT:
            lstrcpy(lpttt->szText, L"Крапка");
            break;
        case ID_TOOL_LINE:
            lstrcpy(lpttt->szText, L"Лінія");
            break;
        case ID_TOOL_RECTANGLE:
            lstrcpy(lpttt->szText, L"Прямокутник");
            break;
        case ID_TOOL_ELLIPSE:
            lstrcpy(lpttt->szText, L"Овал");
            break;
        default: lstrcpy(lpttt->szText, L"Щось невідоме");
        }
    }
}

void pressToolbar(HWND hWnd, int id) {
    int length = sizeof(toolbarButtons) / sizeof(*toolbarButtons);
    for (int i = 0; i < length; i++) {
        int el = toolbarButtons[i];
        if (el == id) SendMessage(hwndToolBar, TB_PRESSBUTTON, id, 1);
        else SendMessage(hwndToolBar, TB_PRESSBUTTON, el, 0);
    }
}