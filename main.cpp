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
            emit staticVariable::GetStatic()->w->buttom_Screen->clicked();
        }
        else if(key==49){//49 =1]
            QClipboard* c = QApplication::clipboard();
            c->setText( "Проверка" );
        }
        else if(key == 50){ //50=2
            QDate dateToday = QDate::currentDate();
            QString now=dateToday.toString("Р dd.MM.yy Л2");
            QClipboard* c = QApplication::clipboard();
            c->setText( now );
        }else{
            return CallNextHookEx(hHook, nCode, wParam, lParam);
        }
    }
    else if (wParam ==WM_KEYUP){
           if (key==192 || key==49 || key == 50){

           }else{
               return CallNextHookEx(hHook, nCode, wParam, lParam);
           }
    }

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
