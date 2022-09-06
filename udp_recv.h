#ifndef UDP_RECV_H
#define UDP_RECV_H

#include <WinSock2.h>
#include <Windows.h>
#include <mainwindow.h>
#include <QThread>
#include "CirQueue.h"

class MainWindow;

class udp_recv : public QThread
{
    Q_OBJECT
public:
    udp_recv(MainWindow* _mainwindow);

    MainWindow* m_mainwindow;

    //winSocket API
    WSADATA wsaData;
    WORD sockVersion;
    SOCKET echo_socket_WIN;
    sockaddr_in addr_WIN;
    sockaddr_in src_addr_WIN;
    int src_addr_len = sizeof(src_addr_WIN);
    int net_pack_size; //UDP实际接收一帧数据长度
    QByteArray p_echo_net_pack_HEX;
    QByteArray p_echo_net_pack_array;
    char p_echo_net_pack[1024];
    int lenoRecv; //设置UDP接受一帧数据长度
    int lenoRecvHEX; //设置的一帧HEX数据长度
    bool isStart = false; //是否开始接收
    int LenoUDP; //设置存储容器的大小

    shared_ptr<CirQueue<int>> CHdata2; //存放UDP接收的HEX数据

    bool isStartFrame = 0; //帧头校验位
    int pack_count=0; //帧计数
    char* pack_HEX_33; //用于存放33帧数据
    char* pack_HEX_Resolve; //用于存放后面解析的数据

signals:

protected:
    void run();

};

#endif // UDP_RECV_H
