#ifndef TEMP_DISTANCE_SAVE_H
#define TEMP_DISTANCE_SAVE_H

#include <QObject>
#include <mainwindow.h>
#include <QDateTime>

class demodulation;

class Temp_distance_save : public QThread
{
    Q_OBJECT
public:
    Temp_distance_save(demodulation* _demodulation);

    demodulation* m_demodultion;
    QDateTime dateTime;
    QString saveFilename;
    QString saveFilenameAll;
    ofstream outfileAll;

    void run();

signals:
    void getFilename();
};

#endif // TEMP_DISTANCE_SAVE_H
