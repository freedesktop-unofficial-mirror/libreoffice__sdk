#*************************************************************************
#
# DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
#
# Copyright 2000, 2010 Oracle and/or its affiliates.
#
# OpenOffice.org - a multi-platform office productivity suite
#
# This file is part of OpenOffice.org.
#
# OpenOffice.org is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License version 3
# only, as published by the Free Software Foundation.
#
# OpenOffice.org is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License version 3 for more details
# (a copy is included in the LICENSE file that accompanied this code).
#
# You should have received a copy of the GNU Lesser General Public License
# version 3 along with OpenOffice.org.  If not, see
# <http://www.openoffice.org/license.html>
# for a copy of the LGPLv3 License.
#
#*************************************************************************

PRJ=..$/..$/..
PRJNAME=odk
TARGET=copying

#----------------------------------------------------------------
.INCLUDE: settings.mk
.INCLUDE: $(PRJ)$/util$/makefile.pmk
#----------------------------------------------------------------

#----------------------------------------------------
# this makefile is only used for copying the example 
# files into the SDK
#----------------------------------------------------

SPREADSHEET_FILES=\
    $(DESTDIRDEVGUIDEEXAMPLES)$/Spreadsheet$/ExampleAddIn.java \
    $(DESTDIRDEVGUIDEEXAMPLES)$/Spreadsheet$/ExampleAddIn.ods \
    $(DESTDIRDEVGUIDEEXAMPLES)$/Spreadsheet$/ExampleDataPilotSource.java \
    $(DESTDIRDEVGUIDEEXAMPLES)$/Spreadsheet$/GeneralTableSample.java \
    $(DESTDIRDEVGUIDEEXAMPLES)$/Spreadsheet$/Makefile \
    $(DESTDIRDEVGUIDEEXAMPLES)$/Spreadsheet$/SpreadsheetDocHelper.java \
    $(DESTDIRDEVGUIDEEXAMPLES)$/Spreadsheet$/SpreadsheetSample.java \
    $(DESTDIRDEVGUIDEEXAMPLES)$/Spreadsheet$/ViewSample.java \
    $(DESTDIRDEVGUIDEEXAMPLES)$/Spreadsheet$/XExampleAddIn.idl \
    $(DESTDIRDEVGUIDEEXAMPLES)$/Spreadsheet$/DataPilotReadme.txt

DIR_FILE_LIST= \
    $(SPREADSHEET_FILES) \

DIR_DIRECTORY_LIST=$(uniq $(DIR_FILE_LIST:d))
DIR_CREATE_FLAG=$(MISC)$/devguide_spreadsheet_dirs_created.txt
DIR_FILE_FLAG=$(MISC)$/devguide_spreadsheet.txt

#--------------------------------------------------
# TARGETS
#--------------------------------------------------
all : \
    $(DIR_FILE_LIST) \
    $(DIR_FILE_FLAG)

#--------------------------------------------------
# use global rules
#--------------------------------------------------   
.INCLUDE: $(PRJ)$/util$/odk_rules.pmk
    
