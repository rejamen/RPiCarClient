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

    //client side
    port = 9999;
    serverAddress = ui->lineServerAddress->text();
    error = false;
    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));

    connect(ui->buttonConnect, SIGNAL(clicked(bool)),
            this, SLOT(connectToServer()));


    ui->angleDial->setValue(INITIAL_ANGLE);
    ui->angleDial->setMaximum(MAX_ANGLE);
    ui->angleDial->setMinimum(MIN_ANGLE);
    ui->angleLabel->setText(QString::number(ui->angleDial->sliderPosition()));

    ui->speedLabel->setText(QString::number(ui->speedSlider->sliderPosition()));




    ui->lineServerAddress->setEnabled(false);
    ui->buttonConnect->setEnabled(false);

    emit connectToServer();


}
//*********************************************************************************
void RPiCarClient::sendSpeed()
{
    QByteArray aux;
    if (speed >= 0)
        aux.setNum(speed);
    else
        aux.setNum(0 - speed);
    sendCommand(aux);
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
    //int angleAux = (16/11)*(angle - 30 ) + 70;

    QByteArray aux;
    aux.setNum(angle);
    sendCommand(aux);

}
//*********************************************************************************
void RPiCarClient::sendCommand(QByteArray cmd)
{

    //Aqui va la implementacion de la Cx con el Server

    tcpSocket->write(cmd);

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


    /*qDebug() << "Status: " + status;
    qDebug() << "Direction: " + direction;
    qDebug() << "Speed: " + QString::number(speed);
    qDebug() << "Angle: " + QString::number(angle);
    qDebug() << flag;*/

    checkFlag();

    //Formato del comando
    // status;speed,direction angle

    sendStatus();
    sendCommand(";");
    sendSpeed();
    sendCommand(",");
    sendDirection();
    sendCommand(" ");
    sendAngle();





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
void RPiCarClient::connectToServer()
{


    tcpSocket->connectToHost(serverAddress, port);

    if(!error)
    {
        /*QMessageBox::information(this, tr("Cliente"),
                             tr("Conexión establecida con éxito."
                                ));*/

        error = false;

        emit sendCommand("Conectado...");

        //ui->lineServerAddress->setEnabled(false);
        ui->labelStatus->setText("Conectado.");
    }

}
//*********************************************************************
void RPiCarClient::slotReadClient()
{
    /*QByteArray msgFromServer = tcpSocket->readAll();
    qDebug() << msgFromServer;

    if (msgFromServer == "OKOK")
    {
        QMessageBox::information(this, tr("Cliente"),
                             "Se ha programado el kit satisfactoriamente."
                                );
        ui->btnBitFile->setEnabled(false);
        ui->btnProgram->setEnabled(false);
        tcpSocket->close();
    }
    else
    {
        QMessageBox::information(this, tr("Cliente"),
                             "Ha ocurrido un error al programar el kit."
                                );
    }*/
}
//*********************************************************************
void RPiCarClient::displayError(QAbstractSocket::SocketError socketError)
{
    /*switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, tr("Cliente"),
                                 tr("Servidor no encontrado. Verifique que la "
                                    "dirección IP y el puerto seleccionados sean correctos."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, tr("Cliente"),
                                 tr("Conexión rechazada."
                                    "Asegúrese de que la aplicación Servidor se está ejecutando, "
                                    "y verifique además la dirección IP y el puerto seleccionados."
                                    ));
        break;
    default:
        QMessageBox::information(this, tr("Cliente"),
                                 tr("Ha ocurrido el siguiente error: %1.")
                                 .arg(tcpSocket->errorString()));
    }*/

    ui->labelStatus->setText("ERROR!!!");
    error = true;
}
