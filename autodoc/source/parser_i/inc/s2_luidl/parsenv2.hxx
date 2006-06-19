/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: parsenv2.hxx,v $
 *
 *  $Revision: 1.9 $
 *
 *  last change: $Author: hr $ $Date: 2006-06-19 12:09:54 $
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

#ifndef LUIDL_PARSENV2_HXX
#define LUIDL_PARSENV2_HXX


// USED SERVICES
    // BASE CLASSES
#include <s2_luidl/tokproct.hxx>
    // COMPONENTS
#include <s2_luidl/semnode.hxx>
    // PARAMETERS
#include <ary/idl/i_language.hxx>
#include <ary/idl/i_module.hxx>

// [ed] 6/15/02 The OS X compilers require full class definitions at the time
// of template instantiation
// np:  Is this really so?
#ifdef MACOSX
#include <ary_i/codeinf2.hxx>
#endif


class ParserInfo;

namespace ary
{
    class QualifiedName;

    namespace n22
    {
        class Repository;
    }


    namespace idl
    {
        class CodeEntity;
    }

    namespace info
    {
        class CodeInformation;
    }
}



namespace csi
{
namespace uidl
{


class Token;
class SemanticNode;


class UnoIDL_PE : virtual protected TokenProcessing_Types
{
  public:
    virtual             ~UnoIDL_PE();

    virtual void	 	EstablishContacts(
                            UnoIDL_PE *			io_pParentPE,
                            ary::n22::Repository &
                                                io_rRepository,
                            TokenProcessing_Result &
                                                o_rResult );
//	virtual void	 	EstablishContacts(
//							UnoIDL_PE *			io_pParentPE,
//							ary::idl::Gate &
//                                                io_rGate,
//							TokenProcessing_Result &
//												o_rResult );
    virtual void		Enter(
                            E_EnvStackAction	i_eWayOfEntering );
    virtual void		Leave(
                            E_EnvStackAction	i_eWayOfLeaving );
    virtual void	  	ProcessToken(
                            const Token &		i_rToken ) = 0;

    void				SetDocu(
                            DYN ary::info::CodeInformation *
                                                let_dpDocu );
    void				SetPublished();
    void				SetOptional();
    void				PassDocuAt(
                            ary::idl::CodeEntity &
                                                io_rCe );

    UnoIDL_PE *			Parent() const			{ return aMyNode.Parent(); }

    void				SetResult(
                            E_TokenDone			i_eDone,
                            E_EnvStackAction	i_eWhat2DoWithEnvStack,
                            UnoIDL_PE *			i_pParseEnv2Push = 0 )
                                                { aMyNode.SetTokenResult( i_eDone, i_eWhat2DoWithEnvStack, i_pParseEnv2Push ); }
    virtual const ary::idl::Module &
                        CurNamespace() const;
    virtual const ParserInfo &
                        ParseInfo() const;
    ary::idl::Gate &	Gate() const			{ return aMyNode.AryGate(); }
    TokenProcessing_Result &
                        TokenResult() const     { return aMyNode.TokenResult(); }
    DYN ary::info::CodeInformation *
                        ReleaseDocu()			{ return pDocu.Release(); }
  protected:
                        UnoIDL_PE();
    ary::n22::Repository &
                        MyRepository()          { csv_assert(pRepository != 0);
                                                  return *pRepository;  }
  private:
    virtual void		InitData();
    virtual void		TransferData() = 0;
    virtual void		ReceiveData();

    SemanticNode		aMyNode;
    Dyn<ary::info::CodeInformation>
                        pDocu;
    ary::n22::Repository *
                        pRepository;
};


// IMPLEMENTATION



}   // namespace uidl
}   // namespace csi

#endif

