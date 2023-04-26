include(openglwindow.pri)

SOURCES += \
    main.cpp \
    volumerenderwindow.cpp

RESOURCES += shaders.qrc

target.path = $$[QT_INSTALL_EXAMPLES]/opengl/openglwindow
INSTALLS += target

HEADERS += \
    volumerenderwindow.h
