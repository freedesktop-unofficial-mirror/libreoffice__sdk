/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: c_enuval.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2007-11-02 14:48:10 $
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

#ifndef ARY_CPP_C_ENUVAL_HXX
#define ARY_CPP_C_ENUVAL_HXX


// USED SERVICES
    // BASE CLASSES
#include <ary/cpp/c_ce.hxx>
    // OTHER
#include <ary/cessentl.hxx>
#include <ary/cpp/c_types4cpp.hxx>



namespace ary
{
namespace cpp
{



/** A C++ enum value declaration and definition.
*/
class EnumValue : public CodeEntity
{
  public:
    enum E_ClassId { class_id = 1006 };

    // LIFECYCLE
                        EnumValue();
                        EnumValue(
                            const String  &     i_sLocalName,
                            Ce_id               i_nOwner,
                            String              i_sInitialisation );
                        ~EnumValue();
    // INQUIRY
    const String  &     Initialisation() const;

  private:
    // Interface csv::ConstProcessorClient
    virtual void        do_Accept(
                            csv::ProcessorIfc & io_processor ) const;

    // Interface ary::cpp::CodeEntity
    virtual const String  &
                        inq_LocalName() const;
    virtual Cid         inq_Owner() const;
    virtual Lid			inq_Location() const;

    // Interface ary::cpp::CppEntity
    virtual ClassId     get_AryClass() const;

    // DATA
    CeEssentials		aEssentials;
    String              sInitialisation;
};




// IMPLEMENTATION
inline const String  &
EnumValue::Initialisation() const
    { return sInitialisation; }




}   // namespace cpp
}   // namespace ary
#endif
