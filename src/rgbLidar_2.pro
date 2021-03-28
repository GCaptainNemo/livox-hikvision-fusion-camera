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

# 注意：win64下livox sdk一定编译成64位的，不然会提示找不到lib文件(LNK2019,申明没有实现)
SOURCES += \
    batch.cpp \
    batchmanager.cpp \
    frontendinfo.cpp \
    main.cpp \
    mainwindow.cpp \
    receiverhikvision.cpp \
    receiverlivox.cpp \
    renderwindow.cpp \
    roamingscenemanager.cpp

HEADERS += \
    batch.h \
    batchmanager.h \
    frontendinfo.h \
    mainwindow.h \
    receiverhikvision.h \
    receiverlivox.h \
    renderwindow.h \
    roamingscenemanager.h

# 控制LapTop和PC的宏
DEFINES += LAB_COMPUTER
if(contains(DEFINES, LAB_COMPUTER)){
INCLUDEPATH += D:/glew/glew-2.1.0/include\
               C:/opencv/opencv/build/include\
               C:/opencv/opencv/build/include/opencv2\
               D:/glm/glm\
               C:/Program Files (x86)/Windows Kits/10/Include/10.0.17763.0/ucrt\
               C:/Program Files (x86)/Windows Kits/10/Lib/10.0.17763.0/um/x64\
               D:/pg_cpp/livox_sdk/Livox-SDK/sdk_core/include\
               D:/pg_cpp/livox_sdk/Livox-SDK/sdk_core/include/third_party/FastCRC\
               D:/pg_cpp/livox_sdk/Livox-SDK/sdk_core/include/third_party/spdlog\
               D:/pg_cpp/livox_sdk/Livox-SDK/third_party/apr/include\
               D:/LIVOX_HIKVISION/Hikvision/sdk/CH-HCNetSDKV6.1.4.42_build20200527_win64/include\
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
        OpenGL32.Lib\
        GlU32.Lib\
        glut32.lib\
        D:/glew/glew-2.1.0/lib/Release/Win32/glew32s.lib\
        C:/opencv/opencv/build/x64/vc15/lib/opencv_world450.lib\
        C:/opencv/opencv/build/x64/vc15/lib/opencv_world450d.lib\
        C:/Qt/Qt5.13.1/5.13.1/msvc2017_64/lib/freeglut.lib\
        D:/pg_cpp/livox_sdk/Livox-SDK/third_party/apr/lib/libapr-1.lib\
        D:/pg_cpp/livox_sdk/Livox-SDK/temp64/sdk_core/Debug/livox_sdk_static.lib\
        D:/LIVOX_HIKVISION/Hikvision/sdk/CH-HCNetSDKV6.1.4.42_build20200527_win64/lib/HCCore.lib\
        D:/LIVOX_HIKVISION/Hikvision/sdk/CH-HCNetSDKV6.1.4.42_build20200527_win64/lib/HCNetSDK.lib\
        D:/LIVOX_HIKVISION/Hikvision/sdk/CH-HCNetSDKV6.1.4.42_build20200527_win64/lib/HCNetSDKCom/HCAlarm.lib\
        D:/LIVOX_HIKVISION/Hikvision/sdk/CH-HCNetSDKV6.1.4.42_build20200527_win64/lib/HCNetSDKCom/HCGeneralCfgMgr.lib\
        D:/LIVOX_HIKVISION/Hikvision/sdk/CH-HCNetSDKV6.1.4.42_build20200527_win64/lib/HCNetSDKCom/HCPreview.lib\
        D:/LIVOX_HIKVISION/Hikvision/sdk/CH-HCNetSDKV6.1.4.42_build20200527_win64/lib/PlayCtrl.lib\
}else{
INCLUDEPATH += D:/glew/glew-2.1.0/include\
               C:/opencv/opencv/build/include\
               C:/opencv/opencv/build/include/opencv2\
               D:/glm/glm\
               C:/Program Files (x86)/Windows Kits/10/Include/10.0.16299.0/ucrt\
               C:/Program Files (x86)/Windows Kits/10/Lib/10.0.16299.0/um/x64\
               D:/livox_hikvision_huawei/livox/Livox-SDK/sdk_core/include\
               D:/livox_hikvision_huawei/livox/Livox-SDK/sdk_core/include/third_party/FastCRC\
               D:/livox_hikvision_huawei/livox/Livox-SDK/sdk_core/include/third_party/spdlog\
               D:/livox_hikvision_huawei/livox/Livox-SDK/third_party/apr/include\
               D:/livox_hikvision_huawei/hikvision/CH-HCNetSDKV6.1.4.42_build20200527_win64/include\
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
        OpenGL32.Lib\
        GlU32.Lib\
        glut32.lib\
        D:/glew/glew-2.1.0/lib/Release/Win32/glew32s.lib\
        C:/opencv/opencv/build/x64/vc15/lib/opencv_world450.lib\
        C:/opencv/opencv/build/x64/vc15/lib/opencv_world450d.lib\
        D:/livox_hikvision_huawei/livox/Livox-SDK/third_party/apr/lib/libapr-1.lib\
        D:/livox_hikvision_huawei/livox/Livox-SDK/build/sdk_core/Debug/livox_sdk_static.lib\
        D:/livox_hikvision_huawei/hikvision/CH-HCNetSDKV6.1.4.42_build20200527_win64/lib/HCCore.lib\
        D:/livox_hikvision_huawei/hikvision/CH-HCNetSDKV6.1.4.42_build20200527_win64/lib/HCNetSDK.lib\
        D:/livox_hikvision_huawei/hikvision/CH-HCNetSDKV6.1.4.42_build20200527_win64/lib/HCNetSDKCom/HCAlarm.lib\
        D:/livox_hikvision_huawei/hikvision/CH-HCNetSDKV6.1.4.42_build20200527_win64/lib/HCNetSDKCom/HCGeneralCfgMgr.lib\
        D:/livox_hikvision_huawei/hikvision/CH-HCNetSDKV6.1.4.42_build20200527_win64/lib/HCNetSDKCom/HCPreview.lib\
        D:/livox_hikvision_huawei/hikvision/CH-HCNetSDKV6.1.4.42_build20200527_win64/lib/PlayCtrl.lib\
}



