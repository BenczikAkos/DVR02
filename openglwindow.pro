SOURCES += \
    main.cpp \
    volumerenderwidget.cpp \
    mainwindow.cpp \
    volumedata.cpp


RESOURCES += shaders.qrc

target.path = ./build_qt
INSTALLS += target

HEADERS += \
    volumerenderwidget.h \
    mainwindow.h \
    volumedata.h

QT += widgets
QT += openglwidgets
