/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: ci_text.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2005-09-07 16:21:04 $
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

#ifndef ARY_INFO_CI_TEXT_HXX
#define ARY_INFO_CI_TEXT_HXX



// USED SERVICES
    // BASE CLASSES
    // COMPONENTS
    // PARAMETERS


namespace ary
{
namespace info
{

class DocuToken;
class DocuDisplay;


class DocuText
{
  public:
    typedef std::vector< DocuToken * >	TokenList;

                        DocuText();
                        ~DocuText();

    void                Set_HtmlUse(
                            bool                i_bUseIt )
                                                { bUsesHtml = i_bUseIt; }
    void              	Add_Token(
                            DYN DocuToken &		let_drToken )
                                                { aTokens.push_back(&let_drToken); }
    const TokenList &	Tokens() const			{ return aTokens; }
    void                StoreAt(
                            DocuDisplay &       o_rDisplay ) const;
    bool                IsNoHtml() const        { return NOT bUsesHtml; }
    bool                IsEmpty() const         { return aTokens.size() == 0; }

  private:
    TokenList			aTokens;
    bool                bUsesHtml;
};






// IMPLEMENTATION


}
}

#endif

