/*************************************************************************
 *
 *  $RCSfile: i_exception.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: np $ $Date: 2002-11-01 17:12:46 $
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
#include <ary/idl/i_exception.hxx>
#include <ary/idl/ik_exception.hxx>


// NOT FULLY DECLARED SERVICES
#include <ary/idl/ihost_ce.hxx>
#include <sci_impl.hxx>
#include "ipi_2s.hxx"

namespace ary
{
namespace idl
{

Exception::Exception( const String &      i_sName,
                      Ce_id               i_nOwner,
                      Type_id             i_nBase )
    :   sName(i_sName),
        nOwner(i_nOwner),
        nBase(i_nBase),
        aElements()
{
}

Exception::~Exception()
{
}

void
Exception::do_Visit_CeHost( CeHost & o_rHost ) const
{
    SCI_Vector<Ce_id>
        itElements(aElements);
    o_rHost.Do_Exception(*this);
}

RCid
Exception::inq_ClassId() const
{
    return class_id;
}

const String &
Exception::inq_LocalName() const
{
    return sName;
}

Ce_id
Exception::inq_NameRoom() const
{
    return nOwner;
}

Ce_id
Exception::inq_Owner() const
{
    return nOwner;
}

E_SightLevel
Exception::inq_SightLevel() const
{
    return sl_File;
}


namespace ifc_exception
{

inline const Exception &
exception_cast( const CodeEntity &  i_ce )
{ 
    csv_assert( i_ce.ClassId() == Exception::class_id );
    return static_cast< const Exception& >(i_ce);
}     

Type_id
attr::Base( const CodeEntity & i_ce )
{
    return exception_cast(i_ce).nBase;
}
                               
void         
attr::Get_Elements( Dyn_CeIterator &    o_result,
                    const CodeEntity &  i_ce )
{
    o_result = new SCI_Vector<Ce_id>( exception_cast(i_ce).aElements );
}


void         
xref::Get_Derivations( Dyn_CeIterator &    o_result,
                       const CodeEntity &  i_ce )
{
    o_result = new SCI_Vector<Ce_id>(i_ce.Secondaries().List(exception_2s_Derivations));
}

void         
xref::Get_RaisingFunctions( Dyn_CeIterator &    o_result,
                            const CodeEntity &  i_ce )
{
    o_result = new SCI_Vector<Ce_id>(i_ce.Secondaries().List(exception_2s_RaisingFunctions));
}
                            
                         
} // namespace ifc_exception


}   //  namespace   idl
}   //  namespace   ary
