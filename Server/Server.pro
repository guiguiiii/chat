QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Class/Module/Common/common.cpp \
    Class/Module/chat.cpp \
    Class/Module/friends.cpp \
    Class/Module/login.cpp \
    Class/Module/mail.cpp \
    Class/Module/personal.cpp \
    Class/server.cpp \
    Form/form_main.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Class/Module/Common/common.h \
    Class/Module/chat.h \
    Class/Module/friends.h \
    Class/Module/login.h \
    Class/Module/mail.h \
    Class/Module/personal.h \
    Class/server.h \
    Form/form_main.h \
    mainwindow.h

FORMS += \
    Form/form_main.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resource/resource.qrc

RC_FILE += \
    resource/logo.rc
