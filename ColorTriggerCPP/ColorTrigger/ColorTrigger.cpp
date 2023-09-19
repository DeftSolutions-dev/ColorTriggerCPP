#include <iostream>
#include <windows.h>
#include <string>
#include <thread>
#include <iomanip>

using namespace std;

bool IsKeyPressed(int vKey) {
    return GetAsyncKeyState(vKey) < 0;
}

COLORREF GetPixelColor(int x, int y) {
    HDC hScreenDC = GetDC(NULL);
    COLORREF colorRef = GetPixel(hScreenDC, x, y);
    ReleaseDC(NULL, hScreenDC);
    return colorRef;
}

void MouseClick() {
    INPUT input = { 0 };
    //this_thread::sleep_for(chrono::milliseconds(10)); //Для того, что бы не было мгновенного клика.
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &input, sizeof(INPUT));
    this_thread::sleep_for(chrono::milliseconds(3));
    input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &input, sizeof(INPUT));
}

int main() {
    if (!SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS)) {
        cerr << "Ошибка установки высокого приоритета процесса, запустите от имени админа!" << endl;
        return 1;
    }
    setlocale(LC_ALL, "");
    SetConsoleTitle(L"https://t.me/desirepro / DS: desirepro");

    int threshold;
    cout << "Введите значение порога (от 4 до 20): ";
    cin >> threshold;
    while (threshold < 4 || threshold > 20) {
        cout << "Некорректное значение порога. Пожалуйста, введите число от 4 до 20." << endl;
        cin >> threshold;
    }

    cout << "Выберите бинд (X, F, LALT, Mouse4, Mouse5): ";
    string selectedBind;
    cin >> selectedBind;

    cout << "Good! Чтобы скрыть консоль, нажмите на Delete/Insert" << endl;
    int bindKey = 0;
    if (selectedBind == "X") {
        bindKey = 'X';
    }
    else if (selectedBind == "F") {
        bindKey = 'F';
    }
    else if (selectedBind == "LALT") {
        bindKey = VK_LMENU;
    }
    else if (selectedBind == "Mouse4") {
        bindKey = VK_XBUTTON1;
    }
    else if (selectedBind == "Mouse5") {
        bindKey = VK_XBUTTON2;
    }

    while (true) {
        if (IsKeyPressed(VK_UP) && threshold < 20) {
            cout << "Порог увеличен до " << ++threshold << endl;
            Sleep(200);
        }
        else if (IsKeyPressed(VK_DOWN) && threshold > 4) {
            cout << "Порог уменьшен до " << --threshold << endl;
            Sleep(200);
        }
        if (IsKeyPressed(VK_INSERT) || IsKeyPressed(VK_DELETE)) {
            HWND hwnd = GetConsoleWindow();
            ShowWindow(hwnd, IsWindowVisible(hwnd) ? SW_HIDE : SW_SHOW);
            Sleep(200);
        }
        if (IsKeyPressed(bindKey)) {
            POINT p;
            GetCursorPos(&p);
            int x = p.x + 2;
            int y = p.y + 2;
            COLORREF color1 = GetPixelColor(x, y);

            GetCursorPos(&p);
            x = p.x + 2;
            y = p.y + 2;
            COLORREF color2 = GetPixelColor(x, y);

            BYTE r1 = GetRValue(color1);
            BYTE g1 = GetGValue(color1);
            BYTE b1 = GetBValue(color1);

            BYTE r2 = GetRValue(color2);
            BYTE g2 = GetGValue(color2);
            BYTE b2 = GetBValue(color2);

            if (abs(r1 - r2) > threshold || abs(g1 - g2) > threshold || abs(b1 - b2) > threshold) {
                cout << "с RGB:(" << static_cast<int>(r1) << ", " << static_cast<int>(g1) << ", " << static_cast<int>(b1) << ") на ";
                cout << "RGB(" << static_cast<int>(r2) << ", " << static_cast<int>(g2) << ", " << static_cast<int>(b2) << "). Произведён клик!" << endl;
                MouseClick();
            }
        }
    }
    return 0;
}
