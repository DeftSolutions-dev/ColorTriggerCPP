#include <iostream>
#include <windows.h>
#include <string>
#include <thread>
#include <iomanip>

using namespace std;

bool IsKeyPressed(int vKey) {
    return GetAsyncKeyState(vKey) < 0;
}

COLORREF GetPixelColorFromCenterWithOffset(int xOffset, int yOffset) {
    HWND hDesktop = GetDesktopWindow();
    HDC hScreenDC = GetDC(hDesktop);

    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    int centerX = screenWidth / 2 + xOffset;
    int centerY = screenHeight / 2 + yOffset;
    
    COLORREF colorRef = GetPixel(hScreenDC, centerX, centerY);

    ReleaseDC(hDesktop, hScreenDC);
    return colorRef;
}

COLORREF GetPixelColorFromCursor(int x, int y) {
    HDC hScreenDC = GetDC(NULL);
    COLORREF colorRef = GetPixel(hScreenDC, x, y);
    ReleaseDC(NULL, hScreenDC);
    return colorRef;
}

void MouseClick(int ms) {
    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.time = 0;
    input.mi.dwExtraInfo = 0;
    this_thread::sleep_for(chrono::milliseconds(ms));
    input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    if (SendInput(1, &input, sizeof(INPUT)) == 0) {
        cerr << "Ошибка при отправке события нажатия мыши: " << GetLastError() << endl;
    }
    this_thread::sleep_for(chrono::milliseconds(1));
    input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    if (SendInput(1, &input, sizeof(INPUT)) == 0) {
        cerr << "Ошибка при отправке события отпускания мыши: " << GetLastError() << endl;
    }
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

    int ms;
    cout << "Введите значение клика в миллисекундах (от 0 до 100): ";
    cin >> ms;
    while (ms < 0 || ms > 100) {
        cout << "Некорректное значение клика в миллисекундах. Пожалуйста, введите число от 0 до 100." << endl;
        cin >> ms;
    }

    cout << "Выберите бинд (X, F, LALT, Mouse4, Mouse5): ";
    string selectedBind;
    cin >> selectedBind;
    while (selectedBind != "X" && selectedBind != "F" && selectedBind != "LALT" && selectedBind != "Mouse4" && selectedBind != "Mouse5") {
        cout << "Некорректный выбор бинда. Пожалуйста, выберите из предложенных биндов(X, F, LALT, Mouse4, Mouse5):" << endl;
        cin >> selectedBind;
    }

    cout << "Выберите источник цвета (cursor или center): ";
    string colorSource;
    cin >> colorSource;
    while (colorSource != "cursor" && colorSource != "center") {
        cout << "Некорректный источник цвета. Пожалуйста, выберите 'cursor' или 'center':" << endl;
        cin >> colorSource;
    }

    cout << "Успешно, скрыть/вернуть консоль на Insert/Delete!" << endl;
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
            COLORREF color1;
            if (colorSource == "cursor") {
                POINT cursorPos;
                GetCursorPos(&cursorPos);
                color1 = GetPixelColorFromCursor(cursorPos.x + 2, cursorPos.y + 2);
            }
            else {
                color1 = GetPixelColorFromCenterWithOffset(2, 2);
            }

            COLORREF color2;
            if (colorSource == "cursor") {
                POINT cursorPos;
                GetCursorPos(&cursorPos);
                color2 = GetPixelColorFromCursor(cursorPos.x + 2, cursorPos.y + 2);
            }
            else {
                color2 = GetPixelColorFromCenterWithOffset(2, 2);
            }

            BYTE r1 = GetRValue(color1);
            BYTE g1 = GetGValue(color1);
            BYTE b1 = GetBValue(color1);

            BYTE r2 = GetRValue(color2);
            BYTE g2 = GetGValue(color2);
            BYTE b2 = GetBValue(color2);

            if (abs(r1 - r2) > threshold || abs(g1 - g2) > threshold || abs(b1 - b2) > threshold) {
                cout << "с RGB:(" << static_cast<int>(r1) << ", " << static_cast<int>(g1) << ", " << static_cast<int>(b1) << ") на ";
                cout << "RGB(" << static_cast<int>(r2) << ", " << static_cast<int>(g2) << ", " << static_cast<int>(b2) << "). Произведён клик!" << endl;
                MouseClick(ms);
            }
        }
    }
    return 0;
}
