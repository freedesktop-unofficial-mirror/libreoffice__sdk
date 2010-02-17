/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
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
#include <cosv/string.hxx>

// NOT FULLY DECLARED SERVICES
#include <ut.hxx>

using csv::SimpleString;


/** @file
    UnitTests for class String.
*/

inline bool
check_value( const String & a, const char * b )
{
     return strcmp( a.c_str(), b ) == 0;
}


bool
classtest_String( csv::SimpleString & rSimpleString )
{
    bool ret = true;

    String x1;
    UT_CHECK( String(), check_value(x1,"") )

    const char * s2a = "";
    String x2a(s2a);
    UT_CHECK( String(const char*), check_value(x2a,s2a) )

    const char * s2b = "_zluoadninger  prrg chi��i(/%$##@\\\"'''fh  kl";
    String x2b(s2b);
    UT_CHECK( String(const char*), check_value(x2b,s2b) )


    bool ret = ftest_Read( rSimpleString );
    ret = ftest_Write( rSimpleString ) AND ret;
    ret = ftest_SeekBack( rSimpleString ) AND ret;
    ret = ftest_SeekRelative( rSimpleString ) AND ret;

    rSimpleString.Close();

    return ret;
}




#if 0
FUT_DECL( SimpleString, Ctor_Def );
FUT_DECL( SimpleString, Seek );
FUT_DECL( SimpleString, SeekBack );
FUT_DECL( SimpleString, SeekRelative );



FUT_DECL( SimpleString, Read )
{
    bool ret = true;

    rSimpleString.SeekBack(0);
    uintt nSourceSize = rSimpleString.Position();
    rSimpleString.Seek(0);

    char * pBuf = new char[nSourceSize+1];
    uintt nCount = rSimpleString.Read(pBuf,nSourceSize);

    UT_CHECK( Read, nCount == nSourceSize );

    return ret;
}

FUT_DECL( SimpleString, Write )
{
    bool ret = true;



    return ret;
}

FUT_DECL( SimpleString, Seek )
{
    bool ret = true;



    return ret;
}

FUT_DECL( SimpleString, SeekBack )
{
    bool ret = true;



    return ret;
}

FUT_DECL( SimpleString, SeekRelative )
{
    bool ret = true;



    return ret;
}

#endif


