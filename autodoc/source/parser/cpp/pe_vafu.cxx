/*************************************************************************
 *
 *  $RCSfile: pe_vafu.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: obo $ $Date: 2005-01-27 11:25:37 $
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
#include "pe_vafu.hxx"


// NOT FULLY DEFINED SERVICES
#include <cosv/template/tpltools.hxx>
#include <ary/cpp/c_rwgate.hxx>
#include <ary/cpp/inpcontx.hxx>
#include <ary/cpp/c_class.hxx>
#include <ary/cpp/c_vari.hxx>
#include <ary/cpp/c_vfflag.hxx>
#include "pe_type.hxx"
#include "pe_vari.hxx"
#include "pe_funct.hxx"
#include "pe_ignor.hxx"
#include <x_parse.hxx>




namespace cpp {



//***********************		PE_VarFunc		***********************//


PE_VarFunc::PE_VarFunc( Cpp_PE * i_pParent )
    :   Cpp_PE(i_pParent),
        pStati( new PeStatusArray<PE_VarFunc> ),
        // pSpType,
        // pSpuType,
        // pSpVariable,
        // pSpuVariable,
        // pSpFunction,
        // pSpuFunctionStd,
        // pSpuFunctionCtor,
        // pSpuFunctionDtor,
        // pSpuFunctionCastOperator,
        // pSpuFunctionNormalOperator
        // pSpIgnore,
        // pSpuIgnore,
        nCounter_TemplateBrackets(0),
        bInDestructor(false),
        // aResultIds,
        nResultFrontType(0),
        eResultType(result_unknown),
        bVirtual(false),
        bStatic(false),
        bExtern(false),
        bExternC(false),
        bMutable(false),
        bInline(false),
        bRegister(false),
        bExplicit(false)
{
    Setup_StatusFunctions();

    pSpType             = new SP_Type(*this);
    pSpuType            = new SPU_Type(*pSpType, 0, &PE_VarFunc::SpReturn_Type);
    pSpVariable         = new SP_Variable(*this);
    pSpuVariable        = new SPU_Variable(*pSpVariable, 0, &PE_VarFunc::SpReturn_Variable);
    pSpFunction         = new SP_Function(*this);
    pSpuFunctionStd     = new SPU_Function(*pSpFunction, &PE_VarFunc::SpInit_FunctionStd, &PE_VarFunc::SpReturn_FunctionStd);
    pSpuFunctionCtor    = new SPU_Function(*pSpFunction, &PE_VarFunc::SpInit_FunctionCtor, &PE_VarFunc::SpReturn_FunctionStd);
    pSpuFunctionDtor    = new SPU_Function(*pSpFunction, &PE_VarFunc::SpInit_FunctionDtor, &PE_VarFunc::SpReturn_FunctionStd);
    pSpuFunctionCastOperator
                        = new SPU_Function(*pSpFunction, &PE_VarFunc::SpInit_FunctionCastOperator, &PE_VarFunc::SpReturn_FunctionStd);
    pSpuFunctionNormalOperator
                        = new SPU_Function(*pSpFunction, &PE_VarFunc::SpInit_FunctionNormalOperator, &PE_VarFunc::SpReturn_FunctionStd);
    pSpIgnore           = new SP_Ignore(*this);
    pSpuIgnore          = new SPU_Ignore(*pSpIgnore, 0, &PE_VarFunc::SpReturn_Ignore);
}

PE_VarFunc::~PE_VarFunc()
{
}

void
PE_VarFunc::Call_Handler( const cpp::Token & i_rTok )
{
    pStati->Cur().Call_Handler(i_rTok.TypeId(), i_rTok.Text());
}

