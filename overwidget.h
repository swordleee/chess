#ifndef OVERWIDGET_H
#define OVERWIDGET_H

#include <QWidget>

namespace Ui {
class OverWidget;
}

class OverWidget : public QWidget
{
    Q_OBJECT

signals:
    void OverSignal(int x);

public:
    explicit OverWidget(QWidget *parent = 0);
    OverWidget(int,QWidget *parent=0);
    ~OverWidget();

   // OverWidget(int x,int y,int w,int h);

private:
    Ui::OverWidget *ui;

public:
    int flag;

    void  sendSignal();
    void  sendSignal2();


//    int x,y, w, h;
//    QPoint p;

//    void paintEvent(QPaintEvent *);
//    void mousePressEvent(QMouseEvent *);
//    void mouseMoveEvent(QMouseEvent *);

};

#endif // OVERWIDGET_H
