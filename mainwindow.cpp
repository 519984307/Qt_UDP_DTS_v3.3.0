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
    /*--����WebEngineView��html�ļ�--*/
    m_raw_data_widget = ui->raw_data_widget;
    m_raw_data_widget->setContextMenuPolicy(Qt::NoContextMenu);
    m_raw_data_widget->load(QUrl::fromLocalFile("E:/Desktop/Qt UDP DTS/Qt_UDP_DTS_v3.1.0/res/raw_data_widget.html")); //ֻ��д���Ե�ַ

    //QWebEngineView �� load ��һ��ҳ���ᷢ��һ������ɵ��ź�,���� QWebEngineView �Ĵ�С������ EChart �Ĵ�С��
    connect(m_raw_data_widget,&QWebEngineView::loadFinished,this,&MainWindow::onResizeEcharts1);

}

void MainWindow::init_widget_add_wave()
{
    /*--����WebEngineView��html�ļ�--*/
    m_add_wave_data_widget = ui->addwave_data_widget;
    m_add_wave_data_widget->setContextMenuPolicy(Qt::NoContextMenu);
    m_add_wave_data_widget->load(QUrl::fromLocalFile("E:/Desktop/Qt UDP DTS/Qt_UDP_DTS_v3.1.0/res/add_wave_widget.html")); //ֻ��д���Ե�ַ

    //QWebEngineView �� load ��һ��ҳ���ᷢ��һ������ɵ��ź�,���� QWebEngineView �Ĵ�С������ EChart �Ĵ�С��
    connect(m_add_wave_data_widget,&QWebEngineView::loadFinished,this,&MainWindow::onResizeEcharts2);
}


void MainWindow::init_widget_max_approach()
{
    /*--����WebEngineView��html�ļ�--*/
    m_max_approach_widget = ui->max_appraoch_widget;
    m_max_approach_widget->setContextMenuPolicy(Qt::NoContextMenu);
    m_max_approach_widget->load(QUrl::fromLocalFile("E:/Desktop/Qt UDP DTS/Qt_UDP_DTS_v3.1.0/res/max_approach_widget.html")); //ֻ��д���Ե�ַ

    //QWebEngineView �� load ��һ��ҳ���ᷢ��һ������ɵ��ź�,���� QWebEngineView �Ĵ�С������ EChart �Ĵ�С��
    connect(m_max_approach_widget,&QWebEngineView::loadFinished,this,&MainWindow::onResizeEcharts3);


}

void MainWindow::init_widget_centroid_approach()
{
    /*--����WebEngineView��html�ļ�--*/
    m_centroid_approach_widget = ui->centroid_approach_widget;
    m_centroid_approach_widget->setContextMenuPolicy(Qt::NoContextMenu);
    m_centroid_approach_widget->load(QUrl::fromLocalFile("E:/Desktop/Qt UDP DTS/Qt_UDP_DTS_v3.1.0/res/centroid_approach_widget.html")); //ֻ��д���Ե�ַ

    //QWebEngineView �� load ��һ��ҳ���ᷢ��һ������ɵ��ź�,���� QWebEngineView �Ĵ�С������ EChart �Ĵ�С��
    connect(m_centroid_approach_widget,&QWebEngineView::loadFinished,this,&MainWindow::onResizeEcharts4);


}

void MainWindow::init_widget_temp_distance()
{
    /*--����WebEngineView��html�ļ�--*/
    m_temp_distance_widget = ui->temp_distance_widget;
    m_temp_distance_widget->setContextMenuPolicy(Qt::NoContextMenu);
    m_temp_distance_widget->load(QUrl::fromLocalFile("E:/Desktop/Qt UDP DTS/Qt_UDP_DTS_v3.1.0/res/Temp_distance_widget.html")); //ֻ��д���Ե�ַ

    //QWebEngineView �� load ��һ��ҳ���ᷢ��һ������ɵ��ź�,���� QWebEngineView �Ĵ�С������ EChart �Ĵ�С��
    connect(m_temp_distance_widget,&QWebEngineView::loadFinished,this,&MainWindow::onResizeEcharts5);


}

