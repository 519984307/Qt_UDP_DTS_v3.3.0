#include "Temp_distance_save.h"

Temp_distance_save::Temp_distance_save(demodulation* _demodulation) :
    m_demodultion(_demodulation)
{

}

void Temp_distance_save::run()
{
    dateTime = QDateTime::currentDateTime();

    emit getFilename();

    //�ļ���·��+�ļ���
    saveFilenameAll = saveFilename+QString("/")+QString("[demo]")+dateTime.toString("yyyyMMddhhmmss")+ QString(".bin");

    outfileAll.open(saveFilenameAll.toStdString().data(), ofstream::binary);

    if (!outfileAll.is_open()) return;

    for(int i=0; i<25002; i++){

        double temp_double = m_demodultion->Temp[i];
        char temp_char[16] = {'\0'} ;

        sprintf(temp_char,"%.8f", temp_double); //doubleתchar* ����ΪС�����8λ
//        qDebug()<< temp_char<<endl;

        for(int j=0;j<14;j++) {  //j=14����Ϊ����������13λ ���һλ��'\0'������ڴ�������
            char* temp_char2 = &temp_char[j];
            outfileAll.write((const char*)temp_char2,sizeof(char));
        }
    }

    outfileAll.close();

    qDebug()<< "Temp_distance_save Thread is Finished! "<<endl;
}

