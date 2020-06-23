#ifndef TXTFILE_H
#define TXTFILE_H


#include<QString>
class txtFile
{
public:
    txtFile();
    int file_id;
    std::pair<int,int>disk_id;//文件位于磁盘内位置
    QString file_name="未命名";
    QString content;
    QString parent;//文件的父目录名
};

#endif // TXTFILE_H