void
PE_VarFunc::Setup_StatusFunctions()
{
    typedef CallFunction<PE_VarFunc>::F_Tok	F_Tok;

    static F_Tok stateF_start[] =			{ &PE_VarFunc::On_start_Identifier,
                                              &PE_VarFunc::On_start_operator,
                                              &PE_VarFunc::On_start_TypeKey,
                                              &PE_VarFunc::On_start_TypeKey,
                                              &PE_VarFunc::On_start_TypeKey,
                                              &PE_VarFunc::On_start_TypeKey,
                                              &PE_VarFunc::On_start_virtual,
                                              &PE_VarFunc::On_start_Tilde,
                                              &PE_VarFunc::On_start_const,
                                              &PE_VarFunc::On_start_volatile,
                                              &PE_VarFunc::On_start_extern,
                                              &PE_VarFunc::On_start_static,
                                              &PE_VarFunc::On_start_mutable,
                                              &PE_VarFunc::On_start_register,
                                              &PE_VarFunc::On_start_inline,
                                              &PE_VarFunc::On_start_explicit,
                                              &PE_VarFunc::On_start_Bracket_Right,
                                              &PE_VarFunc::On_start_Identifier,
                                              &PE_VarFunc::On_start_Identifier,
                                              &PE_VarFunc::On_start_Identifier,
                                              &PE_VarFunc::On_start_typename };
    static INT16 stateT_start[] =       	{ Tid_Identifier,
                                              Tid_operator,
                                              Tid_class,
                                              Tid_struct,
                                              Tid_union,
                                              Tid_enum,
                                              Tid_virtual,
                                              Tid_Tilde,
                                              Tid_const,
                                              Tid_volatile,
                                              Tid_extern,
                                              Tid_static,
                                              Tid_mutable,
                                              Tid_register,
                                              Tid_inline,
                                              Tid_explicit,
                                              Tid_Bracket_Right,
                                              Tid_DoubleColon,
                                              Tid_BuiltInType,
                                              Tid_TypeSpecializer,
                                              Tid_typename };

    static F_Tok stateF_expectCtor[] =		{ &PE_VarFunc::On_expectCtor_Bracket_Left };
    static INT16 stateT_expectCtor[] =     	{ Tid_Bracket_Left };

    static F_Tok stateF_afterClassDecl[] =	{ &PE_VarFunc::On_afterClassDecl_Semicolon };
    static INT16 stateT_afterClassDecl[] =  { Tid_Semicolon };

    static F_Tok stateF_expectName[] =		{ &PE_VarFunc::On_expectName_Identifier,
                                              &PE_VarFunc::On_expectName_operator,
                                              &PE_VarFunc::On_expectName_Bracket_Left };
    static INT16 stateT_expectName[] =     	{ Tid_Identifier,
                                              Tid_operator,
                                              Tid_Bracket_Left };

    static F_Tok stateF_afterName[] =		{ &PE_VarFunc::On_afterName_ArrayBracket_Left,
                                              &PE_VarFunc::On_afterName_Bracket_Left,
                                              &PE_VarFunc::On_afterName_DoubleColon,
                                              &PE_VarFunc::On_afterName_Semicolon,
                                              &PE_VarFunc::On_afterName_Comma,
                                              &PE_VarFunc::On_afterName_Assign,
                                              &PE_VarFunc::On_afterName_Less };
    static INT16 stateT_afterName[] =     	{ Tid_ArrayBracket_Left,
                                              Tid_Bracket_Left,
                                              Tid_DoubleColon,
                                              Tid_Semicolon,
                                              Tid_Comma,
                                              Tid_Assign,
                                              Tid_Less };

    static F_Tok stateF_afterName_inErraneousTemplate[] =
                                            { &PE_VarFunc::On_afterName_inErraneousTemplate_Less,
                                              &PE_VarFunc::On_afterName_inErraneousTemplate_Greater };
    static INT16 stateT_afterName_inErraneousTemplate[] =
                                            { Tid_Less,
                                              Tid_Greater };

    static F_Tok stateF_finished[] =		{ &PE_VarFunc::On_finished_Semicolon,
                                              &PE_VarFunc::On_finished_Comma };
    static INT16 stateT_finished[] =     	{ Tid_Semicolon,
                                              Tid_Comma };

    static F_Tok stateF_finishedIncludingFunctionImplementation[] =
                                            { &PE_VarFunc::On_finishedIncludingFunctionImplementation_Default
                                            };
    static INT16 stateT_finishedIncludingFunctionImplementation[] =
                                            { Tid_BuiltInType     // Just to have one entry, but it is default handled, too.
                                            };

    SEMPARSE_CREATE_STATUS(PE_VarFunc, start, Hdl_UnknownToken);
    SEMPARSE_CREATE_STATUS(PE_VarFunc, expectCtor, Hdl_UnknownToken);
    SEMPARSE_CREATE_STATUS(PE_VarFunc, afterClassDecl, Hdl_UnknownToken);
    SEMPARSE_CREATE_STATUS(PE_VarFunc, expectName, Hdl_UnknownToken);
    SEMPARSE_CREATE_STATUS(PE_VarFunc, afterName, Hdl_UnknownToken);
    SEMPARSE_CREATE_STATUS(PE_VarFunc, afterName_inErraneousTemplate, On_afterName_inErraneousTemplate_Default);
    SEMPARSE_CREATE_STATUS(PE_VarFunc, finished, On_finished_Default);
    SEMPARSE_CREATE_STATUS(PE_VarFunc, finishedIncludingFunctionImplementation, On_finishedIncludingFunctionImplementation_Default);
}

