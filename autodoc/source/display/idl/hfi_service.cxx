/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: hfi_service.cxx,v $
 * $Revision: 1.10 $
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

#include <precomp.h>
#include "hfi_service.hxx"


// NOT FULLY DEFINED SERVICES
#include <ary/idl/i_ce.hxx>
#include <ary/idl/ik_property.hxx>
#include <ary/idl/ik_service.hxx>
#include <toolkit/hf_docentry.hxx>
#include <toolkit/hf_linachain.hxx>
#include <toolkit/hf_navi_sub.hxx>
#include <toolkit/hf_title.hxx>
#include "hfi_doc.hxx"
#include "hfi_navibar.hxx"
#include "hfi_property.hxx"
#include "hfi_tag.hxx"
#include "hfi_typetext.hxx"
#include "hi_linkhelper.hxx"




extern const String
    C_sCePrefix_Service("service");

namespace
{

const String
    C_sList_IncludedServices("Included Services");
const String
    C_sList_IncludedServices_Label("IncludedServices");
const String
    C_sList_ExportedInterfaces("Exported Interfaces");
const String
    C_sList_ExportedInterfaces_Label("ExportedInterfaces");
const String
    C_sList_Properties("Properties' Summary");
const String
    C_sList_Properties_Label("PropertiesSummary");
const String
    C_sList_PropertiesDetails("Properties' Details");
const String
    C_sList_PropertiesDetails_Label("PropertiesDetails");


enum E_SubListIndices
{
    sli_IncludedServices = 0,
    sli_ExportedInterfaces = 1,
    sli_PropertiesSummary = 2,
    sli_PropertiesDetails = 3
};

} //anonymous namespace


HF_IdlService::HF_IdlService( Environment &         io_rEnv,
                              Xml::Element &        o_rOut )
    :   HtmlFactory_Idl(io_rEnv, &o_rOut)
{
}

HF_IdlService::~HF_IdlService()
{

}

typedef ::ary::idl::ifc_service::attr
    ServiceAttr;
typedef ::ary::Dyn_StdConstIterator< ::ary::idl::CommentedRelation >
    dyn_comref_list;

void
HF_IdlService::Produce_byData( const client & i_ce ) const
{
    Dyn<HF_NaviSubRow>
        pNaviSubRow( &make_Navibar(i_ce) );

    HF_TitleTable
        aTitle(CurOut());
    HF_LinkedNameChain
        aNameChain(aTitle.Add_Row());

    aNameChain.Produce_CompleteChain(Env().CurPosition(), nameChainLinker);
    produce_Title(aTitle, C_sCePrefix_Service, i_ce);

    write_Docu(aTitle.Add_Row(), i_ce);
    CurOut() << new Html::HorizontalLine();

    dyn_comref_list
        dpIncludedServices;
    ServiceAttr::Get_IncludedServices(dpIncludedServices, i_ce);
    if ( (*dpIncludedServices).operator bool() )
    {
        produce_IncludedServices( i_ce, *dpIncludedServices );
        pNaviSubRow->SwitchOn(sli_IncludedServices);
    }

    dyn_comref_list
        dpExportedInterfaces;
    ServiceAttr::Get_ExportedInterfaces(dpExportedInterfaces, i_ce);
    if ( (*dpExportedInterfaces).operator bool() )
    {
        produce_ExportedInterfaces( i_ce, *dpExportedInterfaces );
        pNaviSubRow->SwitchOn(sli_ExportedInterfaces);
    }

    dyn_ce_list
        dpProperties;
    ServiceAttr::Get_Properties(dpProperties, i_ce);
    if ( (*dpProperties).operator bool() )
    {
        produce_Members( *dpProperties,
                         C_sList_Properties,
                         C_sList_Properties_Label,
                         C_sList_PropertiesDetails,
                         C_sList_PropertiesDetails_Label );
        pNaviSubRow->SwitchOn(sli_PropertiesSummary);
        pNaviSubRow->SwitchOn(sli_PropertiesDetails);
    }

    pNaviSubRow->Produce_Row();
    CurOut() << new Xml::XmlCode("<br>&nbsp;");
}

typedef ary::idl::ifc_property::attr    PropertyAttr;

