QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    abeille.cpp \
    araignee.cpp \
    case.cpp \
    coccinelle.cpp \
    fourmi.cpp \
    insecte.cpp \
    joueur.cpp \
    main.cpp \
    mainwindow.cpp \
    moustique.cpp \
    partie.cpp \
    plateau.cpp \
    sauterelle.cpp \
    scarabe.cpp \

HEADERS += \
    abeille.h \
    araignee.h \
    case.h \
    coccinelle.h \
    fourmi.h \
    insecte.h \
    joueur.h \
    mainwindow.h \
    moustique.h \
    partie.h \
    plateau.h \
    sauterelle.h \
    scarabe.h \
    teams.h \
    types.h \
    usineinsecte.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
