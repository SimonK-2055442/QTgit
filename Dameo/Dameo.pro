QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    bord.cpp \
    bordcelview.cpp \
    bordview.cpp \
    chaturajiboot.cpp \
    chaturajibordview.cpp \
    chaturajikoning.cpp \
    chaturajiolifant.cpp \
    chaturajipaard.cpp \
    chaturajipion.cpp \
    chaturajispel.cpp \
    dameopion.cpp \
    dameospel.cpp \
    dobbelstenen.cpp \
    main.cpp \
    mainwindow.cpp \
    pion.cpp \
    pionview.cpp \
    speler.cpp \
    welcome.cpp \
    zet.cpp

HEADERS += \
    bord.h \
    bordcelview.h \
    bordview.h \
    chaturajiboot.h \
    chaturajibordview.h \
    chaturajikoning.h \
    chaturajiolifant.h \
    chaturajipaard.h \
    chaturajipion.h \
    chaturajispel.h \
    dameopion.h \
    dameospel.h \
    dobbelstenen.h \
    mainwindow.h \
    pion.h \
    pionview.h \
    speler.h \
    welcome.h \
    zet.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
