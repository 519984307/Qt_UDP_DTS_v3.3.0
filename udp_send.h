#ifndef UDP_SEND_H
#define UDP_SEND_H

#include <WinSock2.h>
#include <Windows.h>
#include <mainwindow.h>
#include <QThread>
#include "CirQueue.h"
#include <stdio.h>

class MainWindow;

class udp_send : public QThread
{
    Q_OBJECT

public:
    udp_send(MainWindow* _mainwindow);

    MainWindow* m_mainwindow;

    //winSocket API
    WSAData wasData;
    SOCKET sendSocket;
    SOCKADDR_IN receiverAddr;
    int addrLength = 0;
    int ret = 0;

protected:
    void run();
};

#endif // UDP_SEND_H
