/*************************************************************************
 *
 *  $RCSfile: nametree.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: np $ $Date: 2002-11-01 17:13:43 $
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

#ifndef ARY_NAMETREE_HXX
#define ARY_NAMETREE_HXX



// USED SERVICES
    // BASE CLASSES
    // COMPONENTS
#include <ary/ids.hxx>
#include "instlist.hxx"
#include "namesort.hxx"
    // PARAMETERS


namespace ary
{


class NameTree
{
  public:        
#if 0 // Test new comparison    
    struct Less_Name
    {
        bool                operator()(
                                const udmstri &     i_r1,
                                const udmstri &     i_r2 ) const;
    };
#endif // 0    
    typedef std::map<  udmstri,
                       InstanceList,
                       CompareCeNames >         Map_Name2Inst;

    typedef Map_Name2Inst::const_iterator       const_iterator;
    typedef Map_Name2Inst::iterator             iterator;


                        NameTree();
                        ~NameTree();

    const InstanceList &
                        operator[](
                            const udmstri &     i_rName ) const;

    void                insert(
                            const udmstri &     i_rName,
                            ary::Rid            i_nId );

    const_iterator      find(
                            const udmstri &     i_rName );
    const_iterator      lower_bound(
                            const udmstri &     i_rName ) const;
    const_iterator      begin() const;
    const_iterator      end() const;

    iterator            begin();
    iterator            end();

  private:
    // DATA                   
    Map_Name2Inst       aNames;
};



// IMPLEMENTATION


}   // namespace ary


#endif

