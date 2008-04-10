/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: x_parse2.hxx,v $
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

#ifndef ADC_X_PARSE2_HXX
#define ADC_X_PARSE2_HXX

// USED SERVICES
    // BASE CLASSES
#include <cosv/x.hxx>
    // COMPONENTS
    // PARAMETERS


class X_AutodocParser : public csv::Exception
{
  public:
    // TYPES
    enum E_Type
    {
        x_Any						= 0,
        x_InvalidChar,
        x_UnexpectedToken,
        x_UnexpectedEOF
    };
    // LIFECYCLE
                        X_AutodocParser(
                            E_Type				i_eType,
                            const char *		i_sName = "" )
                                                :	eType(i_eType), sName(i_sName) {}
    // INQUIRY
    virtual void	   	GetInfo(
                            std::ostream &      o_rOutputMedium ) const;

  private:
    E_Type				eType;
    String              sName;

};




#endif
