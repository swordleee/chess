#include "widget.h"
#include "ui_widget.h"

#include<QPen>
#include<QMouseEvent>
#include<QDebug>
#include<QPainter>
#include<QPalette>
#include<QBrush>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    over=new OverWidget(1);
    over0=new OverWidget(0);

    start=new StartWidget();
    start->show();

    chessX=0;
    chessY=0;


    QPalette palette;
    QPixmap pixmap(":/picture/8.jpg");

    palette.setBrush(QPalette::Active,QPalette::Window, QBrush(pixmap));
    this->setPalette(palette);
    this->setAutoFillBackground(true);

    //this->setStyleSheet("background-color:yellow;");  //设置背景颜色
   /* this->setObjectName("Widget");
    this->setStyleSheet("#Widget{background-image:url(:/5.jpg);}"); *///设置背景图片

//    ui->label->setGeometry(this->x(),this->y(),this->width(),this->height());
//    ui->label->setPixmap(QPixmap("../5.jpg"));



    flag=true;//flag为真黑棋走
    netflag=false;//联网
    blackflag=false;//决定谁先手

    memset(black_chess,'0',sizeof(black_chess));//二维数组清零
    memset(white_chess,'0',sizeof(white_chess));

     qDebug()<<"gouzhao";

     //处理overwidget窗口信号
      connect(over,SIGNAL(OverSignal(int)),this,SLOT(dealSiganl(int)));
      //处理StartWidget窗口信号
      connect(start,SIGNAL(startSignal(int)),this,SLOT(dealSiganl2(int)));
}

Widget::~Widget()
{
    delete ui;
    if(over!=NULL)
    {
        delete over;
        over=NULL;
    }
    if(over0!=NULL)
    {
        delete over0;
        over0=NULL;
    }
    if(start!=NULL)
    {
        delete start;
        start=NULL;
    }
}
//处理startwidget窗口传回的信号
void Widget::dealSiganl2(int a)
{
    qDebug()<<"0";
    if(a==1)
    {
        this->show();
        start->hide();
    }else if(a==2)
    {
        this->show();
        start->hide();
        netflag=true;
    }else if(a==3)
    {
        qDebug()<<"1";
        start->getxy(&chessX,&chessY);//得到回复
        if(blackflag==true)
        {
            qDebug()<<"2";
            white_chess[chessX][chessY]='1';
            flag=true;
        }else
        {
            qDebug()<<"3";
            black_chess[chessX][chessY]='1';
            flag=true;
        }
        qDebug()<<"("<<chessX<<","<<chessY<<")"<<endl;
        update();
    }
}

//处理overwidget窗口传回的信号
void Widget::dealSiganl(int a)
{
    qDebug()<<"退出游戏信号";
    if(a==1)
    {
        memset(black_chess,'0',sizeof(black_chess));//二维数组清零
        memset(white_chess,'0',sizeof(white_chess));
        qDebug()<<"dealSiganl1"<<a;
//        over->close();
//        delete over;
        over->hide();
        over0->hide();

        this->show();


    }else if(a==2)
    {
        memset(black_chess,'0',sizeof(black_chess));//二维数组清零
        memset(white_chess,'0',sizeof(white_chess));
        qDebug()<<"dealSiganl1"<<a;
//        over->close();
//        delete over;
        over->close();
        over0->close();
        this->close();
    }
}

