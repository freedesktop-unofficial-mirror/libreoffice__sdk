/*************************************************************************
 *
 *  $RCSfile: pe_namsp.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: np $ $Date: 2002-05-14 09:02:19 $
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
#include <pe_namsp.hxx>


// NOT FULLY DECLARED SERVICES
#include <all_toks.hxx>
#include <ary/cpp/c_namesp.hxx>
#include <ary/cpp/c_rwgate.hxx>
#include <semantic/callf.hxx>


namespace cpp {

PE_Namespace::PE_Namespace( Cpp_PE * i_pParent )
    :   Cpp_PE(i_pParent),
        pStati( new PeStatusArray<PE_Namespace> ),
        // sLocalname
        bPush(false)
{
    Setup_StatusFunctions();
}

PE_Namespace::~PE_Namespace()
{
}

void
PE_Namespace::Setup_StatusFunctions()
{
    typedef CallFunction<PE_Namespace>::F_Tok	F_Tok;
    static F_Tok stateF_start[] =			{ &PE_Namespace::On_start_Identifier };
    static INT16 stateT_start[] =      		{ Tid_Identifier };
    static F_Tok stateF_gotName[] =			{ &PE_Namespace::On_gotName_SwBracket_Left,
                                              &PE_Namespace::On_gotName_Assign };
    static INT16 stateT_gotName[] =      	{ Tid_SwBracket_Left,
                                              Tid_Assign };
    static F_Tok stateF_expectSemicolon[] =	{ &PE_Namespace::On_expectSemicolon_Semicolon };
    static INT16 stateT_expectSemicolon[] = { Tid_Semicolon };

    SEMPARSE_CREATE_STATUS(PE_Namespace, start, Hdl_SyntaxError);
    SEMPARSE_CREATE_STATUS(PE_Namespace, gotName, Hdl_SyntaxError);
    SEMPARSE_CREATE_STATUS(PE_Namespace, expectSemicolon, Hdl_SyntaxError);
}

void
PE_Namespace::Call_Handler( const cpp::Token &	i_rTok )
{
    pStati->Cur().Call_Handler(i_rTok.TypeId(), i_rTok.Text());
}

void
PE_Namespace::InitData()
{
    pStati->SetCur(start);
    sLocalName = "";
    bPush = false;
}

void
PE_Namespace::TransferData()
{
    if (bPush)
    {
        ary::cpp::Namespace & rNew
                = Env().AryGate().CheckIn_Namespace( Env().Context(), sLocalName );
        Env().OpenNamespace(rNew);
    }
}

void
PE_Namespace::Hdl_SyntaxError( const char *)
{
    csv_assert(false);
}

void
PE_Namespace::On_start_Identifier(const char * i_sText)
{
    SetTokenResult(done, stay);
    pStati->SetCur(gotName);

    sLocalName = i_sText;
}

void
PE_Namespace::On_gotName_SwBracket_Left(const char * )
{
    SetTokenResult(done, pop_success);
    pStati->SetCur(size_of_states);

    bPush = true;
}

void
PE_Namespace::On_gotName_Assign(const char * )
{
    // KORR
    Hdl_SyntaxError(0);
}

void
PE_Namespace::On_expectSemicolon_Semicolon(const char * )
{
    SetTokenResult(done,pop_success);
    pStati->SetCur(size_of_states);
}

}   // namespace cpp




