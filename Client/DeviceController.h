#ifndef DEVICECONTROLLER_H
#define DEVICECONTROLLER_H

#include <QObject>
#include <QTcpSocket>

class DeviceController : public QObject
{
    Q_OBJECT
public:
    explicit DeviceController(QObject *parent = nullptr);

    void connectToDevice(QString ip, int port);
    void disconnect();
    QAbstractSocket::SocketState state();
    bool isConnected();
    void send(QString msg);

signals:
    void connected();
    void disconnected();
    void stateChanged(QAbstractSocket::SocketState);
    void dataReady(QByteArray);

private slots:
    void socket_stateChanged(QAbstractSocket::SocketState state);
    void socket_readyRead();
    void errorOccurred(QAbstractSocket::SocketError error);

private:
    QTcpSocket _socket;
    QString _ip;
    int _port;

};

#endif // DEVICECONTROLLER_H
