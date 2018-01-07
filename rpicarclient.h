#ifndef RPICARCLIENT_H
#define RPICARCLIENT_H

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

private:
    QTimer *timer;
    QMap<int, bool> keys;
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *e);

private slots:
    void timerOutEvent();

};

#endif // RPICARCLIENT_H
