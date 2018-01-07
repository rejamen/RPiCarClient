#include "rpicarclient.h"
#include "ui_rpicarclient.h"

RPiCarClient::RPiCarClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RPiCarClient)
{
    ui->setupUi(this);

    timer = new QTimer();
        timer->setInterval(1000/60);
        timer->start();

        connect(timer, &QTimer::timeout, this, &RPiCarClient::timerOutEvent);
}

RPiCarClient::~RPiCarClient()
{
    delete ui;
}


void RPiCarClient::timerOutEvent()
{

    QString txt = "";

    if(keys[Qt::Key_Up])
    {
        txt += "u";
    }
    if(keys[Qt::Key_Down])
    {
        txt += "d";
    }
    if(keys[Qt::Key_Left])
    {
        txt += "l";
    }
    if(keys[Qt::Key_Right])
    {
        txt += "r";
    }

    qDebug() << txt;
}

void RPiCarClient::keyReleaseEvent(QKeyEvent *event)
{
    keys[event->key()] = false;
    QWidget::keyReleaseEvent(event);
}

void RPiCarClient::keyPressEvent(QKeyEvent *event)
{
    keys[event->key()] = true;
    QWidget::keyPressEvent(event);
}
