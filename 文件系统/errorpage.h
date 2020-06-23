#ifndef ERRORPAGE_H
#define ERRORPAGE_H

#include <QWidget>
#include<QLabel>

namespace Ui {
class ErrorPage;
}

class ErrorPage : public QWidget
{
    Q_OBJECT

public:
    explicit ErrorPage(QWidget *parent = nullptr);
    ~ErrorPage();
    QLabel* errorInfo;
private:
    Ui::ErrorPage *ui;
};

#endif // ERRORPAGE_H