void
PE_VarFunc::InitData()
{
    pStati->SetCur(start);
    csv::erase_container(aResultIds);

    nCounter_TemplateBrackets = 0;
    bInDestructor = false;

    nResultFrontType = 0;
    eResultType = result_unknown;
    sName.clear();
    bVirtual = ary::cpp::VIRTUAL_none;
    bStatic = false;
    bExtern = false;
    bExternC = false;
    bMutable = false;
    bInline = false;
    bRegister = false;
    bExplicit = false;
}

void
PE_VarFunc::TransferData()
{
    pStati->SetCur(size_of_states);
}

void
PE_VarFunc::Hdl_UnknownToken( const char *)
{
    pSpuIgnore->Push(not_done);
}

void
PE_VarFunc::SpInit_FunctionStd()
{
    if ( nResultFrontType != 0 AND sName.length() > 0 )
    {
        pSpuFunctionStd->Child().Init_Std(
                                       sName,
                                       nResultFrontType,
                                       bVirtual,
                                       CreateFunctionFlags() );
    }
    else
    {
        throw X_Parser( X_Parser::x_UnexpectedToken,
                        "",
                        Env().CurFileName(),
                        Env().LineCount() );
    }
}

void
PE_VarFunc::SpInit_FunctionCtor()
{
    ary::cpp::Class * pOwnerClass = Env().Context().CurClass();
    csv_assert( pOwnerClass != 0 );
    pSpuFunctionStd->Child().Init_Ctor( pOwnerClass->LocalName(),
                                        CreateFunctionFlags() );
}

void
PE_VarFunc::SpInit_FunctionDtor()
{
    pSpuFunctionStd->Child().Init_Dtor( sName,
                                        bVirtual,
                                        CreateFunctionFlags() );
}

void
PE_VarFunc::SpInit_FunctionCastOperator()
{
    pSpuFunctionStd->Child().Init_CastOperator( bVirtual,
                                                CreateFunctionFlags() );
}

void
PE_VarFunc::SpInit_FunctionNormalOperator()
{
    pSpuFunctionStd->Child().Init_NormalOperator( nResultFrontType,
                                                  bVirtual,
                                                  CreateFunctionFlags() );
}

void
PE_VarFunc::SpReturn_Type()
{
    switch ( pSpuType->Child().Result_KindOf() )
    {
        case PE_Type::is_type:
                            pStati->SetCur(expectName);
                            nResultFrontType
                                    = pSpuType->Child().Result_Type().Id();
                            break;
        case PE_Type::is_constructor:
                            pStati->SetCur(expectCtor);
                            eResultType = result_function;
                            break;
        case PE_Type::is_explicit_class_declaration:
        case PE_Type::is_explicit_enum_declaration:
                            pStati->SetCur(afterClassDecl);
                            eResultType = result_ignore;
                            break;
        case PE_Type::is_class_predeclaration:
                            pStati->SetCur(afterClassDecl);
                            eResultType = result_ignore;
                            break;
        default:
                            ;
    }
}

