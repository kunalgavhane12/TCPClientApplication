#include "DeviceController.h"

DeviceController::DeviceController(QObject *parent) : QObject(parent)
{
    connect(&_socket, &QTcpSocket::connected, this, &DeviceController::connected);
    connect(&_socket, &QTcpSocket::disconnected, this, &DeviceController::disconnected);
    connect(&_socket, &QTcpSocket::stateChanged, this, &DeviceController::socket_stateChanged);
    connect(&_socket, &QTcpSocket::readyRead, this, &DeviceController::socket_readyRead);
    connect(&_socket, SIGNAL(error(QAbstractSocket::SocketError)),
    this, SLOT(&errorOccurred(QAbstractSocket::SocketError)));
//    connect(&_socket,  QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this,
//            &DeviceController::errorOccurred);
}

void DeviceController::connectToDevice(QString ip, int port)
{
    if(_socket.isOpen())
    {
        if(ip == _ip && port == _port)
        {
            return;
        }
        _socket.close();
    }

    _ip = ip;
    _port = port;
    _socket.connectToHost(_ip, _port);
}

void DeviceController::disconnect()
{
    _socket.close();
}

QAbstractSocket::SocketState DeviceController::state()
{
    return _socket.state();
}

bool DeviceController::isConnected()
{
    return _socket.state() == QAbstractSocket::ConnectedState;
}

void DeviceController::send(QString msg)
{
    _socket.write(msg.toUtf8());
}

void DeviceController::socket_stateChanged(QAbstractSocket::SocketState state)
{
    if(state == QAbstractSocket::UnconnectedState)
    {
        _socket.close();
    }
    emit stateChanged(state);
}

void DeviceController::socket_readyRead()
{
    auto data = _socket.readAll();
    emit dataReady(data);
}

void DeviceController::errorOccurred(QAbstractSocket::SocketError error)
{
    emit errorOccurred(error);
}
