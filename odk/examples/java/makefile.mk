#*************************************************************************
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.6 $
#
#   last change: $Author: rt $ $Date: 2005-01-31 17:08:09 $
#
#   The Contents of this file are made available subject to the terms of
#   either of the following licenses
#
#          - GNU Lesser General Public License Version 2.1
#          - Sun Industry Standards Source License Version 1.1
#
#   Sun Microsystems Inc., October, 2000
#
#   GNU Lesser General Public License Version 2.1
#   =============================================
#   Copyright 2000 by Sun Microsystems, Inc.
#   901 San Antonio Road, Palo Alto, CA 94303, USA
#
#   This library is free software; you can redistribute it and/or
#   modify it under the terms of the GNU Lesser General Public
#   License version 2.1, as published by the Free Software Foundation.
#
#   This library is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#   Lesser General Public License for more details.
#
#   You should have received a copy of the GNU Lesser General Public
#   License along with this library; if not, write to the Free Software
#   Foundation, Inc., 59 Temple Place, Suite 330, Boston,
#   MA  02111-1307  USA
#
#
#   Sun Industry Standards Source License Version 1.1
#   =================================================
#   The contents of this file are subject to the Sun Industry Standards
#   Source License Version 1.1 (the "License"); You may not use this file
#   except in compliance with the License. You may obtain a copy of the
#   License at http://www.openoffice.org/license.html.
#
#   Software provided under this License is provided on an "AS IS" basis,
#   WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
#   WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
#   MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
#   See the License for the specific provisions governing your rights and
#   obligations concerning the Software.
#
#   The Initial Developer of the Original Code is: Sun Microsystems, Inc.
#
#   Copyright: 2000 by Sun Microsystems, Inc.
#
#   All Rights Reserved.
#
#   Contributor(s): _______________________________________
#
#
#
#*************************************************************************

PRJ=..$/..
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

DRAWING_FILES= \
    $(DESTDIRJAVAEXAMPLES)$/Drawing$/SDraw.java \
    $(DESTDIRJAVAEXAMPLES)$/Drawing$/Makefile

SPREADSHEET_FILES= \
    $(DESTDIRJAVAEXAMPLES)$/Spreadsheet$/SCalc.java		   	\
    $(DESTDIRJAVAEXAMPLES)$/Spreadsheet$/EuroAdaption.java		\
    $(DESTDIRJAVAEXAMPLES)$/Spreadsheet$/ChartTypeChange.java   	\
    $(DESTDIRJAVAEXAMPLES)$/Spreadsheet$/CalcAddins.java	   	\
    $(DESTDIRJAVAEXAMPLES)$/Spreadsheet$/CalcAddins.ods	   	\
    $(DESTDIRJAVAEXAMPLES)$/Spreadsheet$/XCalcAddins.idl	   	\
    $(DESTDIRJAVAEXAMPLES)$/Spreadsheet$/Makefile

TEXT_FILES= \
    $(DESTDIRJAVAEXAMPLES)$/Text$/SWriter.java	   		\
    $(DESTDIRJAVAEXAMPLES)$/Text$/StyleInitialization.java 	\
    $(DESTDIRJAVAEXAMPLES)$/Text$/TextDocumentStructure.java 	\
    $(DESTDIRJAVAEXAMPLES)$/Text$/TextReplace.java 		\
    $(DESTDIRJAVAEXAMPLES)$/Text$/BookmarkInsertion.java 	\
    $(DESTDIRJAVAEXAMPLES)$/Text$/HardFormatting.java 	\
    $(DESTDIRJAVAEXAMPLES)$/Text$/StyleCreation.java  	\
    $(DESTDIRJAVAEXAMPLES)$/Text$/WriterSelector.java  	\
    $(DESTDIRJAVAEXAMPLES)$/Text$/GraphicsInserter.java  	\
    $(DESTDIRJAVAEXAMPLES)$/Text$/oo_smiley.gif  	\
    $(DESTDIRJAVAEXAMPLES)$/Text$/Makefile

DOCUMENTHANDLING_FILES= \
    $(DESTDIRJAVAEXAMPLES)$/DocumentHandling$/DocumentConverter.java	\
    $(DESTDIRJAVAEXAMPLES)$/DocumentHandling$/DocumentLoader.java	\
    $(DESTDIRJAVAEXAMPLES)$/DocumentHandling$/DocumentPrinter.java	\
    $(DESTDIRJAVAEXAMPLES)$/DocumentHandling$/DocumentSaver.java	\
    $(DESTDIRJAVAEXAMPLES)$/DocumentHandling$/Makefile \
    $(DESTDIRJAVAEXAMPLES)$/DocumentHandling$/test$/test1.odt

