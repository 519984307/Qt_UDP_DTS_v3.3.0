#ifndef WEBCLASS_H
#define WEBCLASS_H

#include <QObject>
#include "mainwindow.h"

class WebClass : public QObject
{
    Q_OBJECT
//    Q_PROPERTY(QString content MEMBER m_content NOTIFY contentChanged)

public:
    explicit WebClass(QObject *parent = nullptr);

     QString m_content;

signals:

public slots:
    void jscallme();


};

#endif // WEBCLASS_H
