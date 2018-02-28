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

    //init variables de estado
    speed = MIN_SPEED;
    angle = INITIAL_ANGLE;
    status = "off";
    direction = "forward";
    flag = false;


    ui->angleDial->setValue(INITIAL_ANGLE);
    ui->angleLabel->setText(QString::number(ui->angleDial->sliderPosition()));

    ui->speedLabel->setText(QString::number(ui->speedSlider->sliderPosition()));

}
//*********************************************************************************
void RPiCarClient::sendSpeed()
{
    sendCommand(QString::number(speed));
}
//*********************************************************************************
void RPiCarClient::sendDirection()
{
    sendCommand(direction);
}
//*********************************************************************************
void RPiCarClient::sendStatus()
{
    sendCommand(status);

}
//*********************************************************************************
void RPiCarClient::sendAngle()
{
    sendCommand(QString::number(angle));

}
//*********************************************************************************
void RPiCarClient::sendCommand(QString cmd)
{
    //Aqui va la implementacion de la Cx con el Server
}
//*********************************************************************************
RPiCarClient::~RPiCarClient()
{
    delete ui;
}
//*********************************************************************************
void RPiCarClient::timerOutEvent()
{


    flag = false;

    if(keys[Qt::Key_Up]) //Se presiona la tecla ARRIBA
    {
        timer->setInterval(1000/60);

        //tomo la posicion actual del slider
        int valorActual = ui->speedSlider->sliderPosition();
        speed = valorActual + SPEED_STEP;

        if (speed > MAX_SPEED)
        {
           speed = MAX_SPEED;
        }

        ui->speedSlider->setSliderPosition(speed);
        ui->speedLabel->setText(QString::number(speed));

        direction = "forward";
        flag = true;

    }
    if(keys[Qt::Key_Down])
    {
        timer->setInterval(1000/60);

        //tomo la posicion actual del slider
        int valorActual = ui->speedSlider->sliderPosition();
        speed = valorActual - SPEED_STEP;

        if (speed < MAX_BACKWARD_SPEED) //se establece una velocidad maxima para la reversa
        {
            speed = MAX_BACKWARD_SPEED;
        }

        ui->speedSlider->setSliderPosition(speed);
        ui->speedLabel->setText(QString::number(speed));

        if (speed < 0)
            direction = "backward";

        flag = true;


    }
    if(keys[Qt::Key_Left])
    {
        timer->setInterval(1000/20);
        //tomo la posicion actual del dial
        int valorActual = ui->angleDial->sliderPosition();
        angle = valorActual - ANGLE_STEP;

        if (angle < MIN_ANGLE)
        {
            angle = MIN_ANGLE;
        }

        ui->angleDial->setSliderPosition(angle);
        ui->angleLabel->setText(QString::number(angle));


    }
    if(keys[Qt::Key_Right])
    {
        timer->setInterval(1000/20);
        //tomo la posicion actual del dial
        int valorActual = ui->angleDial->sliderPosition();
        angle = valorActual + ANGLE_STEP;

        if (angle > MAX_ANGLE)
        {
            angle = MAX_ANGLE;
        }

        ui->angleDial->setSliderPosition(angle);
        ui->angleLabel->setText(QString::number(angle));

    }

    if (speed != 0)
        status = "on";
    else
        status = "off";


    qDebug() << "Status: " + status;
    qDebug() << "Direction: " + direction;
    qDebug() << "Speed: " + QString::number(speed);
    qDebug() << "Angle: " + QString::number(angle);
    qDebug() << flag;

    checkFlag();

    sendSpeed();
    sendDirection();
    sendAngle();
    sendStatus();



}
//*********************************************************************************
void RPiCarClient::checkFlag()
{
    /*Funcion para comprobar el valor de la variable txt
     *Desacelero si no tengo presionado UP, o sea si txt no tiene la letra U
    */
    if (! flag )
    {
         timer->setInterval(1000/20);
        //tomo la posicion actual del slider
        int valorActual = ui->speedSlider->sliderPosition();
        speed = valorActual - SPEED_STEP;

        if (speed < MIN_SPEED) //se establece una velocidad maxima para la reversa
        {
            speed = MIN_SPEED;
        }

        ui->speedSlider->setSliderPosition(speed);
        ui->speedLabel->setText(QString::number(speed));


    }

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
