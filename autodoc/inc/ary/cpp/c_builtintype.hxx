/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: c_builtintype.hxx,v $
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

#ifndef ARY_CPP_C_BUILTINTYPE_HXX
#define ARY_CPP_C_BUILTINTYPE_HXX



// USED SERVICES
    // BASE CLASSES
#include <ary/cpp/c_type.hxx>
    // COMPONENTS
    // PARAMETERS


namespace ary
{
namespace cpp
{


/**	Represents types like void, int, double.
*/
class BuiltInType : public Type
{
  public:
    enum E_ClassId { class_id = 1200 };

                        BuiltInType(
                            const String  &		i_sName,
                            E_TypeSpecialisation
                                                i_Specialisation );

    String              SpecializedName() const;

    static String       SpecializedName_(
                            const char *		i_sName,
                            E_TypeSpecialisation
                                                i_eTypeSpecialisation );
  private:
    // Interface csv::ConstProcessorClient
    virtual void        do_Accept(
                            csv::ProcessorIfc & io_processor ) const;
    // Interface Object:
    virtual ClassId     get_AryClass() const;

    // Interface Type:
    virtual bool        inq_IsConst() const;
    virtual void        inq_Get_Text(
                            StreamStr &         o_rPreName,
                            StreamStr &         o_rName,
                            StreamStr &         o_rPostName,
                            const Gate &	    i_rGate ) const;
    // DATA
    String              sName;
    E_TypeSpecialisation
                        eSpecialisation;
};



inline String
BuiltInType::SpecializedName() const
{
    return SpecializedName_(sName, eSpecialisation);
}




}	// namespace cpp
}	// namespace ary
#endif
