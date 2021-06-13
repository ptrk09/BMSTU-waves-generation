QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    debuger.cpp \
    dialog.cpp \
    dialog_menu_info.cpp \
    dialog_new_waves.cpp \
    dialog_set_wave.cpp \
    exception.cpp \
    handler.cpp \
    handler_transform.cpp \
    handler_waves.cpp \
    light.cpp \
    light_color_dialog.cpp \
    main.cpp \
    mainwindow.cpp \
    math_vectors_operation.cpp \
    point.cpp \
    surface.cpp \
    transform_buffer.cpp \
    waves.cpp \
    z_buffer.cpp

HEADERS += \
    debuger.h \
    dialog.h \
    dialog_menu_info.h \
    dialog_new_waves.h \
    dialog_set_wave.h \
    exception.h \
    handler.h \
    handler_transform.h \
    handler_waves.h \
    light.h \
    light_color_dialog.h \
    mainwindow.h \
    math_vectors_operation.h \
    point.h \
    structurs.h \
    surface.h \
    transform_buffer.h \
    waves.h \
    z_buffer.h

FORMS += \
    dialog.ui \
    dialog_menu_info.ui \
    dialog_new_waves.ui \
    dialog_set_wave.ui \
    light_color_dialog.ui \
    mainwindow.ui

TRANSLATIONS += \
    water-gen_ru_RU.ts

DEFINES += _TEST_TIME_

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
