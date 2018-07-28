#include "mainwindow.h"
#include <QScreen>
#include <QDir>
#include <QTimer>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
QWidget *window = new QWidget;
this->setCentralWidget(window);
mainLayout =new QVBoxLayout(this);
QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
buttom_P= new QPushButton("P");
buttom_X= new QPushButton("X");
buttom_Screen= new QPushButton("Screen");
buttom_P->setSizePolicy(sizePolicy);
buttom_X->setSizePolicy(sizePolicy);
buttom_Screen->setSizePolicy(sizePolicy);
QLineEdit *testPole=new QLineEdit;
mainLayout->addWidget(buttom_Screen);
mainLayout->addWidget(buttom_P);
mainLayout->addWidget(buttom_X);
mainLayout->addWidget(testPole);
window->setLayout(mainLayout);
connect(buttom_Screen, SIGNAL(clicked()), this, SLOT(slotScreen()));
connect(buttom_P, SIGNAL(clicked()), this, SLOT(slotButton()));
connect(buttom_X, SIGNAL(clicked()), this, SLOT(slotButton()));
}
void MainWindow::slotButton(){
QObject* obj = sender();
QDate dateToday = QDate::currentDate();
if (obj==buttom_P){
    QString now=dateToday.toString("Р dd.MM.yy Л2");
    buttom_P->setText(now);
    QClipboard* c = QApplication::clipboard();
    c->setText( now );
    buttom_X->setText("X");
}
else if (obj==buttom_X){
    QString now=dateToday.toString("X dd.MM.yy Л2");
    buttom_X->setText(now);
    QClipboard* c = QApplication::clipboard();
    c->setText( now );
    buttom_P->setText("P");
}
}

void MainWindow::slotScreen(){
    QDir imageDir(QDir::current().path()+QString("/screen"));
    if(!imageDir.exists()){
        if(!imageDir.mkdir(imageDir.path())){
            buttom_Screen->setText("Can not create dir: "+imageDir.path());
        }
    }
    buttom_Screen->setText("Screen");
    QScreen * screen = QGuiApplication :: primaryScreen();
    QPixmap originalPixmap = screen->grabWindow( 0 );
    QDate dateToday = QDate::currentDate();
    QString now=dateToday.toString("yyyy.MM.dd");
    for(int i=0;i!=2000;++i){
        if(i==1500){
            buttom_Screen->setText("1500 file today");
            break;
        }
        QString fileName=imageDir.path()+"/"+now+"_"+QString("").setNum(i)+".png";
        QFile image(fileName,this);
        if(!image.exists()){
            if (originalPixmap.save(fileName)){
                buttom_Screen->setStyleSheet("background-color:green;");
                QTimer::singleShot(500, this, SLOT(updateBackground()));

            }else{
                buttom_Screen->setText("Не получилось");
            }
            break;
        }
    }
}
void MainWindow::updateBackground(){
    buttom_Screen->setStyleSheet("");
}
