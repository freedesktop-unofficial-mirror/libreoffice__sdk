/*************************************************************************
 *
 *  $RCSfile: i_interface.hxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: np $ $Date: 2002-11-01 17:11:27 $
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

#ifndef ARY_IDL_I_INTERFACE_HXX
#define ARY_IDL_I_INTERFACE_HXX



// USED SERVICES
    // BASE CLASSES
#include <ary/idl/i_ce.hxx>
    // COMPONENTS
    // PARAMETERS
#include <ary/stdconstiter.hxx>


namespace ary
{
namespace idl
{
namespace ifc_interface
{
    struct attr;
}

class Interface_2s;

/** @resp
    Represents an IDL interface.
*/
class Interface : public CodeEntity
{
  public:
    enum E_ClassId { class_id = 2001 };
                                                        
                                                        
    // LIFECYCLE
                        Interface(
                            const String &      i_sName,
                            Ce_id               i_nOwner,
                            Type_id             i_nBase );
                        ~Interface();
    // INQUIRY
    Type_id             Base() const;

    // ACCESS
    void                Add_Function(
                            Ce_id               i_nId );
    void                Add_Attribute(
                            Ce_id               i_nId );

  private:
    // Interface ary::RepositoryEntity:
    virtual RCid        inq_ClassId() const;

    // Interface CodeEntity:
    virtual void            do_Visit_CeHost(CeHost & o_rHost) const;
    virtual const String &  inq_LocalName() const;
    virtual Ce_id           inq_NameRoom() const;
    virtual Ce_id           inq_Owner() const;
    virtual E_SightLevel    inq_SightLevel() const;
                                                        
    // Local
    typedef std::vector<Ce_id>          MemberList;   
    friend struct ifc_interface::attr;

    // DATA
    String              sName;
    Ce_id               nOwner;
    Type_id             nBase;
    MemberList          aFunctions;
    MemberList          aAttributes;

    Dyn<Interface_2s>   p2s;
};



// IMPLEMENTATION

inline Type_id
Interface::Base() const
    { return nBase; }

inline void
Interface::Add_Function( Ce_id i_nId )
    { aFunctions.push_back(i_nId); }
inline void
Interface::Add_Attribute( Ce_id i_nId )
    { aAttributes.push_back(i_nId); }


}   // namespace idl
}   // namespace ary


#endif
