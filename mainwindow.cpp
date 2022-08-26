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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_widget_raw_data()
{
    m_raw_data_widget = ui->raw_data_widget;

    //ÿ�����߶����ռһ��graph()
    m_raw_data_widget->addGraph();
    m_raw_data_widget->graph(0)->setPen(QPen(Qt::blue)); // ���ߵ���ɫ
    m_raw_data_widget->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // ������X���Χ������ɫ

    m_raw_data_widget->yAxis->setRangeLower(-2);
    m_raw_data_widget->yAxis->setRangeUpper(70);

    // �߿��Ҳ���ϲ����ʾ�̶��ߣ�������ʾ�̶�ֵ:
    // (�μ� QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    m_raw_data_widget->xAxis2->setVisible(true);
    m_raw_data_widget->xAxis2->setTickLabels(false);
    m_raw_data_widget->yAxis2->setVisible(true);
    m_raw_data_widget->yAxis2->setTickLabels(false);

    m_raw_data_widget->xAxis->setLabel("Sample Dots");
    m_raw_data_widget->yAxis->setLabel("Amplitudes");
    QFont xFont = m_raw_data_widget->xAxis->labelFont();
     xFont.setPixelSize(20);
     m_raw_data_widget->xAxis->setLabelFont(xFont);
     QFont yFont = m_raw_data_widget->yAxis->labelFont();
      yFont.setPixelSize(20);
      m_raw_data_widget->yAxis->setLabelFont(yFont);

    // ֧�������ק��ķ�Χ������������ķ�Χ�������ѡͼ�㣨ÿ�����߶�ռһ��ͼ�㣩
    m_raw_data_widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    //��ѡ�Ŵ�
    m_raw_data_widget->selectionRect()->setPen(QPen(Qt::black,1,Qt::DashLine));//����ѡ�����ʽ������
    m_raw_data_widget->selectionRect()->setBrush(QBrush(QColor(0,0,100,50)));//����ѡ�����ʽ����͸��ǳ��
    m_raw_data_widget->setSelectionRectMode(QCP::SelectionRectMode::srmZoom);
}

void MainWindow::init_widget_add_wave()
{
    m_add_wave_data_widget = ui->addwave_data_widget;

    //ÿ�����߶����ռһ��graph()
    m_add_wave_data_widget->addGraph();
    m_add_wave_data_widget->graph(0)->setPen(QPen(Qt::blue)); // ���ߵ���ɫ
    m_add_wave_data_widget->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // ������X���Χ������ɫ

    m_add_wave_data_widget->yAxis->setRangeLower(-2);
    m_add_wave_data_widget->yAxis->setRangeUpper(70);

    // �߿��Ҳ���ϲ����ʾ�̶��ߣ�������ʾ�̶�ֵ:
    // (�μ� QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    m_add_wave_data_widget->xAxis2->setVisible(true);
    m_add_wave_data_widget->xAxis2->setTickLabels(false);
    m_add_wave_data_widget->yAxis2->setVisible(true);
    m_add_wave_data_widget->yAxis2->setTickLabels(false);

    m_add_wave_data_widget->xAxis->setLabel("Sample Dots");
    m_add_wave_data_widget->yAxis->setLabel("Amplitudes");
    QFont xFont = m_add_wave_data_widget->xAxis->labelFont();
     xFont.setPixelSize(20);
     m_add_wave_data_widget->xAxis->setLabelFont(xFont);
     QFont yFont = m_add_wave_data_widget->yAxis->labelFont();
      yFont.setPixelSize(20);
      m_add_wave_data_widget->yAxis->setLabelFont(yFont);

    // ֧�������ק��ķ�Χ������������ķ�Χ�������ѡͼ�㣨ÿ�����߶�ռһ��ͼ�㣩
    m_add_wave_data_widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    //��ѡ�Ŵ�
    m_add_wave_data_widget->selectionRect()->setPen(QPen(Qt::black,1,Qt::DashLine));//����ѡ�����ʽ������
    m_add_wave_data_widget->selectionRect()->setBrush(QBrush(QColor(0,0,100,50)));//����ѡ�����ʽ����͸��ǳ��
    m_add_wave_data_widget->setSelectionRectMode(QCP::SelectionRectMode::srmZoom);
}

