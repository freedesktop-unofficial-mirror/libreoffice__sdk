/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: hf_docentry.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: obo $ $Date: 2006-09-16 16:51:44 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/

// MARKER(update_precomp.py): autogen include statement, do not remove
#include "precompiled_autodoc.hxx"


#include <precomp.h>
#include <toolkit/hf_docentry.hxx>


// NOT FULLY DEFINED SERVICES


HF_DocEntryList::HF_DocEntryList( Xml::Element & o_out )
    :   HtmlMaker( o_out >>* new Html::DefList )
{
}

HF_DocEntryList::~HF_DocEntryList()
{
}

Xml::Element &
HF_DocEntryList::Produce_Term(const char * i_sTerm )
{
    Xml::Element &
        ret = CurOut()
           >> *new Html::DefListTerm
              >> *new Html::Bold;
    if ( NOT csv::no_str(i_sTerm))
        ret
            << i_sTerm;
    return ret;
}

Xml::Element &
HF_DocEntryList::Produce_NormalTerm(const char * i_sTerm)
{
    Xml::Element &
        ret = CurOut()
           >> *new Html::DefListTerm;
    if ( NOT csv::no_str(i_sTerm))
        ret
            << i_sTerm;
    return ret;
}

Xml::Element &
HF_DocEntryList::Produce_Definition()
{
    return CurOut()
           >> *new Html::DefListDefinition;
}
