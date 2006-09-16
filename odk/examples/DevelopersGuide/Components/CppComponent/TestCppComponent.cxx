/*************************************************************************
 *
 *  $RCSfile: TestCppComponent.cxx,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: obo $ $Date: 2006-09-17 00:09:36 $
 *
 *  The Contents of this file are made available subject to the terms of
 *  the BSD license.
 *  
 *  Copyright (c) 2003 by Sun Microsystems, Inc.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. Neither the name of Sun Microsystems, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 *  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
 *  TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 *  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *     
 *************************************************************************/

// MARKER(update_precomp.py): autogen include statement, do not remove
#include "precompiled_odk.hxx"

#include <iostream>
#include <cppuhelper/bootstrap.hxx>
#include <com/sun/star/bridge/XUnoUrlResolver.hpp>
#include <com/sun/star/frame/XComponentLoader.hpp>
#include <my_module/MyService1.hpp>
#include <my_module/MyService2.hpp>

using namespace std;
using namespace rtl;
using namespace com::sun::star::uno;
//namespace cssuno = ::com::sun::star::uno;
using namespace com::sun::star::lang;
using namespace com::sun::star::frame;

int SAL_CALL main( int, char ** )
{
    try
    {
        // get the remote office component context
        Reference< XComponentContext > xContext( ::cppu::bootstrap() ); 
        cout << "\nconnected to a running office...\n";

        // create a new instance of MyService1
        Reference<my_module::XSomething> xSomething =
            my_module::MyService1::create(xContext);

        // call methodOne and print the return value on stdout
        OUString s = xSomething->methodOne(OUString(RTL_CONSTASCII_USTRINGPARAM("Hello World!")));
        cout << "\nCreate new instance of MyService1\n"
             << "Call of XSomething.methOne at MyService1 = "
             << OUStringToOString( s, RTL_TEXTENCODING_ASCII_US ).getStr();

        // create a new instance of MyService2 with the specified string argument
        xSomething = my_module::MyService2::create(xContext, OUString(RTL_CONSTASCII_USTRINGPARAM("Hello My World!")));

        // call methodTwo and print the return value of methodTwo
        s = xSomething->methodTwo();
        cout << "\n\nCreate new instance of MyService2 with argument\n"
             << "Call of XSomething.methTwo at MyService2 = "
             << OUStringToOString( s, RTL_TEXTENCODING_ASCII_US ).getStr();

        cout <<"\n\nPlease press 'return' to finish the example!\n";
        getchar();
    }
    catch ( ::cppu::BootstrapException & e )
    {
        cerr << "\ncaught BootstrapException: "
             << OUStringToOString( e.getMessage(), RTL_TEXTENCODING_ASCII_US ).getStr()
             << '\n';
        return 1;
    }
    catch ( Exception & e )
    {
        cerr << "\ncaught UNO exception: "
             << OUStringToOString( e.Message, RTL_TEXTENCODING_ASCII_US ).getStr()
             << '\n';
        return 1;
    }

    return 0;
}
