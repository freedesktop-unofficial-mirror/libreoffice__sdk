/*************************************************************************
 *
 *  $RCSfile: i_namelookup.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: hr $ $Date: 2003-03-18 14:11:29 $
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

#ifndef ARY_IDL_I_NAMELOOKUP_HXX
#define ARY_IDL_I_NAMELOOKUP_HXX


// USED SERVICES
    // BASE CLASSES
#include <ary/idl/i_language.hxx>
    // COMPONENTS
    // PARAMETERS
#include <ary/stdconstiter.hxx>
#include <ary/itrange.hxx>
#include <vector>
#include <map>


namespace ary
{

namespace idl
{


/*  OPEN?
*/

/** @resp
    This class finds all occurrences in the current language of a 
    name in the repository.

    @descr
*/
class NameLookup
{
  public:
    struct NameProperties
    {                    
                            NameProperties()
                                :   nId(0),
                                    nClass(0),
                                    nOwner(0) {}
                            NameProperties(
                                Ce_id               i_id,
                                RCid                i_class,
                                Ce_id               i_owner )
                                :   nId(i_id),
                                    nClass(i_class),
                                    nOwner(i_owner) {}
        Ce_id               nId;
        RCid                nClass;
        Ce_id               nOwner;
    };
    
    /// Map from Name to NameProperties.
    typedef std::multimap<String, NameProperties>   Map_Names;

    // LIFECYCLE
                        NameLookup();
                        ~NameLookup();
    // OPERATIONS
    void                Add_Name(
                            const String &      i_name,
                            Ce_id               i_id,
                            RCid                i_class,
                            Ce_id               i_owner );
    // INQUIRY                  
    /** 
    */
    bool                Has_Name(
                            const String &      i_name,
                            RCid                i_class,
                            Ce_id               i_owner ) const;
    void                Get_Names(
                            Dyn_StdConstIterator<Map_Names::value_type> &
                                                o_rResult,
                            const String &      i_name ) const;
  private:                              
    // DATA
    Map_Names           aNames;
};



// IMPLEMENTATION


}   // namespace idl
}   // namespace ary


#endif

