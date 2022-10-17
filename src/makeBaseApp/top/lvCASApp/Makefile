#*************************************************************************
# Copyright (c) 2002 The University of Chicago, as Operator of Argonne
#     National Laboratory.
# Copyright (c) 2002 The Regents of the University of California, as
#     Operator of Los Alamos National Laboratory.
# EPICS BASE Versions 3.13.7
# and higher are distributed subject to a Software License Agreement found
# in file LICENSE that is included with this distribution. 
#*************************************************************************

TOP=../..

include $(TOP)/configure/CONFIG

PROD_LIBS += $(EPICS_BASE_HOST_LIBS)
LIB_LIBS += $(EPICS_BASE_HOST_LIBS)
LIB_LIBS += dbStaticHost
LIB_LIBS += dbStaticIoc
LIB_LIBS += dbtoolsIoc


#
# Added ws2_32 winmm user32 for the non-dll build
#
SYS_PROD_LIBS_WIN32 += ws2_32 advapi32 user32

#SRCS += main.cc
#SRCS += exServer.cc
#SRCS += exPV.cc
#SRCS += exVectorPV.cc
#SRCS += exScalarPV.cc
#SRCS += exAsyncPV.cc
#SRCS += exChannel.cc

SRCS += lvTest.cpp
SRCS += lvCAS.cpp
SRCS += lvVectorRecord.cpp
SRCS += lvNumericRecord.cpp
SRCS += lvLogicRecord.cpp
SRCS += lvRecord.cpp
SRCS += lvScalarPV.cpp
SRCS += lvVectorPV.cpp
SRCS += lvPV.cpp
SRCS += lvChannel.cpp
SRCS += lvExport.cpp


PROD_HOST = lvCAS
LIBRARY_HOST = lvCAS
include $(TOP)/configure/RULES


