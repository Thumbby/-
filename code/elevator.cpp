#include "elevator.h"
#include "ui_elevator.h"
elevator::elevator(QWidget *parent, int _Num,int FLOOR_NUM) :
    QWidget(parent),
    ui(new Ui::elevator)
{
    ui->setupUi(this);
    this->ui->label_num->setText(QString::number(_Num));
    QFont font("Arial", 14, 75);
    this->ui->label_num->setFont(font);
    this->ui->lcdNumber_elevator->display(this->current_floor);
    this->ui->label_door_status->setText(door_status[0]);
    this->Num=_Num;
    this->Floor_Num=FLOOR_NUM;

    /*楼层按钮*/
    for(int i = 0; i < FLOOR_NUM; i++){
        QPushButton *button = new QPushButton(this);
            button->setGeometry(140+80*(i%2), 620-60*(i/2), 41, 41);
            button->setText(QString::number(i+1, 10));
            button->show();
            connect(button, &QPushButton::clicked, this, [=] {FLOOR_BUTTON[i]->setEnabled(false);destination.enqueue(i+1);});
        FLOOR_BUTTON.push_back(button);
    }

    pushButton_open->setText("Open");
    pushButton_open->setGeometry(122,680,61,51);
    pushButton_open->show();
    connect(pushButton_open,&QPushButton::clicked,this,[=]{OPEN_DOOR();});

    pushButton_close->setText("Close");
    pushButton_close->setGeometry(220,680,61,51);
    pushButton_close->show();
    connect(pushButton_open,&QPushButton::clicked,this,[=]{CLOSE_DOOR();});

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &elevator::time_check);
    timer->start(TIME_CHECK);
}

elevator::~elevator()
{
    delete ui;
}

void elevator::OPEN_DOOR(){
    door = 3; this->ui->label_door_status->setText(door_status[3]);//Opening: 800ms.
    QElapsedTimer t1;
    t1.start();
    while(t1.elapsed() < 800) QCoreApplication::processEvents();

    door = 2; this->ui->label_door_status->setText(door_status[2]);// Opened: 1000ms.
    QElapsedTimer t2;
    t2.start();
    while(t2.elapsed() < 1000) QCoreApplication::processEvents();

    door = 1;  this->ui->label_door_status->setText(door_status[1]); //Closing: 800ms.
    QElapsedTimer t3;
    t3.start();
    while(t3.elapsed() < 800) QCoreApplication::processEvents();

    door = 0;  this->ui->label_door_status->setText(door_status[0]); //Closed.
}

void elevator::CLOSE_DOOR(){
    QElapsedTimer t1;
    t1.start();
    while(t1.elapsed() < 1000) QCoreApplication::processEvents();

    door = 1;  this->ui->label_door_status->setText(door_status[1]); //Closing: 800ms.
    QElapsedTimer t2;
    t2.start();
    while(t2.elapsed() < 800) QCoreApplication::processEvents();

    door = 0;  this->ui->label_door_status->setText(door_status[0]); //Closed.
}

int elevator::WORKING_CHECK(){
    int GOAL=0;
    if(destination.isEmpty()){
        GOAL=0;
    }
    else{
        if(current_floor<destination.head()){
            GOAL=1;
        }
        else if(current_floor>destination.head()){
            GOAL=-1;
        }
        else{
            OPEN_DOOR();
            destination.dequeue();
            GOAL=0;
        }
    }
    return GOAL;
}

bool elevator::receive_request(int dest){
    if((current_floor<dest&&status==1)||(current_floor>dest&&status==-1)){
        return false;
    }
    destination.enqueue(dest);
    status=WORKING_CHECK();
    return true;
}

void elevator::time_check(){
    if(status!=0){//非法情况下不得开/关门
        pushButton_open->setEnabled(false);
        pushButton_close->setEnabled(false);
    }
    if(status==0&&(door==0||door==1)){//非法情况下不得关门
        pushButton_close->setEnabled(false);
    }
    if(status==0&&(door==2||door==3)){//允许关门情况
        pushButton_close->setEnabled(true);
    }
    if(status==0){
        pushButton_open->setEnabled(true);//允许开门情况
    }
    current_floor+=status;
    for(int i=0;i<Floor_Num;i++){
        if(current_floor==(i+1)){
            FLOOR_BUTTON[i]->setEnabled(true);
        }
    }
    this->ui->lcdNumber_elevator->display(current_floor);
    status=WORKING_CHECK();
}
