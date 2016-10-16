#include <QApplication>
#include "msc.h"
#include <iostream>

#include "windows.h"

MSc *wmsc;

LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam){
    Q_UNUSED(code);
    Q_UNUSED(wParam);
    if(lParam >  0x8000){ wmsc->keySignal();}
    return CallNextHookEx(NULL, code, wParam, lParam);
}

using namespace std;

int main(int argc, char *argv[])
{
//    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    QApplication a(argc, argv);
    MSc w;
    wmsc = &w;
    if (argc > 1){
        QString args(argv[1]);
        if(args!="-h" && args!="--hide")
            w.show();
    }
    else
        w.show();
    cout << argc << argv[1] << endl;
    HINSTANCE hInstance = GetModuleHandle(NULL);
    SetWindowsHookEx(WH_KEYBOARD_LL,KeyboardProc,hInstance,NULL);
    SetWindowsHookEx(WH_MOUSE_LL,KeyboardProc,hInstance,NULL);
    return a.exec();
}

