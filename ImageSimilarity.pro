QT       += core gui sql concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += C++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controller/debugdisplaycontroller.cpp \
    Controller/detectdisplaycontroller.cpp \
    Model/basemodel.cpp \
    Model/debugdisplaymodel.cpp \
    Model/detectdisplaymodel.cpp \
    Tools/awesome.cpp \
    Tools/tool.cpp \
    View/ImageSimilarityView.cpp \
    View/aboutview.cpp \
    View/imagealgorithmview.cpp \
    View/imageshowview.cpp \
    View/messageboxview.cpp \
    filesave.cpp \
    imagealgorithm.cpp \
    main.cpp

HEADERS += \
    Controller/debugdisplaycontroller.hpp \
    Controller/detectdisplaycontroller.hpp \
    Model/basemodel.hpp \
    Model/debugdisplaymodel.hpp \
    Model/detectdisplaymodel.hpp \
    Tools/awesome.hpp \
    Tools/tool.hpp \
    View/ImageSimilarityView.hpp \
    View/aboutview.hpp \
    View/imagealgorithmview.hpp \
    View/imageshowview.hpp \
    View/messageboxview.hpp \
    filesave.hpp \
    imagealgorithm.hpp

FORMS += \
    View/ImageSimilarityView.ui \
    View/aboutview.ui \
    View/imageshowview.ui \
    View/messageboxview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#set icon
RC_ICONS = logo128.ico

# QtAwesome
include(./QtAwesome/QtAwesome/QtAwesome.pri)

# opencv
win32:CONFIG(release, debug|release): LIBS += -LD:/Users/souls/Documents/opencv/opencv451/x86/x86/vc16/lib/ -lopencv_world451
else:win32:CONFIG(debug, debug|release): LIBS += -LD:/Users/souls/Documents/opencv/opencv451/x86/x86/vc16/lib/ -lopencv_world451d

INCLUDEPATH += D:/Users/souls/Documents/opencv/opencv451/x86/include
DEPENDPATH += D:/Users/souls/Documents/opencv/opencv451/x86/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += D:/Users/souls/Documents/opencv/opencv451/x86/x86/vc16/lib/libopencv_world451.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += D:/Users/souls/Documents/opencv/opencv451/x86/x86/vc16/lib/libopencv_world451d.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += D:/Users/souls/Documents/opencv/opencv451/x86/x86/vc16/lib/opencv_world451.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += D:/Users/souls/Documents/opencv/opencv451/x86/x86/vc16/lib/opencv_world451d.lib
