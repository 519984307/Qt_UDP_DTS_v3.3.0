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

<<<<<<< HEAD
//    connect(this,&MainWindow::sendToRaw_wave_widget,m_raw_wave_widget,&raw_wave_widget::display_wave);
//    connect(m_demodulation,&demodulation::sendToAdd_wave_widget,m_add_wave_widget,&add_wave_widget::display_wave,Qt::QueuedConnection);
//    connect(m_demodulation,&demodulation::sendToMaxValue_widget,m_maxValue_wavelength_widget,&MaxValue_wavelength_widget::display_wave,Qt::QueuedConnection);
//    connect(m_demodulation,&demodulation::sendToCentroid_widget,m_centroid_wavelength_widget,&Centroid_wavelength_widget::display_wave,Qt::QueuedConnection);
//    connect(m_demodulation,&demodulation::sendToTempDistance_widget,m_tempDistance_widget,&Temp_distance_widget::display_wave,Qt::QueuedConnection);
//    connect(m_raw_wave_widget,&raw_wave_widget::sendToMainwindow_save,this,&MainWindow::save_raw_data);
//    connect(m_tempDistance_widget,&Temp_distance_widget::sendToMainwindow_save,this,&MainWindow::save_temp_distance_data);
=======
    //    connect(this,&MainWindow::sendToRaw_wave_widget,m_raw_wave_widget,&raw_wave_widget::display_wave);
    //    connect(m_demodulation,&demodulation::sendToAdd_wave_widget,m_add_wave_widget,&add_wave_widget::display_wave,Qt::QueuedConnection);
    //    connect(m_demodulation,&demodulation::sendToMaxValue_widget,m_maxValue_wavelength_widget,&MaxValue_wavelength_widget::display_wave,Qt::QueuedConnection);
    //    connect(m_demodulation,&demodulation::sendToCentroid_widget,m_centroid_wavelength_widget,&Centroid_wavelength_widget::display_wave,Qt::QueuedConnection);
    //    connect(m_demodulation,&demodulation::sendToTempDistance_widget,m_tempDistance_widget,&Temp_distance_widget::display_wave,Qt::QueuedConnection);
    //    connect(m_raw_wave_widget,&raw_wave_widget::sendToMainwindow_save,this,&MainWindow::save_raw_data);
    //    connect(m_tempDistance_widget,&Temp_distance_widget::sendToMainwindow_save,this,&MainWindow::save_temp_distance_data);
>>>>>>> efa8b19 (ç¬¬å…­æ¬¡æäº¤)
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
<<<<<<< HEAD
    m_raw_data_widget = ui->raw_data_widget;

    //Ã¿ÌõÇúÏß¶¼»á¶ÀÕ¼Ò»¸ögraph()
    m_raw_data_widget->addGraph();
    m_raw_data_widget->graph(0)->setPen(QPen(Qt::blue)); // ÇúÏßµÄÑÕÉ«
    m_raw_data_widget->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // ÇúÏßÓëXÖá°üÎ§ÇøµÄÑÕÉ«

    m_raw_data_widget->yAxis->setRangeLower(-2);
    m_raw_data_widget->yAxis->setRangeUpper(70);

    // ±ß¿òÓÒ²àºÍÉÏ²à¾ùÏÔÊ¾¿Ì¶ÈÏß£¬µ«²»ÏÔÊ¾¿Ì¶ÈÖµ:
    // (²Î¼û QCPAxisRect::setupFullAxesBox for a quicker method to do this)
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

    // Ö§³ÖÊó±êÍÏ×§ÖáµÄ·¶Î§¡¢¹ö¶¯Ëõ·ÅÖáµÄ·¶Î§£¬×ó¼üµãÑ¡Í¼²ã£¨Ã¿ÌõÇúÏß¶ÀÕ¼Ò»¸öÍ¼²ã£©
    m_raw_data_widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    //¿òÑ¡·Å´ó
    m_raw_data_widget->selectionRect()->setPen(QPen(Qt::black,1,Qt::DashLine));//ÉèÖÃÑ¡¿òµÄÑùÊ½£ºĞéÏß
    m_raw_data_widget->selectionRect()->setBrush(QBrush(QColor(0,0,100,50)));//ÉèÖÃÑ¡¿òµÄÑùÊ½£º°ëÍ¸Ã÷Ç³À¶
    m_raw_data_widget->setSelectionRectMode(QCP::SelectionRectMode::srmZoom);
