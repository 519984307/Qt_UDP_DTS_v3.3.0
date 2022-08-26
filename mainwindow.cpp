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

    //每条曲线都会独占一个graph()
    m_raw_data_widget->addGraph();
    m_raw_data_widget->graph(0)->setPen(QPen(Qt::blue)); // 曲线的颜色
    m_raw_data_widget->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // 曲线与X轴包围区的颜色

    m_raw_data_widget->yAxis->setRangeLower(-2);
    m_raw_data_widget->yAxis->setRangeUpper(70);

    // 边框右侧和上侧均显示刻度线，但不显示刻度值:
    // (参见 QCPAxisRect::setupFullAxesBox for a quicker method to do this)
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

    // 支持鼠标拖拽轴的范围、滚动缩放轴的范围，左键点选图层（每条曲线独占一个图层）
    m_raw_data_widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    //框选放大
    m_raw_data_widget->selectionRect()->setPen(QPen(Qt::black,1,Qt::DashLine));//设置选框的样式：虚线
    m_raw_data_widget->selectionRect()->setBrush(QBrush(QColor(0,0,100,50)));//设置选框的样式：半透明浅蓝
    m_raw_data_widget->setSelectionRectMode(QCP::SelectionRectMode::srmZoom);
}

void MainWindow::init_widget_add_wave()
{
    m_add_wave_data_widget = ui->addwave_data_widget;

    //每条曲线都会独占一个graph()
    m_add_wave_data_widget->addGraph();
    m_add_wave_data_widget->graph(0)->setPen(QPen(Qt::blue)); // 曲线的颜色
    m_add_wave_data_widget->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // 曲线与X轴包围区的颜色

    m_add_wave_data_widget->yAxis->setRangeLower(-2);
    m_add_wave_data_widget->yAxis->setRangeUpper(70);

    // 边框右侧和上侧均显示刻度线，但不显示刻度值:
    // (参见 QCPAxisRect::setupFullAxesBox for a quicker method to do this)
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

    // 支持鼠标拖拽轴的范围、滚动缩放轴的范围，左键点选图层（每条曲线独占一个图层）
    m_add_wave_data_widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    //框选放大
    m_add_wave_data_widget->selectionRect()->setPen(QPen(Qt::black,1,Qt::DashLine));//设置选框的样式：虚线
    m_add_wave_data_widget->selectionRect()->setBrush(QBrush(QColor(0,0,100,50)));//设置选框的样式：半透明浅蓝
    m_add_wave_data_widget->setSelectionRectMode(QCP::SelectionRectMode::srmZoom);
}

void MainWindow::init_widget_max_approach()
{
    m_max_approach_widget = ui->max_appraoch_widget;

    m_max_approach_widget->addGraph();
    m_max_approach_widget->graph(0)->setPen(QPen(Qt::blue)); // 曲线的颜色
    m_max_approach_widget->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // 曲线与X轴包围区的颜色
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
    m_max_approach_widget->selectionRect()->setPen(QPen(Qt::black,1,Qt::DashLine));//设置选框的样式：虚线
    m_max_approach_widget->selectionRect()->setBrush(QBrush(QColor(0,0,100,50)));//设置选框的样式：半透明浅蓝
    m_max_approach_widget->setSelectionRectMode(QCP::SelectionRectMode::srmZoom);
}

void MainWindow::init_widget_centroid_approach()
{
    m_centroid_approach_widget = ui->centroid_approach_widget;

    m_centroid_approach_widget->addGraph();
    m_centroid_approach_widget->graph(0)->setPen(QPen(Qt::blue)); // 曲线的颜色
    m_centroid_approach_widget->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // 曲线与X轴包围区的颜色

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

    m_centroid_approach_widget->selectionRect()->setPen(QPen(Qt::black,1,Qt::DashLine));//设置选框的样式：虚线
    m_centroid_approach_widget->selectionRect()->setBrush(QBrush(QColor(0,0,100,50)));//设置选框的样式：半透明浅蓝
    m_centroid_approach_widget->setSelectionRectMode(QCP::SelectionRectMode::srmZoom);
}

