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
    command_line/subclthread.cpp

HEADERS  += \
    idgenerator.h \
    command_line/cli/cl_basic_functions/mainclfunctions.h \
    command_line/cli/cl_basic_functions/mainclfunctionscli.h \
    command_line/subclthread.h \
    command_line/colorscheme.h \
    command_line/cli/calculate_pi/calculatepi.h \
    command_line/cli/calculate_pi/calculatepicli.h

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
    command_line/cli/main_cl_functions/mainclfunctions.h \
    command_line/cli/main_cl_functions/mainclfunctionscli.h \
    command_line/cli/test_functions/testfunctions.h \
    command_line/cli/test_functions/testfunctionscli.h \
    command_line/maincommandline.h \
    command_line/task.h \
    command_line/subcommandline.h

# Application UI
SOURCES  += \
    ui/mainwindow.cpp \

HEADERS  += \
    ui/mainwindow.h \

FORMS    += \
    ui/mainwindow.ui \
    ui/otherwindow.ui

RESOURCES += \
    res/images.qrc