=======
    /*--¹ØÁªWebEngineViewÓëhtmlÎÄ¼ş--*/
    m_raw_data_widget = ui->raw_data_widget;
    m_raw_data_widget->setContextMenuPolicy(Qt::NoContextMenu);
    m_raw_data_widget->load(QUrl::fromLocalFile("E:/Desktop/Qt UDP DTS/Qt_UDP_DTS_v3.1.0/res/raw_data_widget.html")); //Ö»ÄÜĞ´¾ø¶ÔµØÖ·

    //QWebEngineView ÔÚ load ÍêÒ»¸öÒ³Ãæºó»á·¢³öÒ»¸öÒÑÍê³ÉµÄĞÅºÅ,ÒÀ¾İ QWebEngineView µÄ´óĞ¡À´ÉèÖÃ EChart µÄ´óĞ¡µÄ
    connect(m_raw_data_widget,&QWebEngineView::loadFinished,this,&MainWindow::onResizeEcharts1);

>>>>>>> efa8b19 (ç¬¬å…­æ¬¡æäº¤)
}

void MainWindow::init_widget_add_wave()
{
<<<<<<< HEAD
    m_add_wave_data_widget = ui->addwave_data_widget;

    //Ã¿ÌõÇúÏß¶¼»á¶ÀÕ¼Ò»¸ögraph()
    m_add_wave_data_widget->addGraph();
    m_add_wave_data_widget->graph(0)->setPen(QPen(Qt::blue)); // ÇúÏßµÄÑÕÉ«
    m_add_wave_data_widget->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // ÇúÏßÓëXÖá°üÎ§ÇøµÄÑÕÉ«

    m_add_wave_data_widget->yAxis->setRangeLower(-2);
    m_add_wave_data_widget->yAxis->setRangeUpper(70);

    // ±ß¿òÓÒ²àºÍÉÏ²à¾ùÏÔÊ¾¿Ì¶ÈÏß£¬µ«²»ÏÔÊ¾¿Ì¶ÈÖµ:
    // (²Î¼û QCPAxisRect::setupFullAxesBox for a quicker method to do this)
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

    // Ö§³ÖÊó±êÍÏ×§ÖáµÄ·¶Î§¡¢¹ö¶¯Ëõ·ÅÖáµÄ·¶Î§£¬×ó¼üµãÑ¡Í¼²ã£¨Ã¿ÌõÇúÏß¶ÀÕ¼Ò»¸öÍ¼²ã£©
    m_add_wave_data_widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    //¿òÑ¡·Å´ó
    m_add_wave_data_widget->selectionRect()->setPen(QPen(Qt::black,1,Qt::DashLine));//ÉèÖÃÑ¡¿òµÄÑùÊ½£ºĞéÏß
    m_add_wave_data_widget->selectionRect()->setBrush(QBrush(QColor(0,0,100,50)));//ÉèÖÃÑ¡¿òµÄÑùÊ½£º°ëÍ¸Ã÷Ç³À¶
    m_add_wave_data_widget->setSelectionRectMode(QCP::SelectionRectMode::srmZoom);
}

