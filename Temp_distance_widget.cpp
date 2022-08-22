#include "Temp_distance_widget.h"
#include "ui_Temp_distance_widget.h"

Temp_distance_widget::Temp_distance_widget(demodulation* _demodulation):
    ui(new Ui::Temp_distance_widget),
    m_demodulation(_demodulation)
{
    ui->setupUi(this);

    init_widget();
}

void Temp_distance_widget::init_widget()
{
    setWindowTitle(QString("Temp Distance Display"));

    m_customPlot = ui->customPlot_wave;

    //每条曲线都会独占一个graph()
    m_customPlot->addGraph();
    m_customPlot->graph(0)->setPen(QPen(Qt::blue)); // 曲线的颜色
    m_customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // 曲线与X轴包围区的颜色

    // 边框右侧和上侧均显示刻度线，但不显示刻度值:
    // (参见 QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    m_customPlot->xAxis2->setVisible(true);
    m_customPlot->xAxis2->setTickLabels(false);
    m_customPlot->yAxis2->setVisible(true);
    m_customPlot->yAxis2->setTickLabels(false);
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

void Temp_distance_widget::display_wave()
{
    qDebug()<<"Display Temp Distance Succeed!"<<endl;

    for(int i=0;i<25002;i++){
        QVector<double> x(1),y(1);

        x[0] = i*0.04;
        y[0]= m_demodulation->Temp[i];

        m_customPlot->graph(0)->addData(x, y);
    }

    //自动调整XY轴的范围，以便显示出graph(0)中所有的点
    m_customPlot->graph(0)->rescaleAxes(true);
}

void Temp_distance_widget::on_btn_reset_clicked()
{
    //自动调整XY轴的范围，以便显示出graph(0)中所有的点
    m_customPlot->graph(0)->rescaleAxes(true);

    m_customPlot->yAxis->setRangeLower(-120);
    m_customPlot->yAxis->setRangeUpper(60);
    m_customPlot->xAxis->setRangeLower(0);
    m_customPlot->xAxis->setRangeUpper(1000);

    // 立即刷新图像
    m_customPlot->replot();
}

