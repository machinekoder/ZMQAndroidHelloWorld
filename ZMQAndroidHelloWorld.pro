# Add more folders to ship with the application, here
folder_01.source = qml/ZMQAndroidHelloWorld
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# HEADERS += nzmqt/nzmqt.hpp

SOURCES += main.cpp \
    subscribertest.cpp

HEADERS += \
    subscribertest.h

PROTOS += testmsg.proto

INCLUDEPATH += \
    /home/alexander/projects/nzmqt/include \
    /home/alexander/projects/nzmqt/externals/include

# Installation path
# target.path =

LIBS += -lzmq -lnzmqt -lprotobuf

android: {
LIBS += -L/opt/zeromq-android/lib/ -L/home/alexander/ownCloud/Arbeit/BBB_RepRap/Remote_Components/nzmqt/bin/android/
INCLUDEPATH += /opt/zeromq-android/include/
}
else: {
LIBS += -L/home/alexander/ownCloud/Arbeit/BBB_RepRap/Remote_Components/nzmqt/bin/
}

# Please do not modify the following two lines. Required for deployment.
include(qtquick2controlsapplicationviewer/qtquick2controlsapplicationviewer.pri)
include(protobuf.pri)
qtcAddDeployment()
