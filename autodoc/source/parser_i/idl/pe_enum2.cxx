/*************************************************************************
 *
 *  $RCSfile: pe_enum2.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: np $ $Date: 2002-05-07 18:32:25 $
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
#include <s2_luidl/pe_enum2.hxx>


// NOT FULLY DECLARED SERVICES
#include <ary_i/codeinf2.hxx>
#include <s2_luidl/pe_evalu.hxx>
#include <s2_luidl/tk_punct.hxx>
#include <s2_luidl/tk_ident.hxx>
#include <s2_luidl/tk_keyw.hxx>
#include <csi/l_uidl/enum.hxx>
#include <csi/l_uidl/enumvalu.hxx>
#include <ary_i/uidl/gate.hxx>


namespace csi
{
namespace uidl
{


#ifdef DF
#undef DF
#endif
#define DF 	&PE_Enum::On_Default

PE_Enum::F_TOK
PE_Enum::aDispatcher[PE_Enum::e_STATES_MAX][PE_Enum::tt_MAX] =
        { 	{  DF, DF },  // e_none
            {  &PE_Enum::On_expect_name_Identifier,
                   DF },  // expect_name
            {  DF, &PE_Enum::On_expect_curl_bracket_open_Punctuation },  // expect_curl_bracket_open
            {  &PE_Enum::On_expect_value_Identifier,
                   &PE_Enum::On_expect_value_Punctuation },  // expect_value
            {  DF, &PE_Enum::On_expect_finish_Punctuation }  // expect_finish
        };



inline void
PE_Enum::CallHandler( const char *		i_sTokenText,
                          E_TokenType		i_eTokenType )
    { (this->*aDispatcher[eState][i_eTokenType])(i_sTokenText); }




PE_Enum::PE_Enum()
    :	eState(e_none),
        pData(0),
        pPE_Value(0)
        // sName
        // sAssignment
{
    pPE_Value = new PE_Value(sName, sAssignment, false);
}

void
PE_Enum::EstablishContacts( UnoIDL_PE *					io_pParentPE,
                                ary::Repository &			io_rRepository,
                                TokenProcessing_Result & 	o_rResult )
{
    UnoIDL_PE::EstablishContacts(io_pParentPE,io_rRepository,o_rResult);
    pPE_Value->EstablishContacts(this,io_rRepository,o_rResult);
}

PE_Enum::~PE_Enum()
{
}

void
PE_Enum::ProcessToken( const Token & i_rToken )
{
    i_rToken.Trigger(*this);
}

void
PE_Enum::Process_Identifier( const TokIdentifier & i_rToken )
{
    CallHandler(i_rToken.Text(), tt_identifier);
}

void
PE_Enum::Process_Punctuation( const TokPunctuation & i_rToken )
{
    CallHandler(i_rToken.Text(), tt_punctuation);
}

void
PE_Enum::On_expect_name_Identifier(const char * i_sText)
{
    sName = i_sText;

    SetResult(done,stay);
    eState = expect_curl_bracket_open;
}

void
PE_Enum::On_expect_curl_bracket_open_Punctuation(const char * i_sText)
{
    if ( i_sText[0] == '{')
    {
        pData = new Enum;
        pData->Data().sName = sName;
        nDataId = Gate().Store_Enum(CurNamespace().Id(),*pData).Id();
        PassDocuAt(nDataId);

        SetResult(done,stay);
        eState = expect_value;
    }
    else
    {
        On_Default(i_sText);
    }
}

void
PE_Enum::On_expect_value_Punctuation(const char * i_sText)
{
    if ( i_sText[0] == '}' )
    {
        SetResult(done,stay);
        eState = expect_finish;
    }
    else
    {
        On_Default(i_sText);
    }
}

void
PE_Enum::On_expect_value_Identifier(const char * i_sText)
{
    SetResult( not_done, push_sure, pPE_Value.Ptr() );
}

void
PE_Enum::On_expect_finish_Punctuation(const char * i_sText)
{
    if ( i_sText[0] == ';')
    {
        SetResult(done,pop_success);
        eState = e_none;
    }
    else
    {
        On_Default(i_sText);
    }
}

void
PE_Enum::On_Default(const char * )
{
    SetResult(not_done,pop_failure);
    eState = e_none;
}

void
PE_Enum::EmptySingleValueData()
{
    sName = "";
    sAssignment = "";
}

void
PE_Enum::CreateSingleValue()
{
    DYN EnumValue * dpValue = new EnumValue;

    dpValue->Data().sName = sName;
    dpValue->Data().sValue = sAssignment;

    ary::Cei nId = Gate().Store_EnumValue( nDataId, *dpValue ).Id();
    pPE_Value->PassDocuAt(nId);

    pData->Data().aValues.push_back(nId);
}

void
PE_Enum::InitData()
{
    eState = expect_name;

    pData = 0;
    nDataId = 0;

    EmptySingleValueData();
}

void
PE_Enum::ReceiveData()
{
    switch (eState)
    {
        case expect_value:
        {
                    if (sName.length() == 0)
                    {
                        On_Default("");
                        break;
                    }

                    CreateSingleValue();
                    EmptySingleValueData();
        }			break;
        default:
                    SetResult(not_done, pop_failure);
                    eState = e_none;
    }	// end switch
}

void
PE_Enum::TransferData()
{
    csv_assert(pData != 0);
    eState = e_none;
}

UnoIDL_PE &
PE_Enum::MyPE()
{
    return *this;
}

}   // namespace uidl
}   // namespace csi

