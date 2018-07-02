#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QPushButton>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QDateTime>
#include <QClipboard>
#include <QLineEdit>
#include <QApplication>
#include <QLabel>
#include <QTime>
#include <QDebug>
#include <QTimer>
#include <QCheckBox>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QVBoxLayout *mainLayout;
    QPushButton *buttom_X;
    QPushButton *buttom_P;
    QPushButton *buttom_Screen;
    explicit MainWindow(QWidget *parent = 0);
private slots:
    void slotButton();
    void slotScreen();
    void updateBackground();
};
struct staticVariable{
    MainWindow *w;
    staticVariable(){
        w=new MainWindow();
    }
    static staticVariable * GetStatic(){
        static staticVariable * statica=new staticVariable;
        return statica;
    }
};
#endif // MAINWINDOW_H
