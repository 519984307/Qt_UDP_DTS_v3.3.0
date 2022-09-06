#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
//    raw_data(new double[1250100]),
    m_demodulation(new demodulation(this)),
    m_temp_distance_save(new Temp_distance_save(m_demodulation)),
    m_udp_recv(new udp_recv(this)),
    m_udp_send(new udp_send(this))
//    m_hextodec(new HEXtoDEC(m_udp_recv))
{
    ui->setupUi(this);

//   // Set Style Sheet
//    qDebug()<<QDir::currentPath()<<endl;
//    QFile file(QDir::currentPath()+"/res/my.qss");
//    file.open(QFile::ReadOnly);
//    QString styleSheet = tr(file.readAll());
//    qApp->setStyleSheet(styleSheet);

//    //��ӱ���ͼ
    QPixmap Images("C:/Qt_UDP_DTS/black.jpg");
//    QPalette Palette = this->palette();
//    Palette.setBrush(QPalette::Background,Images);
//    this->setPalette(Palette);


    label = new QLabel(this);
    label->setScaledContents(true);
    label->setPixmap(Images);
    label->lower();


    //Set Local Message
    QString localHostName = QHostInfo:: localHostName();
    qDebug() <<"LocalHostName: "<<localHostName<<endl;
//    ui->m_textBrowser->insertPlainText("LocalHostName: "+localHostName+"\n");
    QHostInfo info = QHostInfo::fromName(localHostName);
    QList<QHostAddress> strIpAddress  = info.addresses();
    QHostAddress IpAddress =  strIpAddress.back();
    qDebug() << "IpAddress: " << IpAddress<<endl;
    qDebug()<<"--------------------------"<<endl;
//    ui->m_textBrowser->insertPlainText("IpAddress: "+IpAddress.toString()+" Port: 7000 \n");

    setWindowTitle(QString("Qt UDP DTS"));

    init_widget_temp_distance();
    init_widget_max_temp();

    Temp_Display_Timer = new QTimer(); // �¶�-���벨��ͼ��ʾ��ʱ��
    Temp_Display_Timer->setTimerType(Qt::PreciseTimer);
    Temp_save_Timer = new QTimer(); // �¶�-���벨��ͼ�洢��ʱ��
    Temp_save_Timer->setTimerType(Qt::PreciseTimer);
    Alarm_Timer = new QTimer();//�¶ȹ��ȱ�����ʱ��
    Alarm_Timer->setTimerType(Qt::PreciseTimer);

    //��ʱ����ʱ��Ӧ
    connect(Temp_Display_Timer,&QTimer::timeout,this,&MainWindow::echarts_load_temp);
    connect(Temp_save_Timer,&QTimer::timeout,this,&MainWindow::Open_Temp_Save_Thread);
    connect(Alarm_Timer,&QTimer::timeout,this,&MainWindow::start_alarm);

    //�߳̽���ʱ��Ӧ
    connect(m_udp_recv,&udp_recv::finished,this,&MainWindow::FinishUdp_recvThread);
//    connect(m_hextodec,&HEXtoDEC::finished,this,&MainWindow::FinishHEXtoDECThread);
    connect(m_demodulation,&demodulation::finished,this,&MainWindow::FinishDemodulationThread);
    connect(m_temp_distance_save,&Temp_distance_save::finished,this,&MainWindow::FinishTemp_saveThread);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *){
    label->resize(this->size());
}

//��ʼ��widget_temp_distance
void MainWindow::init_widget_temp_distance()
{
    /*--����WebEngineView��html�ļ�--*/
    m_temp_distance_widget = ui->temp_distance_widget;
    m_temp_distance_widget->setContextMenuPolicy(Qt::NoContextMenu);
    m_temp_distance_widget->load(QUrl::fromLocalFile(/*QDir::currentPath()+*/"C:/Qt_UDP_DTS/Temp_distance_widget.html"));

    //QWebEngineView �� load ��һ��ҳ���ᷢ��һ������ɵ��ź�,���� QWebEngineView �Ĵ�С������ EChart �Ĵ�С��
    connect(m_temp_distance_widget,&QWebEngineView::loadFinished,this,&MainWindow::onResizeEcharts5);
}

