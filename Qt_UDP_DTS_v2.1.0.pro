QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Centroid_wavelength_widget.cpp \
    MaxValue_wavelength_widget.cpp \
    Temp_distance_widget.cpp \
    add_wave_widget.cpp \
    demodulation.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp \
    raw_wave_widget.cpp

HEADERS += \
    Centroid_wavelength_widget.h \
    MaxValue_wavelength_widget.h \
    Temp_distance_widget.h \
    add_wave_widget.h \
    demodulation.h \
    mainwindow.h \
    qcustomplot.h \
    raw_wave_widget.h

FORMS += \
    Centroid_wavelength_widget.ui \
    MaxValue_wavelength_widget.ui \
    Temp_distance_widget.ui \
    add_wave_widget.ui \
    mainwindow.ui \
    raw_wave_widget.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#下面四条是打开Matlab文件的lib包
INCLUDEPATH += D:\MATLAB2021a\extern\include\
LIBS += -LD:\MATLAB2021a\extern\lib\win64\microsoft\  -llibeng
LIBS += -LD:\MATLAB2021a\extern\lib\win64\microsoft\ -llibmx
LIBS += -LD:\MATLAB2021a\extern\lib\win64\microsoft\ -llibmat

#qwtplot3d的配置
#还需要将qwtplot3d.dll复制到的Qt_UDP_DTS目录下的bin目录里
INCLUDEPATH    +=$$PWD/include
DEPENDPATH	= $$INCLUDEPATH
LIBS += $$PWD/lib/libqwtplot3d.a
DEFINES  += QT_DLL QWT3D_DLL
LIBS += -lopengl32 -lglu32


