# May need to change INCLUDEPATH, QMAKE_LIBDIR_X11 to suit your 
# KDE installation path
# e.g. for SuSe, use /opt/kde3/include

TARGET = app
MOC_DIR = moc
OBJECTS_DIR = obj
INCLUDEPATH = /usr/include/kde /usr/include/mysql

# For SuSE 8.2 use the three lines below - should be harmless on other distros
INCLUDEPATH += /opt/kde3/include
INCLUDEPATH += /usr/lib/qt3/include
QMAKE_LIBDIR_X11 += /opt/kde3/lib

QMAKE_LIBDIR_X11 += /usr/lib  
QMAKE_LIBDIR_X11 += /usr/lib/mysql
QMAKE_LIBS_X11 += -lkdeui -lkdecore -lmysqlclient
SOURCES = MainWindow.cpp main.cpp app_mysql.cpp AddCdDialog.cpp LogonDialog.cpp
HEADERS = MainWindow.h app_mysql.h AddCdDialog.h LogonDialog.h

