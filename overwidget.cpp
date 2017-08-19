#include "overwidget.h"
#include "ui_overwidget.h"
#include<QPainter>
#include<QPen>
#include<QMouseEvent>
#include<QPushButton>
#include<QDebug>
#include<QPalette>
#include<QBrush>

OverWidget::OverWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OverWidget)
{
 //  ui->setupUi(this);
//    this->setWindowFlags(Qt::FramelessWindowHint|windowFlags());
//    this->setAttribute(Qt::WA_TranslucentBackground);

    //ui->widget->resize(this->x(),this->y()/4*3);

//    connect(ui->pushButton,&QPushButton::clicked,this,&OverWidget::sendSignal);
//    connect(ui->pushButton_2,&QPushButton::clicked,this,&OverWidget::sendSignal2);
}
//有参构造函数
OverWidget::OverWidget(int flag,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OverWidget)
{
    ui->setupUi(this);
    this->flag=flag;
    if(flag==1)//1表示胜利
    {
//        ui->widget->setAutoFillBackground(true); // 这句要加上, 否则可能显示不出背景图.
//        QPalette palette = ui->widget->palette();
//        palette.setBrush(QPalette::Window,
//        QBrush(QPixmap(":/3.png").scaled( // 缩放背景图.
//                ui->widget->size(),  Qt::IgnoreAspectRatio,
//                Qt::SmoothTransformation))); // 使用平滑的缩放方式
 //       ui->widget->setPalette(palette); // 至此, 已给widget加上了背景图.


        //ui->widget->setStyleSheet("QWidget{border-image:url(:/3.jpg)}");
        ui->label->setText("<center><h1><b>恭喜你获得胜利!</b></h1></center>");
    }else if(flag==0)//表示失败
    {
        //ui->widget->setStyleSheet("QWidget{border-image:url(:/4.jpg)}");
        ui->label->setText("<center><h1<b>很遗憾！再来一局吧！</b></h1></center>");
    }

    connect(ui->pushButton,&QPushButton::clicked,this,&OverWidget::sendSignal);
    connect(ui->pushButton_2,&QPushButton::clicked,this,&OverWidget::sendSignal2);
}



OverWidget::~OverWidget()
{
    delete ui;
}

void OverWidget::sendSignal()
{
    qDebug()<<"1";
    emit OverSignal(1);

}
void OverWidget::sendSignal2()
{
    qDebug()<<"2";
    emit OverSignal(2);
}
//有参构造函数
//OverWidget::OverWidget(int x, int y, int w, int h)
//{
//    this->x=x;
//    this->y=y;
//    this->w=w;
//    this->h=h;


    //背景透明化
//    this->setWindowFlags(Qt::FramelessWindowHint|windowFlags());
//    this->setAttribute(Qt::WA_TranslucentBackground);
//    this->setGeometry(this->x,this->y,this->w,this->h);

//    ui->pushButton->move(100,100);
//    ui->pushButton->setText("hello");

//    QPushButton pb1(this);
//    pb1.move(w/4,h/4*3);
//    pb1.setText("再来一局");
//    QPushButton pb2(this);
//    pb2.setText("退出游戏");
//    pb2.move(x+(w/4*3),y+(h/4*3));
//}
//画图
//void OverWidget::paintEvent(QPaintEvent *)
//{
//    QPainter p(this);
//    p.drawPixmap(0,0,this->w,this->h,QPixmap("../3.png"));
//}
//鼠标按下事件
//void OverWidget::mousePressEvent(QMouseEvent *me)
//{
//    if(me->button()==Qt::RightButton)
//    {
//        close();
//    }else if(me->button()==Qt::LeftButton)
//    {
//        p=me->globalPos()-this->frameGeometry().topLeft();
//    }
//}
////鼠标移动
//void OverWidget::mouseMoveEvent(QMouseEvent *e)
//{
//    if(e->buttons()&Qt::LeftButton)
//    {
//        move(e->globalPos()-p);
//    }
//}
