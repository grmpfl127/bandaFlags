#-------------------------------------------------
#
# Project created by QtCreator 2014-12-14T19:00:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bandaFlags
TEMPLATE = app


SOURCES += main.cpp\
        bandaflags.cpp \
    result.cpp \
    resmodel.cpp \
    bandaprofile.cpp \
    bandaprofilestatusdialog.cpp \
    bandaprofileview.cpp \
    bandaprofilestatus.cpp

HEADERS  += bandaflags.h \
    result.h \
    resmodel.h \
    resultdialog.h \
    bandaConst.h \
    bandaprofile.h \
    bandaprofilestatusdialog.h \
    bandaprofileview.h \
    bandaprofilestatus.h

FORMS += \
    bandaFlags.ui \
    bandaprofilestatusdialog.ui \
    bandaProfileStatusItem.ui \
    bandaprofilestatus.ui

RESOURCES += \
    res.qrc

