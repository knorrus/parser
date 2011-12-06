#-------------------------------------------------
#
# Project created by QtCreator 2011-12-06T13:54:49
#
#-------------------------------------------------

QT       += core gui

TARGET = parser
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    Visitor.cpp \
    Parser.cpp \
    ExprTree.cpp \
    ExprParser.cpp \
    Drawer.cpp \
    CTreeBuilder.cpp

HEADERS  += widget.h \
    stdafx.h \
    Parser.h \
    ExprTypes.h \
    ExprTree.h \
    ExprParser.h \
    Drawer.h \
    CTreeBuilder.h \
    MathFunctionsWrapper.h

FORMS    += widget.ui



