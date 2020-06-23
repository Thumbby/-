#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"user.h"
#include"ui_user.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //开始按钮
    QPushButton* startButton=new QPushButton(this);
    startButton->setText("登录");
    startButton->setGeometry(320,390,120,60);
    connect(startButton,&QPushButton::clicked,this,[=]{subWindow.show();});
    //退出按钮
    QPushButton* exitButton=new QPushButton(this);
    exitButton->setText("退出");
    exitButton->setGeometry(660,470,100,50);
    connect(exitButton,&QPushButton::clicked,this,[=]{exit(0);});
}

MainWindow::~MainWindow()
{
    delete ui;
}

