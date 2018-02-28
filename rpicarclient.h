#ifndef RPICARCLIENT_H
#define RPICARCLIENT_H

#define SPEED_STEP 5
#define MIN_SPEED 0
#define MAX_SPEED 255

#define MAX_BACKWARD_SPEED -30

#define ANGLE_STEP 3
#define MIN_ANGLE 30
#define MAX_ANGLE 70
#define INITIAL_ANGLE 50

#include <QMainWindow>
#include <QMap>
#include <QTimer>
#include <QDebug>
#include <QKeyEvent>

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
    QString direction;
    QString status;
    int angle;

    bool flag;

    void sendSpeed();
    void sendDirection();
    void sendStatus();
    void sendAngle();
    void sendCommand(QString);
    void checkFlag();

private:
    QTimer *timer;
    QMap<int, bool> keys;
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *e);

private slots:
    void timerOutEvent();

};

#endif // RPICARCLIENT_H
