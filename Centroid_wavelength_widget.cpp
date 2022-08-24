#include "Centroid_wavelength_widget.h"
#include "ui_Centroid_wavelength_widget.h"

Centroid_wavelength_widget::Centroid_wavelength_widget(demodulation* _demodulation):
    ui(new Ui::Centroid_wavelength_widget),
    m_demodulation(_demodulation)
{
    ui->setupUi(this);

    init_widget();
}

void Centroid_wavelength_widget::init_widget()
{
    setWindowTitle(QString("Centroid Wavelength Display"));

    m_customPlot = ui->customPlot_wave;

    //每条曲线都会独占一个graph()
    m_customPlot->addGraph();
    m_customPlot->graph(0)->setPen(QPen(Qt::blue)); // 曲线的颜色
    m_customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // 曲线与X轴包围区的颜色

    m_customPlot->yAxis->setRangeLower(1550);
    m_customPlot->yAxis->setRangeUpper(1554);
    m_customPlot->xAxis->setRangeLower(0);
    m_customPlot->xAxis->setRangeUpper(1000);

    // 边框右侧和上侧均显示刻度线，但不显示刻度值:
    // (参见 QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    m_customPlot->xAxis2->setVisible(true);
    m_customPlot->xAxis2->setTickLabels(false);
    m_customPlot->yAxis2->setVisible(true);
    m_customPlot->yAxis2->setTickLabels(false);

    m_customPlot->xAxis->setLabel("Distance/m");
    m_customPlot->yAxis->setLabel("Wavelength/nm");
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

void Centroid_wavelength_widget::display_wave()
{
    qDebug()<<"Display Centroid_wavelength Succeed!"<<endl;

    for(int i=0;i<25002;i++){

        //如果最大波长值的index是0 则不画出该点
        if(m_demodulation->wavelength_CentroidApproach[i]==0) continue;

        QVector<double> x(1),y(1);

        x[0] = i*0.04;
        y[0]= 1550.5+0.06*m_demodulation->wavelength_CentroidApproach[i];

        m_customPlot->graph(0)->addData(x, y);
    }

    //自动调整XY轴的范围，以便显示出graph(0)中所有的点
    m_customPlot->graph(0)->rescaleAxes(true);
}

void Centroid_wavelength_widget::on_btn_reset_clicked()
{
    //自动调整XY轴的范围，以便显示出graph(0)中所有的点
    m_customPlot->graph(0)->rescaleAxes(true);

    m_customPlot->yAxis->setRangeLower(1550);
    m_customPlot->yAxis->setRangeUpper(1554);
    m_customPlot->xAxis->setRangeLower(0);
    m_customPlot->xAxis->setRangeUpper(1000);

    // 立即刷新图像
    m_customPlot->replot();
}

