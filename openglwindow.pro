SOURCES += \
    main.cpp \
    volumerenderwidget.cpp \
    mainwindow.cpp \
    volumedata.cpp \
    chartdialog.cpp


RESOURCES += shaders.qrc

target.path = ./build_qt
INSTALLS += target

FORMS = mainwindow.ui chartdialog.ui

HEADERS += \
    volumerenderwidget.h \
    ui_mainwindow.h \
    mainwindow.h \
    volumedata.h \
    chartdialog.h

QT += widgets
QT += openglwidgets
QT += charts
