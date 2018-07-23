QT += quick sql quickcontrols2 multimedia
CONFIG += c++11
LIBS += -ltag

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    CXX/albumloader.cpp \
    CXX/artistloader.cpp \
    CXX/databasemanager.cpp \
    CXX/loader.cpp \
    CXX/queueloader.cpp \
    CXX/songloader.cpp \
    CXX/activeinfo.cpp \
    CXX/playlistloader.cpp \
    CXX/recentlyaddedloader.cpp \
    CXX/recentlyplayedloader.cpp \
    CXX/pathmanager.cpp \
    CXX/statusmanager.cpp \
    CXX/trackmanager.cpp \
    CXX/mainmanager.cpp \
    CXX/tagdata.cpp \
    CXX/library.cpp \
    CXX/detailsmanager.cpp \
    CXX/mediaplayer.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

HEADERS += \
    CXX/albumloader.h \
    CXX/artistloader.h \
    CXX/databasemanager.h \
    CXX/loader.h \
    CXX/model.h \
    CXX/queueloader.h \
    CXX/songloader.h \
    CXX/structs.h \
    CXX/activeinfo.h \
    CXX/playlistloader.h \
    CXX/recentlyaddedloader.h \
    CXX/recentlyplayedloader.h \
    CXX/pathmanager.h \
    CXX/statusmanager.h \
    CXX/trackmanager.h \
    CXX/mainmanager.h \
    CXX/tagdata.h \
    CXX/detailsmanager.h \
    CXX/mediaplayer.h
