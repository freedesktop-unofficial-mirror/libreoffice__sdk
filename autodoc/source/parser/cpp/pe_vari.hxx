/*************************************************************************
 *
 *  $RCSfile: pe_vari.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: np $ $Date: 2002-03-08 14:45:32 $
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

#ifndef ADC_CPP_PE_VARI_HXX
#define ADC_CPP_PE_VARI_HXX



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

class PE_Expression;


class PE_Variable : public Cpp_PE
{
  public:
    enum E_State
    {
        afterName,                  //
        afterSize,                  // after ]
        expectFinish,		        // after InitExpression
        size_of_states
    };
                        PE_Variable(
                            Cpp_PE *			i_pParent );
                        ~PE_Variable();

    /** @return
        Bit 0x0001 != 0, if there is a size and
        bit 0x0002 != 0, if there is an initialisation.
    */
    UINT16              Result_Pattern() const;
    const udmstri &     Result_SizeExpression() const;
    const udmstri &	    Result_InitExpression() const;

    virtual void		Call_Handler(
                            const cpp::Token &	i_rTok );

  private:
    typedef SubPe< PE_Variable, PE_Expression >		 	SP_Expression;
    typedef SubPeUse< PE_Variable, PE_Expression> 		SPU_Expression;

    void				Setup_StatusFunctions();
    virtual void		InitData();
    virtual void		TransferData();
    void				Hdl_SyntaxError(const char *);

    void                SpReturn_ArraySizeExpression();
    void                SpReturn_InitExpression();

    void				On_afterName_ArrayBracket_Left(const char * i_sText);
    void				On_afterName_Semicolon(const char * i_sText);
    void				On_afterName_Comma(const char * i_sText);
    void				On_afterName_Assign(const char * i_sText);

    void				On_afterSize_ArrayBracket_Right(const char * i_sText);

    void				On_expectFinish_Semicolon(const char * i_sText);
    void				On_expectFinish_Comma(const char * i_sText);
    void				On_expectFinish_Bracket_Right(const char * i_sText);

    // DATA
    Dyn< PeStatusArray<PE_Variable> >
                        pStati;

    Dyn<SP_Expression>  pSpExpression;
    Dyn<SPU_Expression> pSpuArraySizeExpression;
    Dyn<SPU_Expression> pSpuInitExpression;

    udmstri             sResultSizeExpression;
    udmstri             sResultInitExpression;
};



// IMPLEMENTATION


inline UINT16
PE_Variable::Result_Pattern() const
    { return ( sResultSizeExpression.length() > 0 ? 1 : 0 )
             + ( sResultInitExpression.length() > 0 ? 2 : 0 ); }
inline const udmstri &
PE_Variable::Result_SizeExpression() const
    { return sResultSizeExpression; }
inline const udmstri &
PE_Variable::Result_InitExpression() const
    { return sResultInitExpression; }


}   // namespace cpp


#endif