void MainWindow::init_widget_max_approach()
{
    m_max_approach_widget = ui->max_appraoch_widget;

    m_max_approach_widget->addGraph();
    m_max_approach_widget->graph(0)->setPen(QPen(Qt::blue)); // ÇúÏßµÄÑÕÉ«
    m_max_approach_widget->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // ÇúÏßÓëXÖá°üÎ§ÇøµÄÑÕÉ«
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
    m_max_approach_widget->selectionRect()->setPen(QPen(Qt::black,1,Qt::DashLine));//ÉèÖÃÑ¡¿òµÄÑùÊ½£ºĞéÏß
    m_max_approach_widget->selectionRect()->setBrush(QBrush(QColor(0,0,100,50)));//ÉèÖÃÑ¡¿òµÄÑùÊ½£º°ëÍ¸Ã÷Ç³À¶
    m_max_approach_widget->setSelectionRectMode(QCP::SelectionRectMode::srmZoom);
=======
    /*--¹ØÁªWebEngineViewÓëhtmlÎÄ¼ş--*/
    m_add_wave_data_widget = ui->addwave_data_widget;
    m_add_wave_data_widget->setContextMenuPolicy(Qt::NoContextMenu);
    m_add_wave_data_widget->load(QUrl::fromLocalFile("E:/Desktop/Qt UDP DTS/Qt_UDP_DTS_v3.1.0/res/add_wave_widget.html")); //Ö»ÄÜĞ´¾ø¶ÔµØÖ·

    //QWebEngineView ÔÚ load ÍêÒ»¸öÒ³Ãæºó»á·¢³öÒ»¸öÒÑÍê³ÉµÄĞÅºÅ,ÒÀ¾İ QWebEngineView µÄ´óĞ¡À´ÉèÖÃ EChart µÄ´óĞ¡µÄ
    connect(m_add_wave_data_widget,&QWebEngineView::loadFinished,this,&MainWindow::onResizeEcharts2);
}


void MainWindow::init_widget_max_approach()
{
    /*--¹ØÁªWebEngineViewÓëhtmlÎÄ¼ş--*/
    m_max_approach_widget = ui->max_appraoch_widget;
    m_max_approach_widget->setContextMenuPolicy(Qt::NoContextMenu);
    m_max_approach_widget->load(QUrl::fromLocalFile("E:/Desktop/Qt UDP DTS/Qt_UDP_DTS_v3.1.0/res/max_approach_widget.html")); //Ö»ÄÜĞ´¾ø¶ÔµØÖ·

    //QWebEngineView ÔÚ load ÍêÒ»¸öÒ³Ãæºó»á·¢³öÒ»¸öÒÑÍê³ÉµÄĞÅºÅ,ÒÀ¾İ QWebEngineView µÄ´óĞ¡À´ÉèÖÃ EChart µÄ´óĞ¡µÄ
    connect(m_max_approach_widget,&QWebEngineView::loadFinished,this,&MainWindow::onResizeEcharts3);


>>>>>>> efa8b19 (ç¬¬å…­æ¬¡æäº¤)
}

void MainWindow::init_widget_centroid_approach()
{
<<<<<<< HEAD
    m_centroid_approach_widget = ui->centroid_approach_widget;

    m_centroid_approach_widget->addGraph();
    m_centroid_approach_widget->graph(0)->setPen(QPen(Qt::blue)); // ÇúÏßµÄÑÕÉ«
    m_centroid_approach_widget->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // ÇúÏßÓëXÖá°üÎ§ÇøµÄÑÕÉ«

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

    m_centroid_approach_widget->selectionRect()->setPen(QPen(Qt::black,1,Qt::DashLine));//ÉèÖÃÑ¡¿òµÄÑùÊ½£ºĞéÏß
    m_centroid_approach_widget->selectionRect()->setBrush(QBrush(QColor(0,0,100,50)));//ÉèÖÃÑ¡¿òµÄÑùÊ½£º°ëÍ¸Ã÷Ç³À¶
    m_centroid_approach_widget->setSelectionRectMode(QCP::SelectionRectMode::srmZoom);
=======
    /*--¹ØÁªWebEngineViewÓëhtmlÎÄ¼ş--*/
    m_centroid_approach_widget = ui->centroid_approach_widget;
    m_centroid_approach_widget->setContextMenuPolicy(Qt::NoContextMenu);
    m_centroid_approach_widget->load(QUrl::fromLocalFile("E:/Desktop/Qt UDP DTS/Qt_UDP_DTS_v3.1.0/res/centroid_approach_widget.html")); //Ö»ÄÜĞ´¾ø¶ÔµØÖ·

    //QWebEngineView ÔÚ load ÍêÒ»¸öÒ³Ãæºó»á·¢³öÒ»¸öÒÑÍê³ÉµÄĞÅºÅ,ÒÀ¾İ QWebEngineView µÄ´óĞ¡À´ÉèÖÃ EChart µÄ´óĞ¡µÄ
    connect(m_centroid_approach_widget,&QWebEngineView::loadFinished,this,&MainWindow::onResizeEcharts4);


>>>>>>> efa8b19 (ç¬¬å…­æ¬¡æäº¤)
}

