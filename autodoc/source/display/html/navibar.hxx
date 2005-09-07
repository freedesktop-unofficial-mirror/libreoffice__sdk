/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: navibar.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 17:32:02 $
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

#ifndef ADC_DISPLAY_HTML_NAVIBAR_HXX
#define ADC_DISPLAY_HTML_NAVIBAR_HXX



// USED SERVICES
    // BASE CLASSES
#include <ary/cpp/cpp_disp.hxx>
#include "hdimpl.hxx"
    // COMPONENTS
    // PARAMETERS

namespace ary
{
    class CodeEntity;
}


/** Creates a HTML navigation bar wth the following parts:

    A main bar with fixed items.
    Zero to several subbars with user defined items, depending of
    the contents of the page.

    The main bar contains those items:

    Overview | Namespace | Class | Tree | Project | File | Index | Help
*/
class NavigationBar
{
  public:
    enum E_GlobalLocation
    {
        LOC_Overview,
        LOC_AllDefs,
        LOC_Index,
        LOC_Help
    };
    enum E_CeGatheringType
    {
        CEGT_operations,
        CEGT_data
    };

    /// Used for Overview, Index and Help.
                        NavigationBar(
                            const OuputPage_Environment &
                                                i_rEnv,
                            E_GlobalLocation    i_eLocation );
    /// Used for all Ces except operations and data.
                        NavigationBar(
                            const OuputPage_Environment &
                                                i_rEnv,
                            const ary::CodeEntity &
                                                i_rCe );
    /** Used for operations and data.
        If functions or data ar non-members, i_pFile has to be != 0.
    */
                        NavigationBar(
                            const OuputPage_Environment &
                                                i_rEnv,
                            E_CeGatheringType   i_eCeGatheringType,
                            const ary::cpp::FileGroup *
                                                i_pFile = 0 );
    /** Used for
            Project: i_pProj == 0.
            File:    i_pProj != 0 and i_pFile == 0.
            Defs:    i_pProj != 0 and i_pFile != 0.
    */
                        NavigationBar(
                            const OuputPage_Environment &
                                                i_rEnv,
                            const ary::cpp::ProjectGroup *
                                                i_pPrj,
                            const ary::cpp::FileGroup *
                                                i_pFile = 0 );
                        ~NavigationBar();

    void	  	        MakeSubRow(
                            const char *		i_sTitle );
    void	  	        AddItem(                /// Items are added to last made sub-row.
                            const char *		i_sName,
                            const char *        i_sLink,
                            bool                i_bValid );
    /** This writes the main bar and the pSubRowTable to o_rOut.
        The pSubRowsTable stays in memory and can be filled later,
        when all SubRow items are known.
    */
    void                Write(
                            csi::xml::Element & o_rOut,
                            bool                i_bWithSubRows = false ) const;
    void                Write_SubRows() const;

  private:
    struct CheshireCat;
    Dyn<CheshireCat>    pi;
    csi::html::Table *  pSubRowsTable;
};



#endif

