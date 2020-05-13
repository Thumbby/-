#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include<QCloseEvent>
#include"elevator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void Time_check();//更新界面
    bool send_request(elevator* ele,int floor);//发送请求
    void select_ele(int floor);//选择电梯
    int eleRating(elevator*ele,int floor);//电梯调度估值
private:
    Ui::MainWindow *ui;
    std::vector<elevator*> _ELEVATOR;//存储电梯子界面
    std::vector<QPushButton*>_FLOOR_UP;//存储主界面上行按钮
    std::vector<QPushButton*>_FLOOR_DOWN;//存储主界面下行按钮
    std::vector<std::pair<int,int>>ELE_RATING;//存储电梯调度估值
    const int TIME_CHECK=100;//刷新间隔时间，单位为ms
};
#endif // MAINWINDOW_H
