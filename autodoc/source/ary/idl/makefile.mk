#*************************************************************************
#
#   OpenOffice.org - a multi-platform office productivity suite
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.5 $
#
#   last change: $Author: rt $ $Date: 2005-09-07 16:56:51 $
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
TARGET=ary_idl


# --- Settings -----------------------------------------------------

ENABLE_EXCEPTIONS=true
PRJINC=$(PRJ)$/source

.INCLUDE :  settings.mk
.INCLUDE : $(PRJ)$/source$/mkinc$/fullcpp.mk


# --- Files --------------------------------------------------------


OBJFILES= \
    $(OBJ)$/i_attribute.obj     \
    $(OBJ)$/i_ce.obj            \
    $(OBJ)$/i_ce2s.obj          \
    $(OBJ)$/i_comrela.obj       \
    $(OBJ)$/i_constant.obj      \
    $(OBJ)$/i_constgroup.obj    \
    $(OBJ)$/i_enum.obj          \
    $(OBJ)$/i_enumvalue.obj     \
    $(OBJ)$/i_exception.obj     \
    $(OBJ)$/i_function.obj      \
    $(OBJ)$/i_interface.obj     \
    $(OBJ)$/i_module.obj        \
    $(OBJ)$/i_namelookup.obj    \
    $(OBJ)$/i_param.obj         \
    $(OBJ)$/i_property.obj      \
    $(OBJ)$/i_reposypart.obj    \
    $(OBJ)$/i_service.obj       \
    $(OBJ)$/i_singleton.obj     \
    $(OBJ)$/i_siservice.obj     \
    $(OBJ)$/i_sisingleton.obj   \
    $(OBJ)$/i_strconst.obj      \
    $(OBJ)$/i_struct.obj        \
    $(OBJ)$/i_structelem.obj    \
    $(OBJ)$/i_typedef.obj       \
    $(OBJ)$/ihost_ce.obj        \
    $(OBJ)$/ii_gate.obj         \
    $(OBJ)$/ipi_ce.obj          \
    $(OBJ)$/ipi_type.obj        \
    $(OBJ)$/ipi_2s.obj          \
    $(OBJ)$/is_ce.obj           \
    $(OBJ)$/is_ce_indices.obj   \
    $(OBJ)$/is_type.obj         \
    $(OBJ)$/is_type_indices.obj \
    $(OBJ)$/it_builtin.obj      \
    $(OBJ)$/it_ce.obj           \
    $(OBJ)$/it_explicit.obj     \
    $(OBJ)$/it_sequence.obj     \
    $(OBJ)$/it_tplparam.obj     \
    $(OBJ)$/it_xnameroom.obj



# --- Targets ------------------------------------------------------

.INCLUDE :  target.mk