void MainWindow::echarts_load_raw_data()
{
    /*--���һ�� JSON �ַ��������ݴ���ȥ--*/
    //1.ʹ�� QJonsObject �����һ�� JSON ����
    QJsonObject seriesData;

    //2.ʹ�� QJsonArray �� JSON ���������һ����
    QJsonArray amplitude;
    for(int i=0; i<1250100; i++) amplitude.push_back(raw_data[i]);
    seriesData.insert("amplitude", amplitude);

    //3.ʹ�� QJsonDocument ���� JSON ����ת�����ַ���
    QString optionStr = QJsonDocument(seriesData).toJson();

    //4.����js��init2��������
    QString js = QString("init2(%1)").arg(optionStr);

    //5.���� QWebEngineView�� page()->runJavaScript("function(str)") ������ JS ����
    m_raw_data_widget->page()->runJavaScript(js);
}

void MainWindow::echarts_load_add_wave()
{
    /*--���һ�� JSON �ַ��������ݴ���ȥ--*/
    //1.ʹ�� QJonsObject �����һ�� JSON ����
    QJsonObject seriesData;

    //2.ʹ�� QJsonArray �� JSON ���������һ����
    QJsonArray amplitude;
    for(int i=0; i<25002; i++) amplitude.push_back(m_demodulation->add_wave_data[i]);
    seriesData.insert("amplitude", amplitude);

    //3.ʹ�� QJsonDocument ���� JSON ����ת�����ַ���
    QString optionStr = QJsonDocument(seriesData).toJson();

    //4.����js��init2��������
    QString js = QString("init2(%1)").arg(optionStr);

    //5.���� QWebEngineView�� page()->runJavaScript("function(str)") ������ JS ����
    m_add_wave_data_widget->page()->runJavaScript(js);

}

void MainWindow::echarts_load_max_approach()
{
    /*--���һ�� JSON �ַ��������ݴ���ȥ--*/
    //1.ʹ�� QJonsObject �����һ�� JSON ����
    QJsonObject seriesData;

    //2.ʹ�� QJsonArray �� JSON ���������һ����
    QJsonArray amplitude;
    for(int i=0; i<25002; i++){
        //�����󲨳�ֵ��index��0 �򲻻����õ�
        if(m_demodulation->wavelength_MaxApproach[i]==0) continue;

        amplitude.push_back(1550.5+0.06*m_demodulation->wavelength_MaxApproach[i]);
    }
    seriesData.insert("amplitude", amplitude);

    //3.ʹ�� QJsonDocument ���� JSON ����ת�����ַ���
    QString optionStr = QJsonDocument(seriesData).toJson();

    //4.����js��init2��������
    QString js = QString("init2(%1)").arg(optionStr);

    //5.���� QWebEngineView�� page()->runJavaScript("function(str)") ������ JS ����
    m_max_approach_widget->page()->runJavaScript(js);
}

void MainWindow::echarts_load_centroid_approach()
{
    /*--���һ�� JSON �ַ��������ݴ���ȥ--*/
    //1.ʹ�� QJonsObject �����һ�� JSON ����
    QJsonObject seriesData;

    //2.ʹ�� QJsonArray �� JSON ���������һ����
    QJsonArray amplitude;
    for(int i=0; i<25002; i++){
        //�����󲨳�ֵ��index��0 �򲻻����õ�
        if(m_demodulation->wavelength_CentroidApproach[i]==0) continue;

        amplitude.push_back(1550.5+0.06*m_demodulation->wavelength_CentroidApproach[i]);
    }
    seriesData.insert("amplitude", amplitude);

    //3.ʹ�� QJsonDocument ���� JSON ����ת�����ַ���
    QString optionStr = QJsonDocument(seriesData).toJson();

    //4.����js��init2��������
    QString js = QString("init2(%1)").arg(optionStr);

    //5.���� QWebEngineView�� page()->runJavaScript("function(str)") ������ JS ����
    m_centroid_approach_widget->page()->runJavaScript(js);
}

void MainWindow::echarts_load_temp()
{
    /*--���һ�� JSON �ַ��������ݴ���ȥ--*/
    //1.ʹ�� QJonsObject �����һ�� JSON ����
    QJsonObject seriesData;

    //2.ʹ�� QJsonArray �� JSON ���������һ����
    QJsonArray amplitude;
    for(int i=0; i<25002; i++) {
        //������Ĳ������¶�ֵ��0 �򲻻����õ�
        if(m_demodulation->Temp[i]==0) continue;

        //����¶�ֵ̫С���򲻻����õ�
        if(m_demodulation->Temp[i]<-120) continue;

        amplitude.push_back(m_demodulation->Temp[i]);
    }
    seriesData.insert("amplitude", amplitude);

    //3.ʹ�� QJsonDocument ���� JSON ����ת�����ַ���
    QString optionStr = QJsonDocument(seriesData).toJson();

    //4.����js��init2��������
    QString js = QString("init2(%1)").arg(optionStr);

    //5.���� QWebEngineView�� page()->runJavaScript("function(str)") ������ JS ����
    m_temp_distance_widget->page()->runJavaScript(js);
}

