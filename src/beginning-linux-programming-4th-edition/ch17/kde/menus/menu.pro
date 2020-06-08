
# May need to change INCLUDEPATH to suit your KDE installation path
# e.g. for SuSe, use /opt/kde3/include

TARGET  = kdemenu
MOC_DIR = moc
OBJECTS_DIR = obj
INCLUDEPATH = /usr/include/kde

# For Suse 8.2 add the following three lines, should be harmless on other distros
INCLUDEPATH += /opt/kde3/include
INCLUDEPATH += /usr/lib/qt3/include
QMAKE_LIBDIR_X11 += /opt/kde3/lib

QMAKE_LIBDIR_X11 += /usr/lib
QMAKE_LIBS_X11 += -lkdeui -lkdecore 
SOURCES = KDEMenu.cpp
HEADERS = KDEMenu.h

