#-------------------------------------------------
#
# Project created by QtCreator 2013-09-06T11:21:22
#
#-------------------------------------------------

QT       = core

QT       -= gui

TARGET = oblig_b
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp
LIBS += -larmadillo -lblas -llapack
