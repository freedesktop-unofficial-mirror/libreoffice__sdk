/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
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

#ifndef ARY_CROSS_REFS_HXX
#define ARY_CROSS_REFS_HXX



// USED SERVICES
    // BASE CLASSES
    // COMPONENTS
    // PARAMETERS
#include "sorted_idset.hxx"


template <class VALUE_LIST, class TYPES>
class CrossReferences
{
  public:
    typedef TYPES::element_type         element;

    /// Checks for double occurrences
    void                Add(
                            VALUE_LIST::index_type
                                                i_nPosition
                            const element &     i_rElem );
    void                Get_List(
                            Dyn_StdConstIterator<element> &
                                                o_rResult ) const;
  private:
    SortedIdSet<TYPES>  aData[VALUE_LIST::max];
};



namespace ary
{

template <class TYPES>
class SortedIdSet
{
  public:
    typedef typename TYPES::element_type   element;
    typedef typename TYPES::sort_type      sorter;
    typedef typename TYPES::find_type      finder;

                        SortedIdSet(
                            const finder &      i_rFinder )
                                                : aSorter(i_rFinder),
                                                  aData(aSorter) {}
                        ~SortedIdSet()          {}

    void                Get_Begin(
                            Dyn_StdConstIterator<element> &
                                                o_rResult )
                                                { o_rResult = new SCI_Set<FINDER>(aData); }
    void                Add(
                            const element &     i_rElement )
                                                { aData.insert(i_rElement); }

  private:
    typedef std::set<element, sorter>       Set;

    // DATA
    sorter              aSorter;
    Set                 aData;
};


}   // namespace ary



#endif

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
