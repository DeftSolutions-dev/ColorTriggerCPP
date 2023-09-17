#include <iostream>
#include <windows.h>
#include <gdiplus.h>
#include <string>
#include <thread>

using namespace std;
using namespace Gdiplus;

bool IsKeyPressed(int vKey) {
    return GetAsyncKeyState(vKey) < 0;
}

Color GetPixelColor(int x, int y) {
    HDC hScreenDC = GetDC(NULL);
    COLORREF colorRef = GetPixel(hScreenDC, x, y);
    ReleaseDC(NULL, hScreenDC);
    return Color::MakeARGB(255, GetRValue(colorRef), GetGValue(colorRef), GetBValue(colorRef));
}

void MouseClick() {
    INPUT input = { 0 };
    //this_thread::sleep_for(chrono::milliseconds(10));
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &input, sizeof(INPUT));
    this_thread::sleep_for(chrono::milliseconds(1));
    ZeroMemory(&input, sizeof(INPUT));
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &input, sizeof(INPUT));
}

int main() {
    setlocale(LC_ALL, "");
    SetConsoleTitle(L"https://t.me/devilLucifer69 / DS: desirepro");

    int threshold;
    cout << "Введите значение порога (от 4 до 20): ";
    while (true) {
        cin >> threshold;
        if (threshold >= 4 && threshold <= 20)
            break;
        else
            cout << "Некорректное значение порога. Пожалуйста, введите число от 4 до 20." << endl;
    }

    cout << "Выберите бинд (X, F, LALT, Mouse3, Mouse4): ";
    string selectedBind;
    cin >> selectedBind;

    cout << "Good!" << endl;
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
    else if (selectedBind == "Mouse3") {
        bindKey = VK_MBUTTON;
    }
    else if (selectedBind == "Mouse4") {
        bindKey = VK_XBUTTON1;
    }
    while (true) {
        if (IsKeyPressed(VK_UP)) {
            if (threshold < 20)
                threshold++;
            cout << "Порог увеличен до " << threshold << endl;
        }
        else if (IsKeyPressed(VK_DOWN)) {
            if (threshold > 4)
                threshold--;
            cout << "Порог уменьшен до " << threshold << endl;
        }

        if (IsKeyPressed(bindKey)) {
            POINT p;
            GetCursorPos(&p);
            int x = p.x + 2;
            int y = p.y + 2;
            Color color1 = GetPixelColor(x, y);

            GetCursorPos(&p);
            x = p.x + 2;
            y = p.y + 2;
            Color color2 = GetPixelColor(x, y);

            if (abs(color1.GetR() - color2.GetR()) > threshold ||
                abs(color1.GetG() - color2.GetG()) > threshold ||
                abs(color1.GetB() - color2.GetB()) > threshold) {
                cout << "Color: " << color2.GetValue() << endl;
                MouseClick(); 
            }
        }
    }
    return 0;
}
