#include "mainwindow.h"
#include <windows.h>
#include <QDebug>
HHOOK hHook = NULL;

LRESULT CALLBACK MyLowLevelKeyBoardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    KBDLLHOOKSTRUCT cKey = *((KBDLLHOOKSTRUCT*)lParam);
    int key=cKey.vkCode;
    if (wParam == WM_KEYDOWN ){
        if (key==192){
            staticVariable::GetStatic()->w->buttom_Screen->clicked();
            return 1;
        }
        else if(key==49){//49 =1]
            QClipboard* c = QApplication::clipboard();
            c->setText( "Проверка" );
            return 1;
        }
        else if(key == 50){ //50=2
            QDate dateToday = QDate::currentDate();
            QString now=dateToday.toString("Р dd.MM.yy Л2");
            QClipboard* c = QApplication::clipboard();
            c->setText( now );
            return 1;
        }else{
            //return 1;
            return CallNextHookEx(hHook, nCode, wParam, lParam);
        }
    }
    else if (wParam == WM_KEYUP){
           if (key==192 || key==49 || key == 50){
                return 1;
           }else{
                //return 1;
                return CallNextHookEx(hHook, nCode, wParam, lParam);
           }
    }
    else{
        return CallNextHookEx(hHook, nCode, wParam, lParam);
    }
    return 1;

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
