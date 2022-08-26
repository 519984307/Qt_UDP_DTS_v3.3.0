#include "raw_wave_widget.h"
#include "ui_raw_wave_widget.h"

raw_wave_widget::raw_wave_widget():
    ui(new Ui::raw_wave_widget)
{
    ui->setupUi(this);

    //����html�ļ�
    //��echarts/dist�ļ����ڵ�echarts.min.js��xxx.html������Qt��Ŀ��������Ŀ�ִ���ļ�ͬ��Ŀ¼
    ui->webEngineView_wave->setContextMenuPolicy(Qt::NoContextMenu);
    this->setMinimumSize(500, 350);
//    ui->webEngineView_wave->load(qApp->applicationDirPath() + "/raw_data_echarts.html");
    ui->webEngineView_wave->load(qApp->applicationDirPath() + "/echarts.html");


    //ͨ�����л���������ת��Ϊjson�ַ�������ͨ������js�ű����������ݴ���
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
    QString js = QString("update(%1)").arg(optionStr);//��update�� -- js�еĺ�������
    ui->webEngineView_wave->page()->runJavaScript(js);

//    ui->webEngineView_wave->load(QUrl(QStringLiteral("./res/echarts.html")));
    ui->webEngineView_wave->load(qApp->applicationDirPath() + "/echarts.html");

    init_widget();
}

void raw_wave_widget::init_widget()
{
    setWindowTitle(QString("Raw Wave Display"));

    m_customPlot = ui->customPlot_wave;

    //ÿ�����߶����ռһ��graph()
    m_customPlot->addGraph();
    m_customPlot->graph(0)->setPen(QPen(Qt::blue)); // ���ߵ���ɫ
    m_customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // ������X���Χ������ɫ

    m_customPlot->yAxis->setRangeLower(-2);
    m_customPlot->yAxis->setRangeUpper(70);

    // �߿��Ҳ���ϲ����ʾ�̶��ߣ�������ʾ�̶�ֵ:
    // (�μ� QCPAxisRect::setupFullAxesBox for a quicker method to do this)
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

    //�Զ�����XY��ķ�Χ���Ա���ʾ��graph(0)�����еĵ�
    m_customPlot->graph(0)->rescaleAxes(true);
}

void raw_wave_widget::on_btn_reset_clicked()
{
    //�Զ�����XY��ķ�Χ���Ա���ʾ��graph(0)�����еĵ�
    m_customPlot->graph(0)->rescaleAxes(true);

    m_customPlot->yAxis->setRangeLower(-2);
    m_customPlot->yAxis->setRangeUpper(70);

    // ����ˢ��ͼ��
    m_customPlot->replot();
}

//����������ݰ�ť�����ã�
//void raw_wave_widget::on_btn_save_clicked()
//{
//    emit sendToMainwindow_save(); //������水ť ��mainWindow�����ź�
//}

