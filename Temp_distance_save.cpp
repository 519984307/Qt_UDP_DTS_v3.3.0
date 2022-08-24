#include "Temp_distance_save.h"

Temp_distance_save::Temp_distance_save(demodulation* _demodulation) :
    m_demodultion(_demodulation)
{

}

void Temp_distance_save::run()
{
    dateTime = QDateTime::currentDateTime();

    emit getFilename();

    //文件夹路径+文件名
    saveFilenameAll = saveFilename+QString("/")+QString("[demo]")+dateTime.toString("yyyyMMddhhmmss")+ QString(".bin");

    outfileAll.open(saveFilenameAll.toStdString().data(), ofstream::binary);

    if (!outfileAll.is_open()) return;

    for(int i=0; i<25002; i++){

        double temp_double = m_demodultion->Temp[i];
        char temp_char[16] = {'\0'} ;

        sprintf(temp_char,"%.8f", temp_double); //double转char* 精度为小数点后8位
//        qDebug()<< temp_char<<endl;

        for(int j=0;j<14;j++) {  //j=14是因为最大的数据是13位 最后一位是'\0'方便后期处理数据
            char* temp_char2 = &temp_char[j];
            outfileAll.write((const char*)temp_char2,sizeof(char));
        }
    }

    outfileAll.close();

    qDebug()<< "Temp_distance_save Thread is Finished! "<<endl;
}

