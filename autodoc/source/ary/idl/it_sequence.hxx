/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: it_sequence.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 16:55:23 $
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

#ifndef ARY_IDL_IT_SEQUENCE_HXX
#define ARY_IDL_IT_SEQUENCE_HXX



// USED SERVICES
    // BASE CLASSES
#include <ary/idl/i_type.hxx>
    // COMPONENTS
    // PARAMETERS


namespace ary
{
namespace idl
{


/** A sequence (an array of a type).
*/
class Sequence : public Type
{
  public:
    enum E_ClassId { class_id = 2202 };

    // LIFECYCLE
                        Sequence(
                            Type_id             i_nRelatedType );
    virtual             ~Sequence();

    // INQUIRY                 
    Type_id             RelatedType() const     { return nRelatedType; }

  private:
    // Interface RepositoryEntity:
    virtual void        do_Visit( Host & io_rHost ) const;
    virtual RCid        inq_ClassId() const;

    // Interface Type:
    virtual void        inq_Get_Text(
                            StringVector &      o_module,
                            String &            o_name,
                            Ce_id &             o_nRelatedCe,
                            int &               o_nSequemceCount,
                            const Gate &        i_rGate ) const;
    // DATA
    Type_id             nRelatedType;
};


}   // namespace idl
}   // namespace ary


#endif

