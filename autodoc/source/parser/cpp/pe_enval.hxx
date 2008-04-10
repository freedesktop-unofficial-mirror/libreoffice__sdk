/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: pe_enval.hxx,v $
 * $Revision: 1.4 $
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

#ifndef ADC_CPP_PE_ENVAL_HXX
#define ADC_CPP_PE_ENVAL_HXX



// USED SERVICES
    // BASE CLASSES
#include "cpp_pe.hxx"
    // COMPONENTS
#include <semantic/callf.hxx>
#include <semantic/sub_peu.hxx>
    // PARAMETERS


namespace cpp {

class PE_Expression;


class PE_EnumValue : public Cpp_PE
{
  public:
    enum E_State
    {
        start,                      // before name
        afterName,
        expectFinish,		        // after init-expression
        size_of_states
    };
                        PE_EnumValue(
                            Cpp_PE *			i_pParent );
                        ~PE_EnumValue();

    virtual void		Call_Handler(
                            const cpp::Token &	i_rTok );

  private:
    typedef SubPe< PE_EnumValue, PE_Expression >		SP_Expression;
    typedef SubPeUse< PE_EnumValue, PE_Expression> 		SPU_Expression;

    void				Setup_StatusFunctions();
    virtual void		InitData();
    virtual void		TransferData();
    void				Hdl_SyntaxError(const char *);

    void                SpReturn_InitExpression();

    void				On_start_Identifier(const char * );

    void				On_afterName_SwBracket_Right(const char * );
    void				On_afterName_Comma(const char * );
    void				On_afterName_Assign(const char * );

    void				On_expectFinish_SwBracket_Right(const char * );
    void				On_expectFinish_Comma(const char * );

    // DATA
    Dyn< PeStatusArray<PE_EnumValue> >
                        pStati;
    Dyn<SP_Expression>  pSpExpression;
    Dyn<SPU_Expression> pSpuInitExpression;

    String 				sName;
    String              sInitExpression;
};




}   // namespace cpp
#endif