void MainWindow::init_widget_max_approach()
{
    m_max_approach_widget = ui->max_appraoch_widget;

    m_max_approach_widget->addGraph();
    m_max_approach_widget->graph(0)->setPen(QPen(Qt::blue)); // ���ߵ���ɫ
    m_max_approach_widget->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // ������X���Χ������ɫ
    m_max_approach_widget->yAxis->setRangeLower(1550);
    m_max_approach_widget->yAxis->setRangeUpper(1554);
    m_max_approach_widget->xAxis->setRangeLower(0);
    m_max_approach_widget->xAxis->setRangeUpper(1000);
    m_max_approach_widget->xAxis2->setVisible(true);
    m_max_approach_widget->xAxis2->setTickLabels(false);
    m_max_approach_widget->yAxis2->setVisible(true);
    m_max_approach_widget->yAxis2->setTickLabels(false);

    m_max_approach_widget->xAxis->setLabel("Distance/m");
    m_max_approach_widget->yAxis->setLabel("Wavelength/nm");
    QFont xFont = m_max_approach_widget->xAxis->labelFont();
     xFont.setPixelSize(20);
     m_max_approach_widget->xAxis->setLabelFont(xFont);
     QFont yFont = m_max_approach_widget->yAxis->labelFont();
      yFont.setPixelSize(20);
      m_max_approach_widget->yAxis->setLabelFont(yFont);

    m_max_approach_widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    m_max_approach_widget->selectionRect()->setPen(QPen(Qt::black,1,Qt::DashLine));//����ѡ�����ʽ������
    m_max_approach_widget->selectionRect()->setBrush(QBrush(QColor(0,0,100,50)));//����ѡ�����ʽ����͸��ǳ��
    m_max_approach_widget->setSelectionRectMode(QCP::SelectionRectMode::srmZoom);
}

void MainWindow::init_widget_centroid_approach()
{
    m_centroid_approach_widget = ui->centroid_approach_widget;

    m_centroid_approach_widget->addGraph();
    m_centroid_approach_widget->graph(0)->setPen(QPen(Qt::blue)); // ���ߵ���ɫ
    m_centroid_approach_widget->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // ������X���Χ������ɫ

    m_centroid_approach_widget->yAxis->setRangeLower(1550);
    m_centroid_approach_widget->yAxis->setRangeUpper(1554);
    m_centroid_approach_widget->xAxis->setRangeLower(0);
    m_centroid_approach_widget->xAxis->setRangeUpper(1000);

    m_centroid_approach_widget->xAxis2->setVisible(true);
    m_centroid_approach_widget->xAxis2->setTickLabels(false);
    m_centroid_approach_widget->yAxis2->setVisible(true);
    m_centroid_approach_widget->yAxis2->setTickLabels(false);

    m_centroid_approach_widget->xAxis->setLabel("Distance/m");
    m_centroid_approach_widget->yAxis->setLabel("Wavelength/nm");
    QFont xFont = m_centroid_approach_widget->xAxis->labelFont();
     xFont.setPixelSize(20);
     m_centroid_approach_widget->xAxis->setLabelFont(xFont);
     QFont yFont = m_centroid_approach_widget->yAxis->labelFont();
      yFont.setPixelSize(20);
      m_centroid_approach_widget->yAxis->setLabelFont(yFont);

    m_centroid_approach_widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    m_centroid_approach_widget->selectionRect()->setPen(QPen(Qt::black,1,Qt::DashLine));//����ѡ�����ʽ������
    m_centroid_approach_widget->selectionRect()->setBrush(QBrush(QColor(0,0,100,50)));//����ѡ�����ʽ����͸��ǳ��
    m_centroid_approach_widget->setSelectionRectMode(QCP::SelectionRectMode::srmZoom);
}