CONVERTERSERVLET_FILES= \
    $(DESTDIRJAVAEXAMPLES)$/ConverterServlet$/ConverterServlet.html	\
    $(DESTDIRJAVAEXAMPLES)$/ConverterServlet$/ConverterServlet.java	\
    $(DESTDIRJAVAEXAMPLES)$/ConverterServlet$/web.xml	\
    $(DESTDIRJAVAEXAMPLES)$/ConverterServlet$/Makefile			\
    $(DESTDIRJAVAEXAMPLES)$/ConverterServlet$/README

INSPECTOR_FILES= \
    $(DESTDIRJAVAEXAMPLES)$/Inspector$/Inspector.jpg \
    $(DESTDIRJAVAEXAMPLES)$/Inspector$/InspectorThumbnail.jpg \
    $(DESTDIRJAVAEXAMPLES)$/Inspector$/Inspector.uno.xml \
    $(DESTDIRJAVAEXAMPLES)$/Inspector$/Inspector.java \
    $(DESTDIRJAVAEXAMPLES)$/Inspector$/Makefile \
    $(DESTDIRJAVAEXAMPLES)$/Inspector$/TestInspector.java \
    $(DESTDIRJAVAEXAMPLES)$/Inspector$/XInstanceInspector.idl \
    $(DESTDIRJAVAEXAMPLES)$/Inspector$/InstanceInspector.idl \
    $(DESTDIRJAVAEXAMPLES)$/Inspector$/InstanceInspectorTest.odt

NOTESACCESS_FILES= \
    $(DESTDIRJAVAEXAMPLES)$/NotesAccess$/NotesAccess.java \
    $(DESTDIRJAVAEXAMPLES)$/NotesAccess$/Makefile \
    $(DESTDIRJAVAEXAMPLES)$/NotesAccess$/Stocks.nsf

TODO_FILES= \
    $(DESTDIRJAVAEXAMPLES)$/ToDo$/ToDo.java \
    $(DESTDIRJAVAEXAMPLES)$/ToDo$/ToDo.ods  \
    $(DESTDIRJAVAEXAMPLES)$/ToDo$/ToDo.uno.xml  \
    $(DESTDIRJAVAEXAMPLES)$/ToDo$/ToDo.idl  \
    $(DESTDIRJAVAEXAMPLES)$/ToDo$/XToDo.idl  \
    $(DESTDIRJAVAEXAMPLES)$/ToDo$/Makefile

MINIMALCOMPONENT_FILES= \
    $(DESTDIRJAVAEXAMPLES)$/MinimalComponent$/MinimalComponent.idl \
    $(DESTDIRJAVAEXAMPLES)$/MinimalComponent$/MinimalComponent.java\
    $(DESTDIRJAVAEXAMPLES)$/MinimalComponent$/MinimalComponent.uno.xml \
    $(DESTDIRJAVAEXAMPLES)$/MinimalComponent$/TestMinimalComponent.java\
    $(DESTDIRJAVAEXAMPLES)$/MinimalComponent$/Makefile

PROPERTYSET_FILES= \
    $(DESTDIRJAVAEXAMPLES)$/PropertySet$/PropTest.java \
    $(DESTDIRJAVAEXAMPLES)$/PropertySet$/PropertySet.odt \
    $(DESTDIRJAVAEXAMPLES)$/PropertySet$/Makefile

DIR_FILE_LIST= \
    $(DRAWING_FILES) \
    $(SPREADSHEET_FILES) \
    $(TEXT_FILES) \
    $(DOCUMENTHANDLING_FILES) \
    $(CONVERTERSERVLET_FILES) \
    $(INSPECTOR_FILES) \
    $(NOTESACCESS_FILES) \
    $(TODO_FILES) \
    $(MINIMALCOMPONENT_FILES) \
    $(PROPERTYSET_FILES)

DIR_DIRECTORY_LIST=$(uniq $(DIR_FILE_LIST:d))
DIR_CREATE_FLAG=$(MISC)$/ex_java_dirs_created.txt
DIR_FILE_FLAG=$(MISC)$/ex_java_files.txt

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


