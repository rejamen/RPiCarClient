#ifndef RPICARCLIENT_H
#define RPICARCLIENT_H

#define SPEED_STEP 10
#define MIN_SPEED 0;
#define MAX_SPEED 255;

#define ANGLE_STEP 10
#define MIN_ANGLE 0;
#define MAX_ANGLE 255;

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
    int angle;

private:
    QTimer *timer;
    QMap<int, bool> keys;
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *e);

private slots:
    void timerOutEvent();

};

#endif // RPICARCLIENT_H
