/*************************************************************************
 *
 *  $RCSfile: pe_file.hxx,v $
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

#ifndef ADC_CPP_PE_FILE_HXX
#define ADC_CPP_PE_FILE_HXX



// USED SERVICES
    // BASE CLASSES
#include "cpp_pe.hxx"
    // COMPONENTS
#include <ary/ids.hxx>
#include <semantic/callf.hxx>
#include <semantic/sub_peu.hxx>
    // PARAMETERS


namespace cpp {

    class PeEnvironment;

    class PE_Namespace;
    class PE_Enum;
    class PE_Typedef;
    class PE_VarFunc;
    class PE_TemplateTop;
    class PE_Defines;
    class PE_Ignore;

#if 0
class PE_Template;
class PE_Extern;
#endif


class PE_File : public Cpp_PE
{
  public:
    enum E_State
    {
        std,      		///	before class, struct or union
        in_extern,
        in_externC,
        size_of_states
    };

                        PE_File(
                            PeEnvironment &     io_rEnv );
                        ~PE_File();

    virtual void		Call_Handler(
                            const cpp::Token &	i_rTok );
    virtual Cpp_PE *    Handle_ChildFailure();  

    ary::cpp::RwGate &	AryGate() const;

  private:
    typedef SubPe< PE_File, PE_Namespace>	SP_Namespace;
    typedef SubPe< PE_File, PE_Typedef>		SP_Typedef;
    typedef SubPe< PE_File, PE_VarFunc>	    SP_VarFunc;
    typedef SubPe< PE_File, PE_TemplateTop>	SP_Template;
    typedef SubPe< PE_File, PE_Defines>	    SP_Defines;
    typedef SubPe< PE_File, PE_Ignore >		SP_Ignore;
#if 0
    typedef SubPe< PE_File, PE_Using>		SP_Using;
#endif // 0

    typedef SubPeUse< PE_File, PE_Namespace>    SPU_Namespace;
    typedef SubPeUse< PE_File, PE_Typedef>		SPU_Typedef;
    typedef SubPeUse< PE_File, PE_VarFunc> 		SPU_VarFunc;
    typedef SubPeUse< PE_File, PE_TemplateTop>	SPU_Template;
    typedef SubPeUse< PE_File, PE_Defines>	    SPU_Defines;
    typedef SubPeUse< PE_File, PE_Ignore> 		SPU_Ignore;

    void				Setup_StatusFunctions();
    virtual void		InitData();
    virtual void		TransferData();
    void  				Hdl_SyntaxError( const char *);

    void				SpReturn_VarFunc();
    void				SpReturn_Template();

    void  				On_std_namespace(const char * i_sText);
    void  				On_std_ClassKey(const char * i_sText);
    void  				On_std_typedef(const char * i_sText);
    void  				On_std_enum(const char * i_sText);
    void  				On_std_VarFunc(const char * i_sText);
    void  				On_std_template(const char * i_sText);
    void				On_std_extern(const char * i_sText);
    void  				On_std_using(const char * i_sText);
    void  				On_std_SwBracketRight(const char * i_sText);

    void  				On_std_DefineName(const char * i_sText);
    void  				On_std_MacroName(const char * i_sText);

    void                On_in_extern_Constant(const char * i_sText);
    void                On_in_extern_Ignore(const char * i_sText);
    void                On_in_externC_SwBracket_Left(const char * i_sText);
    void                On_in_externC_NoBlock(const char * i_sText);

    PeEnvironment &     Env()                   { return *pEnv; }


    // DATA
    PeEnvironment *		pEnv;

    Dyn< PeStatusArray<PE_File> >
                        pStati;

    Dyn<SP_Namespace>	pSpNamespace;
    Dyn<SP_Typedef>		pSpTypedef;
    Dyn<SP_VarFunc>	    pSpVarFunc;
    Dyn<SP_Template>	pSpTemplate;
    Dyn<SP_Defines>	    pSpDefs;

    Dyn<SP_Ignore>		pSpIgnore;
#if 0
    SP_Using			aSpUsing;
#endif // 0

    Dyn<SPU_Namespace>	pSpuNamespace;
    Dyn<SPU_Typedef> 	pSpuTypedef;
    Dyn<SPU_VarFunc>	pSpuVarFunc;
    Dyn<SPU_Template>	pSpuTemplate;
    Dyn<SPU_Defines>	pSpuDefs;

    Dyn<SPU_Ignore>		pSpuUsing;
    Dyn<SPU_Ignore>		pSpuIgnoreFailure;

    bool                bWithinSingleExternC;   /** After 'extern "C"' without following '{',
                                                    waiting for the next function or variable to
                                                    set back to false.
                                                */
};

}   // namespace cpp



#if 0	// Branches

namespace
    -> Named Namespace declaration
    -> Unnamed Namespace declaration
    -> Namespace alias definition

class struct union
    -> Class
    -> Predeclaration

typedef
    -> Typedef

enum
    -> Enum

extern
    -> Extern-"C"
    -> TypeDeclaration

TypeDeclaration
    -> FunctionDecl
    -> FunctionDef
    -> Variable

template
    -> TemplateClass
    -> TemplateFunction
    -> TemplateFunction/Method-Implementation
    -> TemplatePredeclaration

}
    -> End of Namespace
    -> End of Extern-"C"

asm
    -> AssemblerDeclaration

using
    -> Using-Declaration
    -> Using-Directive

#endif // 0


#endif

