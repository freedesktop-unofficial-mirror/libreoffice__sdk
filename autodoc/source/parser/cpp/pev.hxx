/*************************************************************************
 *
 *  $RCSfile: pev.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: np $ $Date: 2002-03-08 14:45:30 $
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

#ifndef ADC_CPP_PEV_HXX
#define ADC_CPP_PEV_HXX



// USED SERVICES
    // BASE CLASSES
#include <tokens/tokproct.hxx>
    // COMPONENTS
    // PARAMETERS
#include <ary/cpp/c_etypes.hxx>

namespace ary
{
    namespace cpp
    {
        class RwGate;
        class InputContext;

        class Namespace;
        class Class;
        class Enum;
        class Typedef;
        class Function;
        class Variable;
        class EnumValue;

        class CppDefinition;
    }

    class Documentation;
}


namespace cpp
{


class PeEnvironment : protected TokenProcessing_Types
{
  public:
    // INQUIRY
    virtual				~PeEnvironment() {}

    // OPERATIONS
        // Token results
    void				SetTokenResult(
                            E_TokenDone			i_eDone,
                            E_EnvStackAction	i_eWhat2DoWithEnvStack,
                            ParseEnvironment *	i_pParseEnv2Push = 0 );

        // Owner stack
    void                OpenNamespace(
                            ary::cpp::Namespace &
                                                io_rOpenedNamespace );
    void                OpenExternC(
                            bool				i_bOnlyForOneDeclaration = false );
    void                OpenClass(
                            ary::cpp::Class &	io_rOpenedClass );
    void                OpenEnum(
                            ary::cpp::Enum &	io_rOpenedEnum );
    void                CloseBlock();           /// Handles a '}' on file scope.
    void                CloseClass();
    void                CloseEnum();
    void                SetCurProtection(       /// Handles 'public:', 'protected:' and 'private:' on class scope.
                            ary::cpp::E_Protection
                                                i_eProtection );
    void                OpenTemplate(
                            const StringVector &
                                                i_rParameters );
    /// Removes parameters from this object.
    DYN StringVector *
                        Get_CurTemplateParameters();

        // Special events
    void                Event_Class_FinishedBase(
                            const udmstri &     i_sParameterName );

    void                Event_Store_Typedef(
                            ary::cpp::Typedef & io_rTypedef );
    void                Event_Store_EnumValue(
                            ary::cpp::EnumValue &
                                                io_rEnumValue );
    void                Event_Store_CppDefinition(
                            ary::cpp::CppDefinition &
                                                io_rDefinition );

    void                Event_EnterFunction_ParameterList();
    void                Event_Function_FinishedParameter(
                            const udmstri &     i_sParameterName );
    void                Event_LeaveFunction_ParameterList();
    void                Event_EnterFunction_Implementation();
    void                Event_LeaveFunction_Implementation();

    void                Event_Store_Function(
                            ary::cpp::Function &
                                                io_rFunction );
    void                Event_Store_Variable(
                            ary::cpp::Variable &
                                                io_rVariable );
        // Error recovery
    void                StartWaitingFor_Recovery();

    // INQUIRY
    ary::cpp::RwGate &  AryGate() const;
    const ary::cpp::InputContext &
                        Context() const;
    udmstri             CurFileName() const;
    uintt               LineCount() const;
    bool                IsWaitingFor_Recovery() const;
    bool                IsExternC() const;

  private:
    virtual void        do_SetTokenResult(
                            E_TokenDone			i_eDone,
                            E_EnvStackAction	i_eWhat2DoWithEnvStack,
                            ParseEnvironment *	i_pParseEnv2Push ) = 0;
    virtual void        do_OpenNamespace(
                            ary::cpp::Namespace &
                                                io_rOpenedNamespace ) = 0;
    virtual void        do_OpenExternC(
                            bool				i_bOnlyForOneDeclaration ) = 0;
    virtual void        do_OpenClass(
                            ary::cpp::Class &	io_rOpenedClass ) = 0;
    virtual void        do_OpenEnum(
                            ary::cpp::Enum &	io_rOpenedEnum ) = 0;
    virtual void        do_CloseBlock() = 0;
    virtual void        do_CloseClass() = 0;
    virtual void        do_CloseEnum() = 0;
    virtual void        do_SetCurProtection(
                            ary::cpp::E_Protection
                                                i_eProtection ) = 0;
    virtual void        do_OpenTemplate(
                            const StringVector &
                                                i_rParameters ) = 0;
    virtual DYN StringVector *
                        do_Get_CurTemplateParameters() = 0;
    virtual void        do_Event_Class_FinishedBase(
                            const udmstri &     i_sBaseName ) = 0;

    virtual void        do_Event_Store_Typedef(
                            ary::cpp::Typedef & io_rTypedef ) = 0;
    virtual void        do_Event_Store_EnumValue(
                            ary::cpp::EnumValue &
                                                io_rEnumValue ) = 0;
    virtual void        do_Event_Store_CppDefinition(
                            ary::cpp::CppDefinition &
                                                io_rDefinition ) = 0;
    virtual void        do_Event_EnterFunction_ParameterList() = 0;
    virtual void        do_Event_Function_FinishedParameter(
                            const udmstri &     i_sParameterName ) = 0;
    virtual void        do_Event_LeaveFunction_ParameterList() = 0;
    virtual void        do_Event_EnterFunction_Implementation() = 0;
    virtual void        do_Event_LeaveFunction_Implementation() = 0;
    virtual void        do_Event_Store_Function(
                            ary::cpp::Function &
                                                io_rFunction ) = 0;
    virtual void        do_Event_Store_Variable(
                            ary::cpp::Variable &
                                                io_rVariable ) = 0;
    virtual void        do_StartWaitingFor_Recovery() = 0;
    virtual ary::cpp::RwGate &
                        inq_AryGate() const = 0;
    virtual const ary::cpp::InputContext &
                        inq_Context() const = 0;
    virtual udmstri		inq_CurFileName() const = 0;
    virtual uintt       inq_LineCount() const = 0;
    virtual bool        inq_IsWaitingFor_Recovery() const = 0;
    virtual bool        inq_IsExternC() const = 0;
};



// IMPLEMENTATION

inline void
PeEnvironment::SetTokenResult( E_TokenDone			i_eDone,
                               E_EnvStackAction	    i_eWhat2DoWithEnvStack,
                               ParseEnvironment *	i_pParseEnv2Push )
    { do_SetTokenResult(i_eDone, i_eWhat2DoWithEnvStack,  i_pParseEnv2Push); }
inline void
PeEnvironment::OpenNamespace( ary::cpp::Namespace & io_rOpenedNamespace )
    { do_OpenNamespace(io_rOpenedNamespace); }
inline void
PeEnvironment::OpenExternC( bool i_bOnlyForOneDeclaration )
    { do_OpenExternC(i_bOnlyForOneDeclaration); }
inline void
PeEnvironment::OpenClass( ary::cpp::Class &	io_rOpenedClass )
    { do_OpenClass(io_rOpenedClass); }
inline void
PeEnvironment::OpenEnum( ary::cpp::Enum & io_rOpenedEnum )
    { do_OpenEnum(io_rOpenedEnum); }
inline void
PeEnvironment::CloseBlock()
    { do_CloseBlock(); }
inline void
PeEnvironment::CloseClass()
    { do_CloseClass(); }
inline void
PeEnvironment::CloseEnum()
    { do_CloseEnum(); }
inline void
PeEnvironment::SetCurProtection( ary::cpp::E_Protection i_eProtection )
    { do_SetCurProtection(i_eProtection); }
inline void
PeEnvironment::OpenTemplate( const StringVector & i_rParameters )
    { do_OpenTemplate(i_rParameters); }
inline DYN StringVector *
PeEnvironment::Get_CurTemplateParameters()
    { return do_Get_CurTemplateParameters(); }
inline void
PeEnvironment::Event_Class_FinishedBase( const udmstri &  i_sBaseName )
    { do_Event_Class_FinishedBase(i_sBaseName); }
inline void
PeEnvironment::Event_Store_Typedef( ary::cpp::Typedef & io_rTypedef )
    { do_Event_Store_Typedef(io_rTypedef); }
inline void
PeEnvironment::Event_Store_EnumValue( ary::cpp::EnumValue & io_rEnumValue )
    { do_Event_Store_EnumValue(io_rEnumValue); }
inline void
PeEnvironment::Event_Store_CppDefinition( ary::cpp::CppDefinition & io_rDefinition )
    { do_Event_Store_CppDefinition(io_rDefinition); }
inline void
PeEnvironment::Event_EnterFunction_ParameterList()
    { do_Event_EnterFunction_ParameterList(); }
inline void
PeEnvironment::Event_Function_FinishedParameter( const udmstri & i_sParameterName )
    { do_Event_Function_FinishedParameter(i_sParameterName); }
inline void
PeEnvironment::Event_LeaveFunction_ParameterList()
    { do_Event_LeaveFunction_ParameterList(); }
inline void
PeEnvironment::Event_EnterFunction_Implementation()
    { do_Event_EnterFunction_Implementation(); }
inline void
PeEnvironment::Event_LeaveFunction_Implementation()
    { do_Event_LeaveFunction_Implementation(); }
inline void
PeEnvironment::Event_Store_Function( ary::cpp::Function & io_rFunction )
    { do_Event_Store_Function(io_rFunction); }
inline void
PeEnvironment::Event_Store_Variable( ary::cpp::Variable & io_rVariable )
    { do_Event_Store_Variable(io_rVariable); }
inline void
PeEnvironment::StartWaitingFor_Recovery()
    { do_StartWaitingFor_Recovery(); }
inline ary::cpp::RwGate &
PeEnvironment::AryGate() const
    { return inq_AryGate(); }
inline const ary::cpp::InputContext &
PeEnvironment::Context() const
    { return inq_Context(); }
inline udmstri
PeEnvironment::CurFileName() const
    { return inq_CurFileName(); }
inline uintt
PeEnvironment::LineCount() const
    { return inq_LineCount(); }
inline bool
PeEnvironment::IsWaitingFor_Recovery() const
    { return inq_IsWaitingFor_Recovery(); }
inline bool
PeEnvironment::IsExternC() const
    { return inq_IsExternC(); }



}   // namespace cpp


#endif

