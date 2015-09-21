#-------------------------------------------------
#
# Project created by QtCreator 2015-09-15T02:17:59
#
#-------------------------------------------------

QT       += core gui
CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Parallel
TEMPLATE = app


# Main
SOURCES += \
    main.cpp\
    idgenerator.cpp \

HEADERS  += \
    idgenerator.h \

# Command Line
SOURCES  += \
    command_line/commandline.cpp \
    command_line/command.cpp \
    command_line/cli/commandlineinterface.cpp \
    command_line/task.cpp \
    command_line/maincommandline.cpp \
    command_line/subcommandline.cpp

HEADERS  += \
    command_line/commandline.h \
    command_line/command.h \
    command_line/cli/commandlineinterface.h \
    command_line/cli/function.h \
    command_line/cli/cl_basic_functions/clbasicfunctions.h \
    command_line/cli/cl_basic_functions/clbasicfunctionscli.h \
    command_line/cli/test_functions/testfunctions.h \
    command_line/cli/test_functions/testfunctionscli.h \
    command_line/maincommandline.h \
    command_line/task.h \
    command_line/subcommandline.h

# Application UI
SOURCES  += \
    ui/mainwindow.cpp \
    ui/threadtablemodel.cpp \
    ui/threadtablecontroller.cpp \

HEADERS  += \
    ui/mainwindow.h \
    ui/threadtablemodel.h \
    ui/threadtablecontroller.h \

FORMS    += \
    ui/mainwindow.ui \
    ui/otherwindow.ui

RESOURCES += \
    res/images.qrc