void MainWindow::init_widget_temp_distance()
{
    m_temp_distance_widget = ui->temp_distance_widget;

    //ÿ�����߶����ռһ��graph()
    m_temp_distance_widget->addGraph();
    m_temp_distance_widget->graph(0)->setPen(QPen(Qt::blue)); // ���ߵ���ɫ
    m_temp_distance_widget->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // ������X���Χ������ɫ

    m_temp_distance_widget->yAxis->setRangeLower(-120);
    m_temp_distance_widget->yAxis->setRangeUpper(60);
    m_temp_distance_widget->xAxis->setRangeLower(0);
    m_temp_distance_widget->xAxis->setRangeUpper(1000);

    m_temp_distance_widget->xAxis2->setVisible(true);
    m_temp_distance_widget->xAxis2->setTickLabels(false);
    m_temp_distance_widget->yAxis2->setVisible(true);
    m_temp_distance_widget->yAxis2->setTickLabels(false);

    m_temp_distance_widget->xAxis->setLabel("Distance/m");
    m_temp_distance_widget->yAxis->setLabel("Temperature/C");
    QFont xFont = m_temp_distance_widget->xAxis->labelFont();
     xFont.setPixelSize(20);
     m_temp_distance_widget->xAxis->setLabelFont(xFont);
     QFont yFont = m_temp_distance_widget->yAxis->labelFont();
      yFont.setPixelSize(20);
      m_temp_distance_widget->yAxis->setLabelFont(yFont);

    m_temp_distance_widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    m_temp_distance_widget->selectionRect()->setPen(QPen(Qt::black,1,Qt::DashLine));//����ѡ�����ʽ������
    m_temp_distance_widget->selectionRect()->setBrush(QBrush(QColor(0,0,100,50)));//����ѡ�����ʽ����͸��ǳ��
    m_temp_distance_widget->setSelectionRectMode(QCP::SelectionRectMode::srmZoom);
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
    init_widget_raw_data();

    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Display Raw Data Wave!")+"\n");

    qDebug()<<"Display raw_wave Succeed!"<<endl;

    for(int i=0;i<1250100;i++){
        //display wave
        QVector<double> x(1),y(1);

        x[0] = i;
        y[0]= raw_data[i];

        m_raw_data_widget->graph(0)->addData(x, y);
    }

    //�Զ�����XY��ķ�Χ���Ա���ʾ��graph(0)�����еĵ�
    m_raw_data_widget->graph(0)->rescaleAxes(true);
}

//�����ʾraw_data���ΰ�ť
//void MainWindow::on_btn_dspwave_clicked()
//{
////    emit sendToRaw_wave_widget(raw_data);

////    m_raw_wave_widget->show();

//    init_widget_raw_data();

//    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Display Raw Data Wave!")+"\n");

//    qDebug()<<"Display raw_wave Succeed!"<<endl;

//    for(int i=0;i<1250100;i++){
//        //display wave
//        QVector<double> x(1),y(1);

//        x[0] = i;
//        y[0]= raw_data[i];

//        m_raw_data_widget->graph(0)->addData(x, y);
//    }

//    //�Զ�����XY��ķ�Χ���Ա���ʾ��graph(0)�����еĵ�
//    m_raw_data_widget->graph(0)->rescaleAxes(true);
//}

//��������ť
void MainWindow::on_btn_demodulation_clicked()
{
    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Start Demodulating Data! ")+"\n");

    m_demodulation->start(); //�����ȿ���demodulation�̣߳�����ʾadd_wave_widget

    //  ��ʾadd_wave_data����
    init_widget_add_wave();

    qDebug()<<"Display add_wave Succeed!"<<endl;

    for(int i=0;i<25002;i++){
        QVector<double> x(1),y(1);

        x[0] = i;
        y[0]= m_demodulation->add_wave_data[i];

        m_add_wave_data_widget->graph(0)->addData(x, y);
    }

    on_btn_maxValue_clicked();
    on_btn_centroid_clicked();
    on_btn_temp_clicked();
}

//������ֵ����ť
void MainWindow::on_btn_maxValue_clicked()
{
    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("MaxValue Approach to get Central Wavelength! ")+"\n");

//    m_maxValue_wavelength_widget->show();
    init_widget_max_approach();

    qDebug()<<"Display MaxValue_wavelength Succeed!"<<endl;

    for(int i=0;i<25002;i++){
        //�����󲨳�ֵ��index��0 �򲻻����õ�
        if(m_demodulation->wavelength_MaxApproach[i]==0) continue;

        QVector<double> x(1),y(1);

        x[0] = i*0.04;
        y[0]= 1550.5+0.06*m_demodulation->wavelength_MaxApproach[i];

        m_max_approach_widget->graph(0)->addData(x, y);
    }
}

