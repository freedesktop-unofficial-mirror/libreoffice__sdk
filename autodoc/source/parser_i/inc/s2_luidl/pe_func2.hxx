/*************************************************************************
 *
 *  $RCSfile: pe_func2.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2004-07-12 15:44:52 $
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

#ifndef ADC_UIDL_PE_FUNC2_HXX
#define ADC_UIDL_PE_FUNC2_HXX



// USED SERVICES
    // BASE CLASSES
// #include <ary/idl/i_gate.hxx>
// #include <ary/idl/ip_ce.hxx>
#include <s2_luidl/parsenv2.hxx>
#include <s2_luidl/pestate.hxx>
    // COMPONENTS
#include <ary/idl/i_param.hxx>
    // PARAMETERS

namespace ary
{
     namespace idl
    {
         class Function;
    }
}


namespace csi
{
namespace uidl
{

class PE_Type;
class PE_Variable;

class PE_Function : public UnoIDL_PE,
                    public ParseEnvState
{
  public:
    typedef ary::idl::Ce_id		RParent;
    typedef ary::idl::Ce_id		RFunction;

    enum E_Constructor { constructor };

    /// Constructor for interfaces.
                        PE_Function(
                            const RParent &	    i_rCurInterface );

    /// Constructor for single interface based services.
                        PE_Function(
                            const RParent &	    i_rCurService,
                            E_Constructor       i_eCtorMarker );

    virtual void	 	EstablishContacts(
                            UnoIDL_PE *			io_pParentPE,
                            ary::n22::Repository &	io_rRepository,
                            TokenProcessing_Result &
                                                o_rResult );
    virtual				~PE_Function();

    virtual void	  	ProcessToken(
                            const Token &		i_rToken );

    virtual void		Process_Stereotype(
                            const TokStereotype &
                                                i_rToken );
    virtual void		Process_Identifier(
                            const TokIdentifier &
                                                i_rToken );
    virtual void		Process_Punctuation(
                            const TokPunctuation &
                                                i_rToken );
    virtual void		Process_BuiltInType(
                            const TokBuiltInType &
                                                i_rToken );
    virtual void		Process_ParameterHandling(
                            const TokParameterHandling &
                                                i_rToken );
    virtual void		Process_Raises();
    virtual void		Process_Default();

  private:
    enum E_State
    {
        e_none,
        e_start,
        in_return_type,
        expect_name,
        expect_params_list,
        expect_parameter,
        expect_parameter_variable,
        in_parameter_variable,
        expect_parameter_separator,
        params_finished,
        expect_exceptions_list,
        expect_exception,
        in_exception,
        expect_exception_separator,
        exceptions_finished
    };

    void				GoIntoReturnType();
    void				GoIntoParameterVariable();
    void				GoIntoException();
    void				OnDefault();

    virtual void		InitData();
    virtual void		ReceiveData();
    virtual void		TransferData();
    virtual UnoIDL_PE &	MyPE();

    // DATA
    E_State             eState;

    String              sData_Name;
    ary::idl::Type_id   nData_ReturnType;
    bool                bData_Oneway;
    ary::idl::Function *
                        pCurFunction;

    const RParent *	    pCurParent;

    Dyn<PE_Type>		pPE_Type;
    ary::idl::Type_id   nCurParsedType;		// ReturnType or Exception

    String 			    sName;

    Dyn<PE_Variable>	pPE_Variable;
    ary::idl::E_ParameterDirection
                        eCurParsedParam_Direction;
    ary::idl::Type_id   nCurParsedParam_Type;
    String 			    sCurParsedParam_Name;
    bool                bIsForConstructors;
};



}   // namespace uidl
}   // namespace csi


#endif

