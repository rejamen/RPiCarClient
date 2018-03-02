#ifndef RPICARCLIENT_H
#define RPICARCLIENT_H

#define SPEED_STEP 5
#define MIN_SPEED 0
#define MAX_SPEED 255

#define MAX_BACKWARD_SPEED -30

#define ANGLE_STEP 5
#define MIN_ANGLE 140
#define MAX_ANGLE 230
#define INITIAL_ANGLE 180

#include <QMainWindow>
#include <QMap>
#include <QTimer>
#include <QDebug>
#include <QKeyEvent>
#include <QTcpSocket>
#include <QMessageBox>

namespace Ui {
class RPiCarClient;
}

class RPiCarClient : public QMainWindow
{
    Q_OBJECT

public:
    explicit RPiCarClient(QWidget *parent = 0);
    ~RPiCarClient();

private:
    Ui::RPiCarClient *ui;

public:
    int speed;
    QByteArray direction;
    QByteArray status;
    int angle;

    bool flag;

    //Server side
    QTcpSocket *tcpSocket;
    int port;
    QString serverAddress;
    bool error; //para saber si hay error de conexion



    void sendSpeed();
    void sendDirection();
    void sendStatus();
    void sendAngle();

    void checkFlag();

private:
    QTimer *timer;
    QMap<int, bool> keys;
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *e);

private slots:
    void timerOutEvent();

    //Server side
    void connectToServer();
    void sendCommand(QByteArray);
    void slotReadClient();
    void displayError(QAbstractSocket::SocketError socketError);


};

#endif // RPICARCLIENT_H