void MainWindow::init_widget_max_temp()
{
    /*--����WebEngineView��html�ļ�--*/
    m_max_temp_widget = ui->max_temp_widget;
    m_max_temp_widget->setContextMenuPolicy(Qt::NoContextMenu);
    m_max_temp_widget->load(QUrl::fromLocalFile(/*QDir::currentPath()+*/"C:/Qt_UDP_DTS/max_temperature2.html"));

    //QWebEngineView �� load ��һ��ҳ���ᷢ��һ������ɵ��ź�,���� QWebEngineView �Ĵ�С������ EChart �Ĵ�С��
    connect(m_max_temp_widget,&QWebEngineView::loadFinished,this,&MainWindow::onResizeEcharts6);
}

//echarts����temp����
void MainWindow::echarts_load_temp()
{
    /*--����Temp[]--*/
    //1.ʹ�� QJonsObject �����һ�� JSON ����
    QJsonObject seriesData;

    //2.ʹ�� QJsonArray �� JSON ���������һ����
    QJsonArray amplitude;
    for(int i=0; i<128; i++) {
        //������Ĳ������¶�ֵ��0 �򲻻����õ�
//        if(m_demodulation->Temp[i]==0) continue;

        //����¶�ֵ̫С���򲻻����õ�
//        if(m_demodulation->Temp[i]<-120) continue;

         //����¶�ֵ>100���򲻻����õ�
        if(m_demodulation->Temp[i]>350) continue;

        amplitude.push_back(m_demodulation->Temp[i]);
    }
    seriesData.insert("amplitude", amplitude);

    //3.ʹ�� QJsonDocument ���� JSON ����ת�����ַ���
    QString optionStr = QJsonDocument(seriesData).toJson();

    //4.����js��init2()����
    QString js = QString("init2(%1)").arg(optionStr);

    //5.���� QWebEngineView�� page()->runJavaScript("function(str)") ������ JS ����
    m_temp_distance_widget->page()->runJavaScript(js);

    /*--����MAX_Temp--*/
    //1.ʹ�� QJonsObject �����һ�� JSON ����
    QJsonObject temp_Obj;

    //2.ʹ�� QJsonArray �� JSON ���������һ����
    QJsonArray temp_json;
    temp_json.push_back(m_demodulation->MAX_Temp);

    temp_Obj.insert("temperature", temp_json);

    //3.ʹ�� QJsonDocument ���� JSON ����ת�����ַ���
    QString optionStr2 = QJsonDocument(temp_Obj).toJson();

    //4.����js��load2()����
    QString js2 = QString("load2(%1)").arg(optionStr2);

    //5.���� QWebEngineView�� page()->runJavaScript("function(str)") ������ JS ����
    m_max_temp_widget->page()->runJavaScript(js2);

    //�¶ȹ��ȱ�����ʱ
    if(m_demodulation->MAX_Temp>=180) start_alarm();
    else {
        if(Alarm_Timer->isActive()) Alarm_Timer->stop();
        alarm_count = 0;
    }
    ui->lcd_alarm->display(QString("%1").arg(alarm_count));
}

void MainWindow::Open_Temp_Save_Thread()
{
//    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Start Saving Data! ")+"\n");

    m_temp_distance_save->start();
}

void MainWindow::start_alarm()
{
    alarm_count++;
    ui->lcd_alarm->display(QString("%1").arg(alarm_count));
}

//�����ȡ�ļ���ť
//void MainWindow::on_btn_readfls_clicked()
//{
//    //���ļ�ѡ��Ի���
//    QString fileName = QFileDialog::getOpenFileName(this, tr("open file"), " ",  tr("txt(*.txt);;Allfile(*.*)"));

//    qDebug()<<fileName<<endl;

//    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("File Dir: ")+fileName+"\n");

//    /*--�����ķ�ʽ��.txt�ļ�*/
//    char buf[32];

//    ifstream infile;
//    infile.open(fileName.toStdString().data(),std::ifstream::in);

