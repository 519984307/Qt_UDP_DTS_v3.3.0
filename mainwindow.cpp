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

//    //添加背景图
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

    Temp_Display_Timer = new QTimer(); // 温度-距离波形图显示计时器
    Temp_Display_Timer->setTimerType(Qt::PreciseTimer);
    Temp_save_Timer = new QTimer(); // 温度-距离波形图存储计时器
    Temp_save_Timer->setTimerType(Qt::PreciseTimer);
    Alarm_Timer = new QTimer();//温度过热报警计时器
    Alarm_Timer->setTimerType(Qt::PreciseTimer);

    //计时器定时响应
    connect(Temp_Display_Timer,&QTimer::timeout,this,&MainWindow::echarts_load_temp);
    connect(Temp_save_Timer,&QTimer::timeout,this,&MainWindow::Open_Temp_Save_Thread);
    connect(Alarm_Timer,&QTimer::timeout,this,&MainWindow::start_alarm);

    //线程结束时响应
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

//初始化widget_temp_distance
void MainWindow::init_widget_temp_distance()
{
    /*--关联WebEngineView与html文件--*/
    m_temp_distance_widget = ui->temp_distance_widget;
    m_temp_distance_widget->setContextMenuPolicy(Qt::NoContextMenu);
    m_temp_distance_widget->load(QUrl::fromLocalFile(/*QDir::currentPath()+*/"C:/Qt_UDP_DTS/Temp_distance_widget.html"));

    //QWebEngineView 在 load 完一个页面后会发出一个已完成的信号,依据 QWebEngineView 的大小来设置 EChart 的大小的
    connect(m_temp_distance_widget,&QWebEngineView::loadFinished,this,&MainWindow::onResizeEcharts5);
}

void MainWindow::init_widget_max_temp()
{
    /*--关联WebEngineView与html文件--*/
    m_max_temp_widget = ui->max_temp_widget;
    m_max_temp_widget->setContextMenuPolicy(Qt::NoContextMenu);
    m_max_temp_widget->load(QUrl::fromLocalFile(/*QDir::currentPath()+*/"C:/Qt_UDP_DTS/max_temperature2.html"));

    //QWebEngineView 在 load 完一个页面后会发出一个已完成的信号,依据 QWebEngineView 的大小来设置 EChart 的大小的
    connect(m_max_temp_widget,&QWebEngineView::loadFinished,this,&MainWindow::onResizeEcharts6);
}

//echarts加载temp数据
void MainWindow::echarts_load_temp()
{
    /*--传递Temp[]--*/
    //1.使用 QJonsObject 来组成一个 JSON 对象
    QJsonObject seriesData;

    //2.使用 QJsonArray 往 JSON 对象中添加一数组
    QJsonArray amplitude;
    for(int i=0; i<128; i++) {
        //如果中心波长的温度值是0 则不画出该点
//        if(m_demodulation->Temp[i]==0) continue;

        //如果温度值太小，则不画出该点
//        if(m_demodulation->Temp[i]<-120) continue;

         //如果温度值>100，则不画出该点
        if(m_demodulation->Temp[i]>350) continue;

        amplitude.push_back(m_demodulation->Temp[i]);
    }
    seriesData.insert("amplitude", amplitude);

    //3.使用 QJsonDocument 来将 JSON 对象转化成字符串
    QString optionStr = QJsonDocument(seriesData).toJson();

    //4.调用js的init2()方法
    QString js = QString("init2(%1)").arg(optionStr);

    //5.调用 QWebEngineView的 page()->runJavaScript("function(str)") 来运行 JS 方法
    m_temp_distance_widget->page()->runJavaScript(js);

    /*--传递MAX_Temp--*/
    //1.使用 QJonsObject 来组成一个 JSON 对象
    QJsonObject temp_Obj;

    //2.使用 QJsonArray 往 JSON 对象中添加一数组
    QJsonArray temp_json;
    temp_json.push_back(m_demodulation->MAX_Temp);

    temp_Obj.insert("temperature", temp_json);

    //3.使用 QJsonDocument 来将 JSON 对象转化成字符串
    QString optionStr2 = QJsonDocument(temp_Obj).toJson();

    //4.调用js的load2()方法
    QString js2 = QString("load2(%1)").arg(optionStr2);

    //5.调用 QWebEngineView的 page()->runJavaScript("function(str)") 来运行 JS 方法
    m_max_temp_widget->page()->runJavaScript(js2);

    //温度过热报警计时
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

//点击读取文件按钮
//void MainWindow::on_btn_readfls_clicked()
//{
//    //打开文件选择对话框
//    QString fileName = QFileDialog::getOpenFileName(this, tr("open file"), " ",  tr("txt(*.txt);;Allfile(*.*)"));

//    qDebug()<<fileName<<endl;

//    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("File Dir: ")+fileName+"\n");

//    /*--以流的方式打开.txt文件*/
//    char buf[32];

//    ifstream infile;
//    infile.open(fileName.toStdString().data(),std::ifstream::in);

//    if(!infile.is_open()) {
//        qDebug()<<"Open File Error!"<<endl;

//        ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Open File Error!")+"\n");

//        delete[] raw_data; //释放动态分配的内存

//        return;
//    }
//    else
//        qDebug()<<"Open File Succeed!"<<endl;
//    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Open File Succeed!")+"\n");

//    for(int i=0;i<1250100;i++){
//        infile >> buf; //>>运算符当 >> 遇到空格或换行时，就会终止，并在下次进行 >> 时，从空格或换行后继续进行

//        raw_data[i] = strtod(buf,NULL); //char[]转double数字
//    }

//    infile.close();

//}

//点击开始解调按钮
void MainWindow::on_btn_demodulation_clicked()
{

}

//点击保存数据按钮 保存温度-距离数据
void MainWindow::on_btn_save_temp_clicked()
{
    //打开文件夹对话框获取存储文件路径
    m_temp_distance_save->saveFilename = QFileDialog::getExistingDirectory(this, tr("选择文件保存路径"), "./", QFileDialog::ShowDirsOnly);

//    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")
//                                       +QString("Temperature-Distance Data have been saved at!")+m_temp_distance_save->saveFilename+"\n");

//    m_temp_distance_save->start();
    if(!Temp_save_Timer->isActive()) Temp_save_Timer->start(60000); //存60s数据

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

//自适应窗口变化
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

//因为我们实现在窗口改变大小时 ECharts 也跟着变化，所以我们要在 resizeEvent 时设置也要设置大小
void MainWindow::resizeEvent(QResizeEvent *event)
{
    if(isLoaded5) onResizeEcharts5();
    if(isLoaded6) onResizeEcharts6();
}

//点击开始接收按钮
void MainWindow::on_btn_recv_clicked()
{
//    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")
//                                       +QString("Start Reciving Data! ")+"\n");



    //receive from FPGA
    m_udp_recv->start();

//    QThread::msleep(1000); //延迟ms

//    m_hextodec->start();

//    QThread::msleep(1000); //延迟ms

    m_demodulation->start();

    //定时器控制echarts_load_temp()显示 ms
    if(!Temp_Display_Timer->isActive()) Temp_Display_Timer->start(1000);
}

//点击发送指令按钮
void MainWindow::on_m_send_clicked()
{
//    send_data = ui->m_lineEdit->text();

//    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")
//                                       +QString("Start Sending Data: ")+send_data+"\n");

    //send order to FPGA
    m_udp_send->start();
}

