#*************************************************************************
#
# DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
# 
# Copyright 2008 by Sun Microsystems, Inc.
#
# OpenOffice.org - a multi-platform office productivity suite
#
# $RCSfile: makefile.mk,v $
#
# $Revision: 1.3 $
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

PRJNAME=autodoc
TARGET=display_toolkit


# --- Settings -----------------------------------------------------

ENABLE_EXCEPTIONS=true
PRJINC=$(PRJ)$/source

.INCLUDE :  settings.mk
.INCLUDE : $(PRJ)$/source$/mkinc$/fullcpp.mk


# --- Files --------------------------------------------------------

OBJFILES= \
    $(OBJ)$/hf_docentry.obj     \
    $(OBJ)$/hf_funcdecl.obj     \
    $(OBJ)$/hf_linachain.obj    \
    $(OBJ)$/hf_navi_main.obj    \
    $(OBJ)$/hf_navi_sub.obj     \
    $(OBJ)$/hf_title.obj     	\
    $(OBJ)$/htmlfile.obj        \
    $(OBJ)$/out_node.obj        \
    $(OBJ)$/out_position.obj    \
    $(OBJ)$/out_tree.obj        \
    $(OBJ)$/outputstack.obj


# --- Targets ------------------------------------------------------

.INCLUDE :  target.mk



