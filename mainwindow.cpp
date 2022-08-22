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
    m_tempDistance_widget(new Temp_distance_widget(m_demodulation))
{
    ui->setupUi(this);

    setWindowTitle(QString("Qt UDP DTS"));

    connect(this,&MainWindow::sendToRaw_wave_widget,m_raw_wave_widget,&raw_wave_widget::display_wave);
    connect(m_demodulation,&demodulation::sendToAdd_wave_widget,m_add_wave_widget,&add_wave_widget::display_wave,Qt::QueuedConnection);
    connect(m_demodulation,&demodulation::sendToMaxValue_widget,m_maxValue_wavelength_widget,&MaxValue_wavelength_widget::display_wave,Qt::QueuedConnection);
    connect(m_demodulation,&demodulation::sendToCentroid_widget,m_centroid_wavelength_widget,&Centroid_wavelength_widget::display_wave,Qt::QueuedConnection);
    connect(m_demodulation,&demodulation::sendToTempDistance_widget,m_tempDistance_widget,&Temp_distance_widget::display_wave,Qt::QueuedConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_readfls_clicked()
{
    //���ļ�ѡ��Ի���
    QString fileName = QFileDialog::getOpenFileName(this, tr("open file"), " ",  tr("txt(*.txt);;Allfile(*.*)"));

    qDebug()<<fileName<<endl;

    ui->m_textBrowser->insertPlainText(QString("File Dir: ")+fileName+"\n");

    /*--�����ķ�ʽ��.txt�ļ�*/
    char buf[32];

    ifstream infile;
    infile.open(fileName.toStdString().data(),std::ifstream::in);

    if(!infile.is_open()) {
        qDebug()<<"Open File Error!"<<endl;

        ui->m_textBrowser->insertPlainText(QString("Open File Error !")+"\n");

        delete[] raw_data; //�ͷŶ�̬������ڴ�

        return;
    }
    else
        qDebug()<<"Open File Succeed!"<<endl;
        ui->m_textBrowser->insertPlainText(QString("Open File Succeed !")+"\n");

    for(int i=0;i<1250100;i++){
        infile >> buf; //>>������� >> �����ո����ʱ���ͻ���ֹ�������´ν��� >> ʱ���ӿո���к��������

        raw_data[i] = strtod(buf,NULL); //char[]תdouble����
    }

    infile.close();
}

//�����ʾraw_data���ΰ�ť
void MainWindow::on_btn_dspwave_clicked()
{
    emit sendToRaw_wave_widget(raw_data);

    m_raw_wave_widget->show();

    ui->m_textBrowser->insertPlainText(QString("Display Raw Data Wave")+"\n");
}



void MainWindow::on_btn_demodulation_clicked()
{
    ui->m_textBrowser->insertPlainText(QString("Demodulation Data ! ")+"\n");

    m_demodulation->start(); //�����ȿ���demodulation�̣߳�����ʾadd_wave_widget

    m_add_wave_widget->show();

    m_demodulation->spectrum_wava.loadFromData(m_demodulation->wavelength_distance_array, 50, 50, m_demodulation->s1, m_demodulation->s1, m_demodulation->w1, m_demodulation->w2); //��һ������

//        deleteData(pp, x);
    m_demodulation->spectrum_wava.setRotation(30,0,15);
    m_demodulation->spectrum_wava.setScale(1,1,1);
    m_demodulation->spectrum_wava.setShift(0,0,0);
    m_demodulation->spectrum_wava.setZoom(0.9);

    m_demodulation->spectrum_wava.updateData();
    //m_demodulation->spectrum_wava.updateGL();
    m_demodulation->spectrum_wava.show();
}


void MainWindow::on_btn_maxValue_clicked()
{
    ui->m_textBrowser->insertPlainText(QString("MaxValue Approach to get Central Wavelength ! ")+"\n");

    m_maxValue_wavelength_widget->show();
}


void MainWindow::on_btn_centroid_clicked()
{
    ui->m_textBrowser->insertPlainText(QString("Centroid Approach to get Central Wavelength ! ")+"\n");

    m_centroid_wavelength_widget->show();
}


void MainWindow::on_btn_temp_clicked()
{
    ui->m_textBrowser->insertPlainText(QString("Temperature Judgement ! ")+"\n");

    m_tempDistance_widget->show();
}

