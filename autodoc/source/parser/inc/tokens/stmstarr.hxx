/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: stmstarr.hxx,v $
 * $Revision: 1.3 $
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

#ifndef ADC_STMSTARR_HXX
#define ADC_STMSTARR_HXX

// USED SERVICES
    // BASE CLASSES
#include <tokens/stmstate.hxx>
    // COMPONENTS
    // PARAMETERS
#include <tokens/token.hxx>


class StmArrayStatus : public StmStatus
{
  public:
    typedef TextToken::F_CRTOK F_CRTOK;

    // LIFECYCLE
                        StmArrayStatus(
                            intt				i_nStatusSize,
                            const INT16 * 		in_aArrayModel,
                            F_CRTOK				i_fTokenCreateFunction,
                            bool				in_bIsDefault );
                        ~StmArrayStatus();

    // INQUIRY
    StmStatus::Branch	NextBy(
                            intt				in_nFollowersIndex) const;
    F_CRTOK      		TokenCreateFunction() const
                                                { return fTokenCreateFunction; }
    virtual bool		IsADefault() const;

    // ACCESS
    virtual StmArrayStatus *
                        AsArray();
    void				SetBranches(
                            intt 				in_nStartBranchIx,
                            StmStatus::Branch *	in_aBranchValues,
                            intt            	in_nNrofValues );
    bool 				SetBranch(
                            intt				in_nBranchIx,
                            StmStatus::Branch	in_nBranch );
    void   				SetTokenCreateFunction(
                            F_CRTOK				i_fTokenCreateFunction );
  private:
    StmStatus::Branch *	dpBranches;
    intt				nNrOfBranches;
    F_CRTOK				fTokenCreateFunction;
    bool				bIsADefault;
};


// IMPLEMENTATION

inline void
StmArrayStatus::SetTokenCreateFunction( F_CRTOK i_fTokenCreateFunction )
    { fTokenCreateFunction = i_fTokenCreateFunction; }



#endif


