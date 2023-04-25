include(openglwindow.pri)

SOURCES += \
    main.cpp

RESOURCES += shaders.qrc

target.path = $$[QT_INSTALL_EXAMPLES]/opengl/openglwindow
INSTALLS += target
