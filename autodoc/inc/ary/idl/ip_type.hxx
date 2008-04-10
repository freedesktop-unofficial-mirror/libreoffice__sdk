/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: ip_type.hxx,v $
 * $Revision: 1.7 $
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

#ifndef ARY_IDL_IP_TYPE_HXX
#define ARY_IDL_IP_TYPE_HXX

// USED SERVICES
#include <ary/idl/i_types4idl.hxx>




namespace ary
{
    class QualifiedName;

namespace idl
{
    class Type;
    class ExplicitNameRoom;


/** Access point to all {->Type}s in IDL.
*/
class TypePilot
{
  public:
    // LIFECYCLE
    virtual             ~TypePilot() {}

    // OPERATIONS
    virtual const Type &
                        CheckIn_Type(
                            QualifiedName &     i_rFullName,
                            uintt               i_nSequenceCount,
                            Ce_id               i_nModuleOfOccurrence,
                            Type_id             i_nTemplateType ) = 0;
    // INQUIRY
    virtual const Type &
                        Find_Type(
                            Type_id             i_nType ) const = 0;
    virtual String      Search_LocalNameOf(
                            Type_id             i_nType ) const = 0;
    virtual Ce_id       Search_CeRelatedTo(
                            Type_id             i_nType ) const = 0;
    virtual const ExplicitNameRoom &
                        Find_XNameRoom(
                            Type_id             i_nType ) const = 0;
    virtual bool        IsBuiltInOrRelated(
                            const Type &        i_rType ) const = 0;
};




}   // namespace idl
}   // namespace ary
#endif