void
HF_IdlService::produce_SummaryDeclaration( Xml::Element &      o_row,
                                           const client &      i_property ) const
{
    // KORR_FUTURE
    // Put this in to HF_IdlProperty!

    Xml::Element &
        rCell = o_row
                    >> *new Html::TableCell
                        << new Html::ClassAttr( C_sCellStyle_SummaryLeft );

    if (PropertyAttr::HasAnyStereotype(i_property))
    {
        rCell << "[ ";
        if (PropertyAttr::IsReadOnly(i_property))
            rCell << "readonly ";
        if (PropertyAttr::IsBound(i_property))
            rCell << "bound ";
        if (PropertyAttr::IsConstrained(i_property))
            rCell << "constrained ";
        if (PropertyAttr::IsMayBeAmbiguous(i_property))
            rCell << "maybeambiguous ";
        if (PropertyAttr::IsMayBeDefault(i_property))
            rCell << "maybedefault ";
        if (PropertyAttr::IsMayBeVoid(i_property))
            rCell << "maybevoid ";
        if (PropertyAttr::IsRemovable(i_property))
            rCell << "removable ";
        if (PropertyAttr::IsTransient(i_property))
            rCell << "transient ";
        rCell << "] ";
    }   // end if

    HF_IdlTypeText
        aType( Env(), rCell, true );
    aType.Produce_byData( PropertyAttr::Type(i_property) );

    StreamLock aLocalLink(100);
    aLocalLink() << "#" << i_property.LocalName();
    rCell
        << new Html::LineBreak
        >> *new Html::Link( aLocalLink().c_str() )
            << i_property.LocalName();
}

DYN HF_NaviSubRow &
HF_IdlService::make_Navibar( const client & i_ce ) const
{
    HF_IdlNavigationBar
        aNaviBar(Env(), CurOut());
    aNaviBar.Produce_CeMainRow(i_ce);

    DYN HF_NaviSubRow &
        ret = aNaviBar.Add_SubRow();
    ret.AddItem(C_sList_IncludedServices, C_sList_IncludedServices_Label, false);
    ret.AddItem(C_sList_ExportedInterfaces, C_sList_ExportedInterfaces_Label, false);
    ret.AddItem(C_sList_Properties, C_sList_Properties_Label, false);
    ret.AddItem(C_sList_PropertiesDetails, C_sList_PropertiesDetails_Label, false);

    CurOut() << new Html::HorizontalLine();
    return ret;
}

void
HF_IdlService::produce_IncludedServices( const client & i_ce,
                                         comref_list &  it_list ) const
{
    csv_assert( it_list );

    HF_SubTitleTable
        aTable( CurOut(),
                C_sList_IncludedServices_Label,
                C_sList_IncludedServices,
                2 );

    for ( ; it_list.operator bool(); ++it_list )
    {
        Xml::Element &
            rRow = aTable.Add_Row();
        produce_Link(rRow, (*it_list).Type());
        produce_LinkDoc(i_ce, rRow, it_list);
    }   // end for
}

void
HF_IdlService::produce_ExportedInterfaces( const client &   i_ce,
                                           comref_list &    it_list ) const
{
    csv_assert( it_list );

    HF_SubTitleTable
        aTable( CurOut(),
                C_sList_ExportedInterfaces_Label,
                C_sList_ExportedInterfaces,
                2 );

    for ( ; it_list; ++it_list )
    {
        Xml::Element &
            rRow = aTable.Add_Row();
        produce_Link(rRow, (*it_list).Type());
        produce_LinkDoc(i_ce, rRow, it_list);
    }   // end for
}

void
HF_IdlService::produce_Link( Xml::Element &     o_row,
                             type_id            i_type ) const
{
    Xml::Element &
        rCell = o_row
                >> *new Html::TableCell
                    << new Html::ClassAttr(C_sCellStyle_SummaryLeft);
    HF_IdlTypeText
        aText(Env(), rCell, true);
    aText.Produce_byData(i_type);
}

void
HF_IdlService::produce_LinkDoc( const client &     i_ce,
                                Xml::Element &     o_row,
                                comref_list &      i_commentedRef ) const
{
    Xml::Element &
        rCell = o_row
                >> *new Html::TableCell
                    << new Html::ClassAttr(C_sCellStyle_SummaryRight);

    HF_DocEntryList
        aDocList(rCell);

    if ( (*i_commentedRef).Info() != 0 )
    {
//      aDocList.Produce_Term("Comment on Reference");

        HF_IdlDocu
            aDocuDisplay(Env(), aDocList);
        aDocuDisplay.Produce_byDocu4Reference(*(*i_commentedRef).Info(), i_ce);
    }
    else
    {
        const client *
            pCe = Env().Linker().Search_CeFromType((*i_commentedRef).Type());
        const ce_info *
            pShort = pCe != 0
                        ?   Get_IdlDocu(pCe->Docu())
                        :   (const ce_info *)(0);
        if ( pShort != 0 )
        {
            aDocList.Produce_NormalTerm("(referenced entity's summary:)");
            Xml::Element &
                rDef = aDocList.Produce_Definition();
            HF_IdlDocuTextDisplay
                aShortDisplay( Env(), &rDef, *pCe);
            pShort->Short().DisplayAt(aShortDisplay);
        }   // end if (pShort != 0)
    }   // endif ( (*i_commentedRef).Info() != 0 ) else
}


void
HF_IdlService::produce_MemberDetails( HF_SubTitleTable &  o_table,
                                      const client &      i_ce ) const
{
    HF_IdlProperty
        aProperty( Env(), o_table);
    aProperty.Produce_byData( i_ce );
}