void MainWindow::init_widget_temp_distance()
{
<<<<<<< HEAD
    m_temp_distance_widget = ui->temp_distance_widget;

    //Ã¿ÌõÇúÏß¶¼»á¶ÀÕ¼Ò»¸ögraph()
    m_temp_distance_widget->addGraph();
    m_temp_distance_widget->graph(0)->setPen(QPen(Qt::blue)); // ÇúÏßµÄÑÕÉ«
    m_temp_distance_widget->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // ÇúÏßÓëXÖá°üÎ§ÇøµÄÑÕÉ«

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

    m_temp_distance_widget->selectionRect()->setPen(QPen(Qt::black,1,Qt::DashLine));//ÉèÖÃÑ¡¿òµÄÑùÊ½£ºĞéÏß
    m_temp_distance_widget->selectionRect()->setBrush(QBrush(QColor(0,0,100,50)));//ÉèÖÃÑ¡¿òµÄÑùÊ½£º°ëÍ¸Ã÷Ç³À¶
    m_temp_distance_widget->setSelectionRectMode(QCP::SelectionRectMode::srmZoom);
=======
    /*--¹ØÁªWebEngineViewÓëhtmlÎÄ¼ş--*/
    m_temp_distance_widget = ui->temp_distance_widget;
    m_temp_distance_widget->setContextMenuPolicy(Qt::NoContextMenu);
    m_temp_distance_widget->load(QUrl::fromLocalFile("E:/Desktop/Qt UDP DTS/Qt_UDP_DTS_v3.1.0/res/Temp_distance_widget.html")); //Ö»ÄÜĞ´¾ø¶ÔµØÖ·

    //QWebEngineView ÔÚ load ÍêÒ»¸öÒ³Ãæºó»á·¢³öÒ»¸öÒÑÍê³ÉµÄĞÅºÅ,ÒÀ¾İ QWebEngineView µÄ´óĞ¡À´ÉèÖÃ EChart µÄ´óĞ¡µÄ
    connect(m_temp_distance_widget,&QWebEngineView::loadFinished,this,&MainWindow::onResizeEcharts5);


}

void MainWindow::echarts_load_raw_data()
{
    /*--×é³ÉÒ»¸ö JSON ×Ö·û´®½«Êı¾İ´«¹ıÈ¥--*/
    //1.Ê¹ÓÃ QJonsObject À´×é³ÉÒ»¸ö JSON ¶ÔÏó
    QJsonObject seriesData;

    //2.Ê¹ÓÃ QJsonArray Íù JSON ¶ÔÏóÖĞÌí¼ÓÒ»Êı×é
    QJsonArray amplitude;
    for(int i=0; i<1250100; i++) amplitude.push_back(raw_data[i]);
    seriesData.insert("amplitude", amplitude);

    //3.Ê¹ÓÃ QJsonDocument À´½« JSON ¶ÔÏó×ª»¯³É×Ö·û´®
    QString optionStr = QJsonDocument(seriesData).toJson();

    //4.µ÷ÓÃjsµÄinit2£¨£©·½·¨
    QString js = QString("init2(%1)").arg(optionStr);

    //5.µ÷ÓÃ QWebEngineViewµÄ page()->runJavaScript("function(str)") À´ÔËĞĞ JS ·½·¨
    m_raw_data_widget->page()->runJavaScript(js);
}

