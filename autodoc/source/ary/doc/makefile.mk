#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.2 $
#
#   last change: $Author: hr $ $Date: 2007-11-02 15:42:01 $
#
#   The Contents of this file are made available subject to
#   the terms of GNU Lesser General Public License Version 2.1.
#
#
#     GNU Lesser General Public License Version 2.1
#     =============================================
#     Copyright 2005 by Sun Microsystems, Inc.
#     901 San Antonio Road, Palo Alto, CA 94303, USA
#
#     This library is free software; you can redistribute it and/or
#     modify it under the terms of the GNU Lesser General Public
#     License version 2.1, as published by the Free Software Foundation.
#
#     This library is distributed in the hope that it will be useful,
#     but WITHOUT ANY WARRANTY; without even the implied warranty of
#     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#     Lesser General Public License for more details.
#
#     You should have received a copy of the GNU Lesser General Public
#     License along with this library; if not, write to the Free Software
#     Foundation, Inc., 59 Temple Place, Suite 330, Boston,
#     MA  02111-1307  USA
#
#*************************************************************************

PRJ=..$/..$/..

PRJNAME=autodoc
TARGET=ary_doc



# --- Settings -----------------------------------------------------

ENABLE_EXCEPTIONS=true
PRJINC=$(PRJ)$/source

.INCLUDE :  settings.mk
.INCLUDE : $(PRJ)$/source$/mkinc$/fullcpp.mk



# --- Files --------------------------------------------------------


OBJFILES= \
    $(OBJ)$/d_boolean.obj           \
    $(OBJ)$/d_docu.obj              \
    $(OBJ)$/d_hypertext.obj         \
    $(OBJ)$/d_namedlist.obj         \
    $(OBJ)$/d_node.obj              \
    $(OBJ)$/d_oldcppdocu.obj        \
    $(OBJ)$/d_oldidldocu.obj        \
    $(OBJ)$/d_summary.obj           \
    $(OBJ)$/d_struct.obj            \
    $(OBJ)$/d_unit.obj              \
    $(OBJ)$/dht_component.obj       \
    $(OBJ)$/dht_helper.obj          \
    $(OBJ)$/dht_html.obj            \
    $(OBJ)$/dht_link2ce.obj         \
    $(OBJ)$/dht_link2param.obj      \
    $(OBJ)$/dht_link2unknown.obj    \
    $(OBJ)$/dht_link2url.obj        \
    $(OBJ)$/dht_plain.obj           \
    $(OBJ)$/dht_stream.obj          \
    $(OBJ)$/dht_white.obj



# --- Targets ------------------------------------------------------

.INCLUDE :  target.mk
