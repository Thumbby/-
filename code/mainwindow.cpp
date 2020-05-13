#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QString>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_exit, &QPushButton::clicked, this, [=]{exit(0);});
    for(int i=1;i<=5;i++){
        elevator* ele=new elevator(nullptr,i,20);
        ele->setGeometry(-400 + 400 * i, 50, 400, 750);
        ele->show();
        _ELEVATOR.push_back(ele);
    }
    this->ui->lcdNumber_ele1->display(_ELEVATOR[0]->current_floor);
    this->ui->lcdNumber_ele2->display(_ELEVATOR[1]->current_floor);
    this->ui->lcdNumber_ele3->display(_ELEVATOR[2]->current_floor);
    this->ui->lcdNumber_ele4->display(_ELEVATOR[3]->current_floor);
    this->ui->lcdNumber_ele5->display(_ELEVATOR[4]->current_floor);

    /*楼层标签*/
    for(int i=0;i<20;i++){
        QLabel *FLOOR_NUM=new QLabel(this);
        FLOOR_NUM->setText(QString::number(i+1,10)+"楼");
        FLOOR_NUM->setGeometry(30+60*(i%10),220+90*(i/10),31,21);
    }

    /*存储上行按钮*/
    for(int i=0;i<20;i++){
        QPushButton* BUTTON_UP=new QPushButton(this);
        BUTTON_UP->setGeometry(30+60*(i%10),250+90*(i/10),31,21);
        BUTTON_UP->setText("↑");
        _FLOOR_UP.push_back(BUTTON_UP);
        connect(_FLOOR_UP[i], &QPushButton::clicked, this, [=]{_FLOOR_UP[i]->setEnabled(false);});
        connect(_FLOOR_UP[i],&QPushButton::clicked,this,[=]{select_ele(i+1);});
    }

    /*存储下行按钮*/
    for(int i=0;i<20;i++){
        QPushButton* BUTTON_DOWN=new QPushButton(this);
        BUTTON_DOWN->setGeometry(30+60*(i%10),280+90*(i/10),31,21);
        BUTTON_DOWN->setText("↓");
        _FLOOR_DOWN.push_back(BUTTON_DOWN);
       connect(_FLOOR_DOWN[i], &QPushButton::clicked, this, [=]{_FLOOR_DOWN[i]->setEnabled(false);});
       connect(_FLOOR_DOWN[i],&QPushButton::clicked,this,[=]{select_ele(i+1);});
    }
    _FLOOR_UP[19]->hide();
    _FLOOR_DOWN[0]->hide();

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::Time_check);
    timer->start(TIME_CHECK);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::send_request(elevator* ele,int floor){
    return ele->receive_request(floor);
}

void MainWindow::select_ele(int floor){
    bool GET_ANSWER=false;
    for(int i=0;i<5;i++){
        ELE_RATING.push_back({i,eleRating(_ELEVATOR[i],floor)});
    }
    std::sort(ELE_RATING.begin(), ELE_RATING.end(),
              [](std::pair<int, int> &a, std::pair<int, int> &b){
                    return a.second < b.second;
    });
    for(auto i:ELE_RATING){
        if(send_request(_ELEVATOR[i.first],floor)){
            GET_ANSWER=true;
            return;
        }
        else{
            continue;
        }
    }
    if(GET_ANSWER==false){
        _ELEVATOR[0]->destination.enqueue(floor);
        _ELEVATOR[0]->status=_ELEVATOR[0]->WORKING_CHECK();
    }
}

int MainWindow::eleRating(elevator *ele, int floor){
    int ans=0;
    if(ele->status==0&&ele->destination.isEmpty()){
        ans+=10000;
    }
    if(!ele->destination.isEmpty()){
        ans+=10*(20-(ele->status*abs(ele->current_floor-floor)));

    }
    return ans;
}

void MainWindow::Time_check(){//更新主界面LCD显示
    this->ui->lcdNumber_ele1->display(_ELEVATOR[0]->current_floor);
    this->ui->lcdNumber_ele2->display(_ELEVATOR[1]->current_floor);
    this->ui->lcdNumber_ele3->display(_ELEVATOR[2]->current_floor);
    this->ui->lcdNumber_ele4->display(_ELEVATOR[3]->current_floor);
    this->ui->lcdNumber_ele5->display(_ELEVATOR[4]->current_floor);
    for(int i=0;i<5;i++){
        if(_ELEVATOR[i]->status==0&&_ELEVATOR[i]->door==0){
            _FLOOR_UP[_ELEVATOR[i]->current_floor-1]->setEnabled(true);
            _FLOOR_DOWN[_ELEVATOR[i]->current_floor-1]->setEnabled(true);
        }
    }
}
