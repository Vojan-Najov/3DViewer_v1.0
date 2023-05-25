QT       += core gui openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    oglwindow.cpp \
    gifLib/giflib/dgif_lib.c \
    gifLib/giflib/egif_lib.c \
    gifLib/giflib/gif_err.c \
    gifLib/giflib/gif_font.c \
    gifLib/giflib/gif_hash.c \
    gifLib/giflib/gifalloc.c \
    gifLib/giflib/quantize.c \
    gifLib/qgifimage.cpp

HEADERS += \
    mainwindow.h \
    oglwindow.h \
    gifLib/qgifimage.h

FORMS += \
    mainwindow.ui

LIBS +=
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../viewer/release/ -l3Dviewer
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../viewer/debug/ -l3Dviewer
else:unix: LIBS += -L$$PWD/../viewer/ -l3Dviewer

INCLUDEPATH += $$PWD/../viewer
DEPENDPATH += $$PWD/../viewer

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../viewer/release/lib3Dviewer.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../viewer/debug/lib3Dviewer.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../viewer/release/3Dviewer.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../viewer/debug/3Dviewer.lib
else:unix: PRE_TARGETDEPS += $$PWD/../viewer/lib3Dviewer.a
