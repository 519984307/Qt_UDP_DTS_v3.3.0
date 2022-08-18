QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    add_wave_widget.cpp \
    demodulation.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp \
    raw_wave_widget.cpp

HEADERS += \
    add_wave_widget.h \
    demodulation.h \
    mainwindow.h \
    qcustomplot.h \
    raw_wave_widget.h

FORMS += \
    add_wave_widget.ui \
    mainwindow.ui \
    raw_wave_widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += D:\MATLAB2021a\extern\include\
LIBS += -LD:\MATLAB2021a\extern\lib\win64\microsoft\  -llibeng
LIBS += -LD:\MATLAB2021a\extern\lib\win64\microsoft\ -llibmx
LIBS += -LD:\MATLAB2021a\extern\lib\win64\microsoft\ -llibmat

#LIBS += -LD:\MATLAB2021a\extern\lib\win64\microsoft
#LIBS += -llibeng
#LIBS += -llibmat
#LIBS += -llibmx

