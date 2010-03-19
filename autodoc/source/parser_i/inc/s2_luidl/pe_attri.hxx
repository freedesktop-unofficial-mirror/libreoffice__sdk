/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/

#ifndef ADC_UIDL_PE_ATTRI_HXX
#define ADC_UIDL_PE_ATTRI_HXX



// USED SERVICES
    // BASE CLASSES

#include <s2_luidl/parsenv2.hxx>
#include <s2_luidl/pestate.hxx>
    // COMPONENTS
#include <ary/idl/i_property.hxx>
    // PARAMETERS
#include <ary/idl/i_gate.hxx>


namespace ary
{
     namespace idl
    {
         class Attribute;
    }
}

namespace csi
{
namespace uidl
{


class PE_Variable;
class PE_Type;

class PE_Attribute : public UnoIDL_PE,
                     public ParseEnvState
{
  public:
    typedef ary::idl::Ce_id                     Ce_id;
    typedef ary::idl::Type_id                   Type_id;

                        PE_Attribute(
                            const Ce_id &       i_rCurOwner );

    virtual void	 	EstablishContacts(
                            UnoIDL_PE *			io_pParentPE,
                            ary::Repository &
                                                io_rRepository,
                            TokenProcessing_Result &
                                                o_rResult );
    virtual				~PE_Attribute();

    virtual void	  	ProcessToken(
                            const Token &		i_rToken );

    virtual void		Process_Identifier(
                            const TokIdentifier &
                                                i_rToken );
    virtual void		Process_Stereotype(
                            const TokStereotype &
                                                i_rToken );
    virtual void		Process_MetaType(
                            const TokMetaType &	i_rToken );
    virtual void		Process_Punctuation(
                            const TokPunctuation &
                                                i_rToken );
    virtual void		Process_Raises();
    virtual void		Process_Default();

  private:
    enum E_State
    {
        e_none,
        e_start,
        in_variable,
        expect_end,
        in_raise_std,   /// before 'get', 'set', ';' or '}'
        in_get,
        in_set
    };

    virtual void		InitData();
    virtual void		ReceiveData();
    virtual void		TransferData();
    virtual UnoIDL_PE &	MyPE();

    // DATA
    E_State             eState;
    const Ce_id *       pCurOwner;

    Dyn<PE_Variable>	pPE_Variable;
    Dyn<PE_Type>	    pPE_Exception;

        // object-data
    ary::idl::Attribute *
                        pCurAttribute;
    Type_id	            nCurParsedType;
    String 			    sCurParsedName;
    bool                bReadOnly;
    bool                bBound;
};


}   // namespace uidl
}   // namespace csi


#endif

