#-------------------------------------------------
#
# Project created by QtCreator 2016-01-10T12:20:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ssssmins
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../eternity_common/tinyxml/tinystr.cpp \
    ../eternity_common/tinyxml/tinyxml.cpp \
    ../eternity_common/tinyxml/tinyxmlerror.cpp \
    ../eternity_common/tinyxml/tinyxmlparser.cpp \
    ../eternity_common/BaseFile.cpp \
    ../eternity_common/SSSS/CdcFile.cpp \
    ../eternity_common/SSSS/CmsFile.cpp \
    ../eternity_common/SSSS/CspFile.cpp \
    ../eternity_common/SSSS/RpdFile.cpp \
    ../eternity_common/SSSS/SlotsFile.cpp \
    ../eternity_common/SSSS/SsssData.cpp \
    ../eternity_common/SSSS/SszFile.cpp \
    ../eternity_common/SSSS/TdbFile.cpp \
    ../eternity_common/Utils.cpp \
    debug.cpp \
    ../eternity_common/SSSS/SsminsConfigFile.cpp \
    installdialog.cpp \
    selectdialog.cpp \
    previewdialog.cpp \
    ../eternity_common/SSSS/SstFile.cpp \
    ../eternity_common/SSSS/GpdFile.cpp \
    ../eternity_common/SSSS/GwdFile.cpp \
    ../eternity_common/SSSS/BgrFile.cpp \
    ../eternity_common/crypto/md5.c \
    ../eternity_common/crypto/sha1.c

HEADERS  += mainwindow.h \
    ../eternity_common/tinyxml/tinystr.h \
    ../eternity_common/tinyxml/tinyxml.h \
    ../eternity_common/BaseFile.h \
    ../eternity_common/SSSS/CdcFile.h \
    ../eternity_common/SSSS/CmsFile.h \
    ../eternity_common/common.h \
    ../eternity_common/SSSS/CspFile.h \
    ../eternity_common/debug.h \
    ../eternity_common/SSSS/RpdFile.h \
    ../eternity_common/SSSS/SlotsFile.h \
    ../eternity_common/SSSS/SsssData.h \
    ../eternity_common/SSSS/SszFile.h \
    ../eternity_common/SSSS/TdbFile.h \
    ../eternity_common/Utils.h \
    ../eternity_common/SSSS/SsminsConfigFile.h \
    installdialog.h \
    selectdialog.h \
    previewdialog.h \
    ../eternity_common/SSSS/SstFile.h \
    ../eternity_common/SSSS/GpdFile.h \
    ../eternity_common/SSSS/GwdFile.h \
    ../eternity_common/SSSS/BgrFile.h \
    ../eternity_common/crypto/md5.h \
    ../eternity_common/crypto/sha1.h

FORMS    += mainwindow.ui \
    installdialog.ui \
    selectdialog.ui \
    previewdialog.ui

INCLUDEPATH += ../eternity_common
 
QMAKE_CXXFLAGS += -mno-ms-bitfields -std=c++11 -DTIXML_USE_STL 

LIBS += -lzip -lstdc++

RESOURCES += \
    resources.qrc
	
win32:RC_ICONS += ssssmins.ico


