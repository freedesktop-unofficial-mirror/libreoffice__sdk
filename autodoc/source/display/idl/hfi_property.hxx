        /*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: hfi_property.hxx,v $
 * $Revision: 1.4 $
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

#ifndef ADC_DISPLAY_HFI_PROPERTY_HXX
#define ADC_DISPLAY_HFI_PROPERTY_HXX



// USED SERVICES
    // BASE CLASSES
#include "hi_factory.hxx"
    // COMPONENTS
    // PARAMETERS

class HF_SubTitleTable;

class HF_IdlDataMember : public HtmlFactory_Idl
{
  public:
    void                Produce_byData(
                            const client &      ce ) const;
  protected:
                        HF_IdlDataMember(
                            Environment &       io_rEnv,
                            HF_SubTitleTable &  o_table );
    virtual             ~HF_IdlDataMember() {}

  private:
    /// @descr Must enclose writing a horizontal line.
    virtual void        write_Declaration(
                            const client &      i_ce ) const = 0;

    void                enter_ContentCell() const;
    void                leave_ContentCell() const;
};



class HF_IdlProperty : public HF_IdlDataMember
{
  public:
                        HF_IdlProperty(
                            Environment &       io_rEnv,
                            HF_SubTitleTable &  o_table )
                            :   HF_IdlDataMember(io_rEnv, o_table) {}
    virtual             ~HF_IdlProperty();
  private:
    virtual void        write_Declaration(
                            const client &      i_ce ) const;
};

class HF_IdlAttribute : public HF_IdlDataMember
{
  public:
                        HF_IdlAttribute(
                            Environment &       io_rEnv,
                            HF_SubTitleTable &  o_table )
                            :   HF_IdlDataMember(io_rEnv, o_table) {}
    virtual             ~HF_IdlAttribute();

  private:
    virtual void        write_Declaration(
                            const client &      i_ce ) const;
};


class HF_IdlEnumValue : public HF_IdlDataMember
{
  public:
                        HF_IdlEnumValue(
                            Environment &       io_rEnv,
                            HF_SubTitleTable &  o_table )
                            :   HF_IdlDataMember(io_rEnv, o_table) {}
    virtual             ~HF_IdlEnumValue();

  private:
    virtual void        write_Declaration(
                            const client &      i_ce ) const;
};

class HF_IdlConstant : public HF_IdlDataMember
{
  public:
                        HF_IdlConstant(
                            Environment &       io_rEnv,
                            HF_SubTitleTable &  o_table )
                            :   HF_IdlDataMember(io_rEnv, o_table) {}
    virtual             ~HF_IdlConstant();

  private:
    virtual void        write_Declaration(
                            const client &      i_ce ) const;
};


class HF_IdlStructElement : public HF_IdlDataMember
{
  public:
                        HF_IdlStructElement(
                            Environment &       io_rEnv,
                            HF_SubTitleTable &  o_table )
                            :   HF_IdlDataMember(io_rEnv, o_table) {}
    virtual             ~HF_IdlStructElement();

  private:
    virtual void        write_Declaration(
                            const client &      i_ce ) const;
};


#endif
