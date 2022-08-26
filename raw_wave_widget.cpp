#include "raw_wave_widget.h"
#include "ui_raw_wave_widget.h"

raw_wave_widget::raw_wave_widget():
    ui(new Ui::raw_wave_widget)
{
    ui->setupUi(this);

    //关联html文件
    //将echarts/dist文件夹内的echarts.min.js和xxx.html拷贝到Qt项目编译出来的可执行文件同级目录
    ui->webEngineView_wave->setContextMenuPolicy(Qt::NoContextMenu);
    this->setMinimumSize(500, 350);
//    ui->webEngineView_wave->load(qApp->applicationDirPath() + "/raw_data_echarts.html");
    ui->webEngineView_wave->load(qApp->applicationDirPath() + "/echarts.html");


    //通过序列化，将数据转换为json字符串，在通过调用js脚本，进行数据传输
    QJsonObject seriesData;
    QJsonArray x,y;
    for (int index = 0; index < 10000; ++index)
    {
        x.append(index);
        y.append(qrand()%100);
    }
    seriesData.insert("x", x);
    seriesData.insert("y", y);
    QString optionStr = QJsonDocument(seriesData).toJson();
    QString js = QString("update(%1)").arg(optionStr);//”update“ -- js中的函数名称
    ui->webEngineView_wave->page()->runJavaScript(js);

//    ui->webEngineView_wave->load(QUrl(QStringLiteral("./res/echarts.html")));
    ui->webEngineView_wave->load(qApp->applicationDirPath() + "/echarts.html");

    init_widget();
}

void raw_wave_widget::init_widget()
{
    setWindowTitle(QString("Raw Wave Display"));

    m_customPlot = ui->customPlot_wave;

    //每条曲线都会独占一个graph()
    m_customPlot->addGraph();
    m_customPlot->graph(0)->setPen(QPen(Qt::blue)); // 曲线的颜色
    m_customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // 曲线与X轴包围区的颜色

    m_customPlot->yAxis->setRangeLower(-2);
    m_customPlot->yAxis->setRangeUpper(70);

    // 边框右侧和上侧均显示刻度线，但不显示刻度值:
    // (参见 QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    m_customPlot->xAxis2->setVisible(true);
    m_customPlot->xAxis2->setTickLabels(false);
    m_customPlot->yAxis2->setVisible(true);
    m_customPlot->yAxis2->setTickLabels(false);

    m_customPlot->xAxis->setLabel("Sample Dots");
    m_customPlot->yAxis->setLabel("Amplitudes");
    QFont xFont = m_customPlot->xAxis->labelFont();
     xFont.setPixelSize(20);
     m_customPlot->xAxis->setLabelFont(xFont);
     QFont yFont = m_customPlot->yAxis->labelFont();
      yFont.setPixelSize(20);
      m_customPlot->yAxis->setLabelFont(yFont);

    // 使上下两个X轴的范围总是相等，使左右两个Y轴的范围总是相等
    //    connect(m_customPlot->xAxis, &QCPAxis::rangeChanged(QCPRange), m_customPlot->xAxis2, &QCPAxis::setRange(QCPRange));
    //    connect(m_customPlot->yAxis, &QCPAxis::rangeChanged(QCPRange), m_customPlot->yAxis2, &QCPAxis::setRange(QCPRange));


    // 支持鼠标拖拽轴的范围、滚动缩放轴的范围，左键点选图层（每条曲线独占一个图层）
    m_customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    //框选放大
    m_customPlot->selectionRect()->setPen(QPen(Qt::black,1,Qt::DashLine));//设置选框的样式：虚线
    m_customPlot->selectionRect()->setBrush(QBrush(QColor(0,0,100,50)));//设置选框的样式：半透明浅蓝
    m_customPlot->setSelectionRectMode(QCP::SelectionRectMode::srmZoom);
}

void raw_wave_widget::display_wave(double* _displaydata)
{
    qDebug()<<"Display raw_wave Succeed!"<<endl;

    for(int i=0;i<1250100;i++){
        //display wave
        QVector<double> x(1),y(1);

        x[0] = i;
        y[0]= _displaydata[i];

        m_customPlot->graph(0)->addData(x, y);
    }

    //自动调整XY轴的范围，以便显示出graph(0)中所有的点
    m_customPlot->graph(0)->rescaleAxes(true);
}

void raw_wave_widget::on_btn_reset_clicked()
{
    //自动调整XY轴的范围，以便显示出graph(0)中所有的点
    m_customPlot->graph(0)->rescaleAxes(true);

    m_customPlot->yAxis->setRangeLower(-2);
    m_customPlot->yAxis->setRangeUpper(70);

    // 立即刷新图像
    m_customPlot->replot();
}

//点击保存数据按钮（弃用）
//void raw_wave_widget::on_btn_save_clicked()
//{
//    emit sendToMainwindow_save(); //点击保存按钮 向mainWindow发送信号
//}