//�����ȡ�ļ���ť
void MainWindow::on_btn_readfls_clicked()
{
    //���ļ�ѡ��Ի���
    QString fileName = QFileDialog::getOpenFileName(this, tr("open file"), " ",  tr("txt(*.txt);;Allfile(*.*)"));

    qDebug()<<fileName<<endl;

    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("File Dir: ")+fileName+"\n");

    /*--�����ķ�ʽ��.txt�ļ�*/
    char buf[32];

    ifstream infile;
    infile.open(fileName.toStdString().data(),std::ifstream::in);

    if(!infile.is_open()) {
        qDebug()<<"Open File Error!"<<endl;

        ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Open File Error!")+"\n");

        delete[] raw_data; //�ͷŶ�̬������ڴ�

        return;
    }
    else
        qDebug()<<"Open File Succeed!"<<endl;
    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Open File Succeed!")+"\n");

    for(int i=0;i<1250100;i++){
        infile >> buf; //>>������� >> �����ո����ʱ���ͻ���ֹ�������´ν��� >> ʱ���ӿո���к��������

        raw_data[i] = strtod(buf,NULL); //char[]תdouble����
    }

    infile.close();

    /*--��ʾraw_data����--*/
//    echarts_load_raw_data(); //�ܿ�

    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Display Raw Data Wave!")+"\n");

    qDebug()<<"Display raw_wave Succeed!"<<endl;
}

//��������ť
void MainWindow::on_btn_demodulation_clicked()
{
    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Start Demodulating Data! ")+"\n");

    m_demodulation->start(); //�����ȿ���demodulation�̣߳�����ʾadd_wave_widget

    echarts_load_add_wave();
    echarts_load_max_approach();
    echarts_load_centroid_approach();
    echarts_load_temp();
}

//������ֵ����ť
void MainWindow::on_btn_maxValue_clicked()
{
    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("MaxValue Approach to get Central Wavelength! ")+"\n");

    //    m_maxValue_wavelength_widget->show();
    init_widget_max_approach();

    qDebug()<<"Display MaxValue_wavelength Succeed!"<<endl;
}

//������ķ���ť
void MainWindow::on_btn_centroid_clicked()
{
    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Centroid Approach to get Central Wavelength! ")+"\n");

    //    m_centroid_wavelength_widget->show();

    init_widget_centroid_approach();

    qDebug()<<"Display Centroid_wavelength Succeed!"<<endl;
}

//����¶��жϰ�ť
void MainWindow::on_btn_temp_clicked()
{
    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Temperature Judgement! ")+"\n");

    //    m_tempDistance_widget->show();

    init_widget_temp_distance();

    qDebug()<<"Display Temp Distance Succeed!"<<endl;

}

//�������ԭʼ���ݰ�ť
void MainWindow::save_raw_data()
{
    m_raw_data_save->start();

    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Start Saving raw data! ")+"\n");
}

//��ȡ�洢�ļ�·��
void MainWindow::save_filename()
{
    m_temp_distance_save->saveFilename = QFileDialog::getExistingDirectory(this, tr("ѡ���ļ�����·��"), "./", QFileDialog::ShowDirsOnly);

    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Temperature-Distance Data have been saved at!")+m_temp_distance_save->saveFilename+"\n");
}

//�����λͼ��ť
void MainWindow::on_btn_reset_wave_clicked()
{

}

//����������ݰ�ť
void MainWindow::on_btn_save_temp_clicked()
{
    m_temp_distance_save->start();

    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Start Saving Temperature-Distance Data!")+"\n");
}

//����Ӧ���ڱ仯��С
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

//��Ϊ����ʵ���ڴ��ڸı��Сʱ ECharts Ҳ���ű仯����������Ҫ�� resizeEvent ʱ����ҲҪ���ô�С
void MainWindow::resizeEvent(QResizeEvent *event)
{
    if(isLoaded1) onResizeEcharts1();
    if(isLoaded2) onResizeEcharts2();
    if(isLoaded3) onResizeEcharts3();
    if(isLoaded4) onResizeEcharts4();
    if(isLoaded5) onResizeEcharts5();
}

