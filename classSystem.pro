QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    source/checkmemdialog.cpp \
    source/newmemberdialog.cpp \
    source/classinfo.cpp \
    source/classmemberinfo.cpp \
    main.cpp \
    source/invalidinputdialog.cpp \
    source/mainwindow.cpp \
    source/newclassdialog.cpp \
    source/projectmanager.cpp \
    source/readonlydelegate.cpp

HEADERS += \
    header/checkmemdialog.h \
    header/classinfo.h \
    header/classmemberinfo.h \
    header/invalidinputdialog.h \
    header/mainwindow.h \
    header/newclassdialog.h \
    header/projectmanager.h \
    header/readonlydelegate.h \
    header/newmemberdialog.h

FORMS += \
    checkmemdialog.ui \
    invalidinputdialog.ui \
    mainwindow.ui \
    newclassdialog.ui \
    newmemberdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    img.qrc
