/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: pe_defs.hxx,v $
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

#ifndef ADC_CPP_PE_DEFS_HXX
#define ADC_CPP_PE_DEFS_HXX




// USED SERVICES
    // BASE CLASSES
#include "cpp_pe.hxx"
    // COMPONENTS
#include <semantic/callf.hxx>
#include <semantic/sub_peu.hxx>
    // PARAMETERS


namespace cpp
{



class PE_Defines : public cpp::Cpp_PE
{
  public:
    enum E_State
    {
        expectName,
        gotDefineName,
        expectMacroParameters,
        size_of_states
    };

                        PE_Defines(
                            Cpp_PE *			i_pParent );
                        ~PE_Defines();

    virtual void		Call_Handler(
                            const cpp::Token &	i_rTok );

  private:
    void				Setup_StatusFunctions();
    virtual void		InitData();
    virtual void		TransferData();
    void  				Hdl_SyntaxError( const char *);

    void				On_expectName_DefineName( const char * );
    void				On_expectName_MacroName( const char * );

    void				On_gotDefineName_PreProDefinition( const char * );

    void                On_expectMacroParameters_MacroParameter( const char * );
    void                On_expectMacroParameters_PreProDefinition( const char * );

    // DATA
    Dyn< PeStatusArray<PE_Defines> >
                        pStati;

    String              sName;
    StringVector        aParameters;
    StringVector        aDefinition;
    bool                bIsMacro;
};



}   //namespace cpp
#endif