//������ķ���ť
void MainWindow::on_btn_centroid_clicked()
{
    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Centroid Approach to get Central Wavelength! ")+"\n");

//    m_centroid_wavelength_widget->show();

    init_widget_centroid_approach();

    qDebug()<<"Display Centroid_wavelength Succeed!"<<endl;

    for(int i=0;i<25002;i++){

        //�����󲨳�ֵ��index��0 �򲻻����õ�
        if(m_demodulation->wavelength_CentroidApproach[i]==0) continue;

        QVector<double> x(1),y(1);

        x[0] = i*0.04;
        y[0]= 1550.5+0.06*m_demodulation->wavelength_CentroidApproach[i];

        m_centroid_approach_widget->graph(0)->addData(x, y);
    }
}

//����¶��жϰ�ť
void MainWindow::on_btn_temp_clicked()
{
    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Temperature Judgement! ")+"\n");

//    m_tempDistance_widget->show();

    init_widget_temp_distance();

    qDebug()<<"Display Temp Distance Succeed!"<<endl;

    for(int i=0;i<25002;i++){

        //������Ĳ������¶�ֵ��0 �򲻻����õ�
        if(m_demodulation->Temp[i]==0) continue;

        QVector<double> x(1),y(1);

        x[0] = i*0.04;
        y[0]= m_demodulation->Temp[i];

        //����¶�ֵ̫С���򲻻����õ�
        if(y[0]<-120) continue;

        m_temp_distance_widget->graph(0)->addData(x, y);
    }
}

//�������ԭʼ���ݰ�ť
void MainWindow::save_raw_data()
{
    m_raw_data_save->start();

    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Start Saving raw data! ")+"\n");
}

////��������¶�-�������ݰ�ť(����)
//void MainWindow::save_temp_distance_data()
//{
//    m_temp_distance_save->start();

//    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Start Saving Temperature-Distance Data!")+"\n");
//}

void MainWindow::save_filename()
{
    m_temp_distance_save->saveFilename = QFileDialog::getExistingDirectory(this, tr("ѡ���ļ�����·��"), "./", QFileDialog::ShowDirsOnly);

    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Temperature-Distance Data have been saved at!")+m_temp_distance_save->saveFilename+"\n");
}


void MainWindow::on_btn_reset_wave_clicked()
{
    m_raw_data_widget->yAxis->setRangeLower(-2);
    m_raw_data_widget->yAxis->setRangeUpper(70);
    // ����ˢ��ͼ��
    m_raw_data_widget->replot();

    m_add_wave_data_widget->yAxis->setRangeLower(-2000);
    m_add_wave_data_widget->yAxis->setRangeUpper(14000);
    m_add_wave_data_widget->xAxis->setRangeLower(0);
    m_add_wave_data_widget->xAxis->setRangeUpper(25002);
    m_add_wave_data_widget->replot();

    m_max_approach_widget->yAxis->setRangeLower(1551);
    m_max_approach_widget->yAxis->setRangeUpper(1554);
    m_max_approach_widget->xAxis->setRangeLower(0);
    m_max_approach_widget->xAxis->setRangeUpper(1000);
    m_max_approach_widget->replot();

    m_centroid_approach_widget->yAxis->setRangeLower(1551.9);
    m_centroid_approach_widget->yAxis->setRangeUpper(1552.1);
    m_centroid_approach_widget->xAxis->setRangeLower(0);
    m_centroid_approach_widget->xAxis->setRangeUpper(1000);
    m_centroid_approach_widget->replot();

    m_temp_distance_widget->yAxis->setRangeLower(-120);
    m_temp_distance_widget->yAxis->setRangeUpper(60);
    m_temp_distance_widget->xAxis->setRangeLower(0);
    m_temp_distance_widget->xAxis->setRangeUpper(1000);
    m_temp_distance_widget->replot();
}

//����������ݰ�ť
void MainWindow::on_btn_save_temp_clicked()
{
    m_temp_distance_save->start();

    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Start Saving Temperature-Distance Data!")+"\n");
}

