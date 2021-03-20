QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += C++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    awesome.cpp \
    filesave.cpp \
    imagealgorithm.cpp \
    imageshow.cpp \
    main.cpp \
    mainwindow.cpp \
    messagebox.cpp \
    value.cpp

HEADERS += \
    awesome.hpp \
    filesave.hpp \
    imagealgorithm.hpp \
    imageshow.hpp \
    mainwindow.hpp \
    messagebox.hpp \
    value.hpp

FORMS += \
    imageshow.ui \
    mainwindow.ui \
    messagebox.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#set icon
RC_ICONS = logo.ico


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
