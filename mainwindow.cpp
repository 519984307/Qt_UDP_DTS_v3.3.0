#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    raw_data(new double[1250100]),
    m_raw_wave_widget(new raw_wave_widget()),
    m_demodulation(new demodulation(this)),
    m_add_wave_widget(new add_wave_widget(m_demodulation))
{
    ui->setupUi(this);

    setWindowTitle(QString("Qt UDP DTS"));

    connect(this,&MainWindow::sendToRaw_wave_widget,m_raw_wave_widget,&raw_wave_widget::display_wave);
    connect(m_demodulation,&demodulation::sendToAdd_wave_widget,m_add_wave_widget,&add_wave_widget::display_wave,Qt::QueuedConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_readfls_clicked()
{
    //打开文件选择对话框
    QString fileName = QFileDialog::getOpenFileName(this, tr("open file"), " ",  tr("txt(*.txt);;Allfile(*.*)"));

    qDebug()<<fileName<<endl;

    ui->m_textBrowser->insertPlainText(QString("File Dir: ")+fileName+"\n");

    /*--以流的方式打开.txt文件*/
    char buf[32];

    ifstream infile;
    infile.open(fileName.toStdString().data(),std::ifstream::in);

    if(!infile.is_open()) {
        qDebug()<<"Open File Error!"<<endl;

        ui->m_textBrowser->insertPlainText(QString("Open File Error !")+"\n");

        delete[] raw_data; //释放动态分配的内存

        return;
    }
    else
        qDebug()<<"Open File Succeed!"<<endl;
        ui->m_textBrowser->insertPlainText(QString("Open File Succeed !")+"\n");

    for(int i=0;i<1250100;i++){
        infile >> buf; //>>运算符当 >> 遇到空格或换行时，就会终止，并在下次进行 >> 时，从空格或换行后继续进行

        raw_data[i] = strtod(buf,NULL); //char[]转double数字
    }

    infile.close();
}


void MainWindow::on_btn_dspwave_clicked()
{
    emit sendToRaw_wave_widget(raw_data);

    m_raw_wave_widget->show();

    ui->m_textBrowser->insertPlainText(QString("Display Raw Data Wave")+"\n");
}



void MainWindow::on_btn_demodulation_clicked()
{
    m_demodulation->start(); //必须先开启demodulation线程，再显示add_wave_widget

    m_add_wave_widget->show();
}

