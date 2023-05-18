include(openglwindow.pri)

SOURCES += \
    main.cpp \
    volumerenderwidget.cpp \
    mainwindow.cpp


RESOURCES += shaders.qrc

target.path = $$[QT_INSTALL_EXAMPLES]/opengl/openglwindow
INSTALLS += target

HEADERS += \
    volumerenderwidget.h \
    mainwindow.h
