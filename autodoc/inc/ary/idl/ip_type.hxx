/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: ip_type.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 16:19:36 $
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

#ifndef ARY_IDL_IP_TYPE_HXX
#define ARY_IDL_IP_TYPE_HXX


// USED SERVICES
    // BASE CLASSES
    // COMPONENTS
    // PARAMETERS
#include <ary/idl/i_language.hxx>


namespace ary
{

class QualifiedName;

namespace idl
{

class Type;
class ExplicitNameRoom;

class TypePilot
{
  public:
    // LIFECYCLE
    virtual             TypePilot::~TypePilot() {}

    // OPERATIONS
    const Type &        CheckIn_Type(
                            QualifiedName &     i_rFullName,
                            uintt               i_nSequenceCount,
                            Ce_id               i_nModuleOfOccurrence,
                            Type_id             i_nTemplateType );
    // INQUIRY
    const Type &        Find_Type(
                            Type_id             i_nType ) const;
    String              Search_LocalNameOf(
                            Type_id             i_nType ) const;
    Ce_id               Search_CeRelatedTo(
                            Type_id             i_nType ) const;
    const ExplicitNameRoom &
                        Find_XNameRoom(
                            Type_id             i_nType ) const;
    bool                IsBuiltInOrRelated(
                            const Type &        i_rType ) const;
  private:
    // Locals
    virtual const Type &
                        do_CheckIn_Type(
                            QualifiedName &     i_rFullName,
                            uintt               i_nSequenceCount,
                            Ce_id               i_nModuleOfOccurrence,
                            Type_id             i_nTemplateType ) = 0;
    virtual const Type &
                        inq_Find_Type(
                            Type_id             i_nType ) const = 0;
    virtual String      inq_Search_LocalNameOf(
                            Type_id             i_nType ) const = 0;
    virtual Ce_id       inq_Search_CeRelatedTo(
                            Type_id             i_nType ) const = 0;
    virtual const ExplicitNameRoom &
                        inq_Find_XNameRoom(
                            Type_id             i_nType ) const = 0;
    virtual bool        inq_IsBuiltInOrRelated(
                            const Type &        i_rType ) const = 0;
};




// IMPLEMENTATION

inline const Type &
TypePilot::CheckIn_Type( QualifiedName &     i_rFullName,
                         uintt               i_nSequenceCount,
                         Ce_id               i_nModuleOfOccurrence,
                         Type_id             i_nTemplateType )
    { return do_CheckIn_Type(i_rFullName, i_nSequenceCount, i_nModuleOfOccurrence, i_nTemplateType); }

inline const Type &
TypePilot::Find_Type( Type_id i_nType ) const
    { return inq_Find_Type(i_nType); }

inline String
TypePilot::Search_LocalNameOf( Type_id i_nType ) const
    { return inq_Search_LocalNameOf(i_nType); }

inline Ce_id
TypePilot::Search_CeRelatedTo( Type_id i_nType ) const
    { return inq_Search_CeRelatedTo(i_nType); }

inline const ExplicitNameRoom &
TypePilot::Find_XNameRoom( Type_id i_nType ) const
    { return inq_Find_XNameRoom(i_nType); }

inline bool
TypePilot::IsBuiltInOrRelated( const Type & i_rType ) const
    { return inq_IsBuiltInOrRelated( i_rType ); }


}   // namespace idl
}   // namespace ary



#endif
