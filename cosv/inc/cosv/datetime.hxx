/*************************************************************************
 *
 *  $RCSfile: datetime.hxx,v $
 *
 *  $Revision: 1.1.1.1 $
 *
 *  last change: $Author: np $ $Date: 2002-03-08 14:25:38 $
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

#ifndef CSV_DATETIME_HXX
#define CSV_DATETIME_HXX



namespace csv
{


class Date
{
  public:
                        Date();
                        Date(
                            unsigned 			i_nDay,
                            unsigned 			i_nMonth,
                            unsigned 			i_nYear );

    unsigned			Day() const 			{ return nData >> 24; }
    unsigned			Month() const           { return (nData & 0x00FF0000) >> 16; }
    unsigned			Year() const            { return nData & 0x0000FFFF; }

    static const Date &	Null_();

  private:
    UINT32				nData;
};

class Time
{
  public:
                        Time();
                        Time(
                            unsigned 			i_nHour,
                            unsigned 			i_nMinutes,
                            unsigned 			i_nSeconds = 0,
                            unsigned            i_nSeconds100 = 0 );

    unsigned			Hour() const 			{ return nData >> 24; }
    unsigned			Minutes() const 		{ return (nData & 0x00FF0000) >> 16; }
    unsigned			Seconds() const         { return (nData & 0x0000FF00) >> 8; }
    unsigned			Seconds100() const      { return nData & 0x000000FF; }

    static const Time &	Null_();

  private:
    UINT32				nData;
};


}   // namespace csv




#endif

