/*************************************************************************
 *
 *  $RCSfile: std_outp.hxx,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: np $ $Date: 2002-11-01 12:18:50 $
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

#ifndef CSV_STD_OUTP_HXX
#define CSV_STD_OUTP_HXX

// USED SERVICES
    // BASE CLASSES
    // COMPONENTS
#include <cosv/csv_ostream.hxx>
    // PARAMETERS




namespace csv
{

#ifdef CSV_NO_IOSTREAMS
class redirect_out : public ostream
{
  public:
    virtual             ~redirect_out() {}

    void                re_endl()               { do_re_endl(); }
    void                re_flush()              { do_re_flush(); }

    static void         set_(
                            redirect_out &      o_rStdOut,
                            redirect_out &      o_rStdErr )
                                                { pStdOut_ = &o_rStdOut;
                                                  pStdErr_ = &o_rStdErr; }

    static redirect_out &
                        std_()                  { return *pStdOut_; }
    static redirect_out &
                        err_()                  { return *pStdErr_; }
    static bool         useme_()                { return pStdOut_ != 0; }

  private:
    virtual void        do_re_endl() = 0;
    virtual void        do_re_flush() = 0;

    // DATA
    static redirect_out *
                        pStdOut_;
    static redirect_out *
                        pStdErr_;
};
#endif // defined(CSV_NO_IOSTREAMS)


inline ostream &
Cout()
{

#ifndef CSV_NO_IOSTREAMS
//    return redirect_out::useme_()
//            ?   (ostream&)( redirect_out::std_() )
//            :   (ostream&)( std::cout );
    return (ostream&)( std::cout );
#else
    csv_assert( redirect_out::useme_() );
    return redirect_out::std_();
#endif
}

inline ostream &
Cerr()
{
#ifndef CSV_NO_IOSTREAMS
//    return redirect_out::useme_()
//            ?   (ostream&)( redirect_out::err_() )
//            :   (ostream&)( std::cerr );
    return (ostream&)( std::cerr );
#else
    csv_assert( redirect_out::useme_() );
    return redirect_out::err_();
#endif
}



typedef void (*F_FLUSHING_FUNC)(ostream&, bool, int*);

void                Endl( ostream&, bool, int* );

void                Flush( ostream&, bool, int* );


}   // namespace csv



inline csv::ostream &
operator<<( csv::ostream &		    io_rStream,
            csv::F_FLUSHING_FUNC    i_fFlushingFunc )
{
#ifndef CSV_NO_IOSTREAMS
//    (*i_fFlushingFunc)( io_rStream, csv::redirect_out::useme_(), 0 );
    (*i_fFlushingFunc)( io_rStream, false, 0 );
#else
    csv_assert( csv::redirect_out::useme_() );
    (*i_fFlushingFunc)( io_rStream, true, 0 );
#endif
    return io_rStream;
}


#endif


