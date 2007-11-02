/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: cs_ce.cxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: hr $ $Date: 2007-11-02 15:32:20 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/

#include <precomp.h>
#include "cs_ce.hxx"

// NOT FULLY DEFINED SERVICES
#include <ary/cpp/c_namesp.hxx>



namespace
{
const uintt
    C_nReservedElements = ::ary::cpp::predefined::ce_MAX;    // Skipping "0" and the GlobalNamespace
}




namespace ary
{
namespace cpp
{

Ce_Storage *    Ce_Storage::pInstance_ = 0;



Ce_Storage::Ce_Storage()
    :   stg::Storage<CodeEntity>(C_nReservedElements),
        aTypes(),
        aOperations(),
        aData()

{
    Set_Reserved( predefined::ce_GlobalNamespace,
                  *new Namespace );

    csv_assert(pInstance_ == 0);
    pInstance_ = this;
}

Ce_Storage::~Ce_Storage()
{
    csv_assert(pInstance_ != 0);
    pInstance_ = 0;
}

Ce_id
Ce_Storage::Store_Type(DYN CodeEntity & pass_ce)
{
    Ce_id
        ret = Store_Entity(pass_ce);
    aTypes.Add(ret);
    return ret;
}

Ce_id
Ce_Storage::Store_Operation(DYN CodeEntity & pass_ce)
{
    Ce_id
        ret = Store_Entity(pass_ce);
    aOperations.Add(ret);
    return ret;
}

Ce_id
Ce_Storage::Store_Datum(DYN CodeEntity & pass_ce)
{
    Ce_id
        ret = Store_Entity(pass_ce);
    aData.Add(ret);
    return ret;
}



}   // namespace cpp
}   // namespace ary
