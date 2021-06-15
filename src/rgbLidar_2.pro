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
                   D:/PCL1.8.1/include/pcl-1.8\
                   D:/PCL1.8.1/include/pcl-1.8/pcl\
                   D:/PCL1.8.1/3rdParty/VTK/include/vtk-8.0\
                   D:/PCL1.8.1/3rdParty/Eigen/eigen3\
                   D:/PCL1.8.1/3rdParty/Boost/include/boost-1_64\
                   D:/PCL1.8.1/3rdParty/OpenNI2/Include\
                   D:/PCL1.8.1/3rdParty/FLANN/include\
                   D:/PCL1.8.1/3rdParty/Qhull/include\
                   D:/PCL1.8.1/3rdParty/VTK/include\

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
            C:/Qt/Qt5.13.1/5.13.1/msvc2017_64/lib/freeglut.lib\
            D:/pg_cpp/livox_sdk/Livox-SDK/third_party/apr/lib/libapr-1.lib\
            D:/pg_cpp/livox_sdk/Livox-SDK/temp64/sdk_core/Debug/livox_sdk_static.lib\
            D:/LIVOX_HIKVISION/Hikvision/sdk/CH-HCNetSDKV6.1.4.42_build20200527_win64/lib/HCCore.lib\
            D:/LIVOX_HIKVISION/Hikvision/sdk/CH-HCNetSDKV6.1.4.42_build20200527_win64/lib/HCNetSDK.lib\
            D:/LIVOX_HIKVISION/Hikvision/sdk/CH-HCNetSDKV6.1.4.42_build20200527_win64/lib/HCNetSDKCom/HCAlarm.lib\
            D:/LIVOX_HIKVISION/Hikvision/sdk/CH-HCNetSDKV6.1.4.42_build20200527_win64/lib/HCNetSDKCom/HCGeneralCfgMgr.lib\
            D:/LIVOX_HIKVISION/Hikvision/sdk/CH-HCNetSDKV6.1.4.42_build20200527_win64/lib/HCNetSDKCom/HCPreview.lib\
            D:/LIVOX_HIKVISION/Hikvision/sdk/CH-HCNetSDKV6.1.4.42_build20200527_win64/lib/PlayCtrl.lib\

    CONFIG += debug_and_release
    # 大括号需跟后面，且目录不能有空格和中文字符
    CONFIG(debug,debug|release){
            LIBS += C:/opencv/opencv/build/x64/vc15/lib/opencv_world450d.lib\
            D:/PCL1.8.1/3rdParty/Boost/lib/libboost_system-vc141-mt-gd-1_64.lib\
            D:/PCL1.8.1/3rdParty/Boost/lib/libboost_filesystem-vc141-mt-gd-1_64.lib\
            D:/PCL1.8.1/3rdParty/Boost/lib/libboost_thread-vc141-mt-gd-1_64.lib\
            D:/PCL1.8.1/3rdParty/Boost/lib/libboost_date_time-vc141-mt-gd-1_64.lib\
            D:/PCL1.8.1/3rdParty/Boost/lib/libboost_iostreams-vc141-mt-gd-1_64.lib\
            D:/PCL1.8.1/3rdParty/Boost/lib/libboost_serialization-vc141-mt-gd-1_64.lib\
            D:/PCL1.8.1/3rdParty/Boost/lib/libboost_chrono-vc141-mt-gd-1_64.lib\
            D:/PCL1.8.1/3rdParty/Boost/lib/libboost_atomic-vc141-mt-gd-1_64.lib\
            D:/PCL1.8.1/3rdParty/Boost/lib/libboost_regex-vc141-mt-gd-1_64.lib\
            D:/PCL1.8.1/lib/pcl_common_debug.lib\
            D:/PCL1.8.1/lib/pcl_octree_debug.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkChartsCore-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkCommonColor-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkCommonCore-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtksys-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkCommonDataModel-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkCommonMath-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkCommonMisc-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkCommonSystem-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkCommonTransforms-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkCommonExecutionModel-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkFiltersGeneral-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkCommonComputationalGeometry-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkFiltersCore-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkInfovisCore-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkFiltersExtraction-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkFiltersStatistics-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkImagingFourier-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkImagingCore-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkalglib-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkRenderingContext2D-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkRenderingCore-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkFiltersGeometry-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkFiltersSources-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkRenderingFreeType-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkfreetype-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkzlib-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkDICOMParser-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkDomainsChemistry-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkIOLegacy-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkIOCore-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtklz4-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkIOXMLParser-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkexpat-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkFiltersAMR-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkIOXML-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkParallelCore-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkFiltersFlowPaths-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkFiltersGeneric-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkFiltersHybrid-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkImagingSources-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkFiltersHyperTree-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkFiltersImaging-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkImagingGeneral-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkFiltersModeling-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkFiltersParallel-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkFiltersParallelImaging-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkFiltersPoints-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkFiltersProgrammable-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkFiltersSMP-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkFiltersSelection-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkFiltersTexture-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkFiltersTopology-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkFiltersVerdict-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkverdict-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkGeovisCore-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkIOImage-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkmetaio-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkjpeg-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkpng-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtktiff-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkInfovisLayout-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkImagingHybrid-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkInteractionStyle-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkInteractionWidgets-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkImagingColor-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkRenderingAnnotation-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkRenderingVolume-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkViewsCore-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkproj4-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkIOAMR-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkhdf5_hl-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkhdf5-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkIOEnSight-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkIOExodus-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkexoIIc-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkNetCDF-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkIOExport-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkRenderingGL2PS-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkRenderingContextOpenGL-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkRenderingOpenGL-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkgl2ps-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtklibharu-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkIOExportOpenGL-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkRenderingLabel-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkIOGeometry-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkIOImport-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkIOInfovis-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtklibxml2-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkIOLSDyna-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkIOMINC-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkIOMovie-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkoggtheora-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkIONetCDF-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtknetcdf_c++-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkIOPLY-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkIOParallel-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkjsoncpp-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkIOParallelXML-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkIOSQL-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtksqlite-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkIOTecplotTable-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkIOVideo-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkImagingMath-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkImagingMorphological-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkImagingStatistics-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkImagingStencil-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkInteractionImage-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkRenderingImage-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkRenderingLIC-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkRenderingLOD-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkRenderingVolumeOpenGL-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkViewsContext2D-8.0-gd.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkViewsInfovis-8.0-gd.lib\
            D:/PCL1.8.1/lib/pcl_io_debug.lib\
            D:/PCL1.8.1/3rdParty/FLANN/lib/flann_cpp_s-gd.lib\
            D:/PCL1.8.1/lib/pcl_kdtree_debug.lib\
            D:/PCL1.8.1/lib/pcl_search_debug.lib\
            D:/PCL1.8.1/lib/pcl_sample_consensus_debug.lib\
            D:/PCL1.8.1/lib/pcl_filters_debug.lib\
            D:/PCL1.8.1/lib/pcl_features_debug.lib\
            D:/PCL1.8.1/lib/pcl_ml_debug.lib\
            D:/PCL1.8.1/lib/pcl_segmentation_debug.lib\
            D:/PCL1.8.1/lib/pcl_visualization_debug.lib\
            D:/PCL1.8.1/3rdParty/Qhull/lib/qhullstatic_d.lib\
            D:/PCL1.8.1/lib/pcl_surface_debug.lib\
            D:/PCL1.8.1/lib/pcl_registration_debug.lib\
            D:/PCL1.8.1/lib/pcl_keypoints_debug.lib\
            D:/PCL1.8.1/lib/pcl_tracking_debug.lib\
            D:/PCL1.8.1/lib/pcl_recognition_debug.lib\
            D:/PCL1.8.1/lib/pcl_stereo_debug.lib\
            D:/PCL1.8.1/lib/pcl_outofcore_debug.lib\
            D:/PCL1.8.1/lib/pcl_people_debug.lib\
    }else{
    LIBS += C:/opencv/opencv/build/x64/vc15/lib/opencv_world450.lib\
            D:/PCL1.8.1/3rdParty/Boost/lib/libboost_system-vc141-mt-1_64.lib\
            D:/PCL1.8.1/3rdParty/Boost/lib/libboost_filesystem-vc141-mt-1_64.lib\
            D:/PCL1.8.1/3rdParty/Boost/lib/libboost_thread-vc141-mt-1_64.lib\
            D:/PCL1.8.1/3rdParty/Boost/lib/libboost_date_time-vc141-mt-1_64.lib\
            D:/PCL1.8.1/3rdParty/Boost/lib/libboost_iostreams-vc141-mt-1_64.lib\
            D:/PCL1.8.1/3rdParty/Boost/lib/libboost_serialization-vc141-mt-1_64.lib\
            D:/PCL1.8.1/3rdParty/Boost/lib/libboost_chrono-vc141-mt-1_64.lib\
            D:/PCL1.8.1/3rdParty/Boost/lib/libboost_atomic-vc141-mt-1_64.lib\
            D:/PCL1.8.1/3rdParty/Boost/lib/libboost_regex-vc141-mt-1_64.lib\
            D:/PCL1.8.1/lib/pcl_common_release.lib\
            D:/PCL1.8.1/lib/pcl_octree_release.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkChartsCore-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkCommonColor-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkCommonCore-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtksys-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkCommonDataModel-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkCommonMath-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkCommonMisc-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkCommonSystem-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkCommonTransforms-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkCommonExecutionModel-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkFiltersGeneral-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkCommonComputationalGeometry-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkFiltersCore-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkInfovisCore-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkFiltersExtraction-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkFiltersStatistics-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkImagingFourier-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkImagingCore-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkalglib-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkRenderingContext2D-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkRenderingCore-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkFiltersGeometry-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkFiltersSources-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkRenderingFreeType-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkfreetype-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkzlib-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkDICOMParser-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkDomainsChemistry-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkIOLegacy-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkIOCore-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtklz4-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkIOXMLParser-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkexpat-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkFiltersAMR-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkIOXML-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkParallelCore-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkFiltersFlowPaths-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkFiltersGeneric-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkFiltersHybrid-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkImagingSources-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkFiltersHyperTree-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkFiltersImaging-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkImagingGeneral-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkFiltersModeling-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkFiltersParallel-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkFiltersParallelImaging-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkFiltersPoints-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkFiltersProgrammable-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkFiltersSMP-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkFiltersSelection-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkFiltersTexture-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkFiltersTopology-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkFiltersVerdict-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkverdict-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkGeovisCore-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkIOImage-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkmetaio-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkjpeg-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkpng-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtktiff-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkInfovisLayout-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkImagingHybrid-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkInteractionStyle-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkInteractionWidgets-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkImagingColor-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkRenderingAnnotation-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkRenderingVolume-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkViewsCore-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkproj4-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkIOAMR-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkhdf5_hl-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkhdf5-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkIOEnSight-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkIOExodus-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkexoIIc-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkNetCDF-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkIOExport-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkRenderingGL2PS-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkRenderingContextOpenGL-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkRenderingOpenGL-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkgl2ps-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtklibharu-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkIOExportOpenGL-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkRenderingLabel-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkIOGeometry-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkIOImport-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkIOInfovis-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtklibxml2-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkIOLSDyna-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkIOMINC-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkIOMovie-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkoggtheora-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkIONetCDF-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtknetcdf_c++.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkIOPLY-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkIOParallel-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkjsoncpp-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkIOParallelXML-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkIOSQL-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtksqlite-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkIOTecplotTable-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkIOVideo-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkImagingMath-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkImagingMorphological-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkImagingStatistics-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkImagingStencil-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkInteractionImage-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkRenderingImage-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkRenderingLIC-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkRenderingLOD-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkRenderingVolumeOpenGL-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkViewsContext2D-8.0.lib\
            D:/PCL1.8.1/3rdParty/VTK/lib/vtkViewsInfovis-8.0.lib\
            D:/PCL1.8.1/lib/pcl_io_release.lib\
            D:/PCL1.8.1/3rdParty/FLANN/lib/flann_cpp_s.lib\
            D:/PCL1.8.1/lib/pcl_kdtree_release.lib\
            D:/PCL1.8.1/lib/pcl_search_release.lib\
            D:/PCL1.8.1/lib/pcl_sample_consensus_release.lib\
            D:/PCL1.8.1/lib/pcl_filters_release.lib\
            D:/PCL1.8.1/lib/pcl_features_release.lib\
            D:/PCL1.8.1/lib/pcl_ml_release.lib\
            D:/PCL1.8.1/lib/pcl_segmentation_release.lib\
            D:/PCL1.8.1/lib/pcl_visualization_release.lib\
            D:/PCL1.8.1/3rdParty/Qhull/lib/qhullstatic.lib\
            D:/PCL1.8.1/lib/pcl_surface_release.lib\
            D:/PCL1.8.1/lib/pcl_registration_release.lib\
            D:/PCL1.8.1/lib/pcl_keypoints_release.lib\
            D:/PCL1.8.1/lib/pcl_tracking_release.lib\
            D:/PCL1.8.1/lib/pcl_recognition_release.lib\
            D:/PCL1.8.1/lib/pcl_stereo_release.lib\
            D:/PCL1.8.1/lib/pcl_outofcore_release.lib\
            D:/PCL1.8.1/lib/pcl_people_release.lib\
      }
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

