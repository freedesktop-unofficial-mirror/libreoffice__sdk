/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: i_param.hxx,v $
 * $Revision: 1.4 $
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

#ifndef ARY_IDL_I_PARAM_HXX
#define ARY_IDL_I_PARAM_HXX

// BASE CLASSES
#include <ary/idl/i_types4idl.hxx>




namespace ary
{
namespace idl
{


/** Represents a parameter in an IDL function.
*/
class Parameter
{
  public:
    // LIFECYCLE
                        Parameter();
                        Parameter(
                            const String &      i_sName,
                            Type_id             i_nType,
                            E_ParameterDirection
                                                i_eDirection );
                        ~Parameter();

    // INQUIRY
    const String &      Name() const            { return sName; }
    Type_id             Type() const            { return nType; }
    E_ParameterDirection
                        Direction() const       { return eDirection; }

  private:
    // DATA
    String              sName;
    Type_id             nType;
    E_ParameterDirection
                        eDirection;
};




}   // namespace idl
}   // namespace ary
#endif
