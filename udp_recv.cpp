#include "udp_recv.h"

udp_recv::udp_recv(MainWindow* _mainwindow) :
    m_mainwindow(_mainwindow),
    net_pack_size(0),
    lenoRecv(1024),
    lenoRecvHEX(2*lenoRecv),
    LenoUDP(128*64*33*1000),
    CHdata2(make_shared<CirQueue<int>>(LenoUDP)),
    pack_HEX_33(new char[33*1024*2]),
    pack_HEX_Resolve(new char[33*1024*2])
{
    sockVersion = MAKEWORD(2,2);
    if(WSAStartup(sockVersion, &wsaData) != 0)
    {
        printf("winsock initialization FAILED.");
    }
    echo_socket_WIN = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(echo_socket_WIN == INVALID_SOCKET)
    {
        printf("winsocket error !");
    }
    addr_WIN.sin_family = AF_INET;
    addr_WIN.sin_port = htons(8080); //8080
    addr_WIN.sin_addr.S_un.S_addr = INADDR_ANY;
    if(::bind(echo_socket_WIN, (sockaddr *)&addr_WIN, sizeof(addr_WIN)) == SOCKET_ERROR)
    {
        printf("bind error !");
        closesocket(echo_socket_WIN);
    }
    // set socket buffer size
    int optVal = 0;
    int optLen = sizeof(optVal);
    optVal = 4*1024*100000;
    setsockopt(echo_socket_WIN, SOL_SOCKET, SO_RCVBUF, (char*)&optVal, optLen);

    //Ԥ������洢�ռ�
    p_echo_net_pack_array.reserve(1024);

}

void udp_recv::run()
{
    while(1){

            p_echo_net_pack[0] = '\0'; //��ʼ��Ϊ�գ�����һ��Ϊ���⣬����Ϊ���ֵ

            net_pack_size = recvfrom(echo_socket_WIN, (char*)p_echo_net_pack, lenoRecv, 0, (sockaddr *)&src_addr_WIN, &src_addr_len);

            qDebug()<<"Reciving net_pack_size = "<< net_pack_size <<endl;

            p_echo_net_pack_array.clear();
            p_echo_net_pack_HEX.clear();

            //2.char* ת QByteArray, p_echo_net_pack >> p_echo_pack_array
            p_echo_net_pack_array = QByteArray(p_echo_net_pack,lenoRecv);

            p_echo_net_pack_HEX = p_echo_net_pack_array.toHex().toUpper();

            qDebug()<<p_echo_net_pack_HEX[0]<<p_echo_net_pack_HEX[1]<<p_echo_net_pack_HEX[2]<<p_echo_net_pack_HEX[3]
                    <<p_echo_net_pack_HEX[4]<<p_echo_net_pack_HEX[5]<<p_echo_net_pack_HEX[6]<<p_echo_net_pack_HEX[7]<<endl;

            //֡ͷʶ����
            //�ж�33֡���ݵ�֡ͷ���Ӷ���λ���λ��.
            //��ĳ֡��FEFEFEFE...�����֡�����֡
            if(p_echo_net_pack_HEX[0]=='F' && p_echo_net_pack_HEX[1]=='E' && p_echo_net_pack_HEX[2]=='F' && p_echo_net_pack_HEX[3]=='E'&&p_echo_net_pack_HEX[4]=='F' && p_echo_net_pack_HEX[5]=='E' && p_echo_net_pack_HEX[6]=='F' && p_echo_net_pack_HEX[7]=='E')
                isStartFrame = 1;

            if(isStartFrame){
                for(int k = 2*pack_count; k<(2*pack_count + 2048) ; k++ )
                    pack_HEX_33[k] = p_echo_net_pack_HEX[k-2*pack_count];

                //�����յ��İ�����
                pack_count = pack_count + 1024;

                //ÿ�յ�33����ʱ����Ϊһ���¼�
                if(pack_count>=1024*33){
                    isStartFrame = 0;
                    pack_count = 0;

                    //pack_HEX_33[] >> pack_HEX_Resolve[]
                    memcpy(pack_HEX_Resolve,pack_HEX_33,sizeof(char)*2048*33);
                    memset(pack_HEX_33,'\0',sizeof(char)); //�������

                    qDebug()<<"Has Received 33 Frames! " <<endl;

                    //3.pack_HEX_Resolve >> CHData
                    for(int j=1;j<33;j++){

                        //���յ����ݰ�С�����У�����82 04 14 00ת��Ϊ���������00 14 04 82
                        for(int i=0; i<lenoRecvHEX; i+=8) {

                            bool ok;
                            int temp_DEC = QString((unsigned char)pack_HEX_Resolve[2048*j+i]).toInt(&ok,16)*16
                                    + QString((unsigned char)pack_HEX_Resolve[2048*j+i+1]).toInt(&ok,16)*1
                                    + QString((unsigned char)pack_HEX_Resolve[2048*j+i+2]).toInt(&ok,16)*4096
                                    + QString((unsigned char)pack_HEX_Resolve[2048*j+i+3]).toInt(&ok,16)*256
                                    + QString((unsigned char)pack_HEX_Resolve[2048*j+i+4]).toInt(&ok,16)*1048576
                                    + QString((unsigned char)pack_HEX_Resolve[2048*j+i+5]).toInt(&ok,16)*65536
                                    + QString((unsigned char)pack_HEX_Resolve[2048*j+i+6]).toInt(&ok,16)*0
                                    + QString((unsigned char)pack_HEX_Resolve[2048*j+i+7]).toInt(&ok,16)*0;

                            CHdata2->push(temp_DEC);



                        } //end for

                    } //end for

                     qDebug()<<"temp_DEC:  "<<endl;

                }//end if


            }//end if

    } //end while


}
