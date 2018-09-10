#ifndef TCPCLINET_H
#define TCPCLINET_H

#include<QObject>
#include<QTcpSocket>
#include<QHostAddress>
#include<QByteArray>


class TcpClient : public QObject
{
    Q_OBJECT
public:
    explicit TcpClient(QObject *parent = nullptr);
    ~TcpClient();
    QTcpSocket *m_socket;
    void setIpAddress(QString address);

    bool TcpConnect(QString server);
    void TcpDisconnect(void);
    void onConnectServer(void);
    void sendRequst(char* buffer);
    void connectToServer(void);
    QString readMessage(void);

signals:

public slots:

private:
    QString m_ipAddress;
    bool m_connectState;

};



#endif // TCPCLINET_H
