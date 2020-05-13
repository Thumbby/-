/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label_maintitle;
    QPushButton *pushButton_exit;
    QLCDNumber *lcdNumber_ele1;
    QLCDNumber *lcdNumber_ele2;
    QLCDNumber *lcdNumber_ele3;
    QLCDNumber *lcdNumber_ele4;
    QLCDNumber *lcdNumber_ele5;
    QLabel *label_ele1;
    QLabel *label_ele2;
    QLabel *label_ele3;
    QLabel *label_ele5;
    QLabel *label_ele4;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        MainWindow->setStyleSheet(QString::fromUtf8("background:rgb(255, 255, 255)"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label_maintitle = new QLabel(centralwidget);
        label_maintitle->setObjectName(QString::fromUtf8("label_maintitle"));
        label_maintitle->setGeometry(QRect(320, 0, 181, 21));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(12);
        label_maintitle->setFont(font);
        pushButton_exit = new QPushButton(centralwidget);
        pushButton_exit->setObjectName(QString::fromUtf8("pushButton_exit"));
        pushButton_exit->setGeometry(QRect(740, 450, 51, 31));
        pushButton_exit->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	border-radius:5px;\n"
"    color:black;\n"
"	font-size:15px;\n"
"	background:rgb(205, 223, 255)\n"
"}"));
        lcdNumber_ele1 = new QLCDNumber(centralwidget);
        lcdNumber_ele1->setObjectName(QString::fromUtf8("lcdNumber_ele1"));
        lcdNumber_ele1->setGeometry(QRect(30, 70, 91, 131));
        lcdNumber_ele2 = new QLCDNumber(centralwidget);
        lcdNumber_ele2->setObjectName(QString::fromUtf8("lcdNumber_ele2"));
        lcdNumber_ele2->setGeometry(QRect(180, 70, 91, 131));
        lcdNumber_ele3 = new QLCDNumber(centralwidget);
        lcdNumber_ele3->setObjectName(QString::fromUtf8("lcdNumber_ele3"));
        lcdNumber_ele3->setGeometry(QRect(330, 70, 91, 131));
        lcdNumber_ele4 = new QLCDNumber(centralwidget);
        lcdNumber_ele4->setObjectName(QString::fromUtf8("lcdNumber_ele4"));
        lcdNumber_ele4->setGeometry(QRect(490, 70, 91, 131));
        lcdNumber_ele5 = new QLCDNumber(centralwidget);
        lcdNumber_ele5->setObjectName(QString::fromUtf8("lcdNumber_ele5"));
        lcdNumber_ele5->setGeometry(QRect(650, 70, 91, 131));
        label_ele1 = new QLabel(centralwidget);
        label_ele1->setObjectName(QString::fromUtf8("label_ele1"));
        label_ele1->setGeometry(QRect(50, 40, 72, 15));
        label_ele2 = new QLabel(centralwidget);
        label_ele2->setObjectName(QString::fromUtf8("label_ele2"));
        label_ele2->setGeometry(QRect(190, 40, 72, 15));
        label_ele3 = new QLabel(centralwidget);
        label_ele3->setObjectName(QString::fromUtf8("label_ele3"));
        label_ele3->setGeometry(QRect(350, 40, 72, 15));
        label_ele5 = new QLabel(centralwidget);
        label_ele5->setObjectName(QString::fromUtf8("label_ele5"));
        label_ele5->setGeometry(QRect(670, 40, 72, 15));
        label_ele4 = new QLabel(centralwidget);
        label_ele4->setObjectName(QString::fromUtf8("label_ele4"));
        label_ele4->setGeometry(QRect(510, 40, 72, 15));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_maintitle->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600; color:#55557f;\">\347\224\265\346\242\257\350\260\203\345\272\246\346\250\241\346\213\237\347\263\273\347\273\237</span></p></body></html>", nullptr));
        pushButton_exit->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
        label_ele1->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600; color:#5500ff;\">1\345\217\267\347\224\265\346\242\257</span></p></body></html>", nullptr));
        label_ele2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600; color:#5500ff;\">2\345\217\267\347\224\265\346\242\257</span></p></body></html>", nullptr));
        label_ele3->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600; color:#5500ff;\">3\345\217\267\347\224\265\346\242\257</span></p></body></html>", nullptr));
        label_ele5->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600; color:#5500ff;\">5\345\217\267\347\224\265\346\242\257</span></p></body></html>", nullptr));
        label_ele4->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-weight:600; color:#5500ff;\">4\345\217\267\347\224\265\346\242\257</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
