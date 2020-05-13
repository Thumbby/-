#ifndef ELEVATOR_H
#define ELEVATOR_H

#include <QWidget>
#include<QString>
#include<QLabel>
#include<QFont>
#include<QTimer>
#include<QPushButton>
#include<QElapsedTimer>
#include<QQueue>

namespace Ui {
class elevator;
}

class elevator : public QWidget
{
    Q_OBJECT

public:
    explicit elevator(QWidget *parent =nullptr, int _Num = 0,int FLOOR_NUM=20);
    ~elevator();
    int Num=0;//电梯编号
    int Floor_Num=0;//楼层数
    int current_floor=1;
    int door=0;//0:closed;1:closing;2:opened;3:opening
    QString door_status[4]= {"Closed", "Closing", "Opened", "Opening"};
    int status=0;//0:stop;1:up;-1:down
    const int TIME_CHECK=1000;//刷新间隔时间，单位为ms
    std::vector<QPushButton*>FLOOR_BUTTON;//保存电梯按钮
    QQueue<int>destination;//存放需要前往的目标楼层
    QPushButton *pushButton_open=new QPushButton(this);//开门
    QPushButton *pushButton_close=new QPushButton(this);//关门
    void time_check();//每隔一段时间刷新楼层
    void OPEN_DOOR();
    void CLOSE_DOOR();
    bool receive_request(int dest);
    int WORKING_CHECK();
private:
    Ui::elevator *ui;
};

#endif // ELEVATOR_H
