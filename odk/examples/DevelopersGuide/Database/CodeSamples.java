/*************************************************************************
 *
 *  $RCSfile: CodeSamples.java,v $
 *
 *  $Revision: 1.4 $
 *
 *  last change: $Author: hr $ $Date: 2004-02-02 19:51:34 $
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

import java.io.*;

import com.sun.star.comp.helper.RegistryServiceFactory;
import com.sun.star.comp.servicemanager.ServiceManager;
import com.sun.star.lang.XMultiServiceFactory;
import com.sun.star.lang.XSingleServiceFactory;
import com.sun.star.lang.XServiceInfo;
import com.sun.star.lang.XComponent;
import com.sun.star.bridge.XUnoUrlResolver;
import com.sun.star.uno.*;
import com.sun.star.beans.XPropertySet;
import com.sun.star.container.XNameAccess;
import com.sun.star.container.XNameContainer;
import com.sun.star.sdbc.*;
import com.sun.star.sdb.*;
import com.sun.star.sdbcx.*;
    
public class CodeSamples
{
    public static XMultiServiceFactory rSmgr;
    public static void main(String argv[]) throws java.lang.Exception
    {
        try{
            rSmgr = connect("socket,host=localhost,port=2083");
            //	checkConnection( openConnectionWithDriverManager(rSmgr) );
            //	checkConnection( openConnectionWithDriver(rSmgr) );
            createQuerydefinition( rSmgr );
            printQueryColumnNames( rSmgr );

            XConnection con = openConnectionWithDriverManager( rSmgr );
            if ( con != null ) {
                {
                    SalesMan sm = new SalesMan( con );

                    try {
                        sm.dropSalesManTable( ); // doesn't matter here
                    }
                    catch(com.sun.star.uno.Exception e)
                    {
                    }
                    sm.createSalesManTable( );
                    sm.insertDataIntoSalesMan( );
                    sm.updateSalesMan( );
                    sm.retrieveSalesManData( );
                }

                {
                    Sales sm = new Sales( con );

                    try {
                        sm.dropSalesTable( ); // doesn't matter here
                    }
                    catch(com.sun.star.uno.Exception e)
                    {
                    }
                    sm.createSalesTable( );
                    sm.insertDataIntoSales( );
                    sm.updateSales( );
                    sm.retrieveSalesData( );
                    sm.displayColumnNames( );
                }
                displayTableStructure( con );
            }
            //	printDataSources(rSmgr);
        }
        catch(com.sun.star.uno.Exception e)
        {
            System.out.println(e);
            e.printStackTrace();
        }
        System.exit(0);
    }


    public static XMultiServiceFactory connect( String connectStr )
        throws com.sun.star.uno.Exception,
        com.sun.star.uno.RuntimeException, java.lang.Exception
    {
        // initial serviceManager
        XMultiServiceFactory xLocalServiceManager =
            com.sun.star.comp.helper.Bootstrap.createSimpleServiceManager();

        // create a connector, so that it can contact the office
        Object  xUrlResolver  = xLocalServiceManager.createInstance( "com.sun.star.bridge.UnoUrlResolver" );
        XUnoUrlResolver urlResolver = (XUnoUrlResolver)UnoRuntime.queryInterface(
            XUnoUrlResolver.class, xUrlResolver );

        Object rInitialObject = urlResolver.resolve( "uno:" + connectStr + ";urp;StarOffice.NamingService" );

        XNamingService rName = (XNamingService)UnoRuntime.queryInterface(
            XNamingService.class, rInitialObject );

        XMultiServiceFactory xMSF = null;
        if( rName != null ) {
            System.err.println( "got the remote naming service !" );
            Object rXsmgr = rName.getRegisteredObject("StarOffice.ServiceManager" );

            xMSF = (XMultiServiceFactory)
                UnoRuntime.queryInterface( XMultiServiceFactory.class, rXsmgr );
        }

        return ( xMSF );
    }

    // check if the connection is not null aand dispose it later on.
    public static void checkConnection(XConnection con) throws com.sun.star.uno.Exception
    {
        if(con != null)
        {
            System.out.println("Connection was created!");
            // now we dispose the connection to close it
            XComponent xComponent = (XComponent)UnoRuntime.queryInterface(XComponent.class,con);
            if(xComponent != null)
            {
                // connections must be disposed
                xComponent.dispose();
                System.out.println("Connection disposed!");
            }
        }
        else
            System.out.println("Connection could not be created!");
    }

    // uses the driver manager to create a new connection and dispose it.
    public static XConnection openConnectionWithDriverManager(XMultiServiceFactory _rMSF) throws com.sun.star.uno.Exception
    {
        XConnection con = null;
        // create the DriverManager
        Object driverManager = _rMSF.createInstance("com.sun.star.sdbc.DriverManager");
        // query for the interface
        com.sun.star.sdbc.XDriverManager xDriverManager;
        xDriverManager = (XDriverManager)UnoRuntime.queryInterface(XDriverManager.class,driverManager);
        if(xDriverManager != null)
        {
            // first create the needed url
            String adabasURL = "sdbc:adabas::MYDB0";
            // second create the necessary properties
            com.sun.star.beans.PropertyValue [] adabasProps = new com.sun.star.beans.PropertyValue[]
            {
                new com.sun.star.beans.PropertyValue("user",0,"test1",com.sun.star.beans.PropertyState.DIRECT_VALUE),
                new com.sun.star.beans.PropertyValue("password",0,"test1",com.sun.star.beans.PropertyState.DIRECT_VALUE)
            };
            // now create a connection to adabas
            con = xDriverManager.getConnectionWithInfo(adabasURL,adabasProps);
        }
        return con;
    }

    // uses the driver manager to create a new connection and dispose it.
    public static XConnection openToJDBC(XMultiServiceFactory _rMSF) throws com.sun.star.uno.Exception
    {
        XConnection con = null;
        // create the DriverManager
        Object driverManager = _rMSF.createInstance("com.sun.star.sdbc.DriverManager");
        // query for the interface
        com.sun.star.sdbc.XDriverManager xDriverManager;
        xDriverManager = (XDriverManager)UnoRuntime.queryInterface(XDriverManager.class,driverManager);
        if(xDriverManager != null)
        {
            // first create the needed url
            String url = "jdbc:mysql://localhost:3306/TestTables";
            // second create the necessary properties
            com.sun.star.beans.PropertyValue [] props = new com.sun.star.beans.PropertyValue[]
            {
                new com.sun.star.beans.PropertyValue("user",0,"test1",com.sun.star.beans.PropertyState.DIRECT_VALUE),
                new com.sun.star.beans.PropertyValue("password",0,"test1",com.sun.star.beans.PropertyState.DIRECT_VALUE),
                new com.sun.star.beans.PropertyValue("JavaDriverClass",0,"org.gjt.mm.mysql.Driver",com.sun.star.beans.PropertyState.DIRECT_VALUE)
            };
            // now create a connection to adabas
            con = xDriverManager.getConnectionWithInfo(url,props);
        }
        return con;
    }

    // uses the driver directly to create a new connection and dispose it.
    public static XConnection openConnectionWithDriver(XMultiServiceFactory _rMSF) throws com.sun.star.uno.Exception
    {
        XConnection con = null;
        // create the Driver with the implementation name
        Object aDriver = _rMSF.createInstance("com.sun.star.comp.sdbcx.adabas.ODriver");
        // query for the interface
        com.sun.star.sdbc.XDriver xDriver;
        xDriver = (XDriver)UnoRuntime.queryInterface(XDriver.class,aDriver);
        if(xDriver != null)
        {
            // first create the needed url
            String adabasURL = "sdbc:adabas::MYDB0";
            // second create the necessary properties
            com.sun.star.beans.PropertyValue [] adabasProps = new com.sun.star.beans.PropertyValue[]
            {
                new com.sun.star.beans.PropertyValue("user",0,"test1",com.sun.star.beans.PropertyState.DIRECT_VALUE),
                new com.sun.star.beans.PropertyValue("password",0,"test1",com.sun.star.beans.PropertyState.DIRECT_VALUE)
            };
            // now create a connection to adabas
            con = xDriver.connect(adabasURL,adabasProps);
        }
        return con;
    }

    // print all available datasources
    public static void printDataSources(XMultiServiceFactory _rMSF) throws com.sun.star.uno.Exception
    {
        // create a DatabaseContext and print all DataSource names
        XNameAccess xNameAccess = (XNameAccess)UnoRuntime.queryInterface(XNameAccess.class,
                                            _rMSF.createInstance("com.sun.star.sdb.DatabaseContext"));
        String aNames [] = xNameAccess.getElementNames();
        for(int i=0;i<aNames.length;++i)
            System.out.println(aNames[i]);
    }

    // displays the structure of the first table
    public static void displayTableStructure(XConnection con) throws com.sun.star.uno.Exception
    {
        XDatabaseMetaData dm = con.getMetaData();
        XResultSet rsTables = dm.getTables(null,"%","SALES",null);
        XRow       rowTB = (XRow)UnoRuntime.queryInterface(XRow.class, rsTables);
        while ( rsTables.next() )
        {
            String catalog = rowTB.getString( 1 );
            if ( rowTB.wasNull() )
                catalog = null;

            String schema = rowTB.getString( 2 );
            if ( rowTB.wasNull() )
                schema = null;

            String table = rowTB.getString( 3 );
            String type = rowTB.getString( 4 );
            System.out.println("Catalog: " + catalog + " Schema: " + schema + " Table: " + table + " Type: " + type);
            System.out.println("------------------ Columns ------------------");
            XResultSet rsColumns = dm.getColumns(catalog,schema,table,"%");
            XRow       rowCL = (XRow)UnoRuntime.queryInterface(XRow.class, rsColumns);
            while ( rsColumns.next() )
            {
                System.out.println("Column: " + rowCL.getString( 4 ) + " Type: " + rowCL.getInt( 5 ) + " TypeName: " + rowCL.getString( 6 ) );
            }

        }
    }

    // quote the given name
    public static String quoteTableName(XConnection con, String sCatalog, String sSchema, String sTable) throws com.sun.star.uno.Exception
    {
        XDatabaseMetaData dbmd = con.getMetaData();
        String sQuoteString = dbmd.getIdentifierQuoteString();
        String sSeparator = ".";
        String sComposedName = "";
        String sCatalogSep = dbmd.getCatalogSeparator();
        if (0 != sCatalog.length() && dbmd.isCatalogAtStart() && 0 != sCatalogSep.length())
        {
            sComposedName += sCatalog;
            sComposedName += dbmd.getCatalogSeparator();
        }
        if (0 != sSchema.length())
        {
            sComposedName += sSchema;
            sComposedName += sSeparator;
            sComposedName += sTable;
        }
        else
        {
            sComposedName += sTable;
        }
        if (0 != sCatalog.length() && !dbmd.isCatalogAtStart() && 0 != sCatalogSep.length())
        {
            sComposedName += dbmd.getCatalogSeparator();
            sComposedName += sCatalog;
        }
        return sComposedName;
    }

    // creates a new query definition
    public static void createQuerydefinition(XMultiServiceFactory _rMSF) throws com.sun.star.uno.Exception
    {
        XNameAccess xNameAccess = (XNameAccess)UnoRuntime.queryInterface(XNameAccess.class,
                                            _rMSF.createInstance("com.sun.star.sdb.DatabaseContext"));
        // we use the first datasource
        XQueryDefinitionsSupplier xQuerySup = (XQueryDefinitionsSupplier)
                                            UnoRuntime.queryInterface(XQueryDefinitionsSupplier.class, 
                                            xNameAccess.getByName( "Bibliography" )); 
        XNameAccess xQDefs = xQuerySup.getQueryDefinitions();
        // create new query definition
        XSingleServiceFactory xSingleFac =	(XSingleServiceFactory) 
                                            UnoRuntime.queryInterface(XSingleServiceFactory.class, xQDefs);

        XPropertySet xProp = (XPropertySet) UnoRuntime.queryInterface(
            XPropertySet.class,xSingleFac.createInstance());
        xProp.setPropertyValue("Command","SELECT * FROM biblio");
        xProp.setPropertyValue("EscapeProcessing",new Boolean(true));

        XNameContainer xCont = (XNameContainer) UnoRuntime.queryInterface(XNameContainer.class, xQDefs);
        try
        {
            xCont.removeByName("Query1");
        }
        catch(com.sun.star.uno.Exception e)
        {}
        xCont.insertByName("Query1",xProp);
    }

    // prints all column names from Query1
    public static void printQueryColumnNames(XMultiServiceFactory _rMSF) throws com.sun.star.uno.Exception
    {
        XNameAccess xNameAccess = (XNameAccess)UnoRuntime.queryInterface(XNameAccess.class,
                                            _rMSF.createInstance("com.sun.star.sdb.DatabaseContext"));
        // we use the first datasource
        XDataSource xDS = (XDataSource)UnoRuntime.queryInterface(
            XDataSource.class, xNameAccess.getByName( "Bibliography" )); 
        XConnection con = xDS.getConnection("","");
        XQueriesSupplier xQuerySup = (XQueriesSupplier)
                                            UnoRuntime.queryInterface(XQueriesSupplier.class, con); 
        
        XNameAccess xQDefs = xQuerySup.getQueries();
        
        XColumnsSupplier xColsSup = (XColumnsSupplier) UnoRuntime.queryInterface(
            XColumnsSupplier.class,xQDefs.getByName("Query1"));
        XNameAccess xCols = xColsSup.getColumns();
        String aNames [] = xCols.getElementNames();
        for(int i=0;i<aNames.length;++i)
            System.out.println(aNames[i]);
    }
}