#LIBS += kernel32.lib\
#        user32.lib\
#        gdi32.lib\
#        winspool.lib\
#        shell32.lib\
#        ole32.lib\
#        oleaut32.lib\
#        uuid.lib\
#        comdlg32.lib\
#        advapi32.lib\
#        OpenGL32.Lib\
#        GlU32.Lib\
#        glut32.lib\
#        D:/glew/glew-2.1.0/lib/Release/Win32/glew32s.lib\
#        C:/opencv/opencv/build/x64/vc15/lib/opencv_world450.lib\
#        C:/opencv/opencv/build/x64/vc15/lib/opencv_world450d.lib\
##        D:/livox_hikvision_huawei/livox/Livox-SDK/third_party/apr/lib/libapr-1.lib\
##        D:/livox_hikvision_huawei/livox/Livox-SDK/build/sdk_core/Debug/livox_sdk_static.lib\
##        D:/livox_hikvision_huawei/hikvision/CH-HCNetSDKV6.1.4.42_build20200527_win64/lib/HCCore.lib\
##        D:/livox_hikvision_huawei/hikvision/CH-HCNetSDKV6.1.4.42_build20200527_win64/lib/HCNetSDK.lib\
##        D:/livox_hikvision_huawei/hikvision/CH-HCNetSDKV6.1.4.42_build20200527_win64/lib/HCNetSDKCom/HCAlarm.lib\
##        D:/livox_hikvision_huawei/hikvision/CH-HCNetSDKV6.1.4.42_build20200527_win64/lib/HCNetSDKCom/HCGeneralCfgMgr.lib\
##        D:/livox_hikvision_huawei/hikvision/CH-HCNetSDKV6.1.4.42_build20200527_win64/lib/HCNetSDKCom/HCPreview.lib\
##        D:/livox_hikvision_huawei/hikvision/CH-HCNetSDKV6.1.4.42_build20200527_win64/lib/PlayCtrl.lib\
#        C:/Qt/Qt5.13.1/5.13.1/msvc2017_64/lib/freeglut.lib\
#        D:/program_cpp/livox_sdk/Livox-SDK/third_party/apr/lib/libapr-1.lib\
#        D:/program_cpp/livox_sdk/Livox-SDK/temp64/sdk_core/Debug/livox_sdk_static.lib\
#        D:/LIVOX_HIKVISION/Hikvision/sdk/CH-HCNetSDKV6.1.4.42_build20200527_win64/lib/HCCore.lib\
#        D:/LIVOX_HIKVISION/Hikvision/sdk/CH-HCNetSDKV6.1.4.42_build20200527_win64/lib/HCNetSDK.lib\
#        D:/LIVOX_HIKVISION/Hikvision/sdk/CH-HCNetSDKV6.1.4.42_build20200527_win64/lib/HCNetSDKCom/HCAlarm.lib\
#        D:/LIVOX_HIKVISION/Hikvision/sdk/CH-HCNetSDKV6.1.4.42_build20200527_win64/lib/HCNetSDKCom/HCGeneralCfgMgr.lib\
#        D:/LIVOX_HIKVISION/Hikvision/sdk/CH-HCNetSDKV6.1.4.42_build20200527_win64/lib/HCNetSDKCom/HCPreview.lib\
#        D:/LIVOX_HIKVISION/Hikvision/sdk/CH-HCNetSDKV6.1.4.42_build20200527_win64/lib/PlayCtrl.lib\




# C:\Program Files (x86)\Windows Kits\10\Lib\10.0.17763.0\um\x64\ opengl library


