SOURCES += \
    main.cpp \
    volumerenderwidget.cpp \
    mainwindow.cpp \
    volumedata.cpp


RESOURCES += shaders.qrc

target.path = ./build_qt
INSTALLS += target

FORMS += mainwindow.ui

HEADERS += \
    volumerenderwidget.h \
    ui_mainwindow.h \
    mainwindow.h \
    volumedata.h

QT += widgets
QT += openglwidgets
QT += charts
