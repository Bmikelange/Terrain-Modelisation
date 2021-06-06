QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    array2.cpp \
    box.cpp \
    box2.cpp \
    colorfield.cpp \
    dijkstra.cpp \
    drawing.cpp \
    export.cpp \
    grid2.cpp \
    hemisphere.cpp \
    hf.cpp \
    image.cpp \
    lf.cpp \
    main.cpp \
    mainwindow.cpp \
    random.cpp \
    ray.cpp \
    scalarpoint2.cpp \
    sf2.cpp \
    terrain.cpp \
    vec2.cpp \
    vec3.cpp \
    heightmapwidget.cpp \
    fileselector.cpp \
    world.cpp

HEADERS += \
    Utility.h \
    array2.h \
    box.h \
    box2.h \
    colorfield.h \
    dijkstra.h \
    drawing.h \
    export.h \
    grid2.h \
    hemisphere.h \
    hf.h \
    image.h \
    lf.h \
    mainwindow.h \
    random.h \
    ray.h \
    scalarpoint2.h \
    sf2.h \
    terrain.h \
    vec2.h \
    vec3.h \
    heightmapwidget.h \
    fileselector.h \
    world.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    MMV_TP2_fr_FR.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
unix:LIBS += -L$$PWD/lib -lrichdem -lGLEW -lGLU -lGL
unix:INCLUDEPATH += $$PWD/include/
win32:contains(QT_ARCH, i386) {
    win32:LIBS +=-L$$PWD/richdem -lrichdem -L$$PWD\glew-2.1.0\lib\Release\Win32 -lglew32 -lOpengl32 -lglu32
    win32:INCLUDEPATH += $$PWD\glew-2.1.0\include $$PWD\richdem2\include
}else {
    win32:LIBS +=-L$$PWD/richdem -lrichdem -L$$PWD\glew-2.1.0\lib\Release\x64 -lglew32 -lOpengl32 -lglu32
    win32:INCLUDEPATH += $$PWD\glew-2.1.0\include $$PWD\richdem2\include
}
!isEmpty(target.path): INSTALLS += target
