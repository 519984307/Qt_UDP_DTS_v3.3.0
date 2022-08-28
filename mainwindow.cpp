#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    raw_data(new double[1250100]),
    m_raw_wave_widget(new raw_wave_widget()),
    m_demodulation(new demodulation(this)),
    m_add_wave_widget(new add_wave_widget(m_demodulation)),
    m_maxValue_wavelength_widget(new MaxValue_wavelength_widget(m_demodulation)),
    m_centroid_wavelength_widget(new Centroid_wavelength_widget(m_demodulation)),
    m_tempDistance_widget(new Temp_distance_widget(m_demodulation)),
    m_raw_data_save(new raw_data_save(m_demodulation)),
    m_temp_distance_save(new Temp_distance_save(m_demodulation))
{
    ui->setupUi(this);

    setWindowTitle(QString("Qt UDP DTS"));

    //    connect(this,&MainWindow::sendToRaw_wave_widget,m_raw_wave_widget,&raw_wave_widget::display_wave);
    //    connect(m_demodulation,&demodulation::sendToAdd_wave_widget,m_add_wave_widget,&add_wave_widget::display_wave,Qt::QueuedConnection);
    //    connect(m_demodulation,&demodulation::sendToMaxValue_widget,m_maxValue_wavelength_widget,&MaxValue_wavelength_widget::display_wave,Qt::QueuedConnection);
    //    connect(m_demodulation,&demodulation::sendToCentroid_widget,m_centroid_wavelength_widget,&Centroid_wavelength_widget::display_wave,Qt::QueuedConnection);
    //    connect(m_demodulation,&demodulation::sendToTempDistance_widget,m_tempDistance_widget,&Temp_distance_widget::display_wave,Qt::QueuedConnection);
    //    connect(m_raw_wave_widget,&raw_wave_widget::sendToMainwindow_save,this,&MainWindow::save_raw_data);
    //    connect(m_tempDistance_widget,&Temp_distance_widget::sendToMainwindow_save,this,&MainWindow::save_temp_distance_data);
    connect(m_temp_distance_save,&Temp_distance_save::getFilename,this,&MainWindow::save_filename,Qt::BlockingQueuedConnection);

    init_widget_raw_data();
    init_widget_add_wave();
    init_widget_max_approach();
    init_widget_centroid_approach();
    init_widget_temp_distance();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_widget_raw_data()
{
    /*--关联WebEngineView与html文件--*/
    m_raw_data_widget = ui->raw_data_widget;
    m_raw_data_widget->setContextMenuPolicy(Qt::NoContextMenu);
    m_raw_data_widget->load(QUrl::fromLocalFile("E:/Desktop/Qt UDP DTS/Qt_UDP_DTS_v3.1.0/res/raw_data_widget.html")); //只能写绝对地址

    //QWebEngineView 在 load 完一个页面后会发出一个已完成的信号,依据 QWebEngineView 的大小来设置 EChart 的大小的
    connect(m_raw_data_widget,&QWebEngineView::loadFinished,this,&MainWindow::onResizeEcharts1);

}

void MainWindow::init_widget_add_wave()
{
    /*--关联WebEngineView与html文件--*/
    m_add_wave_data_widget = ui->addwave_data_widget;
    m_add_wave_data_widget->setContextMenuPolicy(Qt::NoContextMenu);
    m_add_wave_data_widget->load(QUrl::fromLocalFile("E:/Desktop/Qt UDP DTS/Qt_UDP_DTS_v3.1.0/res/add_wave_widget.html")); //只能写绝对地址

    //QWebEngineView 在 load 完一个页面后会发出一个已完成的信号,依据 QWebEngineView 的大小来设置 EChart 的大小的
    connect(m_add_wave_data_widget,&QWebEngineView::loadFinished,this,&MainWindow::onResizeEcharts2);
}


void MainWindow::init_widget_max_approach()
{
    /*--关联WebEngineView与html文件--*/
    m_max_approach_widget = ui->max_appraoch_widget;
    m_max_approach_widget->setContextMenuPolicy(Qt::NoContextMenu);
    m_max_approach_widget->load(QUrl::fromLocalFile("E:/Desktop/Qt UDP DTS/Qt_UDP_DTS_v3.1.0/res/max_approach_widget.html")); //只能写绝对地址

    //QWebEngineView 在 load 完一个页面后会发出一个已完成的信号,依据 QWebEngineView 的大小来设置 EChart 的大小的
    connect(m_max_approach_widget,&QWebEngineView::loadFinished,this,&MainWindow::onResizeEcharts3);


}

void MainWindow::init_widget_centroid_approach()
{
    /*--关联WebEngineView与html文件--*/
    m_centroid_approach_widget = ui->centroid_approach_widget;
    m_centroid_approach_widget->setContextMenuPolicy(Qt::NoContextMenu);
    m_centroid_approach_widget->load(QUrl::fromLocalFile("E:/Desktop/Qt UDP DTS/Qt_UDP_DTS_v3.1.0/res/centroid_approach_widget.html")); //只能写绝对地址

    //QWebEngineView 在 load 完一个页面后会发出一个已完成的信号,依据 QWebEngineView 的大小来设置 EChart 的大小的
    connect(m_centroid_approach_widget,&QWebEngineView::loadFinished,this,&MainWindow::onResizeEcharts4);


}

void MainWindow::init_widget_temp_distance()
{
    /*--关联WebEngineView与html文件--*/
    m_temp_distance_widget = ui->temp_distance_widget;
    m_temp_distance_widget->setContextMenuPolicy(Qt::NoContextMenu);
    m_temp_distance_widget->load(QUrl::fromLocalFile("E:/Desktop/Qt UDP DTS/Qt_UDP_DTS_v3.1.0/res/Temp_distance_widget.html")); //只能写绝对地址

    //QWebEngineView 在 load 完一个页面后会发出一个已完成的信号,依据 QWebEngineView 的大小来设置 EChart 的大小的
    connect(m_temp_distance_widget,&QWebEngineView::loadFinished,this,&MainWindow::onResizeEcharts5);


}

void MainWindow::echarts_load_raw_data()
{
    /*--组成一个 JSON 字符串将数据传过去--*/
    //1.使用 QJonsObject 来组成一个 JSON 对象
    QJsonObject seriesData;

    //2.使用 QJsonArray 往 JSON 对象中添加一数组
    QJsonArray amplitude;
    for(int i=0; i<1250100; i++) amplitude.push_back(raw_data[i]);
    seriesData.insert("amplitude", amplitude);

    //3.使用 QJsonDocument 来将 JSON 对象转化成字符串
    QString optionStr = QJsonDocument(seriesData).toJson();

    //4.调用js的init2（）方法
    QString js = QString("init2(%1)").arg(optionStr);

    //5.调用 QWebEngineView的 page()->runJavaScript("function(str)") 来运行 JS 方法
    m_raw_data_widget->page()->runJavaScript(js);
}

void MainWindow::echarts_load_add_wave()
{
    /*--组成一个 JSON 字符串将数据传过去--*/
    //1.使用 QJonsObject 来组成一个 JSON 对象
    QJsonObject seriesData;

    //2.使用 QJsonArray 往 JSON 对象中添加一数组
    QJsonArray amplitude;
    for(int i=0; i<25002; i++) amplitude.push_back(m_demodulation->add_wave_data[i]);
    seriesData.insert("amplitude", amplitude);

    //3.使用 QJsonDocument 来将 JSON 对象转化成字符串
    QString optionStr = QJsonDocument(seriesData).toJson();

    //4.调用js的init2（）方法
    QString js = QString("init2(%1)").arg(optionStr);

    //5.调用 QWebEngineView的 page()->runJavaScript("function(str)") 来运行 JS 方法
    m_add_wave_data_widget->page()->runJavaScript(js);

}

void MainWindow::echarts_load_max_approach()
{
    /*--组成一个 JSON 字符串将数据传过去--*/
    //1.使用 QJonsObject 来组成一个 JSON 对象
    QJsonObject seriesData;

    //2.使用 QJsonArray 往 JSON 对象中添加一数组
    QJsonArray amplitude;
    for(int i=0; i<25002; i++){
        //如果最大波长值的index是0 则不画出该点
        if(m_demodulation->wavelength_MaxApproach[i]==0) continue;

        amplitude.push_back(1550.5+0.06*m_demodulation->wavelength_MaxApproach[i]);
    }
    seriesData.insert("amplitude", amplitude);

    //3.使用 QJsonDocument 来将 JSON 对象转化成字符串
    QString optionStr = QJsonDocument(seriesData).toJson();

    //4.调用js的init2（）方法
    QString js = QString("init2(%1)").arg(optionStr);

    //5.调用 QWebEngineView的 page()->runJavaScript("function(str)") 来运行 JS 方法
    m_max_approach_widget->page()->runJavaScript(js);
}

void MainWindow::echarts_load_centroid_approach()
{
    /*--组成一个 JSON 字符串将数据传过去--*/
    //1.使用 QJonsObject 来组成一个 JSON 对象
    QJsonObject seriesData;

    //2.使用 QJsonArray 往 JSON 对象中添加一数组
    QJsonArray amplitude;
    for(int i=0; i<25002; i++){
        //如果最大波长值的index是0 则不画出该点
        if(m_demodulation->wavelength_CentroidApproach[i]==0) continue;

        amplitude.push_back(1550.5+0.06*m_demodulation->wavelength_CentroidApproach[i]);
    }
    seriesData.insert("amplitude", amplitude);

    //3.使用 QJsonDocument 来将 JSON 对象转化成字符串
    QString optionStr = QJsonDocument(seriesData).toJson();

    //4.调用js的init2（）方法
    QString js = QString("init2(%1)").arg(optionStr);

    //5.调用 QWebEngineView的 page()->runJavaScript("function(str)") 来运行 JS 方法
    m_centroid_approach_widget->page()->runJavaScript(js);
}

void MainWindow::echarts_load_temp()
{
    /*--组成一个 JSON 字符串将数据传过去--*/
    //1.使用 QJonsObject 来组成一个 JSON 对象
    QJsonObject seriesData;

    //2.使用 QJsonArray 往 JSON 对象中添加一数组
    QJsonArray amplitude;
    for(int i=0; i<25002; i++) {
        //如果中心波长的温度值是0 则不画出该点
        if(m_demodulation->Temp[i]==0) continue;

        //如果温度值太小，则不画出该点
        if(m_demodulation->Temp[i]<-120) continue;

        amplitude.push_back(m_demodulation->Temp[i]);
    }
    seriesData.insert("amplitude", amplitude);

    //3.使用 QJsonDocument 来将 JSON 对象转化成字符串
    QString optionStr = QJsonDocument(seriesData).toJson();

    //4.调用js的init2（）方法
    QString js = QString("init2(%1)").arg(optionStr);

    //5.调用 QWebEngineView的 page()->runJavaScript("function(str)") 来运行 JS 方法
    m_temp_distance_widget->page()->runJavaScript(js);
}

//点击读取文件按钮
void MainWindow::on_btn_readfls_clicked()
{
    //打开文件选择对话框
    QString fileName = QFileDialog::getOpenFileName(this, tr("open file"), " ",  tr("txt(*.txt);;Allfile(*.*)"));

    qDebug()<<fileName<<endl;

    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("File Dir: ")+fileName+"\n");

    /*--以流的方式打开.txt文件*/
    char buf[32];

    ifstream infile;
    infile.open(fileName.toStdString().data(),std::ifstream::in);

    if(!infile.is_open()) {
        qDebug()<<"Open File Error!"<<endl;

        ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Open File Error!")+"\n");

        delete[] raw_data; //释放动态分配的内存

        return;
    }
    else
        qDebug()<<"Open File Succeed!"<<endl;
    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Open File Succeed!")+"\n");

    for(int i=0;i<1250100;i++){
        infile >> buf; //>>运算符当 >> 遇到空格或换行时，就会终止，并在下次进行 >> 时，从空格或换行后继续进行

        raw_data[i] = strtod(buf,NULL); //char[]转double数字
    }

    infile.close();

    /*--显示raw_data波形--*/
//    echarts_load_raw_data(); //很卡

    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Display Raw Data Wave!")+"\n");

    qDebug()<<"Display raw_wave Succeed!"<<endl;
}