void MainWindow::echarts_load_add_wave()
{
    /*--×é³ÉÒ»¸ö JSON ×Ö·û´®½«Êı¾İ´«¹ıÈ¥--*/
    //1.Ê¹ÓÃ QJonsObject À´×é³ÉÒ»¸ö JSON ¶ÔÏó
    QJsonObject seriesData;

    //2.Ê¹ÓÃ QJsonArray Íù JSON ¶ÔÏóÖĞÌí¼ÓÒ»Êı×é
    QJsonArray amplitude;
    for(int i=0; i<25002; i++) amplitude.push_back(m_demodulation->add_wave_data[i]);
    seriesData.insert("amplitude", amplitude);

    //3.Ê¹ÓÃ QJsonDocument À´½« JSON ¶ÔÏó×ª»¯³É×Ö·û´®
    QString optionStr = QJsonDocument(seriesData).toJson();

    //4.µ÷ÓÃjsµÄinit2£¨£©·½·¨
    QString js = QString("init2(%1)").arg(optionStr);

    //5.µ÷ÓÃ QWebEngineViewµÄ page()->runJavaScript("function(str)") À´ÔËĞĞ JS ·½·¨
    m_add_wave_data_widget->page()->runJavaScript(js);

}

void MainWindow::echarts_load_max_approach()
{
    /*--×é³ÉÒ»¸ö JSON ×Ö·û´®½«Êı¾İ´«¹ıÈ¥--*/
    //1.Ê¹ÓÃ QJonsObject À´×é³ÉÒ»¸ö JSON ¶ÔÏó
    QJsonObject seriesData;

    //2.Ê¹ÓÃ QJsonArray Íù JSON ¶ÔÏóÖĞÌí¼ÓÒ»Êı×é
    QJsonArray amplitude;
    for(int i=0; i<25002; i++){
        //Èç¹û×î´ó²¨³¤ÖµµÄindexÊÇ0 Ôò²»»­³ö¸Ãµã
        if(m_demodulation->wavelength_MaxApproach[i]==0) continue;

        amplitude.push_back(1550.5+0.06*m_demodulation->wavelength_MaxApproach[i]);
    }
    seriesData.insert("amplitude", amplitude);

    //3.Ê¹ÓÃ QJsonDocument À´½« JSON ¶ÔÏó×ª»¯³É×Ö·û´®
    QString optionStr = QJsonDocument(seriesData).toJson();

    //4.µ÷ÓÃjsµÄinit2£¨£©·½·¨
    QString js = QString("init2(%1)").arg(optionStr);

    //5.µ÷ÓÃ QWebEngineViewµÄ page()->runJavaScript("function(str)") À´ÔËĞĞ JS ·½·¨
    m_max_approach_widget->page()->runJavaScript(js);
}

void MainWindow::echarts_load_centroid_approach()
{
    /*--×é³ÉÒ»¸ö JSON ×Ö·û´®½«Êı¾İ´«¹ıÈ¥--*/
    //1.Ê¹ÓÃ QJonsObject À´×é³ÉÒ»¸ö JSON ¶ÔÏó
    QJsonObject seriesData;

    //2.Ê¹ÓÃ QJsonArray Íù JSON ¶ÔÏóÖĞÌí¼ÓÒ»Êı×é
    QJsonArray amplitude;
    for(int i=0; i<25002; i++){
        //Èç¹û×î´ó²¨³¤ÖµµÄindexÊÇ0 Ôò²»»­³ö¸Ãµã
        if(m_demodulation->wavelength_CentroidApproach[i]==0) continue;

        amplitude.push_back(1550.5+0.06*m_demodulation->wavelength_CentroidApproach[i]);
    }
    seriesData.insert("amplitude", amplitude);

    //3.Ê¹ÓÃ QJsonDocument À´½« JSON ¶ÔÏó×ª»¯³É×Ö·û´®
    QString optionStr = QJsonDocument(seriesData).toJson();

    //4.µ÷ÓÃjsµÄinit2£¨£©·½·¨
    QString js = QString("init2(%1)").arg(optionStr);

    //5.µ÷ÓÃ QWebEngineViewµÄ page()->runJavaScript("function(str)") À´ÔËĞĞ JS ·½·¨
    m_centroid_approach_widget->page()->runJavaScript(js);
}

