QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = croco-assistant
TEMPLATE = app
CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
# Build section
BUILD_PREFIX = $$(CA_BUILD_DIR)

isEmpty( BUILD_PREFIX ) {
        BUILD_PREFIX = ./build
}

MOC_DIR       = $$BUILD_PREFIX/moc-qt5
OBJECTS_DIR   = $$BUILD_PREFIX/obj-qt5
RCC_DIR	      = $$BUILD_PREFIX/qrc-qt5
UI_DIR        = $$BUILD_PREFIX/uic-qt5

# Disable QDebug on Release build
#CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT

# Unused not working
#CONFIG(release):DEFINES += QT_NO_DEBUG_OUTPUT

unix {
        isEmpty(PREFIX) {
                PREFIX = /usr
        }
        BINDIR = $$PREFIX/bin

        target.path = $$BINDIR

        desktop.path = $$PREFIX/share/applications/
        desktop.files = "croco-assistant.desktop"

        icons.path = /usr/share/icons/hicolor/scalable/apps/
        icons.files = croco-assistant.png

        SCRIPTS_PATH = $$PREFIX/share/croco/

        scripts.files = scripts
        scripts.path  = $$SCRIPTS_PATH

        INSTALLS += target icons desktop scripts
}
SOURCES += \
    main.cpp \
    crocoassistant.cpp

HEADERS += \
    crocoassistant.h

FORMS += \
    crocoassistant.ui


