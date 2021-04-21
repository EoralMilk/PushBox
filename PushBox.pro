QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GameMap.cpp \
    MainWindow.cpp \
    MapForm.cpp \
    Player.cpp \
    main.cpp

HEADERS += \
    GameMap.h \
    MainWindow.h \
    MapForm.h \
    Player.h \
    Settings.h

FORMS += \
    MainWindow.ui



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

defineTest(AddDir){
    Dirs = $${1}
    for(Dir, Dirs){
        CONFIG(debug, debug|release){
            DDIR = $${OUT_PWD}/debug
        } else {
            DDIR = $${OUT_PWD}/release
        }

        depPath = $${PWD}/$${Dir}
        targetPath = $${DDIR}/$${Dir}
        win32:depPath ~= s,/,\\,g
        win32:targetPath ~= s,/,\\,g

        copyFile$${Dir}.depends = $${depPath}
        copyFile$${Dir}.target = $${targetPath}
        copyFile$${Dir}.commands = $${QMAKE_COPY_DIR} $${depPath} $${targetPath}
        QMAKE_EXTRA_TARGETS += copyFile$${Dir}
        PRE_TARGETDEPS += $${targetPath}
        OTHER_FILES += $${Dir}/*
        export(copyFile$${Dir}.depends)
        export(copyFile$${Dir}.target)
        export(copyFile$${Dir}.commands)
    }
    export(OTHER_FILES)
    export(QMAKE_EXTRA_TARGETS)
    export(PRE_TARGETDEPS)
}

AddDir(content/imgs maps)
