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

    connect(this,&MainWindow::sendToRaw_wave_widget,m_raw_wave_widget,&raw_wave_widget::display_wave);
    connect(m_demodulation,&demodulation::sendToAdd_wave_widget,m_add_wave_widget,&add_wave_widget::display_wave,Qt::QueuedConnection);
    connect(m_demodulation,&demodulation::sendToMaxValue_widget,m_maxValue_wavelength_widget,&MaxValue_wavelength_widget::display_wave,Qt::QueuedConnection);
    connect(m_demodulation,&demodulation::sendToCentroid_widget,m_centroid_wavelength_widget,&Centroid_wavelength_widget::display_wave,Qt::QueuedConnection);
    connect(m_demodulation,&demodulation::sendToTempDistance_widget,m_tempDistance_widget,&Temp_distance_widget::display_wave,Qt::QueuedConnection);
    connect(m_raw_wave_widget,&raw_wave_widget::sendToMainwindow_save,this,&MainWindow::save_raw_data);
    connect(m_tempDistance_widget,&Temp_distance_widget::sendToMainwindow_save,this,&MainWindow::save_temp_distance_data);
    connect(m_temp_distance_save,&Temp_distance_save::getFilename,this,&MainWindow::save_filename,Qt::BlockingQueuedConnection);
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
}

//�����ʾraw_data���ΰ�ť
void MainWindow::on_btn_dspwave_clicked()
{
    emit sendToRaw_wave_widget(raw_data);

    m_raw_wave_widget->show();

    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Display Raw Data Wave!")+"\n");
}


void MainWindow::on_btn_demodulation_clicked()
{
    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Start Demodulating Data! ")+"\n");

    m_demodulation->start(); //�����ȿ���demodulation�̣߳�����ʾadd_wave_widget

    m_add_wave_widget->show();

    //������qwtplot3d������-����-ǿ��ͼ ����
//    m_demodulation->spectrum_wava.loadFromData(m_demodulation->wavelength_distance_array, 50, 50, m_demodulation->s1, m_demodulation->s1, m_demodulation->w1, m_demodulation->w2); //��һ������

////        deleteData(pp, x);
//    m_demodulation->spectrum_wava.setRotation(30,0,15);
//    m_demodulation->spectrum_wava.setScale(1,1,1);
//    m_demodulation->spectrum_wava.setShift(0,0,0);
//    m_demodulation->spectrum_wava.setZoom(0.9);

//    m_demodulation->spectrum_wava.updateData();
//    //m_demodulation->spectrum_wava.updateGL();
//    m_demodulation->spectrum_wava.show();
}


void MainWindow::on_btn_maxValue_clicked()
{
    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("MaxValue Approach to get Central Wavelength! ")+"\n");

    m_maxValue_wavelength_widget->show();
}


void MainWindow::on_btn_centroid_clicked()
{
    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Centroid Approach to get Central Wavelength! ")+"\n");

    m_centroid_wavelength_widget->show();
}


void MainWindow::on_btn_temp_clicked()
{
    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Temperature Judgement! ")+"\n");

    m_tempDistance_widget->show();
}

void MainWindow::save_raw_data()
{
    m_raw_data_save->start();

    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Start Saving raw data! ")+"\n");
}

void MainWindow::save_temp_distance_data()
{
    m_temp_distance_save->start();

    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Start Saving Temperature-Distance Data!")+"\n");
}

void MainWindow::save_filename()
{
    m_temp_distance_save->saveFilename = QFileDialog::getExistingDirectory(this, tr("ѡ���ļ�����·��"), "./", QFileDialog::ShowDirsOnly);

    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Temperature-Distance Data have been saved at!")+m_temp_distance_save->saveFilename+"\n");
}

