QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    app/file_dialog.cpp \
    app/results.cpp \
    app/sorter.cpp \
    app/start_page.cpp \
    main.cpp \
    app/mainwindow.cpp

HEADERS += \
    app/color.hpp \
    app/file_dialog.hpp \
    app/mainwindow.hpp \
    app/results.hpp \
    app/sorter.hpp \
    app/start_page.hpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS +=


win32:CONFIG(release, debug|release): LIBS += -LC:/taglib/taglib-release/ -ltaglib
else:unix: LIBS += -LC:/taglib/taglib-release/ -ltaglib

#unix|win32: LIBS += -LC:/taglib/taglib/taglib-release/ -ltaglib

INCLUDEPATH += C:/taglib
DEPENDPATH += C:/taglib

INCLUDEPATH += C:/taglib/taglib
HEADERS += C:/taglib/taglib/fileref.h
#HEADERS += C:/taglib/taglib/taglib_export.h

INCLUDEPATH += C:/taglib/taglib/toolkit
HEADERS += C:/taglib/taglib/toolkit/tfile.h

win32:RC_ICONS += resources/icon.ico