void MainWindow::echarts_load_temp()
{
    /*--×é³ÉÒ»¸ö JSON ×Ö·û´®½«Êı¾İ´«¹ıÈ¥--*/
    //1.Ê¹ÓÃ QJonsObject À´×é³ÉÒ»¸ö JSON ¶ÔÏó
    QJsonObject seriesData;

    //2.Ê¹ÓÃ QJsonArray Íù JSON ¶ÔÏóÖĞÌí¼ÓÒ»Êı×é
    QJsonArray amplitude;
    for(int i=0; i<25002; i++) {
        //Èç¹ûÖĞĞÄ²¨³¤µÄÎÂ¶ÈÖµÊÇ0 Ôò²»»­³ö¸Ãµã
        if(m_demodulation->Temp[i]==0) continue;

        //Èç¹ûÎÂ¶ÈÖµÌ«Ğ¡£¬Ôò²»»­³ö¸Ãµã
        if(m_demodulation->Temp[i]<-120) continue;

        amplitude.push_back(m_demodulation->Temp[i]);
    }
    seriesData.insert("amplitude", amplitude);

    //3.Ê¹ÓÃ QJsonDocument À´½« JSON ¶ÔÏó×ª»¯³É×Ö·û´®
    QString optionStr = QJsonDocument(seriesData).toJson();

    //4.µ÷ÓÃjsµÄinit2£¨£©·½·¨
    QString js = QString("init2(%1)").arg(optionStr);

    //5.µ÷ÓÃ QWebEngineViewµÄ page()->runJavaScript("function(str)") À´ÔËĞĞ JS ·½·¨
    m_temp_distance_widget->page()->runJavaScript(js);
>>>>>>> efa8b19 (ç¬¬å…­æ¬¡æäº¤)
}

//µã»÷¶ÁÈ¡ÎÄ¼ş°´Å¥
void MainWindow::on_btn_readfls_clicked()
{
    //´ò¿ªÎÄ¼şÑ¡Ôñ¶Ô»°¿ò
    QString fileName = QFileDialog::getOpenFileName(this, tr("open file"), " ",  tr("txt(*.txt);;Allfile(*.*)"));

    qDebug()<<fileName<<endl;

    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("File Dir: ")+fileName+"\n");

    /*--ÒÔÁ÷µÄ·½Ê½´ò¿ª.txtÎÄ¼ş*/
    char buf[32];

    ifstream infile;
    infile.open(fileName.toStdString().data(),std::ifstream::in);

    if(!infile.is_open()) {
        qDebug()<<"Open File Error!"<<endl;

        ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Open File Error!")+"\n");

        delete[] raw_data; //ÊÍ·Å¶¯Ì¬·ÖÅäµÄÄÚ´æ

        return;
    }
    else
        qDebug()<<"Open File Succeed!"<<endl;
    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Open File Succeed!")+"\n");

    for(int i=0;i<1250100;i++){
        infile >> buf; //>>ÔËËã·ûµ± >> Óöµ½¿Õ¸ñ»ò»»ĞĞÊ±£¬¾Í»áÖÕÖ¹£¬²¢ÔÚÏÂ´Î½øĞĞ >> Ê±£¬´Ó¿Õ¸ñ»ò»»ĞĞºó¼ÌĞø½øĞĞ

        raw_data[i] = strtod(buf,NULL); //char[]×ªdoubleÊı×Ö
    }

    infile.close();
<<<<<<< HEAD

    /*--ÏÔÊ¾raw_data²¨ĞÎ--*/
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

    //×Ô¶¯µ÷ÕûXYÖáµÄ·¶Î§£¬ÒÔ±ãÏÔÊ¾³ögraph(0)ÖĞËùÓĞµÄµã
    m_raw_data_widget->graph(0)->rescaleAxes(true);
}

