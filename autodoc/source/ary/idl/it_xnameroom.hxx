/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: it_xnameroom.hxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 16:56:33 $
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

#ifndef ARY_IDL_IT_XNAMEROOM_HXX
#define ARY_IDL_IT_XNAMEROOM_HXX


// USED SERVICES
    // BASE CLASSES
#include <ary/idl/i_type.hxx>
#include <nametreenode.hxx>
    // COMPONENTS
    // PARAMETERS


namespace ary
{
namespace idl
{


/** A namespace for ->Type s, as they are explicitely written in code.

    The search/identification string is usually the local name of
    the Type. But for templated structs, the search string has this
    pattern:
                <LocalName> '<' <StringOfTemplateTypeId>
*/
class ExplicitNameRoom : public Type
{
  public:
    enum E_ClassId { class_id = 2204 };

    // LIFECYCLE
                        ExplicitNameRoom();
                        ExplicitNameRoom(
                            const String &      i_sName,
                            const ExplicitNameRoom &
                                                i_rParent );
    virtual             ~ExplicitNameRoom();

    // OPERATIONS
    /** @param i_sSearchString
                A local type name  usually.
                For templated types see class docu.
        @see ExplicitNameRoom
    */
    void                Add_Name(
                            const String &      i_sSearchString,
                            Type_id             i_nId )
                            { aImpl.Add_Name(i_sSearchString,i_nId); }
    // INQUIRY
    const String &      Name() const            { return aImpl.Name(); }
    intt                Depth() const           { return aImpl.Depth(); }
    void                Get_FullName(
                            StringVector &      o_rText,
                            Ce_idList *         o_pRelatedCes,
                            const Gate &        i_rGate ) const;
    bool                IsAbsolute() const      { return Depth() > 0
                                                    ?   (*NameChain_Begin()).empty()
                                                    :   false; }
    /** @param i_sSearchString
                A local type name  usually.
                For templated types see class docu.
        @see ExplicitNameRoom
    */
    Type_id             Search_Name(
                            const String &      i_sSearchString ) const
                            { return aImpl.Search_Name(i_sSearchString); }

    StringVector::const_iterator
                        NameChain_Begin() const
                            { return aImpl.NameChain_Begin(); }
    StringVector::const_iterator
                        NameChain_End() const
                            { return aImpl.NameChain_End(); }
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
    NameTreeNode<Type_id>
                        aImpl;
};


}   // namespace idl
}   // namespace ary


#endif
