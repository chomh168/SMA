#include "tcpclinet.h"

TcpClient::TcpClient(QObject *parent) : QObject (parent)
{
    m_socket = new QTcpSocket;
}

TcpClient::~TcpClient()
{

}



void TcpClient::setIpAddress(QString address)
{
    m_ipAddress = address;

    return;
}

bool TcpClient::TcpConnect(QString server)
{
    this->setIpAddress(server);
    this->connectToServer();

    bool rst = m_socket->state() == QTcpSocket::ConnectedState;

    return rst;
}

void TcpClient::connectToServer(void)
{
    m_socket->connectToHost(m_ipAddress,502);


    return;
}

void TcpClient::TcpDisconnect(void)
{
    if(m_connectState==true)
    {
        m_socket->close();
        m_connectState = false;
    }

    return;
}

void TcpClient::onConnectServer(void)
{
    m_connectState = true;

    return;
}

void TcpClient::sendRequst(char* buffer)
{
    if(m_connectState==true)
    {
        m_socket->write((const char*)&buffer, 12);
    }
}

QString TcpClient::readMessage(void)
{
    //unsigned char buffer[256];
    unsigned chr;
    QString baMessageTemp;
    QByteArray baMessage = m_socket->readAll();

    baMessageTemp.append("Receive Data : ");
    for(int index = 0; index < baMessage.length();index++)
    {
        chr = baMessage.at(index);
        baMessageTemp.append(QString::number(chr));
        if(index != baMessage.length()-1)
            baMessageTemp.append(", ");
    }

    return baMessageTemp;

}