//µã»÷ÏÔÊ¾raw_data²¨ĞÎ°´Å¥
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

//    //×Ô¶¯µ÷ÕûXYÖáµÄ·¶Î§£¬ÒÔ±ãÏÔÊ¾³ögraph(0)ÖĞËùÓĞµÄµã
//    m_raw_data_widget->graph(0)->rescaleAxes(true);
//}

=======

    /*--ÏÔÊ¾raw_data²¨ĞÎ--*/
//    echarts_load_raw_data(); //ºÜ¿¨

    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Display Raw Data Wave!")+"\n");

    qDebug()<<"Display raw_wave Succeed!"<<endl;
}

>>>>>>> efa8b19 (ç¬¬å…­æ¬¡æäº¤)
//µã»÷½âµ÷°´Å¥
void MainWindow::on_btn_demodulation_clicked()
{
    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Start Demodulating Data! ")+"\n");

    m_demodulation->start(); //±ØĞëÏÈ¿ªÆôdemodulationÏß³Ì£¬ÔÙÏÔÊ¾add_wave_widget

<<<<<<< HEAD
    //  ÏÔÊ¾add_wave_data²¨ĞÎ
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
=======
    echarts_load_add_wave();
    echarts_load_max_approach();
    echarts_load_centroid_approach();
    echarts_load_temp();
>>>>>>> efa8b19 (ç¬¬å…­æ¬¡æäº¤)
}

//µã»÷×î´óÖµ·¨°´Å¥
void MainWindow::on_btn_maxValue_clicked()
{
    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("MaxValue Approach to get Central Wavelength! ")+"\n");

<<<<<<< HEAD
//    m_maxValue_wavelength_widget->show();
    init_widget_max_approach();

    qDebug()<<"Display MaxValue_wavelength Succeed!"<<endl;

    for(int i=0;i<25002;i++){
        //Èç¹û×î´ó²¨³¤ÖµµÄindexÊÇ0 Ôò²»»­³ö¸Ãµã
        if(m_demodulation->wavelength_MaxApproach[i]==0) continue;

        QVector<double> x(1),y(1);

        x[0] = i*0.04;
        y[0]= 1550.5+0.06*m_demodulation->wavelength_MaxApproach[i];

        m_max_approach_widget->graph(0)->addData(x, y);
    }
=======
    //    m_maxValue_wavelength_widget->show();
    init_widget_max_approach();

    qDebug()<<"Display MaxValue_wavelength Succeed!"<<endl;
>>>>>>> efa8b19 (ç¬¬å…­æ¬¡æäº¤)
}

//µã»÷ÖÊĞÄ·¨°´Å¥
void MainWindow::on_btn_centroid_clicked()
{
    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Centroid Approach to get Central Wavelength! ")+"\n");

<<<<<<< HEAD
//    m_centroid_wavelength_widget->show();
=======
    //    m_centroid_wavelength_widget->show();
>>>>>>> efa8b19 (ç¬¬å…­æ¬¡æäº¤)

    init_widget_centroid_approach();

    qDebug()<<"Display Centroid_wavelength Succeed!"<<endl;
<<<<<<< HEAD

    for(int i=0;i<25002;i++){

        //Èç¹û×î´ó²¨³¤ÖµµÄindexÊÇ0 Ôò²»»­³ö¸Ãµã
        if(m_demodulation->wavelength_CentroidApproach[i]==0) continue;

        QVector<double> x(1),y(1);

        x[0] = i*0.04;
        y[0]= 1550.5+0.06*m_demodulation->wavelength_CentroidApproach[i];

        m_centroid_approach_widget->graph(0)->addData(x, y);
    }
=======
>>>>>>> efa8b19 (ç¬¬å…­æ¬¡æäº¤)
}

