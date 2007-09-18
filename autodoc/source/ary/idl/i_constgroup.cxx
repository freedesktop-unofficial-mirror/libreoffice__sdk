/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: i_constgroup.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: vg $ $Date: 2007-09-18 13:31:50 $
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
#include <ary/idl/i_constgroup.hxx>
#include <ary/idl/ik_constgroup.hxx>


// NOT FULLY DECLARED SERVICES
#include <ary/idl/ihost_ce.hxx>
#include <sci_impl.hxx>


namespace ary
{
namespace idl
{


ConstantsGroup::ConstantsGroup( const String &      i_sName,
                                Ce_id               i_nModule )
    :   sName(i_sName),
        nModule(i_nModule),
        aConstants()
{
}

ConstantsGroup::~ConstantsGroup()
{
}

void
ConstantsGroup::do_Visit_CeHost( CeHost & o_rHost ) const
{
    o_rHost.Do_ConstantsGroup(*this);
}

RCid
ConstantsGroup::inq_ClassId() const
{
    return class_id;
}

const String &
ConstantsGroup::inq_LocalName() const
{
    return sName;
}

Ce_id
ConstantsGroup::inq_NameRoom() const
{
    return nModule;
}

Ce_id
ConstantsGroup::inq_Owner() const
{
    return nModule;
}

E_SightLevel
ConstantsGroup::inq_SightLevel() const
{
    return sl_File;
}


namespace ifc_constgroup
{

inline const ConstantsGroup &
constgroup_cast( const CodeEntity & i_ce )
{ 
    csv_assert( i_ce.ClassId() == ConstantsGroup::class_id );
    return static_cast< const ConstantsGroup& >(i_ce);
}     

void
attr::Get_Constants( Dyn_CeIterator &    o_result,
                     const CodeEntity &  i_ce )
{
    o_result = new SCI_Vector<Ce_id>(constgroup_cast(i_ce).aConstants);
}
                                                        
} // namespace ifc_constgroup


}   //  namespace   idl
}   //  namespace   ary
