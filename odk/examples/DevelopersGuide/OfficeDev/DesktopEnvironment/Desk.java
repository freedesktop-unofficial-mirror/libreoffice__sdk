/*************************************************************************
 *
 *  $RCSfile: Desk.java,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2004-02-02 20:00:35 $
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

package OfficeDev.samples.DesktopEnvironment;

// __________ Imports __________

// structs, const ...
import com.sun.star.beans.PropertyValue;
import com.sun.star.frame.DispatchResultEvent;
import com.sun.star.frame.DispatchResultState;

// interfaces
import com.sun.star.frame.XDispatchResultListener;
import com.sun.star.frame.XFrame;
import com.sun.star.lang.XComponent;

// helper
import com.sun.star.uno.UnoRuntime;

// Exceptions
import java.lang.IllegalMonitorStateException;
import java.lang.InterruptedException;

// base classes
import java.lang.String;

// __________ Implementation __________

/**
 * TODO
 *
 * @author     Andreas Schl&uuml;ns
 * @created    08.02.2002 14:05
 */
public class Desk
{
    // ____________________

    /**
     * main
     * Establish connection to a remote office and starts the demo application.
     * User can overwrite some of neccessary start options by using command line parameters.
     *
     * syntax: Desk [host=<hostname>] [port=<portnumber>] [mode={inplace|outplace}] [file=<filename>]
     *
     * @param  args  command line arguments
     *                  host        describe host on which remote office runs
     *                              default=localhost
     *                  port        describe port which is used by remote office
     *                              default=2083
     *                  mode        describe using mode of document view {inplace/outplace}
     *                              default=inplace
     *                  file        name of first file which should be open
     *                              default="private:factory/swriter" to open empty writer document
     */
    public static void main(String[] lArguments)
    {
        // Analyze command line parameters.
        String  sHost  = new String("localhost");
        String  sPort  = new String("2083");
        String  sMode  = new String("inplace");
        String  sFile  = new String("private:factory/swriter");

        for(int i=0; i<lArguments.length; ++i)
        {
            lArguments[i] = lArguments[i].toLowerCase();
            if(lArguments[i].startsWith("host=")==true)
                sHost = lArguments[i].substring(5);
            else
            if(lArguments[i].startsWith("port=")==true)
                sPort = lArguments[i].substring(5);
            else
            if(lArguments[i].startsWith("mode=")==true)
                sMode = lArguments[i].substring(5);
            else
            if(lArguments[i].startsWith("file=")==true)
                sFile = lArguments[i].substring(5);
        }

        ViewContainer.mbInplace = (sMode.compareTo("inplace")==0);

        // Connect to remote office.
        OfficeConnect.createConnection(sHost,sPort);

        // Create first document view.
        // This one will register himself at the global
        // ViewContainer. Further views will be open
        // automaticly started from this first one.
        DocumentView aView = new DocumentView();
        aView.setVisible(true);
        aView.createFrame();
        aView.load(sFile);
    }
}
