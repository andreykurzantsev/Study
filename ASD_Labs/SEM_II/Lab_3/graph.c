#include <windows.h>
#include <math.h>
#define N 11

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow) {
    const wchar_t ProgName[] = L"Лаба 3";

    HWND hWnd;
    MSG lpMsg;

    WNDCLASS w; //создаём экземпляр структуры WNDCLASS

    w.lpszClassName = ProgName; //имя программы - объявлено выше
    w.hInstance = hInstance; //идентификатор текущего приложения
    w.lpfnWndProc = WndProc; //указатель на функцию окна
    w.hCursor = LoadCursor(NULL, IDC_ARROW); //загружаем курсор
    w.hIcon = 0; //иконки у нас не будет пока
    w.lpszMenuName = 0; //и меню пока не будет
    w.hbrBackground = CreateSolidBrush(RGB(200, 500, 600)); //цвет фона окна
    w.style = CS_HREDRAW | CS_VREDRAW; //стиль - перерисовываемое по х и по у
    w.cbClsExtra = 0;
    w.cbWndExtra = 0;

    if (!RegisterClass(&w))
        return 0;

    //Создадим окно в памяти
    hWnd = CreateWindow(ProgName, //Имя программы
        L"ІП-05 Лаб. №3; Виконав Курзанцев А.І.", //Заголовок окна
        WS_OVERLAPPEDWINDOW, //Стиль окна
        100, //положение окна на экране по х
        100, //положение по у
        1920 / 2, //ширина
        1080 / 2, //висота
        (HWND)NULL, //идентификатор окна
        (HMENU)NULL, //идентификатор меню
        (HINSTANCE)hInstance, //идентификатор экземпляра программы
        (HINSTANCE)NULL); //отсутствие дополнительных параметров

    ShowWindow(hWnd, nCmdShow);

    while (GetMessage(&lpMsg, hWnd, 0, 0)) { //Получаем сообщение из очереди
        TranslateMessage(&lpMsg); //Преобразует сообщения клавиш в символы
        DispatchMessage(&lpMsg); //Передаёт сообщение соответствующей функции окна
    }
    return(lpMsg.wParam);
}

void arrow(HDC hdc, double fi, int px, int py) {
    fi = 3.1416 * (180.0 - fi) / 180.0;
    int lx, ly, rx, ry; //px,py, px=150; py=60;
    lx = px + 15 * cos(fi + 0.3);
    rx = px + 15 * cos(fi - 0.3);
    ly = py + 15 * sin(fi + 0.3);
    ry = py + 15 * sin(fi - 0.3);
    MoveToEx(hdc, lx, ly, NULL);
    LineTo(hdc, px, py);
    LineTo(hdc, rx, ry);
}

void MTXGen(int matrix[N][N], int n3, int n4) {
    srand(0514);
    float num;
    float koef = 1.0 - n3 * 0.02 - n4 * 0.005 - 0.25;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            num = (rand() / (float)RAND_MAX * 2) * koef;
            if (num < 1) matrix[i][j] = 0;
            else matrix[i][j] = 1;
        }
    }
}