//点击解调按钮
void MainWindow::on_btn_demodulation_clicked()
{
    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Start Demodulating Data! ")+"\n");

    m_demodulation->start(); //必须先开启demodulation线程，再显示add_wave_widget

    echarts_load_add_wave();
    echarts_load_max_approach();
    echarts_load_centroid_approach();
    echarts_load_temp();
}

//点击最大值法按钮
void MainWindow::on_btn_maxValue_clicked()
{
    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("MaxValue Approach to get Central Wavelength! ")+"\n");

    //    m_maxValue_wavelength_widget->show();
    init_widget_max_approach();

    qDebug()<<"Display MaxValue_wavelength Succeed!"<<endl;
}

//点击质心法按钮
void MainWindow::on_btn_centroid_clicked()
{
    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Centroid Approach to get Central Wavelength! ")+"\n");

    //    m_centroid_wavelength_widget->show();

    init_widget_centroid_approach();

    qDebug()<<"Display Centroid_wavelength Succeed!"<<endl;
}

//点击温度判断按钮
void MainWindow::on_btn_temp_clicked()
{
    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Temperature Judgement! ")+"\n");

    //    m_tempDistance_widget->show();

    init_widget_temp_distance();

    qDebug()<<"Display Temp Distance Succeed!"<<endl;

}

