QT       += core gui printsupport webenginewidgets webchannel network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 resources_big

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Temp_distance_save.cpp \
    demodulation.cpp \
    main.cpp \
    mainwindow.cpp \
    udp_recv.cpp \
    udp_send.cpp

HEADERS += \
    CirQueue.h \
    Temp_distance_save.h \
    demodulation.h \
    mainwindow.h \
    udp_recv.h \
    udp_send.h

FORMS += \
    mainwindow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#下面四条是打开Matlab文件的lib包
#INCLUDEPATH += D:\MATLAB2021a\extern\include\
#LIBS += -LD:\MATLAB2021a\extern\lib\win64\microsoft\  -llibeng
#LIBS += -LD:\MATLAB2021a\extern\lib\win64\microsoft\ -llibmx
#LIBS += -LD:\MATLAB2021a\extern\lib\win64\microsoft\ -llibmat

#qwtplot3d的配置
#还需要将qwtplot3d.dll复制到的Qt_UDP_DTS目录下的bin目录里
#INCLUDEPATH    +=$$PWD/include
#DEPENDPATH	= $$INCLUDEPATH
#LIBS += $$PWD/lib/libqwtplot3d.a
#DEFINES  += QT_DLL QWT3D_DLL
#LIBS += -lopengl32 -lglu32

QTQUICK_COMPILER_SKIPPED_RESOURCES += xxxx.qrc

DISTFILES += \
    res/echarts.js \
    res/echarts.min.js \
    res/my.qss \
    res/raw_data_echarts.html

LIBS += -lws2_32

RESOURCES += \
    res.qrc