void drawGraph(int nn[N], int nx[N], int ny[N], int matrix[N][N], int radius, int type, int dtx, HDC hdc, HPEN KPen, HPEN BPen) {
    int isOriented = type; // 1 - oriented, 0 - nonoriented

    if (!isOriented)
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (i > j) matrix[i][j] = 0;

    // обход матрицы
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (1 == matrix[i][j]) {
                MoveToEx(hdc, nx[i], ny[i], NULL); // старт с первого элемента
                if (i == j) {
                    MoveToEx(hdc, nx[i], ny[j], NULL);
                    Arc(hdc, nx[i], ny[i] - 20, nx[i] + 20, ny[i], nx[i] + 10, ny[i], nx[i], ny[i] - 10);
                }
                if (nx[i] == nx[j]) {
                    if (ny[j] > ny[i]) {
                        if (abs(ny[j] - ny[i]) > 100) {
                            Arc(hdc, nx[i] - 40, ny[i], nx[j] + 40, ny[j], nx[i], ny[i], nx[j], ny[j]);
                            if (isOriented) arrow(hdc, -45.0, nx[j] - radius * 0.8, ny[j] - radius * 0.5);
                        }
                        else {
                            LineTo(hdc, nx[j], ny[j]);
                            if (isOriented) arrow(hdc, 270.0, nx[j], ny[j] - radius);
                        }
                    }
                    else if (ny[j] < ny[i]) {
                        if (abs(ny[j] - ny[i]) > 100) {
                            Arc(hdc, nx[i] - 40, ny[i], nx[j] + 40, ny[j], nx[i], ny[i], nx[j], ny[j]);
                            if (isOriented) arrow(hdc, 135, nx[j] + radius * 0.9, ny[j] + radius * 0.6);
                        }
                        else {
                            LineTo(hdc, nx[j], ny[j]);
                            if (isOriented) arrow(hdc, 90.0, nx[j], ny[j] + radius);
                        }
                    }
                }
                else if (ny[i] == ny[j]) {
                    if (nx[j] > nx[i]) {
                        if (abs(nx[j] - nx[i]) > 100)
                        {
                            Arc(hdc, nx[i], ny[i] - 40, nx[j], ny[j] + 40, nx[j], ny[j], nx[i], ny[i]);
                            if (isOriented) arrow(hdc, -45.0, nx[j] - radius * 0.5, ny[j] - radius * 0.8);
                        }
                        else {
                            LineTo(hdc, nx[j], ny[j]);
                            if (isOriented) arrow(hdc, 0.0, nx[j] - radius, ny[j]);
                        }
                    }
                    else if (nx[j] < nx[i]) {
                        if (abs(nx[j] - nx[i]) > 100) {
                            Arc(hdc, nx[i], ny[i] - 40, nx[j], ny[j] + 40, nx[j], ny[j], nx[i], ny[i]);
                            if (isOriented) arrow(hdc, 135.0, nx[j] + radius * 0.5, ny[j] + radius * 0.8);
                        }
                        else {
                            LineTo(hdc, nx[j], ny[j]);
                            if (isOriented) arrow(hdc, 180.0, nx[j] + radius, ny[j]);
                        }
                    }
                }
                else {
                    int midX = (nx[i] + nx[j]) / 2;
                    int midY = (ny[i] + ny[j]) / 2;
                    if (matrix[i][j] == matrix[j][i])
                    {
                        if (nx[i] > nx[j] && ny[i] < ny[j])
                        {
                            LineTo(hdc, midX - radius, midY - radius);
                            MoveToEx(hdc, midX - radius, midY - radius, NULL);
                            LineTo(hdc, nx[j], ny[j]);
                            if (isOriented) arrow(hdc, 180 + 45, nx[j] + radius * 0.45, ny[j] - radius * 0.6);
                        }
                        else if (nx[i] < nx[j] && ny[i] > ny[j]) {
                            LineTo(hdc, midX + radius, midY + radius);
                            MoveToEx(hdc, midX + radius, midY + radius, NULL);
                            LineTo(hdc, nx[j], ny[j]);
                            if (isOriented) arrow(hdc, 45, nx[j] - radius * 0.5, ny[j] + radius * 0.8);
                        }
                        else if (nx[i] < nx[j] && ny[i] < ny[j]) {
                            LineTo(hdc, midX + radius, midY - radius);
                            MoveToEx(hdc, midX + radius, midY - radius, NULL);
                            LineTo(hdc, nx[j], ny[j]);
                            if (isOriented) arrow(hdc, 270 + 45, nx[j] - radius * 0.5, ny[j] - radius * 0.75);
                        }
                        else if (nx[i] > nx[j] && ny[i] > ny[j]) {
                            LineTo(hdc, midX - radius, midY + radius);
                            MoveToEx(hdc, midX - radius, midY + radius, NULL);
                            LineTo(hdc, nx[j], ny[j]);
                            if (isOriented) arrow(hdc, 135, nx[j] + radius * 0.6, ny[j] + radius * 0.9);
                        }

                    }
                    else {
                        int adjLeg = abs(nx[i] - nx[j]);
                        int oppLeg = abs(ny[i] - ny[j]);
                        double x = (double)oppLeg / (double)adjLeg;
                        double val = 180.8 / 3.14159265;
                        double angle = atan(x) * val;
                        if (nx[i] > nx[j] && ny[i] < ny[j]) {
                            LineTo(hdc, nx[j], ny[j]);
                            if (isOriented) arrow(hdc, 180 + angle, nx[j] + radius * 0.5, ny[j] - radius * 0.3);
                        }
                        else if (nx[i] < nx[j] && ny[i] > ny[j]) {
                            LineTo(hdc, nx[j], ny[j]);
                            if (isOriented) arrow(hdc, angle, nx[j] - radius * 0.5, ny[j] + radius * 0.7);
                        }
                        else if (nx[i] < nx[j] && ny[i] < ny[j]) {
                            LineTo(hdc, nx[j], ny[j]);
                            if (isOriented) arrow(hdc, -angle, nx[j] - radius * 0.5, ny[j] - radius * 0.5);
                        }
                        else if (nx[i] > nx[j] && ny[i] > ny[j]) {
                            LineTo(hdc, nx[j], ny[j]);
                            if (isOriented) arrow(hdc, 180 - angle, nx[j] + radius * 0.5, ny[j] + radius * 0.5);
                        }
                    }
                }
            }
        }
    }

    SelectObject(hdc, BPen);

    // рендер элементов
    for (int i = 0; i < N; i++) {
        Ellipse(hdc, nx[i] - radius, ny[i] - radius, nx[i] + radius, ny[i] + radius);
        TextOut(hdc, nx[i] - dtx, ny[i] - radius / 2, nn[i], i < 9 ? 1 : 2);
    }
};

