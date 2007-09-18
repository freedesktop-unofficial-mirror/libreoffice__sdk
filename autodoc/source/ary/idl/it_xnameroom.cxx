/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: it_xnameroom.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: vg $ $Date: 2007-09-18 13:39:57 $
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
#include "it_xnameroom.hxx"


// NOT FULLY DEFINED SERVICES
#include <cosv/template/tpltools.hxx>
#include <ary/idl/i_gate.hxx>
#include <ary/idl/ip_type.hxx>
#include "i_strconst.hxx"



namespace ary
{
namespace idl
{

ExplicitNameRoom::ExplicitNameRoom()
    :   aImpl()
{
}

ExplicitNameRoom::ExplicitNameRoom( const String &           i_sName,
                                    const ExplicitNameRoom & i_rParent )
    :   aImpl( i_sName, i_rParent.aImpl, i_rParent.TypeId() )
{
}

ExplicitNameRoom::~ExplicitNameRoom()
{
}

void
ExplicitNameRoom::do_Visit( Host &
                                    ) const
{
    // yet unused.
}

RCid
ExplicitNameRoom::inq_ClassId() const
{
    return class_id;
}

void
ExplicitNameRoom::inq_Get_Text( StringVector &      o_module,
                                String &            ,
                                Ce_id &             ,
                                int &               ,
                                const Gate &        ) const
{
    StringVector::const_iterator it = NameChain_Begin();
    if ( it != NameChain_End()
            ? (*it).empty()
            : false )
    {	// Don't put out the root global namespace
        ++it;
    }

    for ( ;
          it != NameChain_End();
          ++it )
    {
        o_module.push_back(*it);
    }
}




}   // namespace idl
}   // namespace ary