//    if(!infile.is_open()) {
//        qDebug()<<"Open File Error!"<<endl;

//        ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Open File Error!")+"\n");

//        delete[] raw_data; //�ͷŶ�̬������ڴ�

//        return;
//    }
//    else
//        qDebug()<<"Open File Succeed!"<<endl;
//    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Open File Succeed!")+"\n");

//    for(int i=0;i<1250100;i++){
//        infile >> buf; //>>������� >> �����ո����ʱ���ͻ���ֹ�������´ν��� >> ʱ���ӿո���к��������

//        raw_data[i] = strtod(buf,NULL); //char[]תdouble����
//    }

//    infile.close();

//}

//�����ʼ�����ť
void MainWindow::on_btn_demodulation_clicked()
{

}

//����������ݰ�ť �����¶�-��������
void MainWindow::on_btn_save_temp_clicked()
{
    //���ļ��жԻ����ȡ�洢�ļ�·��
    m_temp_distance_save->saveFilename = QFileDialog::getExistingDirectory(this, tr("ѡ���ļ�����·��"), "./", QFileDialog::ShowDirsOnly);

//    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")
//                                       +QString("Temperature-Distance Data have been saved at!")+m_temp_distance_save->saveFilename+"\n");

//    m_temp_distance_save->start();
    if(!Temp_save_Timer->isActive()) Temp_save_Timer->start(60000); //��60s����

//    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Start Saving Temperature-Distance Data!")+"\n");
}

void MainWindow::FinishUdp_recvThread()
{
    m_udp_recv->quit();
    m_udp_recv->wait();
}

//void MainWindow::FinishHEXtoDECThread()
//{
//    m_hextodec->quit();
//    m_hextodec->wait();
//}

void MainWindow::FinishDemodulationThread()
{
    m_demodulation->quit();
    m_demodulation->wait();
}

void MainWindow::FinishTemp_saveThread()
{
    m_temp_distance_save->quit();
    m_temp_distance_save->wait();
}

//����Ӧ���ڱ仯
void MainWindow::onResizeEcharts5()
{
    isLoaded5 = true;
    QJsonObject sizeData;
    sizeData.insert("width", m_temp_distance_widget->width() - 20);
    sizeData.insert("height", m_temp_distance_widget->height() - 20);
    QString sizeStr = QJsonDocument(sizeData).toJson();
    QString js = QString("setSize(%1)").arg(sizeStr);
    m_temp_distance_widget->page()->runJavaScript(js);
}

void MainWindow::onResizeEcharts6()
{
    isLoaded6 = true;
    QJsonObject sizeData2;
    sizeData2.insert("width", m_max_temp_widget->width() - 20);
    sizeData2.insert("height", m_max_temp_widget->height() - 20);
    QString sizeStr2 = QJsonDocument(sizeData2).toJson();
    QString js2 = QString("setSize(%1)").arg(sizeStr2);
    m_max_temp_widget->page()->runJavaScript(js2);
}

//��Ϊ����ʵ���ڴ��ڸı��Сʱ ECharts Ҳ���ű仯����������Ҫ�� resizeEvent ʱ����ҲҪ���ô�С
void MainWindow::resizeEvent(QResizeEvent *event)
{
    if(isLoaded5) onResizeEcharts5();
    if(isLoaded6) onResizeEcharts6();
}

//�����ʼ���հ�ť
void MainWindow::on_btn_recv_clicked()
{
//    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")
//                                       +QString("Start Reciving Data! ")+"\n");



    //receive from FPGA
    m_udp_recv->start();

//    QThread::msleep(1000); //�ӳ�ms

//    m_hextodec->start();

//    QThread::msleep(1000); //�ӳ�ms

    m_demodulation->start();

    //��ʱ������echarts_load_temp()��ʾ ms
    if(!Temp_Display_Timer->isActive()) Temp_Display_Timer->start(1000);
}

//�������ָ�ť
void MainWindow::on_m_send_clicked()
{
//    send_data = ui->m_lineEdit->text();

//    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")
//                                       +QString("Start Sending Data: ")+send_data+"\n");

    //send order to FPGA
    m_udp_send->start();
}