//Функция окна
LRESULT CALLBACK WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam) {
    HDC hdc; //создаём контекст устройства
    PAINTSTRUCT ps; //создаём экземпляр структуры графического вывода

    //Цикл обработки сообщений
    switch (messg) {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        char* nn[N] = { L"1", L"2", L"3", L"4", L"5", L"6", L"7", L"8", L"9", L"10", L"11", };

        int nx1[N] = { 250, 300, 325, 350, 400, 300, 200, 100, 150, 175, 200 };
        int ny1[N] = { 100, 200, 250, 300, 400, 400, 400, 400, 300, 250, 200 };

        int nx2[N] = { 650, 700 ,725, 750, 800, 700, 600, 500, 550, 575, 600 };
        int ny2[N] = { 100, 200, 250, 300, 400, 400, 400, 400, 300, 250, 200 };

        int radius = 16, dx = 16, dy = 16, dtx = 5;
        int n1 = 0, n2 = 5, n3 = 1, n4 = 4; // 0514
        int matrix[N][N] = { 0 };
        int simMatrix[N][N] = { 0 };
        MTXGen(matrix, n3, n4);
        /*int matrix[N][N] = {
        {0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1},
        {1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0},
        {1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0},
        {0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0},
        {1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1},
        {1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1},
        {1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}};

        int simMatrix[N][N] = {
        {0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
        {1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1},
        {0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1},
        {0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1},
        {0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0},
        {0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0},
        {1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0},
        {0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0},
        {0, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1},
        {1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0};*/

        // создание симметричной матрицы
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (1 == matrix[i][j]) {
                    simMatrix[j][i] = 1;
                    simMatrix[i][j] = 1;
                }

        HPEN BPen = CreatePen(PS_SOLID, 1, RGB(50, 0, 255));
        HPEN KPen = CreatePen(PS_SOLID, 1, RGB(20, 20, 5));

        SelectObject(hdc, KPen);

        drawGraph(nn, nx1, ny1, matrix, radius, 1, dtx, hdc, KPen, BPen);
        drawGraph(nn, nx2, ny2, simMatrix, radius, 0, dtx, hdc, KPen, BPen);

        EndPaint(hWnd, &ps);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return(DefWindowProc(hWnd, messg, wParam, lParam));
    }
    return 0;
}
