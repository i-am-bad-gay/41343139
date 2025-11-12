QT += core gui widgets qml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets qml

CONFIG += c++17

SOURCES += \
    main.cpp \
    calculatordig.cpp

HEADERS += \
    calculatordig.h

INCLUDEPATH += $$[QT_INSTALL_HEADERS]/QtQml

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
