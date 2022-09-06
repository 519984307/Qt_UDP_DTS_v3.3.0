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
    int net_pack_size; //UDPʵ�ʽ���һ֡���ݳ���
    QByteArray p_echo_net_pack_HEX;
    QByteArray p_echo_net_pack_array;
    char p_echo_net_pack[1024];
    int lenoRecv; //����UDP����һ֡���ݳ���
    int lenoRecvHEX; //���õ�һ֡HEX���ݳ���
    bool isStart = false; //�Ƿ�ʼ����
    int LenoUDP; //���ô洢�����Ĵ�С

    shared_ptr<CirQueue<int>> CHdata2; //���UDP���յ�HEX����

    bool isStartFrame = 0; //֡ͷУ��λ
    int pack_count=0; //֡����
    char* pack_HEX_33; //���ڴ��33֡����
    char* pack_HEX_Resolve; //���ڴ�ź������������

signals:

protected:
    void run();

};

#endif // UDP_RECV_H
