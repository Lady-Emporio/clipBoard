#include "mainwindow.h"
#include <windows.h>
#include <QDebug>
HHOOK hHook = NULL;

LRESULT CALLBACK MyLowLevelKeyBoardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (wParam == WM_KEYDOWN){
        KBDLLHOOKSTRUCT cKey = *((KBDLLHOOKSTRUCT*)lParam);
        int key=cKey.vkCode;
        if (key==192){
            emit staticVariable::GetStatic()->w->buttom_Screen->clicked();
        }
    }
    return CallNextHookEx(hHook, nCode, wParam, lParam);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow *w=staticVariable::GetStatic()->w;
    w->resize(200,250);
    w->show();
    hHook = SetWindowsHookEx(WH_KEYBOARD_LL, MyLowLevelKeyBoardProc, NULL, 0);
    if (hHook == NULL)
    {
        w->buttom_Screen->setText("Hook Failed");
    }

    return a.exec();
}