void Widget::paintEvent(QPaintEvent *)
{
    qDebug()<<"paint";
    //每个格子的长宽
    gwidth=width()/16;
    gheight=height()/16;

    QPainter p(this);
    //设置画笔
    QPen pen;
    pen.setWidth(5);
    pen.setColor(Qt::black);
    p.setPen(pen);
    qDebug()<<"paint2";

    //画棋盘格子
    for(int i=1;i<16;i++)
    {
       p.drawLine(gwidth,gheight*i,gwidth*15,gheight*i);
       p.drawLine(gwidth*i,gheight,gwidth*i,gheight*15);
    }
    qDebug()<<"paint3";
    //画出棋盘上的所有黑白棋
    for(int i=0;i<15;i++)
    {
        for(int j=0;j<15;j++)
        {
            if(black_chess[i][j]=='1')
            {
                p.drawPixmap((i+1)*gwidth-(0.5*gwidth),
                             (j+1)*gheight-(0.5*gheight),
                             gwidth,gheight,QPixmap(":/picture/1.png"));

            }
            if(white_chess[i][j]=='1')
            {
                p.drawPixmap((i+1)*gwidth-(0.5*gwidth),
                             (j+1)*gheight-(0.5*gheight),
                             gwidth,gheight,QPixmap(":/picture/2.png"));
            }
        }
    }
    qDebug()<<"paint4";
    if(blackflag==true)//游戏结束画面
    {
        //绘制黑棋游戏结束画面
        if(checkOver(black_chess,chessX,chessY))
        {
    //        OverWidget *over=new OverWidget(this->x(),this->y(),this->width(),this->height());
            flag=true;
            this->hide();
            over->show();
            //connect(over,SIGNAL(OverSignal(int)),this,SLOT(dealSiganl(int)));
            qDebug()<<"You Win!black chessman"<<endl;
        }
        //绘制白棋游戏结束画面
        if(checkOver(white_chess,chessX,chessY))
        {
            //结束窗口
    //        over=new OverWidget();
            this->hide();
            over0->show();
            //connect(over,SIGNAL(OverSignal(int)),this,SLOT(dealSiganl(int)));
            qDebug()<<"You defeat!black chessman"<<endl;
        }
    }else if(blackflag==false)
    {
        qDebug()<<"paint5";
        //绘制白棋游戏结束画面
        if(checkOver(white_chess,chessX,chessY))
        {
            //结束窗口
    //        over=new OverWidget();
            this->hide();
            over->show();
            //connect(over,SIGNAL(OverSignal(int)),this,SLOT(dealSiganl(int)));
            qDebug()<<"You Win!white chessman"<<endl;
        }
        //绘制黑棋游戏结束画面
        if(checkOver(black_chess,chessX,chessY))
        {
    //        OverWidget *over=new OverWidget(this->x(),this->y(),this->width(),this->height());
            flag=true;
            this->hide();
            over0->show();
            //connect(over,SIGNAL(OverSignal(int)),this,SLOT(dealSiganl(int)));
            qDebug()<<"You defeat!white chessman"<<endl;
        }
    }

    qDebug()<<"paint6";
}
//鼠标按下事件
void Widget::mousePressEvent(QMouseEvent *e)
{
    if(e->x()<gwidth/2||e->x()>gwidth*15||
            e->y()<gheight/2||e->y()>gheight*15)
    {
        return;
    }else
    {
        if(netflag==false)
        {
            //棋盘上的坐标
            chessX=(e->x()-(gwidth/2))/gwidth;
            chessY=(e->y()-(gheight/2))/gheight;

            if(flag==true)//黑棋走
            {
                if(white_chess[chessX][chessY]=='1'||black_chess[chessX][chessY]=='1')
                {
                    return;
                }
                black_chess[chessX][chessY]='1';
                qDebug()<<"("<<chessX<<","<<chessY<<")"<<endl;
                flag=false;
                update();
            }else
            {
                if(black_chess[chessX][chessY]=='1'||white_chess[chessX][chessY]=='1')
                {
                    return;
                }
                white_chess[chessX][chessY]='1';
                qDebug()<<"("<<chessX<<","<<chessY<<")"<<endl;
                flag=true;
                update();
            }
        }else if(netflag==true)
        {
            qDebug()<<"net1";
            if(start->chess==0)//判断谁先手
            {
                blackflag=true;
            }
            qDebug()<<"net2";
            if(blackflag==true)
            {
                if(flag==true)
                {
                    qDebug()<<"net1";
                    //棋盘上的坐标
                    chessX=(e->x()-(gwidth/2))/gwidth;
                    chessY=(e->y()-(gheight/2))/gheight;
                    if(white_chess[chessX][chessY]=='1'||black_chess[chessX][chessY]=='1')
                    {
                        return;
                    }
                    black_chess[chessX][chessY]='1';
                    start->sendmes(chessX,chessY);//向对方发送消息
                    qDebug()<<"("<<chessX<<","<<chessY<<")"<<endl;
                    flag=false;
                    update();
                }

            }else
            {
                if(flag==true)
                {
                    qDebug()<<"net3";
                    //棋盘上的坐标
                    chessX=(e->x()-(gwidth/2))/gwidth;
                    chessY=(e->y()-(gheight/2))/gheight;
                    if(black_chess[chessX][chessY]=='1'||white_chess[chessX][chessY]=='1')
                    {
                        return;
                    }
                    white_chess[chessX][chessY]='1';
                    start->sendmes(chessX,chessY);//向对方发送消息
                    qDebug()<<"("<<chessX<<","<<chessY<<")"<<endl;
                    flag=false;
                    update();
                }

            }
        }


    }

}

bool Widget::checkOver(char (*c)[15],int x,int y)
{
    int count=1,county=1,countv=1,countf=1;
    //横向判断
    for(int i=1;i<5;i++)
    {
        if(x-i>=0&&c[x-i][y]=='1')
        {
            count++;
            if(count==5)
            {
                return true;
            }
        }else
        {
            for(int j=1;j<5;j++)
            {
                if(x+j<15&&c[x+j][y]=='1')
                {
                    count++;
                    if(count==5)
                    {
                        return true;
                    }
                }else
                {
                    break;
                }
            }
            if(count!=5)
            {
                break;
            }
        }
    }

    //纵向判断
    for(int i=1;i<5;i++)
    {
        if(y-i>=0&&c[x][y-i]=='1')
        {
            county++;
            if(county==5)
            {
                return true;
            }
        }else
        {
            for(int j=1;j<5;j++)
            {
                if(y+j<15&&c[x][y+j]=='1')
                {
                    county++;
                    if(county==5)
                    {
                        return true;
                    }
                }else
                {
                    break;
                }
            }
            if(count!=5)
            {
                break;
            }
        }
    }

    //斜向判读
    for(int i=1;i<5;i++)
    {
        if(x-i>=0&&y-i>=0&&c[x-i][y-i]=='1')
        {
            countv++;
            if(countv==5)
            {
                return true;
            }
        }else
        {
            for(int j=1;j<5;j++)
            {
                if(x+j<15&&y+j<15&&c[x+j][y+j]=='1')
                {
                    countv++;
                    if(countv==5)
                    {
                        return true;
                    }
                }else
                {
                    break;
                }
            }
            if(count!=5)
            {
                break;
            }
        }
    }
    //反斜向判读
    for(int i=1;i<5;i++)
    {
        if(x-i>=0&&y+i<15&&c[x-i][y+i]=='1')
        {
            countf++;
            if(countf==5)
            {
                return true;
            }
        }else
        {
            for(int j=1;j<5;j++)
            {
                if(x+j<15&&y-j>=0&&c[x+j][y-j]=='1')
                {
                    countf++;
                    if(countf==5)
                    {
                        return true;
                    }
                }else
                {
                    break;
                }
            }
            if(count!=5)
            {
                break;
            }
        }
    }
    return false;
}
