#ifndef USER_H
#define USER_H

#include <QWidget>
#include<QLabel>
#include<QPushButton>
#include<QTreeWidget>
#include<QList>
#include<QTextEdit>
#include<QLineEdit>
#include<QStack>
#include"txtfile.h"
#include"errorpage.h"

#include<QFile>
#include<QCoreApplication>
#include<QFileDialog>
#include<QTextStream>
#include<QDebug>

//将文件数据与磁盘数据写入xml
#include<QtXml/QDomDocument>

namespace Ui {
class User;
}

class User : public QWidget
{
    Q_OBJECT

public:
    explicit User(QWidget *parent = nullptr);
    ~User();

    ErrorPage errorPage;//报错界面
    void save();//保存程序信息
    void read();//读取程序信息
    int searchFileByIterator(QTreeWidgetItemIterator it);
    void findCatalogue(QString parentName);

    void createFile();
    void openFile();
    void saveFile();
    void closeFile();
    void submitFileName();
    void deleteFile();
    int searchFile(QTreeWidgetItem* it);
    void createFolder();
    void submitFolderName();
    void deleteFolder();
    void iterateCatalogue();

    void clearDisk();

    //模拟磁盘
    int diskSpace[32][32];
    bool isDiskFull();//磁盘初始化

    //用来记录当前操作的文本
    int file_iterator=-1;
    QString now_name;
    std::vector<txtFile>cata;

    //显示文件模块
    QLabel* File_name;
    QTextEdit* inputTXT;
    QPushButton* saveButton;
    QPushButton* closeButton;

    //显示文件目录模块
    QTreeWidget* catalogue;
    QTreeWidgetItem* root;

    QPushButton* formatButton;//格式化按钮
    QPushButton* createFileButton;
    QPushButton* submitFileNameButton;//创建文件
    QPushButton* openFileButton;//打开文件
    QPushButton* deleteFileButton;//删除文件
    QPushButton* submitFolderNameButton;
    QPushButton* createFolderButton;//创建文件夹
    QPushButton* deleteFolderButton;//删除文件夹
private:
    Ui::User *ui;
};

#endif // USER_H