//点击保存原始数据按钮
void MainWindow::save_raw_data()
{
    m_raw_data_save->start();

    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Start Saving raw data! ")+"\n");
}

//获取存储文件路径
void MainWindow::save_filename()
{
    m_temp_distance_save->saveFilename = QFileDialog::getExistingDirectory(this, tr("选择文件保存路径"), "./", QFileDialog::ShowDirsOnly);

    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Temperature-Distance Data have been saved at!")+m_temp_distance_save->saveFilename+"\n");
}

//点击复位图像按钮
void MainWindow::on_btn_reset_wave_clicked()
{

}

//点击保存数据按钮
void MainWindow::on_btn_save_temp_clicked()
{
    m_temp_distance_save->start();

    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Start Saving Temperature-Distance Data!")+"\n");
}

//自适应窗口变化大小
void MainWindow::onResizeEcharts1()
{
    isLoaded1 = true;
    QJsonObject sizeData;
    sizeData.insert("width", m_raw_data_widget->width() - 20);
    sizeData.insert("height", m_raw_data_widget->height() - 20);
    QString sizeStr = QJsonDocument(sizeData).toJson();
    QString js = QString("setSize(%1)").arg(sizeStr);
     m_raw_data_widget->page()->runJavaScript(js);

}

void MainWindow::onResizeEcharts2()
{
    isLoaded2 = true;
    QJsonObject sizeData;
    sizeData.insert("width", m_raw_data_widget->width() - 20);
    sizeData.insert("height", m_raw_data_widget->height() - 20);
    QString sizeStr = QJsonDocument(sizeData).toJson();
    QString js = QString("setSize(%1)").arg(sizeStr);
    m_add_wave_data_widget->page()->runJavaScript(js);
}