void
PE_VarFunc::SpReturn_Variable()
{
    typedef ary::cpp::VariableFlags  VarFlags;

    if ( NOT bExtern )
    {
        VarFlags aFlags( UINT16(0)
                         | ( bStatic AND Env().Context().CurClass() == 0 ? VarFlags::f_static_local : 0 )
                         | ( bStatic AND Env().Context().CurClass() != 0 ? VarFlags::f_static_member : 0 )
                         | ( bMutable  ? VarFlags::f_mutable : 0 )
                       );

//      ary::S_InitData aData( 0, Env().CurCeSpace().Id(), i_sName, 0 );
        ary::cpp::Variable & rCurParsedVariable
                = Env().AryGate().Store_Variable(	Env().Context(),
                                                    sName,
                                                    nResultFrontType,
                                                    aFlags,
                                                    pSpuVariable->Child().Result_SizeExpression(),
                                                    pSpuVariable->Child().Result_InitExpression() );
        Env().Event_Store_Variable(rCurParsedVariable);
        aResultIds.push_back( rCurParsedVariable.Id() );
        eResultType = result_variable;
    }
    else if (bExtern)
    {
        eResultType = result_ignore;
    }

    pStati->SetCur(finished);
}

void
PE_VarFunc::SpReturn_FunctionStd()
{
    if ( (NOT bExtern) OR bExternC )
    {
        aResultIds.push_back(pSpuFunctionStd->Child().Result_Id());
        eResultType = result_function;
    }
    else
    {
        eResultType = result_ignore;
    }

    if ( NOT pSpuFunctionStd->Child().Result_WithImplementation() )
        pStati->SetCur(finished);
    else
        pStati->SetCur(finishedIncludingFunctionImplementation);
}

void
PE_VarFunc::SpReturn_Ignore()
{
    pStati->SetCur(finished);
}

void
PE_VarFunc::On_start_Identifier(const char * i_sText)
{
    pSpuType->Push(not_done);
}

void
PE_VarFunc::On_start_operator(const char * i_sText)
{
    pSpuFunctionCastOperator->Push(done);
}

void
PE_VarFunc::On_start_TypeKey(const char * i_sText)
{
    pSpuType->Push(not_done);
}

void
PE_VarFunc::On_start_virtual(const char * i_sText)
{
    SetTokenResult(done, stay);
    bVirtual = true;
}

void
PE_VarFunc::On_start_Tilde(const char * i_sText)
{
    SetTokenResult(done, stay);
    pStati->SetCur(expectName);

    bInDestructor = true;
}

void
PE_VarFunc::On_start_const(const char * i_sText)
{
    pSpuType->Push(not_done);
}

void
PE_VarFunc::On_start_volatile(const char * i_sText)
{
    pSpuType->Push(not_done);
}

void
PE_VarFunc::On_start_extern(const char * i_sText)
{
    SetTokenResult(done, stay);
    bExtern = true;
}

void
PE_VarFunc::On_start_static(const char * i_sText)
{
    SetTokenResult(done, stay);
    bStatic = true;
}

void
PE_VarFunc::On_start_mutable(const char * i_sText)
{
    SetTokenResult(done, stay);
    bMutable = true;
}

void
PE_VarFunc::On_start_register(const char * i_sText)
{
    SetTokenResult(done, stay);
    bRegister = true;
}

void
PE_VarFunc::On_start_inline(const char * i_sText)
{
       SetTokenResult(done, stay);

    bInline = true;
}

void
PE_VarFunc::On_start_explicit(const char * i_sText)
{
    SetTokenResult(done, stay);
    bExplicit = true;
}

void
PE_VarFunc::On_start_Bracket_Right(const char * i_sText)
{
    SetTokenResult(not_done, pop_success);
}

void
PE_VarFunc::On_start_typename(const char * i_sText)
{
    pSpuType->Push(not_done);
}

void
PE_VarFunc::On_expectCtor_Bracket_Left(const char * i_sText)
{
    pSpuFunctionCtor->Push(not_done);
}

