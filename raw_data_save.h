#ifndef RAW_DATA_SAVE_H
#define RAW_DATA_SAVE_H

#include <QObject>
#include <mainwindow.h>

class demodulation;

class raw_data_save : public QThread
{
    Q_OBJECT
public:
    raw_data_save(demodulation* _demodulation);

    demodulation* m_demodultion;
    QDateTime dateTime;
    QString saveFilenameAll;
    ofstream outfileAll;

    void run();

signals:

};

#endif // RAW_DATA_SAVE_H
