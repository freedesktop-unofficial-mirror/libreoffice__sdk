/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: pe_param.cxx,v $
 *
 *  $Revision: 1.6 $
 *
 *  last change: $Author: hr $ $Date: 2006-06-19 12:04:56 $
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


#include <precomp.h>
#include "pe_param.hxx"


// NOT FULLY DEFINED SERVICES
#include <cosv/template/tpltools.hxx>
#include <ary/cpp/c_rwgate.hxx>
#include "pe_type.hxx"
#include "pe_vari.hxx"


namespace cpp {



//***********************		PE_Parameter		***********************//


PE_Parameter::PE_Parameter( Cpp_PE * i_pParent )
    :   Cpp_PE(i_pParent),
        pStati( new PeStatusArray<PE_Parameter> )
        // pSpType,
        // pSpuType,
        // pSpVariable,
        // pSpuVariable,
        // aResultParamInfo
{
    Setup_StatusFunctions();

    pSpType         = new SP_Type(*this);
    pSpuType        = new SPU_Type(*pSpType, &PE_Parameter::SpInit_Type, &PE_Parameter::SpReturn_Type);
    pSpVariable     = new SP_Variable(*this);
    pSpuVariable    = new SPU_Variable(*pSpVariable, &PE_Parameter::SpInit_Variable, &PE_Parameter::SpReturn_Variable);
}

PE_Parameter::~PE_Parameter()
{
}

void
PE_Parameter::Call_Handler( const cpp::Token & i_rTok )
{
    pStati->Cur().Call_Handler(i_rTok.TypeId(), i_rTok.Text());
}

void
PE_Parameter::Setup_StatusFunctions()
{
    typedef CallFunction<PE_Parameter>::F_Tok	F_Tok;
    static F_Tok stateF_start[] =			{ &PE_Parameter::On_start_Type,
                                              &PE_Parameter::On_start_Type,
                                              &PE_Parameter::On_start_Type,
                                              &PE_Parameter::On_start_Type,
                                              &PE_Parameter::On_start_Type,

                                              &PE_Parameter::On_start_Type,
                                              &PE_Parameter::On_start_Type,
                                              &PE_Parameter::On_start_Bracket_Right,
                                              &PE_Parameter::On_start_Type,
                                              &PE_Parameter::On_start_Ellipse,

                                              &PE_Parameter::On_start_Type,
                                              &PE_Parameter::On_start_Type,
                                              &PE_Parameter::On_start_Type };
    static INT16 stateT_start[] =       	{ Tid_Identifier,
                                              Tid_class,
                                              Tid_struct,
                                              Tid_union,
                                              Tid_enum,

                                              Tid_const,
                                              Tid_volatile,
                                              Tid_Bracket_Right,
                                              Tid_DoubleColon,
                                              Tid_Ellipse,

                                              Tid_BuiltInType,
                                              Tid_TypeSpecializer,
                                              Tid_typename };

    static F_Tok stateF_expectName[] =		{ &PE_Parameter::On_expectName_Identifier,
                                              &PE_Parameter::On_expectName_ArrayBracket_Left,
                                              &PE_Parameter::On_expectName_Bracket_Right,
                                              &PE_Parameter::On_expectName_Comma,
                                              &PE_Parameter::On_afterName_Assign  };
    static INT16 stateT_expectName[] =     	{ Tid_Identifier,
                                              Tid_ArrayBracket_Left,
                                              Tid_Bracket_Right,
                                              Tid_Comma,
                                              Tid_Assign };
    static F_Tok stateF_afterName[] =		{ &PE_Parameter::On_afterName_ArrayBracket_Left,
                                              &PE_Parameter::On_afterName_Bracket_Right,
                                              &PE_Parameter::On_afterName_Comma,
                                              &PE_Parameter::On_afterName_Assign };
    static INT16 stateT_afterName[] =     	{ Tid_ArrayBracket_Left,
                                              Tid_Bracket_Right,
                                              Tid_Comma,
                                              Tid_Assign };
    static F_Tok stateF_finished[] =		{ &PE_Parameter::On_finished_Comma,
                                              &PE_Parameter::On_finished_Bracket_Right };
    static INT16 stateT_finished[] =     	{ Tid_Bracket_Right,
                                              Tid_Comma };

    SEMPARSE_CREATE_STATUS(PE_Parameter, start, Hdl_SyntaxError);
    SEMPARSE_CREATE_STATUS(PE_Parameter, expectName, Hdl_SyntaxError);
    SEMPARSE_CREATE_STATUS(PE_Parameter, afterName, Hdl_SyntaxError);
    SEMPARSE_CREATE_STATUS(PE_Parameter, finished, Hdl_SyntaxError);
}


void
PE_Parameter::InitData()
{
    pStati->SetCur(start);
    aResultParamInfo.Empty();
}

void
PE_Parameter::TransferData()
{
    pStati->SetCur(size_of_states);
}

void
PE_Parameter::Hdl_SyntaxError( const char * i_sText)
{
    StdHandlingOfSyntaxError(i_sText);
}

void
PE_Parameter::SpInit_Type()
{
    // Does nothing.
}

void
PE_Parameter::SpInit_Variable()
{
    // Does nothing.
}

void
PE_Parameter::SpReturn_Type()
{
    aResultParamInfo.nType = pSpuType->Child().Result_Type().Id();
    pStati->SetCur(expectName);
}

void
PE_Parameter::SpReturn_Variable()
{
    if (pSpuVariable->Child().Result_Pattern() > 0)
    {
        aResultParamInfo.sSizeExpression = pSpuVariable->Child().Result_SizeExpression();
        aResultParamInfo.sInitExpression = pSpuVariable->Child().Result_InitExpression();
    }
}

void
PE_Parameter::On_start_Type(const char *)
{
    pSpuType->Push(not_done);
}

void
PE_Parameter::On_start_Bracket_Right(const char *)
{
    SetTokenResult(not_done, pop_success);
}

void
PE_Parameter::On_start_Ellipse(const char *)
{
    SetTokenResult(done, pop_success);

    aResultParamInfo.nType = Env().AryGate().Tid_Ellipse();
}

void
PE_Parameter::On_expectName_Identifier(const char * i_sText)
{
    SetTokenResult(done, stay);
    pStati->SetCur(afterName);

    aResultParamInfo.sName = i_sText;
}

void
PE_Parameter::On_expectName_ArrayBracket_Left(const char * i_sText)
{
    On_afterName_ArrayBracket_Left(i_sText);
}

void
PE_Parameter::On_expectName_Bracket_Right(const char * i_sText)
{
    On_afterName_Bracket_Right(i_sText);
}

void
PE_Parameter::On_expectName_Comma(const char * i_sText)
{
    On_afterName_Comma(i_sText);
}

void
PE_Parameter::On_expectName_Assign(const char * i_sText)
{
    On_afterName_Assign(i_sText);
}

void
PE_Parameter::On_afterName_ArrayBracket_Left(const char *)
{
    pSpuVariable->Push(not_done);
}

void
PE_Parameter::On_afterName_Bracket_Right(const char *)
{
    SetTokenResult(not_done, pop_success);
}

void
PE_Parameter::On_afterName_Comma(const char *)
{
    SetTokenResult(not_done, pop_success);
}

void
PE_Parameter::On_afterName_Assign(const char *)
{
    pSpuVariable->Push(not_done);
}

void
PE_Parameter::On_finished_Bracket_Right(const char *)
{
    SetTokenResult(not_done, pop_success);
}

void
PE_Parameter::On_finished_Comma(const char *)
{
    SetTokenResult(not_done, pop_success);
}


}   // namespace cpp









