/*************************************************************************
 *
 *  $RCSfile: pe_vafu.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: np $ $Date: 2002-03-08 14:45:31 $
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


#ifndef ADC_CPP_PE_VAFU_HXX
#define ADC_CPP_PE_VAFU_HXX



// USED SERVICES
    // BASE CLASSES
#include "cpp_pe.hxx"
    // COMPONENTS
#include <semantic/callf.hxx>
#include <semantic/sub_peu.hxx>
#include <ary/cpp/c_etypes.hxx>
#include <ary/cpp/c_vfflag.hxx>
    // PARAMETERS


namespace cpp {

class PE_Type;
class PE_Variable;
class PE_Function;
class PE_Ignore;


class PE_VarFunc : public Cpp_PE
{
  public:
    enum E_State
    {
        start,
        expectCtor,
        afterClassDecl,     // Also used for after enum declaration.
        expectName,
        afterName,
        afterName_inErraneousTemplate,
        finished,
        finishedIncludingFunctionImplementation,
        size_of_states
    };
    enum E_ResultType
    {
        result_unknown = 0,
        result_ignore,         	/// Used for class and enum declarations and predeclarations and for extern variables and functions.
        result_variable,
        result_function
    };

    typedef ary::cpp::E_Protection 				E_Protection;


                        PE_VarFunc(
                            Cpp_PE *			i_pParent );
                        ~PE_VarFunc();

    virtual void		Call_Handler(
                            const cpp::Token &	i_rTok );

    const std::vector<ary::Cid> &
                        Result_Ids() const;
    ary::Tid     	    Result_FrontType() const;
    const StringVector &
                        Result_Names() const;
    E_ResultType		Result_CeType() const;

  private:
    typedef SubPe< PE_VarFunc, PE_Type >		SP_Type;
    typedef SubPeUse< PE_VarFunc, PE_Type >		SPU_Type;
    typedef SubPe< PE_VarFunc, PE_Variable >	SP_Variable;
    typedef SubPeUse< PE_VarFunc, PE_Variable >	SPU_Variable;
    typedef SubPe< PE_VarFunc, PE_Function >	SP_Function;
    typedef SubPeUse< PE_VarFunc, PE_Function >	SPU_Function;
    typedef SubPe< PE_VarFunc, PE_Ignore >		SP_Ignore;
    typedef SubPeUse< PE_VarFunc, PE_Ignore >   SPU_Ignore;

    void				Setup_StatusFunctions();
    virtual void		InitData();
    virtual void		TransferData();
    void  				Hdl_UnknownToken( const char *);

    void				SpInit_FunctionStd();
    void				SpInit_FunctionCtor();
    void				SpInit_FunctionDtor();
    void				SpInit_FunctionCastOperator();
    void				SpInit_FunctionNormalOperator();
    void				SpReturn_Type();
    void				SpReturn_Variable();
    void				SpReturn_FunctionStd();
    void				SpReturn_Ignore();

    void				On_start_Identifier(const char * i_sText);
    void				On_start_operator(const char * i_sText);
    void				On_start_TypeKey(const char * i_sText);
    void				On_start_virtual(const char * i_sText);
    void				On_start_Tilde(const char * i_sText);
    void				On_start_const(const char * i_sText);
    void				On_start_volatile(const char * i_sText);
    void				On_start_extern(const char * i_sText);
    void				On_start_static(const char * i_sText);
    void				On_start_mutable(const char * i_sText);
    void				On_start_register(const char * i_sText);
    void				On_start_inline(const char * i_sText);
    void				On_start_explicit(const char * i_sText);
    void				On_start_Bracket_Right(const char * i_sText);

    void				On_expectCtor_Bracket_Left(const char * i_sText);

    void				On_afterClassDecl_Semicolon(const char * i_sText);

    void				On_expectName_Identifier(const char * i_sText);
    void				On_expectName_operator(const char * i_sText);
    void				On_expectName_Bracket_Left(const char * i_sText);

    void				On_afterName_ArrayBracket_Left(const char * i_sText);
    void				On_afterName_Bracket_Left(const char * i_sText);
    void                On_afterName_DoubleColon(const char * i_sText);
    void				On_afterName_Semicolon(const char * i_sText);
    void				On_afterName_Comma(const char * i_sText);
    void				On_afterName_Assign(const char * i_sText);
    void				On_afterName_Less(const char * i_sText);

    void                On_afterName_inErraneousTemplate_Less(const char * i_sText);
    void                On_afterName_inErraneousTemplate_Greater(const char * i_sText);
    void                On_afterName_inErraneousTemplate_Default(const char * i_sText);

    void				On_finished_Semicolon(const char * i_sText);
    void				On_finished_Comma(const char * i_sText);
    void				On_finished_Default(const char * i_sText);

    void                On_finishedIncludingFunctionImplementation_Default(const char * i_sText);

    ary::cpp::FunctionFlags
                        CreateFunctionFlags();

    // DATA
    Dyn< PeStatusArray<PE_VarFunc> >
                        pStati;

    Dyn<SP_Type>	    pSpType;
    Dyn<SPU_Type>	 	pSpuType;
    Dyn<SP_Variable>	pSpVariable;
    Dyn<SPU_Variable>	pSpuVariable;
    Dyn<SP_Function>	pSpFunction;
    Dyn<SPU_Function> 	pSpuFunctionStd;
    Dyn<SPU_Function> 	pSpuFunctionCtor;
    Dyn<SPU_Function> 	pSpuFunctionDtor;
    Dyn<SPU_Function> 	pSpuFunctionCastOperator;
    Dyn<SPU_Function> 	pSpuFunctionNormalOperator;
    Dyn<SP_Ignore>	    pSpIgnore;
    Dyn<SPU_Ignore>	 	pSpuIgnore;

    intt                nCounter_TemplateBrackets;
    bool                bInDestructor;

    std::vector<ary::Cid>
                        aResultIds;
    ary::Tid			nResultFrontType;
    E_ResultType        eResultType;

    // Pre-Results
    udmstri             sName;

    bool                bVirtual;
    bool                bStatic;
    bool                bExtern;
    bool                bExternC;
    bool                bMutable;
    bool                bInline;
    bool                bRegister;
    bool                bExplicit;
};



// IMPLEMENTATION

inline const std::vector<ary::Tid> &
PE_VarFunc::Result_Ids() const
    { return aResultIds; }
inline ary::Tid
PE_VarFunc::Result_FrontType() const
    { return nResultFrontType; }
inline PE_VarFunc::E_ResultType
PE_VarFunc::Result_CeType() const
    { return eResultType; }



}   // namespace cpp




#endif


/*	// Overview of Stati

Undecided
---------

start			// vor und w�hrend storage class specifiern
    any         ->stay
    operaator   ->goto Function

->Typ

expectName
    Identifier  ->stay
    operator    ->goto Function

afterName       ->goto Variable or Function




Variable
--------

start			// vor und w�hrend storage class specifiern

->Typ

expectName		// Typ ist da  -> im Falle von '(': notyetimplemented
afterName

expectSize  	// after [
expectFinish
                // vor ; oder ,
expectNextVarName  // anders als bei expectName kann hier auch * oder & kommen





Function
--------

start				// vor und w�hrend storage class specifiern

->Typ

expectName			// Typ ist da
expectBracket		// Nach Name
expectParameter		// nach ( oder ,
-> Parameter
after Parameters    // before const, volatile throw or = 0.
after throw			// expect (
expectException		// after (
after exceptions	// = 0 oder ; oder ,


expectNextVarName  // anders als bei expectName kann hier auch * oder & kommen







*/
