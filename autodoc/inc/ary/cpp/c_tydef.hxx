/*************************************************************************
 *
 *  $RCSfile: c_tydef.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: hr $ $Date: 2003-06-30 15:25:09 $
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

#ifndef ARY_CPP_C_TYDEF_HXX
#define ARY_CPP_C_TYDEF_HXX



// USED SERVICES
    // BASE CLASSES
#include <ary/ce.hxx>
    // COMPONENTS
#include <ary/cessentl.hxx>
#include <ary/cpp/c_etypes.hxx>
    // PARAMETERS



namespace ary
{
namespace cpp
{


class Typedef : public CodeEntity
{
  public:
    // LIFECYCLE
                        Typedef();
                        Typedef(
                            Cid                 i_nId,
                            const udmstri &     i_sLocalName,
                            Cid                 i_nOwner,
                            E_Protection        i_eProtection,
                            Lid                 i_nFile,
                            Tid                 i_nDescribingType );
                        ~Typedef();
    // INQUIRY
    static RCid         RC_()                   { return 0x1004; }

    Tid                 DescribingType() const;
    E_Protection        Protection() const      { return eProtection; }

  private:
    // Interface ary::CodeEntity
    virtual Cid			inq_Id() const;
    virtual const udmstri &
                        inq_LocalName() const;
    virtual Cid         inq_Owner() const;
    virtual Lid			inq_Location() const;

    // Interface ary::RepositoryEntity
    virtual void        do_StoreAt(
                            ary::Display &      o_rOut ) const;
    virtual RCid 		inq_RC() const;
    virtual const Documentation &
                        inq_Info() const;
    virtual void        do_Add_Documentation(
                            DYN Documentation & let_drInfo );

    // DATA
    CeEssentials		aEssentials;
    Tid                 nDescribingType;
    E_Protection		eProtection;
};



// IMPLEMENTATION

inline Tid
Typedef::DescribingType() const
    { return nDescribingType; }



}   //  namespace cpp
}   //  namespace ary


#endif

