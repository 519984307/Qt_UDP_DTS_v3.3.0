#include "udp_send.h"

udp_send::udp_send(MainWindow* _mainwindow):
    m_mainwindow(_mainwindow)
{
    // 初始化
        if(WSAStartup(MAKEWORD(2, 2), &wasData)!=0){
            printf("WSAStartup failed\n");
        };

        // 创建套接字
        // 套接字类型—：UDP/IP-SOCK_DGRAM
        // 协议：UDP-IPPROTO_UDP
        sendSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (SOCKET_ERROR == sendSocket){
            printf("Create Socket Error!");
            goto exit;
        }

        // 创建一个SOCKADDR_IN结构，指定接收端地址信息
        receiverAddr.sin_family = AF_INET;   // 使用IP地址族
        receiverAddr.sin_port = htons(7000); // 端口号
        receiverAddr.sin_addr.S_un.S_addr = inet_addr("10.118.239.200"); //接收方IP

exit:
    closesocket(sendSocket);
}

void udp_send::run()
{
    QByteArray m_send = m_mainwindow->send_data.toLatin1();
    int lenoSend = strlen(m_send);

    ret = sendto(sendSocket, m_send , lenoSend, 0, (sockaddr *)&receiverAddr, sizeof(receiverAddr));
    qDebug()<<"Sending Buffer Size = "<< ret <<endl;

    int errorindex = WSAGetLastError();
    qDebug()<<"errorindex =  "<< errorindex <<endl;


    if (0 == ret){
        printf("fail to send\n");
    }
//                printf("send info: %s\n", sendBuf);

//    }
}


