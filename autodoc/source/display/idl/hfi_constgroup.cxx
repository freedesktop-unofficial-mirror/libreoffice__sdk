/*************************************************************************
 *
 *  $RCSfile: hfi_constgroup.cxx,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: vg $ $Date: 2003-06-10 11:32:44 $
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
#include "hfi_constgroup.hxx"


// NOT FULLY DEFINED SERVICES
#include <ary/idl/i_ce.hxx>
#include <ary/idl/ik_constgroup.hxx>
#include <toolkit/hf_linachain.hxx>
#include <toolkit/hf_navi_sub.hxx>
#include <toolkit/hf_title.hxx>
#include "hfi_navibar.hxx"
#include "hfi_property.hxx"
#include "hi_linkhelper.hxx"

        
extern const String
    C_sCePrefix_Constants("constants group");
        

namespace
{

const String
    C_sList_Constants("Constants");
const String
    C_sList_Constants_Label("Constants");
const String
    C_sList_ConstantDetails("Constants' Details");
const String
    C_sList_ConstantDetails_Label("ConstantDetails");

enum E_SubListIndices
{
    sli_ConstantsSummary = 0,
    sli_ConstantDetails = 1
};


}   // anonymous namespace
                         
                         
                         
HF_IdlConstGroup::HF_IdlConstGroup( Environment &   io_rEnv,
                                    Xml::Element &  o_rOut )
    :   HtmlFactory_Idl(io_rEnv, &o_rOut)
{
}

HF_IdlConstGroup::~HF_IdlConstGroup()
{
}

void
HF_IdlConstGroup::Produce_byData( const client & i_ce ) const
{       
    Dyn<HF_NaviSubRow>
        pNaviSubRow( &make_Navibar(i_ce) );

    HF_TitleTable
        aTitle(CurOut());   
    HF_LinkedNameChain
        aNameChain(aTitle.Add_Row());

    aNameChain.Produce_CompleteChain(Env().CurPosition(), nameChainLinker);
    aTitle.Produce_Title( StreamLock(200)()
                          << C_sCePrefix_Constants
                          << " "
                          << i_ce.LocalName()
                          << c_str );
    write_Docu(aTitle.Add_Row(), i_ce);
    CurOut() << new Html::HorizontalLine();
                      
    dyn_ce_list 
        dpConstants;
    ary::idl::ifc_constgroup::attr::Get_Constants(dpConstants, i_ce);
    
    if ( BOOL_OF(*dpConstants) )
    {               
        produce_Members( *dpConstants,
                         C_sList_Constants,
                         C_sList_Constants_Label,
                         C_sList_ConstantDetails,
                         C_sList_ConstantDetails_Label );
        pNaviSubRow->SwitchOn(sli_ConstantsSummary);
        pNaviSubRow->SwitchOn(sli_ConstantDetails);
    }
    pNaviSubRow->Produce_Row();
}

HF_NaviSubRow &
HF_IdlConstGroup::make_Navibar( const client & i_ce ) const
{
    HF_IdlNavigationBar
        aNaviBar(Env(), CurOut());
    aNaviBar.Produce_CeMainRow(i_ce,true);  // true := avoid link to Use-page.

    DYN HF_NaviSubRow &
        ret = aNaviBar.Add_SubRow();
    ret.AddItem(C_sList_Constants, C_sList_Constants_Label, false);
    ret.AddItem(C_sList_ConstantDetails, C_sList_ConstantDetails_Label, false);
    
    CurOut() << new Html::HorizontalLine();
    return ret;
}

void                
HF_IdlConstGroup::produce_MemberDetails( HF_SubTitleTable &  o_table,
                                         const client &      i_ce ) const
{
    HF_IdlConstant
        aElement( Env(), o_table );
    aElement.Produce_byData(i_ce);
}

