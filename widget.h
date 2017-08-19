#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"overwidget.h"
#include"startwidget.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;

    int gwidth;
    int gheight;

    int chessX;
    int chessY;

    bool flag;

    char black_chess[15][15];
    char white_chess[15][15];

    bool netflag;

    bool blackflag;

public:
    OverWidget *over;
    OverWidget *over0;

    StartWidget *start;

public:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);

    bool checkOver(char (*c)[15],int x,int y);

public slots:
    void dealSiganl(int);
    void dealSiganl2(int);
};

#endif // WIDGET_H
