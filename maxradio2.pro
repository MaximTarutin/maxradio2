QT       += core gui sql multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aboutwindow.cpp \
    databaseradio.cpp \
    editlistradio.cpp \
    main.cpp \
    mainwindow.cpp \
    playlistradio.cpp \
    radioplayer.cpp

HEADERS += \
    aboutwindow.h \
    databaseradio.h \
    editlistradio.h \
    mainwindow.h \
    playlistradio.h \
    radioplayer.h

FORMS += \
    aboutwindow.ui \
    editlistradio.ui \
    playlistradio.ui

RC_ICONS = maxradio2.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/./release/ -lbass
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/./debug/ -lbass
else:unix: LIBS += -L$$PWD/./ -lbass

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

