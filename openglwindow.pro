SOURCES += \
    main.cpp \
    volumerenderwidget.cpp \
    mainwindow.cpp


RESOURCES += shaders.qrc

target.path = ./build_qt
INSTALLS += target

HEADERS += \
    volumerenderwidget.h \
    mainwindow.h

QT += widgets
QT += openglwidgets