void MainWindow::onResizeEcharts3()
{
    isLoaded3 = true;
    QJsonObject sizeData;
    sizeData.insert("width", m_raw_data_widget->width() - 20);
    sizeData.insert("height", m_raw_data_widget->height() - 20);
    QString sizeStr = QJsonDocument(sizeData).toJson();
    QString js = QString("setSize(%1)").arg(sizeStr);
    m_max_approach_widget->page()->runJavaScript(js);
}

void MainWindow::onResizeEcharts4()
{
    isLoaded4 = true;
    QJsonObject sizeData;
    sizeData.insert("width", m_raw_data_widget->width() - 20);
    sizeData.insert("height", m_raw_data_widget->height() - 20);
    QString sizeStr = QJsonDocument(sizeData).toJson();
    QString js = QString("setSize(%1)").arg(sizeStr);
    m_centroid_approach_widget->page()->runJavaScript(js);
}

void MainWindow::onResizeEcharts5()
{
    isLoaded5 = true;
    QJsonObject sizeData;
    sizeData.insert("width", m_raw_data_widget->width() - 20);
    sizeData.insert("height", m_raw_data_widget->height() - 20);
    QString sizeStr = QJsonDocument(sizeData).toJson();
    QString js = QString("setSize(%1)").arg(sizeStr);
    m_temp_distance_widget->page()->runJavaScript(js);
}

//因为我们实现在窗口改变大小时 ECharts 也跟着变化，所以我们要在 resizeEvent 时设置也要设置大小
void MainWindow::resizeEvent(QResizeEvent *event)
{
    if(isLoaded1) onResizeEcharts1();
    if(isLoaded2) onResizeEcharts2();
    if(isLoaded3) onResizeEcharts3();
    if(isLoaded4) onResizeEcharts4();
    if(isLoaded5) onResizeEcharts5();
}

