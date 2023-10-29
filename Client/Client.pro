QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Class/Common/common.cpp \
    Class/Data/info.cpp \
    Class/Data/mail.cpp \
    Class/DataAccess/chat_socket.cpp \
    Class/DataAccess/friend_socket.cpp \
    Class/DataAccess/login_socket.cpp \
    Class/DataAccess/mail_socket.cpp \
    Class/DataAccess/myfile.cpp \
    Class/DataAccess/personal_socket.cpp \
    Class/Data/friend.cpp \
    Class/Data/message.cpp \
    Class/Service/chat_service.cpp \
    Class/Service/friends_service.cpp \
    Class/Service/personal_service.cpp \
    Class/Transfer/noaname.cpp \
    Class/socket.cpp \
    Form/Common/widget_choose.cpp \
    Form/Common/widget_tips.cpp \
    Form/Common/widget_wait.cpp \
    Form/Form_Main/Common/widget_head.cpp \
    Form/Form_Main/form_friend.cpp \
    Form/Form_Main/form_mail.cpp \
    Form/Form_Main/form_makefriends.cpp \
    Form/Form_Main/Form_MyInfo/widget_sethead.cpp \
    Form/Form_Main/form_myfriends.cpp \
    Form/Form_Main/form_myinfo.cpp \
    Form/Form_Login/form_register.cpp \
    Form/Form_Main/widget_chat.cpp \
    Form/Form_Main/widget_friendlist.cpp \
    Form/form_connect.cpp \
    Form/form_login.cpp \
    Form/form_main.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Class/Common/common.h \
    Class/Data/info.h \
    Class/Data/mail.h \
    Class/DataAccess/chat_socket.h \
    Class/DataAccess/friend_socket.h \
    Class/DataAccess/login_socket.h \
    Class/DataAccess/mail_socket.h \
    Class/DataAccess/myfile.h \
    Class/DataAccess/personal_socket.h \
    Class/Data/friend.h \
    Class/Data/message.h \
    Class/Service/chat_service.h \
    Class/Service/friends_service.h \
    Class/Service/personal_service.h \
    Class/Transfer/noaname.h \
    Class/socket.h \
    Form/Common/widget_choose.h \
    Form/Common/widget_tips.h \
    Form/Common/widget_wait.h \
    Form/Form_Main/Common/widget_head.h \
    Form/Form_Main/form_friend.h \
    Form/Form_Main/form_mail.h \
    Form/Form_Main/form_makefriends.h \
    Form/Form_Main/Form_MyInfo/widget_sethead.h \
    Form/Form_Main/form_myfriends.h \
    Form/Form_Main/form_myinfo.h \
    Form/Form_Login/form_register.h \
    Form/Form_Main/widget_chat.h \
    Form/Form_Main/widget_friendlist.h \
    Form/form_connect.h \
    Form/form_login.h \
    Form/form_main.h \
    mainwindow.h

FORMS += \
    Form/Common/widget_choose.ui \
    Form/Common/widget_tips.ui \
    Form/Common/widget_wait.ui \
    Form/Form_Main/Common/widget_head.ui \
    Form/Form_Main/form_friend.ui \
    Form/Form_Main/form_mail.ui \
    Form/Form_Main/form_makefriends.ui \
    Form/Form_Main/Form_MyInfo/widget_sethead.ui \
    Form/Form_Main/form_myfriends.ui \
    Form/Form_Main/form_myinfo.ui \
    Form/Form_Login/form_register.ui \
    Form/Form_Main/widget_chat.ui \
    Form/Form_Main/widget_friendlist.ui \
    Form/form_connect.ui \
    Form/form_login.ui \
    Form/form_main.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resource/resource.qrc

RC_FILE += \
    Resource/logo.rc
