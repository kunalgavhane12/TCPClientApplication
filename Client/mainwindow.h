#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "DeviceController.h"
#include <QHostAddress>
#include <QStyle>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_lnIPAddress_textChanged(const QString &arg1);

    void on_btnConnect_clicked();

    void device_connected();
    void device_disconnected();
    void device_stateChanged(QAbstractSocket::SocketState);
    void device_dataready(QByteArray data);

    void on_btnSend_clicked();

private:
    Ui::MainWindow *ui;
    DeviceController _controller;

    void setDeviceController();
};
#endif // MAINWINDOW_H
