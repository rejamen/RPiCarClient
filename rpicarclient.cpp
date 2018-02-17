#include "rpicarclient.h"
#include "ui_rpicarclient.h"

//*********************************************************************************
RPiCarClient::RPiCarClient(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RPiCarClient)
{
    ui->setupUi(this);

    timer = new QTimer();
    timer->setInterval(1000/60);
    timer->start();

    connect(timer, &QTimer::timeout, this, &RPiCarClient::timerOutEvent);

    /*Deshabilitar widgets de UI*/
    /*ui->speedSlider->setEnabled(false);
    ui->angleDial->setEnabled(false);*/

    speed = MIN_SPEED;
    angle = MIN_ANGLE;
}
//*********************************************************************************

RPiCarClient::~RPiCarClient()
{
    delete ui;
}
//*********************************************************************************
void RPiCarClient::timerOutEvent()
{

    QString txt = "";

    if(keys[Qt::Key_Up])
    {
        txt += "u";

        //tomo la posicion actual del slider
        int valorActual = ui->speedSlider->sliderPosition();
        int nuevoValor = valorActual + 5;

        ui->speedSlider->setSliderPosition(nuevoValor);
        ui->speedLabel->setText(QString::number(nuevoValor));
    }
    if(keys[Qt::Key_Down])
    {
        txt += "d";
        //tomo la posicion actual del slider
        int valorActual = ui->speedSlider->sliderPosition();
        int nuevoValor = valorActual - 5;

        ui->speedSlider->setSliderPosition(nuevoValor);
        ui->speedLabel->setText(QString::number(nuevoValor));
    }
    if(keys[Qt::Key_Left])
    {
        txt += "l";

        //tomo la posicion actual del dial
        int valorActual = ui->angleDial->sliderPosition();
        int nuevoValor = valorActual - 1;

        ui->angleDial->setSliderPosition(nuevoValor);
        ui->angleLabel->setText(QString::number(nuevoValor));
    }
    if(keys[Qt::Key_Right])
    {
        txt += "r";

        //tomo la posicion actual del dial
        int valorActual = ui->angleDial->sliderPosition();
        int nuevoValor = valorActual + 1;

        ui->angleDial->setSliderPosition(nuevoValor);
        ui->angleLabel->setText(QString::number(nuevoValor));
    }

    qDebug() << txt;
}
//*********************************************************************************
void RPiCarClient::keyReleaseEvent(QKeyEvent *event)
{
    keys[event->key()] = false;
    QWidget::keyReleaseEvent(event);
}
//*********************************************************************************
void RPiCarClient::keyPressEvent(QKeyEvent *event)
{
    keys[event->key()] = true;
    QWidget::keyPressEvent(event);
}
//*********************************************************************************
