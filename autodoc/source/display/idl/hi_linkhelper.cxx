/*************************************************************************
 *
 *  $RCSfile: hi_linkhelper.cxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: np $ $Date: 2002-11-01 17:14:57 $
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
#include "hi_linkhelper.hxx"


// NOT FULLY DEFINED SERVICES      
#include <ary/idl/i_module.hxx>



                   
const ary::idl::Module *  
LinkHelper::Search_CurModule() const
{           
    return Search_Module( rEnv.CurPosition().RelatedNode() );               
}

const ary::idl::Module *  
LinkHelper::Search_Module( output::Node & i_node ) const
{
    static StringVector aNames_;

    output::Node::relative_id
        nId = i_node.RelatedNameRoom();
    if (nId == 0)
    {                          
        csv::erase_container(aNames_);
        i_node.Get_Chain(aNames_);
        const ary::idl::Module *  pModule =
            rEnv.Data().Search_Module(aNames_);
        if ( pModule == 0 )
            return 0;
        nId = static_cast<output::Node::relative_id>(pModule->Id());
        rEnv.CurPosition().RelatedNode().Set_RelatedNameRoom(nId);
    }                     
    
    return & rEnv.Data().Find_Module( static_cast<ary::idl::Ce_id>(nId) );
}

LinkHelper::OutPosition         
LinkHelper::PositionOf_Ce(const CE & i_ce) const
{
    static StringVector aModule_;
    csv::erase_container(aModule_);
    String sCe;
    String sMember;
    rEnv.Data().Get_CeText(aModule_, sCe, sMember, i_ce); 
    output::Node & 
        rNode = rEnv.OutputTree().RootNode().Provide_Child(aModule_);
    return OutPosition(rNode,sCe);
}
                
                              
namespace
{
    const String C_sXrefsSuffix("-xref");                
}

                
LinkHelper::OutPosition         
LinkHelper::PositionOf_CurXRefs( const String & i_ceName ) const
{                                                       
    return OutPosition( rEnv.CurPosition(),
                        StreamLock(100)() << i_ceName 
                                              << C_sXrefsSuffix        
                                              << ".html"
                                              << c_str );
}

const String &      
LinkHelper::XrefsSuffix() const
{
    return C_sXrefsSuffix;
}

      
String 
nameChainLinker( const char * )
{           
    static const String 
        sModuleFileName_( output::ModuleFileName() );   
    return sModuleFileName_;    
}
