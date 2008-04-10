/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: c_macro.cxx,v $
 * $Revision: 1.6 $
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

#include <precomp.h>
#include <ary/cpp/c_macro.hxx>


// NOT FULLY DECLARED SERVICES
#include <prprpr.hxx>



namespace ary
{
namespace cpp
{


Macro::Macro( const String  &       i_name,
              const StringVector &  i_params,
              const StringVector &  i_definition,
              loc::Le_id            i_declaringFile )
    :   DefineEntity(i_name, i_declaringFile),
        aParams(i_params),
        aDefinition(i_definition)
{
}

Macro::~Macro()
{
}

void
Macro::do_Accept(csv::ProcessorIfc & io_processor) const
{
    csv::CheckedCall(io_processor,*this);
}

ClassId
Macro::get_AryClass() const
{
    return class_id;

    // return RCID_MACRO;
}

const StringVector &
Macro::inq_DefinitionText() const
{
     return aDefinition;
}

void
Macro::GetText( StreamStr &                     o_rText,
                const StringVector &  i_rGivenArguments ) const
{
    bool bSwitch_Stringify = false;
    bool bSwitch_Concatenate = false;
    intt nActiveParamNr = -1;

    if ( aDefinition.begin() == aDefinition.end() )
        return;

    for ( StringVector::const_iterator it = aDefinition.begin();
          it != aDefinition.end();
          ++it )
    {
        if ( HandleOperatorsBeforeTextItem( o_rText,
                                            bSwitch_Stringify,
                                            bSwitch_Concatenate,
                                            *it ) )
        {
            continue;
        }

        for ( StringVector::const_iterator param_it = aParams.begin();
              param_it != aParams.end() AND nActiveParamNr == -1;
              ++param_it )
        {
             if ( strcmp(*it, *param_it) == 0 )
                nActiveParamNr = param_it - aParams.begin();
        }
        if ( nActiveParamNr == -1 )
        {
            o_rText << (*it);
        }
        else
        {
            o_rText << i_rGivenArguments[nActiveParamNr];
            nActiveParamNr = -1;
        }

        Do_bStringify_end(o_rText, bSwitch_Stringify);
        o_rText << " ";
    }
    o_rText.seekp(-1, csv::cur);
}


}   // namespace cpp
}   // namespace ary
