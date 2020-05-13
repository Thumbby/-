/********************************************************************************
** Form generated from reading UI file 'elevator.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ELEVATOR_H
#define UI_ELEVATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_elevator
{
public:
    QLCDNumber *lcdNumber_elevator;
    QLabel *label_floor;
    QLabel *label_num;
    QLabel *label_door;
    QLabel *label_door_status;

    void setupUi(QWidget *elevator)
    {
        if (elevator->objectName().isEmpty())
            elevator->setObjectName(QString::fromUtf8("elevator"));
        elevator->resize(400, 762);
        lcdNumber_elevator = new QLCDNumber(elevator);
        lcdNumber_elevator->setObjectName(QString::fromUtf8("lcdNumber_elevator"));
        lcdNumber_elevator->setGeometry(QRect(120, 40, 71, 31));
        lcdNumber_elevator->setStyleSheet(QString::fromUtf8("background:rgb(246, 254, 255);\n"
""));
        label_floor = new QLabel(elevator);
        label_floor->setObjectName(QString::fromUtf8("label_floor"));
        label_floor->setGeometry(QRect(40, 50, 72, 15));
        label_num = new QLabel(elevator);
        label_num->setObjectName(QString::fromUtf8("label_num"));
        label_num->setGeometry(QRect(200, 10, 61, 20));
        label_door = new QLabel(elevator);
        label_door->setObjectName(QString::fromUtf8("label_door"));
        label_door->setGeometry(QRect(220, 50, 91, 16));
        label_door_status = new QLabel(elevator);
        label_door_status->setObjectName(QString::fromUtf8("label_door_status"));
        label_door_status->setGeometry(QRect(320, 50, 72, 15));

        retranslateUi(elevator);

        QMetaObject::connectSlotsByName(elevator);
    } // setupUi

    void retranslateUi(QWidget *elevator)
    {
        elevator->setWindowTitle(QCoreApplication::translate("elevator", "Form", nullptr));
        label_floor->setText(QCoreApplication::translate("elevator", "<html><head/><body><p><span style=\" font-weight:600; color:#00557f;\">\345\275\223\345\211\215\346\245\274\345\261\202\357\274\232</span></p></body></html>", nullptr));
        label_num->setText(QCoreApplication::translate("elevator", "<html><head/><body><p><span style=\" font-size:12pt; font-weight:600; color:#5500ff;\"><br/></span></p></body></html>", nullptr));
        label_door->setText(QCoreApplication::translate("elevator", "<html><head/><body><p><span style=\" font-weight:600; color:#00557f;\">\345\275\223\345\211\215\351\227\250\347\212\266\346\200\201\357\274\232</span></p></body></html>", nullptr));
        label_door_status->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class elevator: public Ui_elevator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ELEVATOR_H
