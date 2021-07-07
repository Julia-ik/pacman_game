QT       += core gui opengl
LIBS += -LD:\Lilu\qt\5.12.11\mingw73_32\lib\libQt5OpenGL.a -lopengl32
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pacman2
TEMPLATE = app
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG +=c++1z

SOURCES += \
    appsettings.cpp \
    drawer.cpp \
    ghost.cpp \
    lvl.cpp \
    main.cpp \
    pacman_game.cpp

HEADERS += \
    appsettings.h \
    drawer.h \
    ghost.h \
    lvl.h \
    pacman_game.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
