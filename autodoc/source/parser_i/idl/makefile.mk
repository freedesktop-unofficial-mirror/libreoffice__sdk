#*************************************************************************
#
#   $RCSfile: makefile.mk,v $
#
#   $Revision: 1.3 $
#
#   last change: $Author: rt $ $Date: 2004-07-12 15:39:59 $
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
#   WITHOUT WARRUNTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING,
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

PRJ=..$/..$/..

PRJNAME=autodoc
TARGET=parser2_s2_luidl


# --- Settings -----------------------------------------------------

ENABLE_EXCEPTIONS=true
PRJINC=$(PRJ)$/source

.INCLUDE :  settings.mk
.INCLUDE : $(PRJ)$/source$/mkinc$/fullcpp.mk



# --- Files --------------------------------------------------------


OBJFILES= \
    $(OBJ)$/cx_idlco.obj		\
    $(OBJ)$/cx_sub.obj		    \
    $(OBJ)$/distrib.obj		    \
    $(OBJ)$/parsenv2.obj		\
    $(OBJ)$/pe_attri.obj	    \
    $(OBJ)$/pe_const.obj	    \
    $(OBJ)$/pe_enum2.obj    	\
    $(OBJ)$/pe_evalu.obj	    \
    $(OBJ)$/pe_excp.obj		    \
    $(OBJ)$/pe_file2.obj	    \
    $(OBJ)$/pe_func2.obj	    \
    $(OBJ)$/pe_iface.obj	    \
    $(OBJ)$/pe_property.obj	    \
    $(OBJ)$/pe_selem.obj	    \
    $(OBJ)$/pe_servi.obj	    \
    $(OBJ)$/pe_singl.obj	    \
    $(OBJ)$/pe_struc.obj 	    \
    $(OBJ)$/pe_tydf2.obj 	    \
    $(OBJ)$/pe_type2.obj 	    \
    $(OBJ)$/pe_vari2.obj 	    \
    $(OBJ)$/pestate.obj 	    \
    $(OBJ)$/semnode.obj		    \
    $(OBJ)$/tk_const.obj		\
    $(OBJ)$/tk_ident.obj		\
    $(OBJ)$/tk_keyw.obj			\
    $(OBJ)$/tk_punct.obj		\
    $(OBJ)$/tkp_uidl.obj		\
    $(OBJ)$/unoidl.obj



# --- Targets ------------------------------------------------------

.INCLUDE :  target.mk



