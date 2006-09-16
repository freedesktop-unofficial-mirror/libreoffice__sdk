/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: i_namelookup.cxx,v $
 *
 *  $Revision: 1.5 $
 *
 *  last change: $Author: obo $ $Date: 2006-09-16 16:23:13 $
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

// MARKER(update_precomp.py): autogen include statement, do not remove
#include "precompiled_autodoc.hxx"

#include <precomp.h>
#include <ary/idl/i_namelookup.hxx>

// NOT FULLY DECLARED SERVICES
#include <sci_impl.hxx>

namespace ary
{
namespace idl
{

NameLookup::NameLookup()
    :   aNames()
{    
}   

NameLookup::~NameLookup()
{    
}   

void                
NameLookup::Add_Name( const String &      i_name,
                      Ce_id               i_id,
                      RCid                i_class,
                      Ce_id               i_owner )
{
    aNames.insert( std::pair< const String, NameProperties>( 
                                   i_name, 
                                   NameProperties( i_id,
                                                   i_class,
                                                   i_owner )));    
//    aNames.insert( std::make_pair( i_name, 
//                                   NameProperties( i_id,
//                                                   i_class,
//                                                   i_owner )));    
}   

bool                
NameLookup::Has_Name( const String &      i_name,
                      RCid                i_class,
                      Ce_id               i_owner ) const
{          
    IteratorRange<Map_Names::const_iterator> 
        aResult( aNames.equal_range(i_name) );
            
    for ( ; aResult.operator bool(); ++aResult )
    {
        if ( (i_class == 0
                OR (*aResult.cur()).second.nClass == i_class)
             AND                
             ((*aResult.cur()).second.nOwner == i_owner
                OR NOT i_owner.IsValid()) )
        {
            return true;
        }
    }   // end for  
    return false;
}   

void                
NameLookup::Get_Names( Dyn_StdConstIterator<Map_Names::value_type> & o_rResult,
                       const String &                         i_name ) const
{
    IteratorRange<Map_Names::const_iterator> 
        aResult( aNames.equal_range(i_name) );
    o_rResult = new SCI_MultiMap<String, NameProperties>(aResult.cur(), aResult.end());
}


}   //  namespace   idl
}   //  namespace   ary
