/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: adoc_tok.hxx,v $
 * $Revision: 1.3 $
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

#ifndef ADC_ADOC_ADOC_TOK_HXX
#define ADC_ADOC_ADOC_TOK_HXX

// USED SERVICES
    // BASE CLASSES
#include <tokens/token.hxx>
    // COMPONENTS
    // PARAMETERS


namespace adoc {


class TokenInterpreter;


class Token : public TextToken
{
  public:
    // LIFECYCLE
    virtual			  	~Token() {}

    // OPERATIONS
    virtual void		DealOut(
                            ::TokenDealer &		o_rDealer );
    virtual void		Trigger(
                            TokenInterpreter &	io_rInterpreter ) const = 0;
};


}   // namespace adoc

#endif


