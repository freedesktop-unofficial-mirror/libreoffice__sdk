/*************************************************************************
 *
 *  $RCSfile: hfi_service.hxx,v $
 *
 *  $Revision: 1.1 $
 *
 *  last change: $Author: np $ $Date: 2002-11-01 17:14:41 $
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

#ifndef ADC_DISPLAY_HFI_SERVICE_HXX
#define ADC_DISPLAY_HFI_SERVICE_HXX


// USED SERVICES
    // BASE CLASSES
#include "hi_factory.hxx"
    // COMPONENTS
    // PARAMETERS

class HF_NaviSubRow;
class HF_SubTitleTable;

class HF_IdlService : public HtmlFactory_Idl
{
  public:
    typedef ::ary::StdConstIterator< ::ary::idl::CommentedReference> comref_list;
                        HF_IdlService(
                            Environment &       io_rEnv,    // The CurDirecory() is the one of the here displayed Module.
                            Xml::Element &      o_rOut );
    virtual             ~HF_IdlService();

    void                Produce_byData(
                           const client &       i_ce ) const;
   private:
    DYN HF_NaviSubRow & make_Navibar(
                            const client &      i_ce ) const;

    void                produce_IncludedServices(    
                            const client &      i_ce,
                            comref_list &       it_list ) const;
    void                produce_ExportedInterfaces(
                            const client &      i_ce,
                            comref_list &       it_list ) const;

    void                produce_Link(                                    
                            Xml::Element &      o_row,
                            type_id             i_type ) const;                            
    void                produce_LinkDoc(                                    
                            const client &      i_ce,
                            Xml::Element &      o_row,
                            comref_list &       i_commentedRef ) const;                            

    void                produce_MemberDetails(        /// of property
                            HF_SubTitleTable &  o_table,
                            const client &      i_ce ) const;                            
};



// IMPLEMENTATION

extern const String
    C_sCePrefix_Service;



#endif


