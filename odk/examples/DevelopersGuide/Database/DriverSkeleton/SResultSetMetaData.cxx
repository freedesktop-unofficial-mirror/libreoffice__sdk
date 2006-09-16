/*************************************************************************
 *
 *  $RCSfile: SResultSetMetaData.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: obo $ $Date: 2006-09-17 00:11:41 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  the BSD license.
 *  
 *  Copyright (c) 2003 by Sun Microsystems, Inc.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. Neither the name of Sun Microsystems, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 *  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
 *  TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 *  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *     
 *************************************************************************/

// MARKER(update_precomp.py): autogen include statement, do not remove
#include "precompiled_odk.hxx"

#include "SResultSetMetaData.hxx"

using namespace connectivity::skeleton;
using namespace com::sun::star::uno;
using namespace com::sun::star::lang;
using namespace com::sun::star::sdbc;

// -------------------------------------------------------------------------
OResultSetMetaData::~OResultSetMetaData()
{
}
// -------------------------------------------------------------------------
// -------------------------------------------------------------------------
sal_Int32 SAL_CALL OResultSetMetaData::getColumnDisplaySize( sal_Int32 column ) throw(SQLException, RuntimeException)
{
    return 50;
}
// -------------------------------------------------------------------------

sal_Int32 SAL_CALL OResultSetMetaData::getColumnType( sal_Int32 column ) throw(SQLException, RuntimeException)
{
    sal_Int32 nType = 0;
    return nType;
}
// -------------------------------------------------------------------------

sal_Int32 SAL_CALL OResultSetMetaData::getColumnCount(  ) throw(SQLException, RuntimeException)
{
    // this make no sense here so you have to change this
    return 0;
}
// -------------------------------------------------------------------------

sal_Bool SAL_CALL OResultSetMetaData::isCaseSensitive( sal_Int32 column ) throw(SQLException, RuntimeException)
{
    return sal_True;
}
// -------------------------------------------------------------------------

::rtl::OUString SAL_CALL OResultSetMetaData::getSchemaName( sal_Int32 column ) throw(SQLException, RuntimeException)
{
    return ::rtl::OUString();
}
// -------------------------------------------------------------------------

::rtl::OUString SAL_CALL OResultSetMetaData::getColumnName( sal_Int32 column ) throw(SQLException, RuntimeException)
{
    return ::rtl::OUString::createFromAscii("Column") + ::rtl::OUString::valueOf(column);
}
// -------------------------------------------------------------------------
::rtl::OUString SAL_CALL OResultSetMetaData::getTableName( sal_Int32 column ) throw(SQLException, RuntimeException)
{
    return ::rtl::OUString();
}
// -------------------------------------------------------------------------
::rtl::OUString SAL_CALL OResultSetMetaData::getCatalogName( sal_Int32 column ) throw(SQLException, RuntimeException)
{
    return ::rtl::OUString();
}
// -------------------------------------------------------------------------
::rtl::OUString SAL_CALL OResultSetMetaData::getColumnTypeName( sal_Int32 column ) throw(SQLException, RuntimeException)
{
    return ::rtl::OUString();
}
// -------------------------------------------------------------------------
::rtl::OUString SAL_CALL OResultSetMetaData::getColumnLabel( sal_Int32 column ) throw(SQLException, RuntimeException)
{
    return ::rtl::OUString();
}
// -------------------------------------------------------------------------
::rtl::OUString SAL_CALL OResultSetMetaData::getColumnServiceName( sal_Int32 column ) throw(SQLException, RuntimeException)
{
    return ::rtl::OUString();
}
// -------------------------------------------------------------------------

sal_Bool SAL_CALL OResultSetMetaData::isCurrency( sal_Int32 column ) throw(SQLException, RuntimeException)
{
    return sal_False;
}
// -------------------------------------------------------------------------

sal_Bool SAL_CALL OResultSetMetaData::isAutoIncrement( sal_Int32 column ) throw(SQLException, RuntimeException)
{
    return sal_False;
}
// -------------------------------------------------------------------------


sal_Bool SAL_CALL OResultSetMetaData::isSigned( sal_Int32 column ) throw(SQLException, RuntimeException)
{
    return sal_False;
}
// -------------------------------------------------------------------------
sal_Int32 SAL_CALL OResultSetMetaData::getPrecision( sal_Int32 column ) throw(SQLException, RuntimeException)
{
    return 0;
}
// -----------------------------------------------------------------------------
sal_Int32 SAL_CALL OResultSetMetaData::getScale( sal_Int32 column ) throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException)
{
    return 0;
}
// -------------------------------------------------------------------------

sal_Int32 SAL_CALL OResultSetMetaData::isNullable( sal_Int32 column ) throw(SQLException, RuntimeException)
{
    return 0;
}
// -------------------------------------------------------------------------

sal_Bool SAL_CALL OResultSetMetaData::isSearchable( sal_Int32 column ) throw(SQLException, RuntimeException)
{
    return sal_True;
}
// -------------------------------------------------------------------------

sal_Bool SAL_CALL OResultSetMetaData::isReadOnly( sal_Int32 column ) throw(SQLException, RuntimeException)
{
    return sal_True;
}
// -------------------------------------------------------------------------

sal_Bool SAL_CALL OResultSetMetaData::isDefinitelyWritable( sal_Int32 column ) throw(SQLException, RuntimeException)
{
    return sal_False;
;
}
// -------------------------------------------------------------------------
sal_Bool SAL_CALL OResultSetMetaData::isWritable( sal_Int32 column ) throw(SQLException, RuntimeException)
{
    return sal_False;
}
// -------------------------------------------------------------------------

