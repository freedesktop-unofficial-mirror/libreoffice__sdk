/*************************************************************************
 *
 *  $RCSfile: pe_selem.cxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: np $ $Date: 2002-03-08 14:45:34 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/

#include <precomp.h>
#include <s2_luidl/pe_selem.hxx>

// NOT FULLY DECLARED SERVICES
#include <ary_i/codeinf2.hxx>
#include <s2_luidl/pe_type2.hxx>
#include <s2_luidl/tk_ident.hxx>
#include <s2_luidl/tk_punct.hxx>
#include <csi/l_uidl/struelem.hxx>


namespace csi
{
namespace uidl
{


PE_StructElement::PE_StructElement( RStructElement &	o_rResult,
                                    const RStruct &		i_rCurStruct )
    :	eState(e_none),
        pResult(&o_rResult),
        pCurStruct(&i_rCurStruct),
        pPE_Type(0),
        pType(0)
        // sName
{
    pPE_Type = new PE_Type(pType);
}

void
PE_StructElement::EstablishContacts( UnoIDL_PE *				io_pParentPE,
                                     ary::Repository &			io_rRepository,
                                     TokenProcessing_Result & 	o_rResult )
{
    UnoIDL_PE::EstablishContacts(io_pParentPE,io_rRepository,o_rResult);
    pPE_Type->EstablishContacts(this,io_rRepository,o_rResult);
}

PE_StructElement::~PE_StructElement()
{
}

void
PE_StructElement::ProcessToken( const Token & i_rToken )
{
    i_rToken.Trigger(*this);
}


void
PE_StructElement::Process_Default()
{
    if (eState == expect_type)
    {
        SetResult( not_done, push_sure, pPE_Type.Ptr() );
        eState = expect_name;
    }
    else
        csv_assert(false);
}

void
PE_StructElement::Process_Identifier( const TokIdentifier & i_rToken )
{
    if (eState == expect_type)
    {
        SetResult( not_done, push_sure, pPE_Type.Ptr() );
        eState = expect_name;
    }
    else if (eState == expect_name)
    {
        sName = i_rToken.Text();
        SetResult( done, stay );
        eState = expect_finish;
    }
    else
        csv_assert(false);
}

void
PE_StructElement::Process_Punctuation( const TokPunctuation & i_rToken )
{
    if (eState == expect_finish)
    {
        SetResult( done, pop_success );
    }
    else
        csv_assert(false);
}

void
PE_StructElement::InitData()
{
    eState = expect_type;

    pType = 0;
    sName = "";
}

void
PE_StructElement::TransferData()
{
    DYN StructElement * pNew = new StructElement;
    pNew->Data().pType = pType;
    pNew->Data().sName = sName;

    csv_assert(pResult != 0 AND pCurStruct != 0);
    *pResult = Gate().Store_StructElement( pCurStruct->Id(), *pNew );
    PassDocuAt(pResult->Id());

    eState = e_none;
}

UnoIDL_PE &
PE_StructElement::MyPE()
{
    return *this;
}

}   // namespace uidl
}   // namespace csi

