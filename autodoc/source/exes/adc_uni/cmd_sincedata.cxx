/*************************************************************************
 *
 *  $RCSfile: cmd_sincedata.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: obo $ $Date: 2004-11-15 13:37:03 $
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


#include <precomp.h>
#include "cmd_sincedata.hxx"


// NOT FULLY DEFINED SERVICES
#include <cosv/file.hxx>
#include <cosv/template/tpltools.hxx>
#include "adc_cmds.hxx"



namespace autodoc
{
namespace command
{

SinceTagTransformationData::SinceTagTransformationData()
    :   aTransformationTable()
{
}

SinceTagTransformationData::~SinceTagTransformationData()
{
}

bool
SinceTagTransformationData::DoesTransform() const
{
    return NOT aTransformationTable.empty();
}

const String &
SinceTagTransformationData::DisplayOf( const String & i_sVersionNumber ) const
{
    if (DoesTransform())
    {
        const String * ret = csv::find_in_map(aTransformationTable, i_sVersionNumber);
        return ret != 0
                ?   *ret
                :   String::Null_();
    }
    else
    {
        return i_sVersionNumber;
    }
}

void
SinceTagTransformationData::do_Init( opt_iter &  it,
                                     opt_iter    itEnd )
{
    ++it;   // Cur is since-file path.

    CHECKOPT(   it != itEnd ,
              "file path",
              C_opt_SinceFile );

    csv::File           aSinceFile(*it);
    csv::OpenCloseGuard aSinceFileGuard(aSinceFile);
    StreamStr           sLine(200);

    if (aSinceFileGuard)
    {
        for ( sLine.operator_read_line(aSinceFile);
              NOT sLine.empty();
              sLine.operator_read_line(aSinceFile) )
        {

            if (*sLine.begin() != '"')
                continue;

            const char * pVersion = sLine.c_str() + 1;
            const char * pVersionEnd = strchr(pVersion, '"');
            if (pVersionEnd == 0)
                continue;
            const char * pDisplay = strchr(pVersionEnd+1, '"');
            if (pDisplay == 0)
                continue;
            ++pDisplay;
            const char * pDisplayEnd = strchr(pDisplay, '"');
            if (pDisplayEnd == 0)
                continue;

            aTransformationTable[ String(pVersion,pVersionEnd) ]
                                        = String(pDisplay,pDisplayEnd);
            sLine.clear();
        }   // end for
    }   // end if

    ++it;   // Cur is next option.
}

}   // namespace command
}   // namespace autodoc