void
PE_VarFunc::On_afterClassDecl_Semicolon(const char * i_sText)
{
    SetTokenResult(done, pop_success);
}

void
PE_VarFunc::On_expectName_Identifier(const char * i_sText)
{
    SetTokenResult(done, stay);
    pStati->SetCur(afterName);
    sName = i_sText;
}

void
PE_VarFunc::On_expectName_operator(const char * i_sText)
{
    pSpuFunctionNormalOperator->Push(done);
}

void
PE_VarFunc::On_expectName_Bracket_Left(const char * i_sText)
{
    // Function pointer declaration
    pSpuIgnore->Push(not_done);
    // TODO
}


void
PE_VarFunc::On_afterName_ArrayBracket_Left(const char * i_sText)
{
    pSpuVariable->Push(not_done);
}

void
PE_VarFunc::On_afterName_Bracket_Left(const char * i_sText)
{
    if ( NOT bInDestructor)
        pSpuFunctionStd->Push(not_done);
    else
        pSpuFunctionDtor->Push(not_done);
}

void
PE_VarFunc::On_afterName_DoubleColon(const char * i_sText)
{
    pSpuIgnore->Push(done);   // This seems to be only an implementation.

    // This may have been a template.
    // In that case, the declaration needs to be closed.
    Env().Close_OpenTemplate();
}

void
PE_VarFunc::On_afterName_Semicolon(const char * i_sText)
{
    pSpuVariable->Push(not_done);
}

void
PE_VarFunc::On_afterName_Comma(const char * i_sText)
{
    pSpuVariable->Push(not_done);
}

void
PE_VarFunc::On_afterName_Assign(const char * )
{
    pSpuVariable->Push(not_done);
}

void
PE_VarFunc::On_afterName_Less(const char * )
{
    SetTokenResult(done, stay);
    pStati->SetCur(afterName_inErraneousTemplate);

    nCounter_TemplateBrackets = 1;
}

void
PE_VarFunc::On_afterName_inErraneousTemplate_Less(const char * )
{
    SetTokenResult(done, stay);

    nCounter_TemplateBrackets++;
}

void
PE_VarFunc::On_afterName_inErraneousTemplate_Greater(const char * )
{
    SetTokenResult(done, stay);

    nCounter_TemplateBrackets--;
    if ( nCounter_TemplateBrackets == 0 )
        pStati->SetCur(afterName);
}

void
PE_VarFunc::On_afterName_inErraneousTemplate_Default(const char * )
{
    SetTokenResult(done, stay);
}

void
PE_VarFunc::On_finished_Semicolon(const char * )  // Should be Semicolon !!!
{
    SetTokenResult(done, pop_success);
}

void
PE_VarFunc::On_finished_Comma(const char * )
{
    SetTokenResult(done, stay);
    pStati->SetCur(expectName);
}

void
PE_VarFunc::On_finished_Default(const char * )
{
    SetTokenResult(not_done, pop_success);
}

void
PE_VarFunc::On_finishedIncludingFunctionImplementation_Default(const char * )
{
    SetTokenResult(not_done, pop_success);
}

ary::cpp::FunctionFlags
PE_VarFunc::CreateFunctionFlags()
{
    typedef ary::cpp::FunctionFlags  FuncFlags;

    return FuncFlags(     UINT16(0)
                          | ( bStatic AND Env().Context().CurClass() == 0 ? FuncFlags::f_static_local : 0 )
                          | ( bStatic AND Env().Context().CurClass() != 0 ? FuncFlags::f_static_member : 0 )
                          | ( bExtern ? FuncFlags::f_extern : 0 )
                          | ( Env().IsExternC() ? FuncFlags::f_externC : 0 )
                          | ( bMutable  ? FuncFlags::f_mutable : 0 )
                          | ( bInline  ? FuncFlags::f_inline : 0 )
                          | ( bRegister  ? FuncFlags::f_register : 0 )
                          | ( bExplicit  ? FuncFlags::f_explicit : 0 )
                        );

}


}   // namespace cpp



