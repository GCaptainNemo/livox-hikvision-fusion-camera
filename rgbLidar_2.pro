QT       += core gui
QT       += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    centralwindow.cpp \
    frontendinfo.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    centralwindow.h \
    frontendinfo.h \
    mainwindow.h


INCLUDEPATH += D:/program_cpp/livox_sdk/Livox-SDK/sdk_core/include/third_party/FastCRC\
               D:/program_cpp/livox_sdk/Livox-SDK/sdk_core/include/third_party/spdlog\
               C:/Program Files (x86)/Windows Kits/10/Include/10.0.17763.0/ucrt\
               D:/program_cpp/livox_sdk/Livox-SDK/third_party/apr/include\
               D:/program_cpp/livox_sdk/Livox-SDK/sdk_core/include\
               C:/Program Files (x86)/Windows Kits/10/Lib/10.0.17763.0/um/x64



LIBS += kernel32.lib\
        user32.lib\
        gdi32.lib\
        winspool.lib\
        shell32.lib\
        ole32.lib\
        oleaut32.lib\
        uuid.lib\
        comdlg32.lib\
        advapi32.lib\
        D:/program_cpp/livox_sdk/Livox-SDK/temp64/sdk_core/Debug/livox_sdk_static.lib\
        D:/program_cpp/livox_sdk/Livox-SDK/third_party/apr/lib/libapr-1.lib\
        OpenGL32.Lib\
        GlU32.Lib\
        glut32.lib\
        C:/Qt/Qt5.13.1/5.13.1/msvc2017_64/lib/freeglut.lib



