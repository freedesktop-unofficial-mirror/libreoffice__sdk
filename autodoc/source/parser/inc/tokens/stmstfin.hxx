/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
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

#ifndef ADC_STMSTFIN_HXX
#define ADC_STMSTFIN_HXX

// USED SERVICES
    // BASE CLASSES
#include <tokens/stmstate.hxx>
    // COMPONENTS
    // PARAMETERS


class TkpContext;
class StateMachineContext;

/**
**/
class StmBoundsStatus : public StmStatus
{
  public:
    // LIFECYCLE
                        StmBoundsStatus(
                            StateMachineContext &
                                                o_rOwner,
                            TkpContext &		i_rFollowUpContext,
                            uintt				i_nStatusFunctionNr,
                            bool            	i_bIsDefault  );
    // INQUIRY
    TkpContext *		FollowUpContext();
    uintt       		StatusFunctionNr() const;
    virtual bool	   	IsADefault() const;

    // ACCESS
    virtual StmBoundsStatus *
                        AsBounds();

  private:
    StateMachineContext *
                        pOwner;
    TkpContext *		pFollowUpContext;
    uintt				nStatusFunctionNr;
    bool            	bIsDefault;
};

inline TkpContext *
StmBoundsStatus::FollowUpContext()
    { return pFollowUpContext; }
inline uintt
StmBoundsStatus::StatusFunctionNr() const
    { return nStatusFunctionNr; }


#endif


