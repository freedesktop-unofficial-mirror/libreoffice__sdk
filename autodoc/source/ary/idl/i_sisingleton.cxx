/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: i_sisingleton.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 16:46:11 $
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
#include <ary/idl/i_sisingleton.hxx>


// NOT FULLY DECLARED SERVICES
#include <ary/idl/ik_sisingleton.hxx>
#include <ary/idl/ihost_ce.hxx>



namespace ary
{
namespace idl
{

SglIfcSingleton::SglIfcSingleton( const String &      i_sName,
                                  Ce_id               i_nOwner,
                                  Type_id             i_nBaseInterface )
    :   sName(i_sName),
        nOwner(i_nOwner),
        nBaseInterface(i_nBaseInterface)
{
}

SglIfcSingleton::~SglIfcSingleton()
{
}

void
SglIfcSingleton::do_Visit_CeHost( CeHost & o_rHost ) const
{
    o_rHost.Do_SglIfcSingleton(*this);
}

RCid
SglIfcSingleton::inq_ClassId() const
{
    return class_id;
}

const String &
SglIfcSingleton::inq_LocalName() const
{
    return sName;
}

Ce_id
SglIfcSingleton::inq_NameRoom() const
{
    return nOwner;
}

Ce_id
SglIfcSingleton::inq_Owner() const
{
    return nOwner;
}

E_SightLevel
SglIfcSingleton::inq_SightLevel() const
{
    return sl_File;
}

namespace ifc_sglifcsingleton
{

inline const SglIfcSingleton &
sglifcsingleton_cast( const CodeEntity &  i_ce )
{
    csv_assert( i_ce.ClassId() == SglIfcSingleton::class_id );
    return static_cast< const SglIfcSingleton& >(i_ce);
}

Type_id
attr::BaseInterface( const CodeEntity & i_ce )
{
    return sglifcsingleton_cast(i_ce).nBaseInterface;
}


} // namespace ifc_sglifcsingleton


}   //  namespace   idl
}   //  namespace   ary

