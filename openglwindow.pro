SOURCES += \
    main.cpp \
    volumerenderwidget.cpp \
    mainwindow.cpp \
    volumedata.cpp \
    graphdialog.cpp


RESOURCES += shaders.qrc

target.path = ./build_qt
INSTALLS += target

FORMS += mainwindow.ui \
        graphdialog.ui

HEADERS += \
    volumerenderwidget.h \
    ui_mainwindow.h \
    mainwindow.h \
    volumedata.h \
    graphdialog.h

QT += widgets
QT += openglwidgets
QT += charts
