#ifndef STARTWIDGET_H
#define STARTWIDGET_H

#include <QWidget>
#include<QUdpSocket>

namespace Ui {
class StartWidget;
}

class StartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StartWidget(QWidget *parent = 0);
    ~StartWidget();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

signals:
    void startSignal(int x);

private:
    Ui::StartWidget *ui;

    QUdpSocket *udpsocket;
    QString ip;
    qint16 port;
    QString oppositeip;
    qint16 oppositeport;

    int x,y;

public:
    int chess;
    void getxy(int *x,int *y);

    void dealmes();
    void sendmes(int,int);

    void sendSignal();
    void sendSignal2();

    bool isOk=false;
};

#endif // STARTWIDGET_H
