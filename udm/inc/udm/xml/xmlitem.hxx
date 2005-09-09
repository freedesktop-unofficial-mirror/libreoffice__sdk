/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: xmlitem.hxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-09 14:33:41 $
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

#ifndef CSI_XML_XMLITEM_HXX
#define CSI_XML_XMLITEM_HXX

// USED SERVICES
    // BASE CLASSES
    // COMPONENTS
#include <cosv/template/swelist.hxx>
#include <cosv/template/dyn.hxx>
    // PARAMETERS

namespace csv
{
    class bostream;
}


namespace csi
{
namespace xml
{


/*	Basics:
    Item, Attribute, Element, TextContext
*/

class Item
{
  public:
    virtual				~Item() {}
    void				WriteOut(
                            csv::bostream &		io_aFile ) const;
  private:
    virtual void		do_WriteOut(
                            csv::bostream &		io_aFile ) const = 0;
};

typedef csv::SweList_dyn< Item >			ItemList;

class Attribute
{
  public:
    virtual				~Attribute() {}

    void				WriteOut(
                            csv::bostream &		io_aFile ) const;

    const ::csv::String& Name() const;
    const ::csv::String& Value() const;

  private:
    virtual const ::csv::String &
                        inq_Name() const = 0;
    virtual const ::csv::String &
                        inq_Value() const = 0;
};

typedef csv::SweList_dyn< Attribute >	AttrList;


class Element : public Item
{
  public:
    Element &			operator<<(				/// For multiple content items.
                            DYN Item *			let_dpItem );
    Element &			operator<<(				/// For multiple content items.
                            const ::csv::String& let_drText );
    Element &			operator<<(				/// For multiple content items.
                            const char *		let_dpText );
    Element &			operator<<(
                            DYN Attribute *		let_dpAttr );

    Element &			operator>>(				/// For multiple content items. @return the child Element.
                            DYN Element &		let_drElement );


    Item *				SetContent(             /// For only one content item.
                            DYN Item *			let_dpItem );   	/// Replaces previous content. May be 0, then all content is deleted.
  private:
    // Interface Item:
    virtual void		do_WriteOut(
                            csv::bostream &		io_aFile ) const;
    // Local
    virtual void	  	op_streamout(
                            DYN Item *			let_dpItem ) = 0;
    virtual void	  	op_streamout(
                            DYN Attribute *		let_dpAttr ) = 0;

    virtual void	  	do_SetContent(
                            DYN Item *			let_dpItem ) = 0;
    // Helpers
    virtual const ::csv::String &
                        inq_TagName() const = 0;
    virtual const Item *
                        inq_Content() const = 0;
    virtual const AttrList *
                        inq_Attrs() const = 0;

    virtual bool		FinishEmptyTag_XmlStyle() const;    /// Defaulted to: true

    virtual bool		LineBreakAfterBeginTag() const;	    /// Defaulted to: false
    virtual bool		LineBreakAfterEndTag() const;	    /// Defaulted to: true, if LineBreakAfterBeginTag()
};

class TextContent : public Item
{
};


/*	Implementation simplifiers:
    EmptyElement, PureElement, SglTag
*/

class EmptyElement : public Element
{
  private:
    // Interface Element:
    virtual void	  	op_streamout(          /// does nothing
                            DYN Item *			let_dpItem );
    virtual void	  	op_streamout(
                            DYN Attribute *		let_dpAttr );
    virtual void	  	do_SetContent(          /// does nothing
                            DYN Item *			let_dpItem );
    virtual const Item *
                        inq_Content() const;	/// @return 0
    virtual const AttrList *
                        inq_Attrs() const;

    // Local
    virtual AttrList &	inq_RefAttrs() = 0;
    const AttrList &	inq_RefAttrs() const;
};

class PureElement : public Element
{
  private:
    // Interface Element:
    virtual void	  	op_streamout(
                            DYN Item *			let_dpItem );
    virtual void	  	op_streamout(          /// does nothing
                            DYN Attribute *		let_dpAttr );
    virtual void	  	do_SetContent(
                            DYN Item *			let_dpItem );
    virtual const Item *
                        inq_Content() const;
    virtual const AttrList *
                        inq_Attrs() const;      /// @return 0
    // Local
    virtual Dyn< Item > &
                        inq_RefContent() = 0;
    const Dyn< Item > &	inq_RefContent() const;
};

class SglTag : public Element
{
  private:
    // Interface Element:
    virtual void	  	op_streamout(          /// does nothing
                            DYN Item *			let_dpItem );
    virtual void	  	op_streamout(          /// does nothing
                            DYN Attribute *		let_dpAttr );
    virtual void	  	do_SetContent(          /// does nothing
                            DYN Item *			let_dpItem );
    virtual const Item *
                        inq_Content() const;	/// @return 0
    virtual const AttrList *
                        inq_Attrs() const;      /// @return 0
};



/* 	Standard Element implementations, if there are not any
    specialized ones.
*/

class AnElement : public Element
{
  public:
                        AnElement(
                            const ::csv::String& i_sTagName );
                        AnElement(
                            const char *         i_sTagName );
                        ~AnElement();
  private:
    // Interface Element
    virtual void	  	op_streamout(
                            DYN Item *			let_dpItem );
    virtual void	  	op_streamout(
                            DYN Attribute *		let_dpAttr );
    virtual void	  	do_SetContent(
                            DYN Item *			let_dpItem );
    virtual const ::csv::String &
                        inq_TagName() const;
    virtual const Item *
                        inq_Content() const;
    virtual const AttrList *
                        inq_Attrs() const;
    // DATA
    ::csv::String       sTagName;
    Dyn< Item >			pContent;
    AttrList			aAttrs;
};


class AnEmptyElement : public EmptyElement
{
  public:
                        AnEmptyElement(
                            const ::csv::String & i_sTagName );
                        AnEmptyElement(
                            const char * i_sTagName );
                        ~AnEmptyElement();
  private:
    // Interface Element:
    virtual const ::csv::String &
                        inq_TagName() const;
    // Interface EmptyElement:
    virtual AttrList &	inq_RefAttrs();

