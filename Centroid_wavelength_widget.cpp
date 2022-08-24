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

    //ÿ�����߶����ռһ��graph()
    m_customPlot->addGraph();
    m_customPlot->graph(0)->setPen(QPen(Qt::blue)); // ���ߵ���ɫ
    m_customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // ������X���Χ������ɫ

    m_customPlot->yAxis->setRangeLower(1550);
    m_customPlot->yAxis->setRangeUpper(1554);
    m_customPlot->xAxis->setRangeLower(0);
    m_customPlot->xAxis->setRangeUpper(1000);

    // �߿��Ҳ���ϲ����ʾ�̶��ߣ�������ʾ�̶�ֵ:
    // (�μ� QCPAxisRect::setupFullAxesBox for a quicker method to do this)
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

    // ʹ��������X��ķ�Χ������ȣ�ʹ��������Y��ķ�Χ�������
    //    connect(m_customPlot->xAxis, &QCPAxis::rangeChanged(QCPRange), m_customPlot->xAxis2, &QCPAxis::setRange(QCPRange));
    //    connect(m_customPlot->yAxis, &QCPAxis::rangeChanged(QCPRange), m_customPlot->yAxis2, &QCPAxis::setRange(QCPRange));


    // ֧�������ק��ķ�Χ������������ķ�Χ�������ѡͼ�㣨ÿ�����߶�ռһ��ͼ�㣩
    m_customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    //��ѡ�Ŵ�
    m_customPlot->selectionRect()->setPen(QPen(Qt::black,1,Qt::DashLine));//����ѡ�����ʽ������
    m_customPlot->selectionRect()->setBrush(QBrush(QColor(0,0,100,50)));//����ѡ�����ʽ����͸��ǳ��
    m_customPlot->setSelectionRectMode(QCP::SelectionRectMode::srmZoom);
}

void Centroid_wavelength_widget::display_wave()
{
    qDebug()<<"Display Centroid_wavelength Succeed!"<<endl;

    for(int i=0;i<25002;i++){

        //�����󲨳�ֵ��index��0 �򲻻����õ�
        if(m_demodulation->wavelength_CentroidApproach[i]==0) continue;

        QVector<double> x(1),y(1);

        x[0] = i*0.04;
        y[0]= 1550.5+0.06*m_demodulation->wavelength_CentroidApproach[i];

        m_customPlot->graph(0)->addData(x, y);
    }

    //�Զ�����XY��ķ�Χ���Ա���ʾ��graph(0)�����еĵ�
    m_customPlot->graph(0)->rescaleAxes(true);
}

void Centroid_wavelength_widget::on_btn_reset_clicked()
{
    //�Զ�����XY��ķ�Χ���Ա���ʾ��graph(0)�����еĵ�
    m_customPlot->graph(0)->rescaleAxes(true);

    m_customPlot->yAxis->setRangeLower(1550);
    m_customPlot->yAxis->setRangeUpper(1554);
    m_customPlot->xAxis->setRangeLower(0);
    m_customPlot->xAxis->setRangeUpper(1000);

    // ����ˢ��ͼ��
    m_customPlot->replot();
}

