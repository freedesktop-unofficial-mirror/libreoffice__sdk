/*************************************************************************
 *
 *  $RCSfile: propertyids.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: vg $ $Date: 2003-06-10 10:20:00 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  either of the following licenses
 *
 *         - GNU Lesser General Public License Version 2.1
 *         - Sun Industry Standards Source License Version 1.1
 *
 *  Sun Microsystems Inc., October, 2000
 *
 *  GNU Lesser General Public License Version 2.1
 *  =============================================
 *  Copyright 2000 by Sun Microsystems, Inc.
 *  901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License version 2.1, as published by the Free Software Foundation.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *  MA  02111-1307  USA
 *
 *
 *  Sun Industry Standards Source License Version 1.1
 *  =================================================
 *  The contents of this file are subject to the Sun Industry Standards
 *  Source License Version 1.1 (the "License"); You may not use this file
 *  except in compliance with the License. You may obtain a copy of the
 *  License at http://www.openoffice.org/license.html.
 *
 *  Software provided under this License is provided on an "AS IS" basis,
 *  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING,
 *  WITHOUT LIMITATION, WARRANTIES THAT THE SOFTWARE IS FREE OF DEFECTS,
 *  MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE, OR NON-INFRINGING.
 *  See the License for the specific provisions governing your rights and
 *  obligations concerning the Software.
 *
 *  The Initial Developer of the Original Code is: Sun Microsystems, Inc.
 *
 *  Copyright: 2000 by Sun Microsystems, Inc.
 *
 *  All Rights Reserved.
 *
 *  Contributor(s): _______________________________________
 *
 *
 ************************************************************************/
#ifndef _CONNECTIVITY_PROPERTYIDS_HXX_
#define _CONNECTIVITY_PROPERTYIDS_HXX_

// this define has to be set to split the names into different dll's or so's
// every dll has his own set of property names
#ifndef _RTL_USTRING_
#include <rtl/ustring>
#endif
#ifndef _MAP_
#include <map>
#endif

namespace connectivity
{
namespace skeleton
{
    class OPropertyMap
    {
        ::std::map<sal_Int32 , rtl_uString*> m_aPropertyMap; 

        ::rtl::OUString fillValue(sal_Int32 _nIndex);
    public:
        OPropertyMap()
        {
        }
        ~OPropertyMap();
        ::rtl::OUString getNameByIndex(sal_Int32 _nIndex) const;

        static OPropertyMap& getPropMap()
        {
            static OPropertyMap s_aPropMap;
            return s_aPropMap;
        }
    };


    
        typedef const sal_Char* (*PVFN)();

        struct UStringDescription
        {
            const sal_Char*	pZeroTerminatedName;
            sal_Int32 nLength;

            UStringDescription(PVFN _fCharFkt); 
            operator ::rtl::OUString() const { return ::rtl::OUString(pZeroTerminatedName,nLength,RTL_TEXTENCODING_ASCII_US); }
            ~UStringDescription();
        private:
            UStringDescription();
        };
    }
}


//------------------------------------------------------------------------------
#define DECL_PROP1IMPL(varname, type) \
pProperties[nPos++] = ::com::sun::star::beans::Property(OPropertyMap::getPropMap().getNameByIndex(PROPERTY_ID_##varname), PROPERTY_ID_##varname, ::getCppuType(reinterpret_cast< type*>(NULL)),
//------------------------------------------------------------------------------
#define DECL_PROP0(varname, type)	\
    DECL_PROP1IMPL(varname, type) 0)
//------------------------------------------------------------------------------
#define DECL_BOOL_PROP1IMPL(varname) \
        pProperties[nPos++] = ::com::sun::star::beans::Property(OPropertyMap::getPropMap().getNameByIndex(PROPERTY_ID_##varname), PROPERTY_ID_##varname, ::getBooleanCppuType(),
//------------------------------------------------------------------------------
#define DECL_BOOL_PROP0(varname)	\
    DECL_BOOL_PROP1IMPL(varname) 0)


#define PROPERTY_ID_QUERYTIMEOUT					1
#define PROPERTY_ID_MAXFIELDSIZE					2
#define PROPERTY_ID_MAXROWS							3
#define PROPERTY_ID_CURSORNAME						4
#define PROPERTY_ID_RESULTSETCONCURRENCY			5
#define PROPERTY_ID_RESULTSETTYPE					6
#define PROPERTY_ID_FETCHDIRECTION					7
#define PROPERTY_ID_FETCHSIZE						8
#define PROPERTY_ID_ESCAPEPROCESSING				9
#define PROPERTY_ID_USEBOOKMARKS					10
// Column
#define PROPERTY_ID_NAME							11
#define PROPERTY_ID_TYPE							12
#define PROPERTY_ID_TYPENAME						13
#define PROPERTY_ID_PRECISION						14
#define PROPERTY_ID_SCALE							15
#define PROPERTY_ID_ISNULLABLE						16
#define PROPERTY_ID_ISAUTOINCREMENT					17
#define PROPERTY_ID_ISROWVERSION					18
#define PROPERTY_ID_DESCRIPTION						19
#define PROPERTY_ID_DEFAULTVALUE					20

#define PROPERTY_ID_REFERENCEDTABLE					21
#define PROPERTY_ID_UPDATERULE						22
#define PROPERTY_ID_DELETERULE						23
#define PROPERTY_ID_CATALOG							24
#define PROPERTY_ID_ISUNIQUE						25
#define PROPERTY_ID_ISPRIMARYKEYINDEX				26
#define PROPERTY_ID_ISCLUSTERED						27
#define PROPERTY_ID_ISASCENDING						28
#define PROPERTY_ID_SCHEMANAME						29
#define PROPERTY_ID_CATALOGNAME						30

#define PROPERTY_ID_COMMAND							31
#define PROPERTY_ID_CHECKOPTION						32
#define PROPERTY_ID_PASSWORD						33
#define PROPERTY_ID_RELATEDCOLUMN					34

#define PROPERTY_ID_FUNCTION           				35
#define PROPERTY_ID_TABLENAME          				36
#define PROPERTY_ID_REALNAME           				37
#define PROPERTY_ID_DBASEPRECISIONCHANGED			38
#define PROPERTY_ID_ISCURRENCY						39
#define PROPERTY_ID_ISBOOKMARKABLE					40

#define PROPERTY_ID_INVALID_INDEX					41
#define PROPERTY_ID_ERRORMSG_SEQUENCE				42
#define PROPERTY_ID_HY010							43
#define PROPERTY_ID_HY0000							44
#define PROPERTY_ID_DELIMITER						45
#define PROPERTY_ID_FORMATKEY						46
#define PROPERTY_ID_LOCALE							47
#define PROPERTY_ID_IM001							48

#define PROPERTY_ID_AUTOINCREMENTCREATION			49

#define PROPERTY_ID_PRIVILEGES						50

#endif // _CONNECTIVITY_PROPERTYIDS_HXX_


