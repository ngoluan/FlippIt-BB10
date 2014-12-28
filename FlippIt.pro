APP_NAME = FlippIt

CONFIG += qt warn_on cascades10
LIBS += -lbbnetwork
LIBS += -lbbplatform
LIBS += -lbbdata
LIBS += -lbbsystem
LIBS += -lbbcascadespickers
QT += network

include(config.pri)
