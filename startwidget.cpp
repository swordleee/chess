#include "startwidget.h"
#include "ui_startwidget.h"
#include<QHostAddress>
#include<QDebug>

StartWidget::StartWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartWidget)
{
    ui->setupUi(this);
    //获取ip和端口

    x=0;
    y=0;
    chess=0;

    udpsocket=new QUdpSocket();
    //绑定自己端口
    udpsocket->bind(8888);
    setWindowTitle("五子棋");
    //有消息发过来触发readyread
    connect(udpsocket,&QUdpSocket::readyRead,this,&StartWidget::dealmes);

    connect(ui->pushButton,&QPushButton::clicked,this,&StartWidget::sendSignal);
    connect(ui->pushButton_2,&QPushButton::clicked,this,&StartWidget::sendSignal2);

}

//给主窗口发送信号
void StartWidget::sendSignal()
{
    emit startSignal(1);
}
void StartWidget::sendSignal2()
{
    emit startSignal(2);
}


void StartWidget::dealmes()
{
    qDebug()<<"deal";
    chess=1;
    //读取对方内容
    char buf[1024]={0};
    QHostAddress hostaddr;//对方ip
    quint16 port;//对方端口
    qint64 len=udpsocket->readDatagram(buf,sizeof(buf),&hostaddr,&port);
    qDebug()<<len<<port;
    if(len>0)
    {
        x=QString(buf).section("##",0,0).toInt();
        y=QString(buf).section("##",1,1).toInt();
        //z=QString(buf).section("##",2,2).toInt();
        //格式化输出到窗口
        QString str=QString("[%1:%2]%3").arg(hostaddr.toString()).arg(port).arg(buf);
        qDebug()<<str;
        emit startSignal(3);
    }
}

void StartWidget::getxy(int *x, int *y)
{
    qDebug()<<"get";
    *x=this->x;
    *y=this->y;
    //*chess=this->chess;
}

void StartWidget::sendmes(int x, int y)
{
    oppositeip=ui->lineEdit_3->text();
    //oppositeport=ui->lineEdit_4->text().toInt();
    //把信息转化为字符串
    QString buf=QString("%1##%2").arg(x).arg(y);
    qDebug()<<buf<<oppositeip<<oppositeport;
    //向对方地址发送信息
    udpsocket->writeDatagram(buf.toUtf8(),QHostAddress(oppositeip),8888);
    qDebug()<<"send";


}

StartWidget::~StartWidget()
{
    delete ui;
}

void StartWidget::on_pushButton_clicked()
{
    emit startSignal(1);
}

void StartWidget::on_pushButton_2_clicked()
{
    emit startSignal(2);
}
