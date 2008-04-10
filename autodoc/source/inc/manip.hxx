/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2008 by Sun Microsystems, Inc.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * $RCSfile: manip.hxx,v $
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

#ifndef ARY_MANIP_HXX
#define ARY_MANIP_HXX

template <class XY >
class Manipulator
{
  public:
    virtual             ~Manipulator() {}

    void                operator()(
                            XY &                io_r ) const
                            { op_fcall(io_r); }
  private:
    virtual void        op_fcall(
                            XY &                io_r ) const = 0;
};

template <class XY >
class Const_Manipulator
{
  public:
    virtual             ~Const_Manipulator() {}

    void                operator()(
                            const XY &          io_r ) const
                            { op_fcall(io_r); }
  private:
    virtual void        op_fcall(
                            const XY &          io_r ) const = 0;
};


#endif

