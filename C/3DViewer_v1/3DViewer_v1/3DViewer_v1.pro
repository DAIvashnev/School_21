QT       += core gui opengl
//QT += openglwidgets
QT += gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../affine.c \
    ../gif.cpp \
    ../parser.c \
    main.cpp \
    mainwindow.cpp \
    viewer.cpp

HEADERS += \
    ../gif.h \
    ../affine.h \
    ../parser.h \
    mainwindow.h \
    viewer.h

FORMS += \
    mainwindow.ui

#LIBS += -lopengl32 # For Win32

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

