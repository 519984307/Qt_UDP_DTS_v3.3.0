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

    //ÿ�����߶����ռһ��graph()
    m_customPlot->addGraph();
    m_customPlot->graph(0)->setPen(QPen(Qt::blue)); // ���ߵ���ɫ
    m_customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // ������X���Χ������ɫ

    // �߿��Ҳ���ϲ����ʾ�̶��ߣ�������ʾ�̶�ֵ:
    // (�μ� QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    m_customPlot->xAxis2->setVisible(true);
    m_customPlot->xAxis2->setTickLabels(false);
    m_customPlot->yAxis2->setVisible(true);
    m_customPlot->yAxis2->setTickLabels(false);
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

void Temp_distance_widget::display_wave()
{
    qDebug()<<"Display Temp Distance Succeed!"<<endl;

    for(int i=0;i<25002;i++){
        QVector<double> x(1),y(1);

        x[0] = i*0.04;
        y[0]= m_demodulation->Temp[i];

        m_customPlot->graph(0)->addData(x, y);
    }

    //�Զ�����XY��ķ�Χ���Ա���ʾ��graph(0)�����еĵ�
    m_customPlot->graph(0)->rescaleAxes(true);
}

void Temp_distance_widget::on_btn_reset_clicked()
{
    //�Զ�����XY��ķ�Χ���Ա���ʾ��graph(0)�����еĵ�
    m_customPlot->graph(0)->rescaleAxes(true);

    m_customPlot->yAxis->setRangeLower(-120);
    m_customPlot->yAxis->setRangeUpper(60);
    m_customPlot->xAxis->setRangeLower(0);
    m_customPlot->xAxis->setRangeUpper(1000);

    // ����ˢ��ͼ��
    m_customPlot->replot();
}