    // DATA
    ::csv::String	    sTagName;
    AttrList			aAttrs;
};

class APureElement : public PureElement
{
  public:
                        APureElement(
                            const ::csv::String &	i_sTagName );
                        APureElement(
                            const char *            i_sTagName );
                        ~APureElement();
  private:
    // Interface Element:
    virtual const ::csv::String &
                        inq_TagName() const;
    // Interface PureElement:
    virtual Dyn< Item > &
                        inq_RefContent();
    // DATA
    ::csv::String         sTagName;
    Dyn< Item >			pContent;
};

class ASglTag : public SglTag
{
  public:
                        ASglTag(
                            const ::csv::String & i_sTagName );
                        ASglTag(
                            const char *          i_sTagName );
                        ~ASglTag();
  private:
    // Interface Element:
    virtual const ::csv::String &
                        inq_TagName() const;
    // DATA
    ::csv::String         sTagName;
};


/* Standard Attribute implementation
*/
class AnAttribute : public Attribute
{
  public:
                        AnAttribute(
                            const ::csv::String & i_sName,
                            const ::csv::String & i_sValue );
                        AnAttribute(
                            const char *          i_sName,
                            const char *          i_sValue );
                        ~AnAttribute();
  private:
    // Interface Attribute:
    virtual const ::csv::String &
                        inq_Name() const;
    virtual const ::csv::String &
                        inq_Value() const;
    // DATA
    ::csv::String         sName;
    ::csv::String         sValue;
};



/*	Implementations of TextContent:

    Text  		( reserved characters will be replaced and appear unchanged )
    XmlCode		( reserved characters stay and are interpreted
                  by the XML-viewer )
*/
class Text : public TextContent
{
  public:
                        Text(
                            const ::csv::String & i_sText );
                        Text(
                            const char *		i_sText );
                        ~Text();
  private:
    virtual void		do_WriteOut(
                            csv::bostream &		io_aFile ) const;
    // DATA
    ::csv::String         sText;
};


class XmlCode : public TextContent
{
  public:
                        XmlCode(
                            const ::csv::String & i_sText );
                        XmlCode(
                            const char *          i_sText );
                        ~XmlCode();
  private:
    virtual void		do_WriteOut(
                            csv::bostream &		io_aFile ) const;
    // DATA
    ::csv::String         sText;
};



// IMPLEMENTATION

inline void
Item::WriteOut( csv::bostream &	io_aFile ) const
    { do_WriteOut(io_aFile); }

inline const ::csv::String &
Attribute::Name() const
    { return inq_Name(); }
inline const ::csv::String &
Attribute::Value() const
    { return inq_Value(); }

inline Element &
Element::operator<<( DYN Item *	let_dpItem )
    { op_streamout(let_dpItem); return *this; }
inline Element &
Element::operator<<( const ::csv::String & let_drText )
    { op_streamout( new Text(let_drText) ); return *this; }
inline Element &
Element::operator<<( const char * let_drText )
    { op_streamout( new Text(let_drText) ); return *this; }
inline Element &
Element::operator<<( DYN Attribute * let_dpAttr )
    { op_streamout(let_dpAttr); return *this; }
inline Element &
Element::operator>>( DYN Element & let_drElement )
    { op_streamout(&let_drElement); return let_drElement; }
inline Item *
Element::SetContent( DYN Item *	let_dpItem )
    { do_SetContent(let_dpItem); return let_dpItem; }

inline const AttrList &
EmptyElement::inq_RefAttrs() const
    { return const_cast< EmptyElement* >(this)->inq_RefAttrs(); }

inline const Dyn< Item > &
PureElement::inq_RefContent() const
    { return const_cast< PureElement* >(this)->inq_RefContent(); }

}   // namespace xml
}   // namespace csi


#endif


