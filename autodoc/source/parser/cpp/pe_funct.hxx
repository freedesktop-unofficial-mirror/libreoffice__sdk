/*************************************************************************
 *
 *  $RCSfile: pe_funct.hxx,v $
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


#ifndef ADC_CPP_PE_FUNCT_HXX
#define ADC_CPP_PE_FUNCT_HXX



// USED SERVICES
    // BASE CLASSES
#include "cpp_pe.hxx"
    // COMPONENTS
#include <semantic/callf.hxx>
#include <semantic/sub_peu.hxx>
#include <ary/cpp/c_etypes.hxx>
#include <ary/cpp/c_vfflag.hxx>
    // PARAMETERS


namespace ary
{
namespace cpp
{
class Function;
struct S_VariableInfo;
}
}

namespace cpp
{

class PE_Type;
class PE_Parameter;

class PE_Function : public Cpp_PE
{
  public:
    enum E_State
    {
        afterStdOperator,           // if initializes as operator
        afterStdOperatorLeftBracket,
                                    // if initializes as operator with ( or [ 
        afterCastOperator,          // if initializes as operator
        afterName,	  				// undecided
        expectParameterSeparator,	//
        afterParameters,            // before const, volatile throw or = 0.
        afterThrow,			        // expect (
        expectExceptionSeparator,   //
        afterExceptions,	        // = 0 oder ; oder ,
        expectZero,	                // after '='
        inImplementation,           // after { 
        size_of_states
    };
    typedef ary::cpp::E_Protection 				E_Protection;
    typedef ary::cpp::E_Virtuality 				E_Virtuality;
    typedef ary::cpp::E_ConVol 				    E_ConVol;

                        PE_Function(
                            Cpp_PE *			i_pParent );
                        ~PE_Function();

    void		        Init_Std(
                            const udmstri &     i_sName,
                            ary::Tid            i_nReturnType,
                            bool                i_bVirtual,
                            ary::cpp::FunctionFlags
                                                i_aFlags );
    void		        Init_Ctor(
                            const udmstri &     i_sName,
                            ary::cpp::FunctionFlags
                                                i_aFlags );
    void		        Init_Dtor(
                            const udmstri &     i_sName,
                            bool                i_bVirtual,
                            ary::cpp::FunctionFlags
                                                i_aFlags );
    void		        Init_CastOperator(
                            bool                i_bVirtual,
                            ary::cpp::FunctionFlags
                                                i_aFlags );
    void		        Init_NormalOperator(
                            ary::Tid            i_nReturnType,
                            bool                i_bVirtual,
                            ary::cpp::FunctionFlags
                                                i_aFlags );

    ary::Cid	        Result_Id() const;
    bool	            Result_WithImplementation() const;

    virtual void		Call_Handler(
                            const cpp::Token &	i_rTok );
  private:
    typedef SubPe< PE_Function, PE_Type >		    SP_Type;
    typedef SubPeUse< PE_Function, PE_Type >	    SPU_Type;
    typedef SubPe< PE_Function, PE_Parameter>	    SP_Parameter;
    typedef SubPeUse<PE_Function, PE_Parameter>	    SPU_Parameter;

    typedef std::vector<ary::cpp::S_Parameter>	    ParameterList;
    typedef std::vector<ary::Tid>	                ExceptionTypeList;

    void				Setup_StatusFunctions();
    virtual void		InitData();
    virtual void		TransferData();
    void				Hdl_SyntaxError(const char * i_sText);

    void				SpInit_CastOperatorType();

    void				SpReturn_Parameter();
    void				SpReturn_Exception();
    void				SpReturn_CastOperatorType();

    void				On_afterOperator_Std_Operator(const char * i_sText);             // Operator+() etc.
    void				On_afterOperator_Std_LeftBracket(const char * i_sText); // operator [] or ()
    void                On_afterStdOperatorLeftBracket_RightBracket(const char * i_sText);
    void				On_afterOperator_Cast_Type(const char * i_sText);    // Type

    void				On_afterName_Bracket_Left(const char * i_sText);

    void				On_expectParameterSeparator_BracketRight(const char * i_sText);
    void				On_expectParameterSeparator_Comma(const char * i_sText);

    void				On_afterParameters_const(const char * i_sText);
    void				On_afterParameters_volatile(const char * i_sText);
    void				On_afterParameters_throw(const char * i_sText);
    void				On_afterParameters_SwBracket_Left(const char * i_sText);
    void				On_afterParameters_Semicolon(const char * i_sText);
    void				On_afterParameters_Comma(const char * i_sText);
    void				On_afterParameters_Colon(const char * i_sText);
    void				On_afterParameters_Assign(const char * i_sText);

    void				On_afterThrow_Bracket_Left(const char * i_sText);

    void				On_expectExceptionSeparator_BracketRight(const char * i_sText);
    void				On_expectExceptionSeparator_Comma(const char * i_sText);

    void				On_afterExceptions_SwBracket_Left(const char * i_sText);
    void				On_afterExceptions_Semicolon(const char * i_sText);
    void				On_afterExceptions_Comma(const char * i_sText);
    void				On_afterExceptions_Colon(const char * i_sText);
    void				On_afterExceptions_Assign(const char * i_sText);

    void				On_expectZero_Constant(const char * i_sText);

    void				On_inImplementation_SwBracket_Left(const char * i_sText);
    void				On_inImplementation_SwBracket_Right(const char * i_sText);
    void				On_inImplementation_Default(const char * i_sText);

    void                PerformFinishingPunctuation();
    void                EnterImplementation(
                            intt                i_nBracketCountStart ); /// 1 normally, 0 in initialisation section of c'tors.

    // DATA
    Dyn< PeStatusArray<PE_Function> >
                        pStati;

    Dyn< SP_Parameter > pSpParameter;
    Dyn< SPU_Parameter> pSpuParameter;
    Dyn< SP_Type >      pSpType;
    Dyn< SPU_Type >     pSpuException;
    Dyn< SPU_Type >     pSpuCastOperatorType;       // in "operator int()" or "operator ThatClass *()"

    ary::Cid            nResult;
    bool                bResult_WithImplementation; // Necessary for the parent ParseEnvironment
                                                    //   to know, there is no semicolon or comma following.
        // Pre results
    StreamStr           aName;
    E_Virtuality        eVirtuality;
    E_ConVol            eConVol;
    ary::cpp::FunctionFlags
                        aFlags;
    ary::Tid            nReturnType;
    ParameterList       aParameters;
    ExceptionTypeList   aExceptions;
    bool                bThrow;                     // Indicates, if there is a throw - important, if there are 0 exceptions listed.
    intt                nBracketCounterInImplementation;
};



// IMPLEMENTATION


inline bool
PE_Function::Result_WithImplementation() const
    { return bResult_WithImplementation; }


}   // namespace cpp




#endif


/*	// Overview of Stati

Undecided
---------

start			// vor und w�hrend storage class specifiern

->Typ

expectName		// Typ ist da

afterName




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