void MainWindow::init_widget_temp_distance()
{
    m_temp_distance_widget = ui->temp_distance_widget;

    //每条曲线都会独占一个graph()
    m_temp_distance_widget->addGraph();
    m_temp_distance_widget->graph(0)->setPen(QPen(Qt::blue)); // 曲线的颜色
    m_temp_distance_widget->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // 曲线与X轴包围区的颜色

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

    m_temp_distance_widget->selectionRect()->setPen(QPen(Qt::black,1,Qt::DashLine));//设置选框的样式：虚线
    m_temp_distance_widget->selectionRect()->setBrush(QBrush(QColor(0,0,100,50)));//设置选框的样式：半透明浅蓝
    m_temp_distance_widget->setSelectionRectMode(QCP::SelectionRectMode::srmZoom);
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

    //自动调整XY轴的范围，以便显示出graph(0)中所有的点
    m_raw_data_widget->graph(0)->rescaleAxes(true);
}

//点击显示raw_data波形按钮
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

//    //自动调整XY轴的范围，以便显示出graph(0)中所有的点
//    m_raw_data_widget->graph(0)->rescaleAxes(true);
//}

//点击解调按钮
void MainWindow::on_btn_demodulation_clicked()
{
    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Start Demodulating Data! ")+"\n");

    m_demodulation->start(); //必须先开启demodulation线程，再显示add_wave_widget

    //  显示add_wave_data波形
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

//点击最大值法按钮
void MainWindow::on_btn_maxValue_clicked()
{
    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("MaxValue Approach to get Central Wavelength! ")+"\n");

//    m_maxValue_wavelength_widget->show();
    init_widget_max_approach();

    qDebug()<<"Display MaxValue_wavelength Succeed!"<<endl;

    for(int i=0;i<25002;i++){
        //如果最大波长值的index是0 则不画出该点
        if(m_demodulation->wavelength_MaxApproach[i]==0) continue;

        QVector<double> x(1),y(1);

        x[0] = i*0.04;
        y[0]= 1550.5+0.06*m_demodulation->wavelength_MaxApproach[i];

        m_max_approach_widget->graph(0)->addData(x, y);
    }
}

//点击质心法按钮
void MainWindow::on_btn_centroid_clicked()
{
    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Centroid Approach to get Central Wavelength! ")+"\n");

//    m_centroid_wavelength_widget->show();

    init_widget_centroid_approach();

    qDebug()<<"Display Centroid_wavelength Succeed!"<<endl;

    for(int i=0;i<25002;i++){

        //如果最大波长值的index是0 则不画出该点
        if(m_demodulation->wavelength_CentroidApproach[i]==0) continue;

        QVector<double> x(1),y(1);

        x[0] = i*0.04;
        y[0]= 1550.5+0.06*m_demodulation->wavelength_CentroidApproach[i];

        m_centroid_approach_widget->graph(0)->addData(x, y);
    }
}

//点击温度判断按钮
void MainWindow::on_btn_temp_clicked()
{
    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Temperature Judgement! ")+"\n");

//    m_tempDistance_widget->show();

    init_widget_temp_distance();

    qDebug()<<"Display Temp Distance Succeed!"<<endl;

    for(int i=0;i<25002;i++){

        //如果中心波长的温度值是0 则不画出该点
        if(m_demodulation->Temp[i]==0) continue;

        QVector<double> x(1),y(1);

        x[0] = i*0.04;
        y[0]= m_demodulation->Temp[i];

        //如果温度值太小，则不画出该点
        if(y[0]<-120) continue;

        m_temp_distance_widget->graph(0)->addData(x, y);
    }
}

//点击保存原始数据按钮
void MainWindow::save_raw_data()
{
    m_raw_data_save->start();

    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Start Saving raw data! ")+"\n");
}

////点击保存温度-波长数据按钮(弃用)
//void MainWindow::save_temp_distance_data()
//{
//    m_temp_distance_save->start();

//    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Start Saving Temperature-Distance Data!")+"\n");
//}

void MainWindow::save_filename()
{
    m_temp_distance_save->saveFilename = QFileDialog::getExistingDirectory(this, tr("选择文件保存路径"), "./", QFileDialog::ShowDirsOnly);

    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Temperature-Distance Data have been saved at!")+m_temp_distance_save->saveFilename+"\n");
}


void MainWindow::on_btn_reset_wave_clicked()
{
    m_raw_data_widget->yAxis->setRangeLower(-2);
    m_raw_data_widget->yAxis->setRangeUpper(70);
    // 立即刷新图像
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

//点击保存数据按钮
void MainWindow::on_btn_save_temp_clicked()
{
    m_temp_distance_save->start();

    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Start Saving Temperature-Distance Data!")+"\n");
}

