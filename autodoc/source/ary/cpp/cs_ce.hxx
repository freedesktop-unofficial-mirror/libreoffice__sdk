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

#ifndef ARY_CPP_CS_CE_HXX
#define ARY_CPP_CS_CE_HXX



// USED SERVICES
    // BASE CLASSES
#include <store/s_storage.hxx>
    // OTHER
#include <ary/cpp/c_ce.hxx>
#include <ary/cpp/c_traits.hxx>
#include <sortedids.hxx>



namespace ary
{
namespace cpp
{


/** The data base for all ->ary::cpp::CodeEntity objects.
*/
class Ce_Storage : public ::ary::stg::Storage<CodeEntity>
{
  public:
    typedef SortedIds<Ce_Compare>       Index;

                        Ce_Storage();
    virtual             ~Ce_Storage();

    Ce_id               Store_Type(
                            DYN CodeEntity &    pass_ce );
    Ce_id               Store_Operation(
                            DYN CodeEntity &    pass_ce );
    Ce_id               Store_Datum(
                            DYN CodeEntity &    pass_ce );

    const Index &       TypeIndex() const           { return aTypes; }
    const Index &       OperationIndex() const      { return aOperations; }
    const Index &       DataIndex() const           { return aData; }

    Index &             TypeIndex()                 { return aTypes; }
    Index &             OperationIndex()            { return aOperations; }
    Index &             DataIndex()                 { return aData; }

    static Ce_Storage & Instance_()                 { csv_assert(pInstance_ != 0);
                                                      return *pInstance_; }
  private:
    // DATA
    Index               aTypes;
    Index               aOperations;
    Index               aData;

    static Ce_Storage * pInstance_;
};




namespace predefined
{

enum E_CodeEntity
{
    ce_GlobalNamespace = 1,
    ce_MAX
};

}   // namespace predefined





}   // namespace cpp
}   // namespace ary
#endif
