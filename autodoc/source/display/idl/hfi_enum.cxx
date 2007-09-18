/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: hfi_enum.cxx,v $
 *
 *  $Revision: 1.7 $
 *
 *  last change: $Author: vg $ $Date: 2007-09-18 13:56:16 $
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

#include <precomp.h>
#include "hfi_enum.hxx"


// NOT FULLY DEFINED SERVICES
#include <ary/idl/i_ce.hxx>
#include <ary/idl/ik_enum.hxx>
#include <toolkit/hf_linachain.hxx>
#include <toolkit/hf_navi_sub.hxx>
#include <toolkit/hf_title.hxx>
#include "hfi_navibar.hxx"
#include "hfi_property.hxx"
#include "hi_linkhelper.hxx"


extern const String
    C_sCePrefix_Enum("enum");

namespace
{

const String
    C_sList_Values("Values");
const String
    C_sList_Values_Label("Values");
const String
    C_sList_ValueDetails("Values' Details");
const String
    C_sList_ValueDetails_Label("ValueDetails");

enum E_SubListIndices
{
    sli_ValuesSummary = 0,
    sli_ValueDetails = 1
};

}   // anonymous namespace

HF_IdlEnum::HF_IdlEnum( Environment &       io_rEnv,
                        Xml::Element &      o_rOut )
    :   HtmlFactory_Idl(io_rEnv, &o_rOut)
{
}

HF_IdlEnum::~HF_IdlEnum()
{
}

void
HF_IdlEnum::Produce_byData( const client & i_ce ) const
{
    Dyn<HF_NaviSubRow>
        pNaviSubRow( &make_Navibar(i_ce) );

    HF_TitleTable
        aTitle(CurOut());

    HF_LinkedNameChain
        aNameChain(aTitle.Add_Row());

    aNameChain.Produce_CompleteChain(Env().CurPosition(), nameChainLinker);
    produce_Title(aTitle, C_sCePrefix_Enum, i_ce);

    write_Docu(aTitle.Add_Row(), i_ce);
    CurOut() << new Html::HorizontalLine();

    dyn_ce_list
        dpValues;
    ary::idl::ifc_enum::attr::Get_Values(dpValues, i_ce);
    if ( (*dpValues).operator bool() )
    {
        produce_Members( *dpValues,
                         C_sList_Values,
                         C_sList_Values_Label,
                         C_sList_ValueDetails,
                         C_sList_ValueDetails_Label );
        pNaviSubRow->SwitchOn(sli_ValuesSummary);
        pNaviSubRow->SwitchOn(sli_ValueDetails);
    }
    pNaviSubRow->Produce_Row();
}

HF_NaviSubRow &
HF_IdlEnum::make_Navibar( const client & i_ce ) const
{
    HF_IdlNavigationBar
        aNaviBar(Env(), CurOut());
    aNaviBar.Produce_CeMainRow(i_ce);

    DYN HF_NaviSubRow &
        ret = aNaviBar.Add_SubRow();
    ret.AddItem(C_sList_Values, C_sList_Values_Label, false);
    ret.AddItem(C_sList_ValueDetails, C_sList_ValueDetails_Label, false);

    CurOut() << new Html::HorizontalLine();
    return ret;
}

void
HF_IdlEnum::produce_MemberDetails( HF_SubTitleTable &  o_table,
                                   const client &      i_ce) const
{
    HF_IdlEnumValue
        aElement( Env(), o_table );
    aElement.Produce_byData(i_ce);
}