//µã»÷ÎÂ¶ÈÅĞ¶Ï°´Å¥
void MainWindow::on_btn_temp_clicked()
{
    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Temperature Judgement! ")+"\n");

<<<<<<< HEAD
//    m_tempDistance_widget->show();
=======
    //    m_tempDistance_widget->show();
>>>>>>> efa8b19 (ç¬¬å…­æ¬¡æäº¤)

    init_widget_temp_distance();

    qDebug()<<"Display Temp Distance Succeed!"<<endl;

<<<<<<< HEAD
    for(int i=0;i<25002;i++){

        //Èç¹ûÖĞĞÄ²¨³¤µÄÎÂ¶ÈÖµÊÇ0 Ôò²»»­³ö¸Ãµã
        if(m_demodulation->Temp[i]==0) continue;

        QVector<double> x(1),y(1);

        x[0] = i*0.04;
        y[0]= m_demodulation->Temp[i];

        //Èç¹ûÎÂ¶ÈÖµÌ«Ğ¡£¬Ôò²»»­³ö¸Ãµã
        if(y[0]<-120) continue;

        m_temp_distance_widget->graph(0)->addData(x, y);
    }
=======
>>>>>>> efa8b19 (ç¬¬å…­æ¬¡æäº¤)
}

//µã»÷±£´æÔ­Ê¼Êı¾İ°´Å¥
void MainWindow::save_raw_data()
{
    m_raw_data_save->start();

    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Start Saving raw data! ")+"\n");
}

<<<<<<< HEAD
////µã»÷±£´æÎÂ¶È-²¨³¤Êı¾İ°´Å¥(ÆúÓÃ)
//void MainWindow::save_temp_distance_data()
//{
//    m_temp_distance_save->start();

//    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Start Saving Temperature-Distance Data!")+"\n");
//}

=======
//»ñÈ¡´æ´¢ÎÄ¼şÂ·¾¶
>>>>>>> efa8b19 (ç¬¬å…­æ¬¡æäº¤)
void MainWindow::save_filename()
{
    m_temp_distance_save->saveFilename = QFileDialog::getExistingDirectory(this, tr("Ñ¡ÔñÎÄ¼ş±£´æÂ·¾¶"), "./", QFileDialog::ShowDirsOnly);

    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Temperature-Distance Data have been saved at!")+m_temp_distance_save->saveFilename+"\n");
}

<<<<<<< HEAD

void MainWindow::on_btn_reset_wave_clicked()
{
    m_raw_data_widget->yAxis->setRangeLower(-2);
    m_raw_data_widget->yAxis->setRangeUpper(70);
    // Á¢¼´Ë¢ĞÂÍ¼Ïñ
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
=======
//µã»÷¸´Î»Í¼Ïñ°´Å¥
void MainWindow::on_btn_reset_wave_clicked()
{

>>>>>>> efa8b19 (ç¬¬å…­æ¬¡æäº¤)
}

//µã»÷±£´æÊı¾İ°´Å¥
void MainWindow::on_btn_save_temp_clicked()
{
    m_temp_distance_save->start();

    ui->m_textBrowser->insertPlainText(QDateTime::currentDateTime().toString("yyyy-MMdd-hh:mm:ss ")+QString("Start Saving Temperature-Distance Data!")+"\n");
}

<<<<<<< HEAD
=======
//×ÔÊÊÓ¦´°¿Ú±ä»¯´óĞ¡
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

//ÒòÎªÎÒÃÇÊµÏÖÔÚ´°¿Ú¸Ä±ä´óĞ¡Ê± ECharts Ò²¸ú×Å±ä»¯£¬ËùÒÔÎÒÃÇÒªÔÚ resizeEvent Ê±ÉèÖÃÒ²ÒªÉèÖÃ´óĞ¡
void MainWindow::resizeEvent(QResizeEvent *event)
{
    if(isLoaded1) onResizeEcharts1();
    if(isLoaded2) onResizeEcharts2();
    if(isLoaded3) onResizeEcharts3();
    if(isLoaded4) onResizeEcharts4();
    if(isLoaded5) onResizeEcharts5();
}

>>>>>>> efa8b19 (ç¬¬å…­æ¬¡æäº¤)
