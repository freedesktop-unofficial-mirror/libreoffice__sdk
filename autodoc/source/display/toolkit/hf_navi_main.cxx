/*************************************************************************
 *
 *  $RCSfile: hf_navi_main.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: np $ $Date: 2002-11-01 17:15:24 $
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


#include <precomp.h>
#include <toolkit/hf_navi_main.hxx>


// NOT FULLY DEFINED SERVICES
#include <cosv/template/tpltools.hxx>



//********************    MainItem and derived ones      ***************//
class HF_MainItem : public HtmlMaker
{
  public:
    virtual             ~HF_MainItem() {}
    void                Produce_Item() const    { do_ProduceItem(); }
  protected:
                        HF_MainItem(
                            Xml::Element &      o_out )
                                                :   HtmlMaker(o_out) {}
  private:
    virtual void        do_ProduceItem() const = 0;
};


namespace
{

class StdItem : public HF_MainItem
{
  public:
                        StdItem(
                            Xml::Element &      o_out,
                            const char *        i_sText,
                            const char *        i_sLink );

                        ~StdItem();
  private:
    virtual void        do_ProduceItem() const;

    // DATA
    udmstri             sText;
    udmstri             sLink;
};

class SelfItem : public HF_MainItem
{
  public:
                        SelfItem(
                            Xml::Element &      o_out,
                            const char *        i_sText );
                        ~SelfItem();
  private:
    virtual void        do_ProduceItem() const;

    // DATA
    udmstri             sText;
};

class NoneItem : public HF_MainItem
{
  public:
                        NoneItem(
                            Xml::Element &      o_out,
                            const char *        i_sText );
                        ~NoneItem();
  private:
    virtual void        do_ProduceItem() const;

    // DATA
    udmstri             sText;
};

}   // anonymous namespace



//********************    HF_NaviMainRow      ***************//



HF_NaviMainRow::HF_NaviMainRow( Xml::Element & o_out )
    :   HtmlMaker(o_out),
        aItems(),
        pRow(0)
{
    aItems.reserve(5);

    pRow = 
    &(  CurOut()
        >> *new Html::Table
           << new Xml::AnAttribute( "border", "0" )
           << new Xml::AnAttribute( "cellpadding", "3" )
           << new Html::ClassAttr("lightbg")
           >> *new Html::TableRow
     );
}

HF_NaviMainRow::~HF_NaviMainRow()
{
    csv::erase_container_of_heap_ptrs(aItems);
}

void
HF_NaviMainRow::Add_StdItem( const char * i_sText,
                             const char * i_sLink )
{
    aItems.push_back(new StdItem( *pRow,i_sText,i_sLink ));
}

void
HF_NaviMainRow::Add_SelfItem( const char * i_sText )
{
    aItems.push_back(new SelfItem( *pRow,i_sText ));
}

void
HF_NaviMainRow::Add_NoneItem( const char * i_sText )
{
    aItems.push_back(new NoneItem( *pRow,i_sText ));
}

void
HF_NaviMainRow::Produce_Row()
{
    ItemList::iterator itEnd = aItems.end();
    for ( ItemList::iterator iter = aItems.begin();
          iter != itEnd;
          ++iter )
    {
         (*iter)->Produce_Item();
    }
}




//********************    MainItem and derived ones      ***************//

namespace
{

StdItem::StdItem( Xml::Element &      o_out,
                  const char *        i_sText,
                  const char *        i_sLink )
    :   HF_MainItem(o_out),
        sText(i_sText),
        sLink(i_sLink)
{
}

StdItem::~StdItem()
{
}

void
StdItem::do_ProduceItem() const
{
    Xml::Element &
                rCell = CurOut() >>* new Html::TableCell;
    rCell
        << new Html::ClassAttr( "navimain" )
        >> *new Html::Link(sLink.c_str())
            << new Html::ClassAttr( "navimain" )
            << sText.c_str();
}

SelfItem::SelfItem( Xml::Element &      o_out,
                    const char *        i_sText )
    :   HF_MainItem(o_out),
        sText(i_sText)
{
}

SelfItem::~SelfItem()
{
}

void
SelfItem::do_ProduceItem() const
{
    Xml::Element &
                rCell = CurOut() >>* new Html::TableCell;
    rCell
        << new Html::ClassAttr( "navimainself" )
        << sText.c_str();
}

NoneItem::NoneItem( Xml::Element &      o_out,
                    const char *        i_sText )
    :   HF_MainItem(o_out),
        sText(i_sText)
{
}

NoneItem::~NoneItem()
{
}

void
NoneItem::do_ProduceItem() const
{
    Xml::Element &
                rCell = CurOut() >>* new Html::TableCell;
    rCell
        << new Html::ClassAttr( "navimainnone" )
        << sText.c_str();
}

}   // anonymous namespace


