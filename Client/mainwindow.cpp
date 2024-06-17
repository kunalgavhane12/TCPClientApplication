#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHostAddress>
#include <QMetaEnum>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setDeviceController();

//    ui->lnIPAddress->setText("127.000.000.001");

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_lnIPAddress_textChanged(const QString &arg1)
{
    QString state = "0";

    if(arg1 == "...")
    {
        state = "";
    }
    else
    {
        QHostAddress address(arg1);
        if(QAbstractSocket::IPv4Protocol == address.protocol())
        {
            state = "1";
        }
    }
    ui->lnIPAddress->setProperty("state", state);
    style()->polish(ui->lnIPAddress);
}


void MainWindow::on_btnConnect_clicked()
{
    if(_controller.isConnected())
    {
        _controller.disconnect();
    }
    else
    {
        auto ip = ui->lnIPAddress->text();
        auto port =ui->spnPort->value();
        _controller.connectToDevice(ip,port);
    }
}

void MainWindow::device_connected()
{
    ui->lstConsole->addItem("Connected To Device");
    ui->btnConnect->setText("Disconnected");
    ui->grpSendData->setEnabled(true);
}

void MainWindow::device_disconnected()
{
    ui->lstConsole->addItem("Disconnected To Device");
    ui->btnConnect->setText("Connected");
    ui->grpSendData->setEnabled(false);
}

void MainWindow::device_stateChanged(QAbstractSocket::SocketState state)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketState>();
    ui->lstConsole->addItem(metaEnum.valueToKey(state));
}

void MainWindow::device_dataready(QByteArray data)
{
    ui->lstConsole->addItem(QString(data));
}

void MainWindow::setDeviceController()
{
    connect(&_controller, &DeviceController::connected, this, &MainWindow::device_connected);
    connect(&_controller, &DeviceController::disconnected, this, &MainWindow::device_disconnected);
    connect(&_controller, &DeviceController::stateChanged, this, &MainWindow::device_stateChanged);
    connect(&_controller, &DeviceController::dataReady, this, &MainWindow::device_dataready);
}


void MainWindow::on_btnSend_clicked()
{
    auto message = ui->lnMsg->text().trimmed();
    _controller.send(message);
}

