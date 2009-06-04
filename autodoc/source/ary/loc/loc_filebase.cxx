/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: loc_filebase.cxx,v $
 * $Revision: 1.3 $
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
#include <ary/loc/loc_filebase.hxx>


// NOT FULLY DEFINED SERVICES



namespace ary
{
namespace loc
{

FileBase::FileBase( const String  &     i_localName,
                    Le_id               i_parentDirectory )
    :   sLocalName(i_localName),
        nParentDirectory(i_parentDirectory)
{
}

const String &
FileBase::inq_LocalName() const
{
    return sLocalName;
}

Le_id
FileBase::inq_ParentDirectory() const
{
    return nParentDirectory;
}



} // namespace loc
} // namespace ary
