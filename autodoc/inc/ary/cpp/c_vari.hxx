/*************************************************************************
 *
 *  $RCSfile: c_vari.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: np $ $Date: 2002-03-08 14:45:14 $
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

#ifndef ARY_CPP_C_VARI_HXX
#define ARY_CPP_C_VARI_HXX


// USED SERVICES
    // BASE CLASSES
#include <ary/ce.hxx>
    // COMPONENTS
#include <ary/cessentl.hxx>
#include <ary/cpp/c_etypes.hxx>
#include <ary/cpp/c_vfflag.hxx>
    // PARAMETERS



namespace ary
{

namespace cpp
{


class Variable : public CodeEntity
{
  public:
    // LIFECYCLE
                        Variable();
                        Variable(
                            Cid                 i_nId,
                            const udmstri &     i_sLocalName,
                            Cid                 i_nOwner,
                            E_Protection        i_eProtection,
                            Lid                 i_nFile,
                            Tid                 i_nType,
                            VariableFlags       i_aFlags,
                            const udmstri &     i_sArraySize,
                            const udmstri &     i_sInitValue );
                        ~Variable();


    // INQUIRY
    static RCid         RC_()                   { return 0x1006; }

    Tid                 Type() const;
    const udmstri &     ArraySize() const;
    const udmstri &     Initialisation() const;
    E_Protection        Protection() const      { return eProtection; }

    // ACCESS

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
    virtual const ary::Documentation &
                        inq_Info() const;
    virtual void        do_Add_Documentation(
                            DYN ary::Documentation &
                                                let_drInfo );

    // DATA
    CeEssentials		aEssentials;
    Tid                 nType;
    E_Protection		eProtection;
    VariableFlags       aFlags;
    udmstri             sArraySize;
    udmstri             sInitialisation;
};



// IMPLEMENTATION

inline Tid
Variable::Type() const
    { return nType; }
inline const udmstri &
Variable::ArraySize() const
    { return sArraySize; }
inline const udmstri &
Variable::Initialisation() const
    { return sInitialisation; }


}   // namespace cpp
}   // namespace ary


#endif

