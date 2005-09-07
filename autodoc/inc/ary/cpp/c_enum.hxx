/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: c_enum.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 15:57:58 $
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

#ifndef ARY_CPP_C_ENUM_HXX
#define ARY_CPP_C_ENUM_HXX



// USED SERVICES
    // BASE CLASSES
#include <ary/ce.hxx>
#include <ary/arygroup.hxx>
    // COMPONENTS
#include <ary/cessentl.hxx>
#include <ary/idlists.hxx>
#include <ary/cpp/c_etypes.hxx>
    // PARAMETERS

namespace ary
{
namespace cpp
{


class Enum : public CodeEntity,
             public AryGroup
{
  public:
    enum E_Slots
    {
        SLOT_Values = 1
    };

    // LIFECYCLE
                        Enum();
                        Enum(
                            Cid                 i_nId,
                            const udmstri &     i_sLocalName,
                            Cid                 i_nOwner,
                            E_Protection        i_eProtection,
                            Lid                 i_nFile );
                        ~Enum();

    // OPERATIONS
    void				Add_Value(
                            Cid                 i_nId );

    // INQUIRY
    static RCid         RC_()                   { return 0x1003; }

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
    virtual const ary::Documentation &
                        inq_Info() const;
    virtual void        do_Add_Documentation(
                            DYN ary::Documentation &
                                                let_drInfo );
    // Interface ary::AryGroup
    virtual Gid 		inq_Id_Group() const;
    virtual const RepositoryEntity &
                        inq_RE_Group() const;
    virtual const group::SlotList &
                        inq_Slots() const;
    virtual DYN Slot *  inq_Create_Slot(
                            SlotAccessId        i_nSlot ) const;

    // DATA
       CeEssentials		aEssentials;
    List_Rid            aValues;
    E_Protection		eProtection;
};



}   // namespace cpp
}   // namespace ary


#endif

