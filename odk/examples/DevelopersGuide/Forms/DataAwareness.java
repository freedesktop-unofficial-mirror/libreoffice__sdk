/*************************************************************************
 *
 *  $RCSfile: DataAwareness.java,v $
 *
 *  $Revision: 1.2 $
 *
 *  last change: $Author: rt $ $Date: 2005-01-31 16:28:50 $
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

// __________ Imports __________

// base classes
import com.sun.star.uno.*;
import com.sun.star.lang.*;

// factory for creating components
import com.sun.star.bridge.XUnoUrlResolver;
import com.sun.star.frame.XComponentLoader;

// container handling
import com.sun.star.container.*;

// property access
import com.sun.star.beans.*;

// toolkit specific stuff
import com.sun.star.awt.*;

// drawing layer
import com.sun.star.drawing.*;

// text documents
import com.sun.star.text.*;

// form layer
import com.sun.star.form.*;

// data access
import com.sun.star.sdbc.*;
import com.sun.star.sdbcx.*;
import com.sun.star.sdb.*;

// document framework
import com.sun.star.frame.*;
import com.sun.star.view.*;

// miscellaneous
import com.sun.star.util.*;

/**************************************************************************/
/** a class for enumerating a form component tree
*/
class PrintComponentTree extends ComponentTreeTraversal
{
    private String m_sPrefix;

    public PrintComponentTree()
    {
        m_sPrefix = new String();
    }

    public void handle( Object aFormComponent ) throws com.sun.star.uno.Exception
    {
        // the name of the child
        XNamed xName = (XNamed)UnoRuntime.queryInterface( XNamed.class, aFormComponent );

        // if it's a form control model, check it's type
        XPropertySet xProps = UNO.queryPropertySet( aFormComponent );
        String sTypeName = FLTools.classifyFormComponentType( xProps );

        String sName;
        if ( null == xName )
            sName = "<unnamed>";
        else
            sName = xName.getName();

        // print the component's name
        if ( 0 != sTypeName.length() )
        {
            System.out.println( m_sPrefix + sName + " (" + sTypeName + ")" );
        }
        else
        {
            System.out.println( m_sPrefix + sName );
        }

        // let the super class step down the tree
        m_sPrefix = m_sPrefix + " ";
        super.handle( aFormComponent );
        m_sPrefix = m_sPrefix.substring( 0, m_sPrefix.length() - 1 );
    }
};

/**************************************************************************/
/** a class revoking button models from a ButtonOperator instance
*/
class RevokeButtons extends ComponentTreeTraversal
{
    private ButtonOperator m_aOperator;

    public RevokeButtons( ButtonOperator aOperator )
    {
        m_aOperator = aOperator;
    }

    public void handle( Object aFormComponent ) throws com.sun.star.uno.Exception
    {
        // check if it's a button
        XPropertySet xProps = UNO.queryPropertySet( aFormComponent );
        XPropertySetInfo xPI = null;
        if ( null != xProps )
            xPI = xProps.getPropertySetInfo();
        if ( ( null != xPI ) && xPI.hasPropertyByName( "ClassId" ) )
        {
            Short nClassId = (Short)xProps.getPropertyValue( "ClassId" );
            if ( FormComponentType.COMMANDBUTTON == nClassId.shortValue() )
            {
                // yes, it is
                m_aOperator.revokeButton( xProps );
            }
        }

        // let the super class step down the tree (if possible)
        super.handle( aFormComponent );
    }
}

/**************************************************************************/
public class DataAwareness extends DocumentBasedExample implements XPropertyChangeListener, XResetListener
{
    /* ================================================================== */
    private class Parameters
    {
        public	String	sDataSourceName;
        public	String	sUser;
        public	String	sPassword;
        public	String	sTablePrefix;

        public	String addTablePrefix( String sBaseName )
        {
            String sReturn = new String( sTablePrefix );
            if ( 0 < sTablePrefix.length() )
                sReturn += ".";
            sReturn += sBaseName;
            return sReturn;
        }
    };

    /* ================================================================== */
    private Parameters				m_aParameters;

    private XPropertySet			m_xMasterForm;
    private ButtonOperator			m_aOperator;
    private SalesFilter				m_aSalesFilter;

    private KeyGenerator			m_aSalesmanKeyGenerator;
    private KeyGenerator			m_aSalesKeyGenerator;
    private ControlLock				m_aSalesmenLocker;
    private	ControlLock				m_aSalesLocker;
    private	GridFieldValidator		m_aSalesNameValidator;

    private boolean					m_bDefaultSalesDate;
    private boolean					m_bProtectKeyFields;
    private boolean					m_bAllowEmptySales;

    /* ------------------------------------------------------------------ */
    public DataAwareness()
    {
        super( DocumentType.CALC );
        m_bDefaultSalesDate = false;
        m_bProtectKeyFields = false;
        m_bAllowEmptySales = false;
    }

    /* ==================================================================
       = form components
       ================================================================== */

    /* ------------------------------------------------------------------ */
    /** enumerates and prints all the elements in the given container, together with the container itself
    */
    protected void enumFormComponents( XNameAccess xContainer ) throws java.lang.Exception
    {
        String sObjectName;

        XNamed xNameAcc = (XNamed)UnoRuntime.queryInterface( XNamed.class, xContainer );
        if ( null == xNameAcc )
            sObjectName = new String( "<unnamed>" );
        else
            sObjectName = xNameAcc.getName();
        System.out.println( new String( "enumerating the container named \"" ) + sObjectName +
            new String( "\"\n" ) );

        PrintComponentTree aPrinter = new PrintComponentTree();
        aPrinter.handle( xContainer );
    }

    /* ------------------------------------------------------------------ */
    /** enumerates and prints all form elements in the document
    */
    protected void enumFormComponents( ) throws java.lang.Exception
    {
        enumFormComponents( m_document.getFormComponentTreeRoot() );
    }

    /* ==================================================================
       = UNO callbacks
       ================================================================== */

    /* ------------------------------------------------------------------ */
    // XResetListener overridables
    /* ------------------------------------------------------------------ */
    public boolean approveReset( EventObject aEvent ) throws com.sun.star.uno.RuntimeException
    {
        // not interested in vetoing this
        return true;
    }

    /* ------------------------------------------------------------------ */
    public void resetted( EventObject aEvent ) throws com.sun.star.uno.RuntimeException
    {
        // check if this reset occured becase we're on a new record
        XPropertySet xFormProps = UNO.queryPropertySet(  aEvent.Source );
        try
        {
            Boolean aIsNew = (Boolean)xFormProps.getPropertyValue( "IsNew" );
            if ( aIsNew.booleanValue() )
            {	// yepp

                if ( !m_bDefaultSalesDate )
                {	// we're interested to do all this only if the user told us to default the sales date
                    // to "today"
                    // As date fields do this defaulting automatically, the semantics is inverted here:
                    // If we're told to default, we must do nothing, if we should not default, we must
                    // reset the value which the date field set automatically.

                    Integer aConcurrency = (Integer)xFormProps.getPropertyValue( "ResultSetConcurrency" );
                    if ( ResultSetConcurrency.READ_ONLY != aConcurrency.intValue() )
                    {
                        // we're going to modify the record, though after that, to the user, it should look
                        // like it has not been modified
                        // So we need to ensure that we do not change the IsModified property with whatever we do
                        Object aModifiedFlag = xFormProps.getPropertyValue( "IsModified" );


                        // get the columns of our master form
                        XColumnsSupplier xSuppCols = (XColumnsSupplier)UnoRuntime.queryInterface(
                            XColumnsSupplier.class, xFormProps );
                        XNameAccess xCols = xSuppCols.getColumns();

                        // and update the date column with a NULL value
                        XColumnUpdate xDateColumn = (XColumnUpdate)UnoRuntime.queryInterface(
                            XColumnUpdate.class, xCols.getByName( "SALEDATE" ) );
                        xDateColumn.updateNull();


                        // then restore the flag
                        xFormProps.setPropertyValue( "IsModified", aModifiedFlag );
                    }
                }
            }
        }
        catch( com.sun.star.uno.Exception e )
        {
            System.out.println(e);
            e.printStackTrace();
        }
    }

    /* ------------------------------------------------------------------ */
    // XPropertyChangeListener overridables
    /* ------------------------------------------------------------------ */
    public void propertyChange( PropertyChangeEvent aEvent ) throws com.sun.star.uno.RuntimeException
    {
        try
        {
            // did it come from a radio button or checkbox?
            if ( aEvent.PropertyName.equals( "State" ) )
            {	// yep
                Short aNewState = (Short)aEvent.NewValue;

                XPropertySet xModel = UNO.queryPropertySet( aEvent.Source );
                String sName = (String)xModel.getPropertyValue( "Name" );

                Short aClassId = (Short)xModel.getPropertyValue( "ClassId" );
                if ( FormComponentType.RADIOBUTTON == aClassId.shortValue() )
                {
                    String sRefValue = (String)xModel.getPropertyValue( "RefValue" );

                    short nNewValue = ((Short)aEvent.NewValue).shortValue();
                    if ( sName.equals( "KeyGen" ) )
                    {
                        // it's one of the options for key generation
                        if ( sRefValue.equals( "none" ) )
                        {	// no automatic generation at all
                            m_aSalesmanKeyGenerator.stopGenerator( );
                            m_aSalesKeyGenerator.stopGenerator( );
                        }
                        else
                        {
                            boolean bGenerateOnReset = true;
                            if ( sRefValue.equals( "update" ) )
                            {	// generate on update
                                bGenerateOnReset = ( 0 == nNewValue );
                            }
                            else if ( sRefValue.equals( "reset" ) )
                            {	// generat on reset
                                bGenerateOnReset = ( 0 != nNewValue );
                            }
                            m_aSalesmanKeyGenerator.activateKeyGenerator( bGenerateOnReset );
                            m_aSalesKeyGenerator.activateKeyGenerator( bGenerateOnReset );
                        }
                    }
                }
                else if ( FormComponentType.CHECKBOX == aClassId.shortValue() )
                {
                    boolean bEnabled = ( 0 != aNewState.shortValue() );
                    if ( sName.equals( "defaultdate" ) )
                    {
                        m_bDefaultSalesDate = bEnabled;
                    }
                    else if ( sName.equals( "protectkeys" ) )
                    {
                        m_bProtectKeyFields = bEnabled;
                        m_aSalesmenLocker.enableLock( m_bProtectKeyFields );
                        m_aSalesLocker.enableLock( m_bProtectKeyFields );
                    }
                    else if ( sName.equals( "emptysales" ) )
                    {
                        m_bAllowEmptySales = bEnabled;
                        m_aSalesNameValidator.enableColumnWatch( m_bAllowEmptySales );
                    }
                }
            }
        }
        catch(com.sun.star.uno.Exception e)
        {
            System.out.println(e);
            e.printStackTrace();
        }
    }

    /* ------------------------------------------------------------------ */
    // XEventListener overridables
    /* ------------------------------------------------------------------ */
    public void disposing( EventObject aEvent )
    {
        // simply disambiguate
        super.disposing( aEvent );
    }

    /* ==================================================================
       = miscellaneous
       ================================================================== */

    /* ------------------------------------------------------------------ */
    /** skips line feeds in the input stream

        @returns
            the first character which does not belong to a line feed
    */
    protected int skipLineFeeds( java.io.InputStream aInput ) throws java.io.IOException
    {
        // read characters, until we encounter something which is not a line feed character
        int nChar = aInput.read( );
        while ( ( 13 == nChar ) || ( 10 == nChar ) )
            nChar = aInput.read( );

        // now read everything which is behind this single character we are interested in
        while ( 0 < aInput.available() )
            aInput.read( );

        return nChar;
    }

    /* ==================================================================
       = table handling
       ================================================================== */
    /* ------------------------------------------------------------------ */
    /** checks if a given table exists.

        <p>The check is made using a SELECT statement, so even if the connection
        is a n SDB-level connection, which may filter tables in it's table
        supplier, the result may be reliable ....</p>
    */
    protected boolean existsInvisibleTable( XConnection xConn, String sTableName ) throws java.lang.Exception
    {
        String sStatement = "SELECT * FROM ";
        sStatement += sTableName;
        sStatement += " WHERE 0=1";

        boolean bSuccess = false;
        try
        {
            XStatement xStatement = xConn.createStatement();
            xStatement.execute( sStatement );
            // if we reached this point, the table probably exists
            bSuccess = true;
        }
        catch(com.sun.star.sdbc.SQLException e)
        {
        }
        return bSuccess;
    }

    /* ------------------------------------------------------------------ */
    /** add a specified table name to the table filter of the given data source.
    */
    protected void makeTableVisible( XDataSource xDS, XConnection xConn, String sTableName ) throws java.lang.Exception
    {
        // get the table filter
        XPropertySet xDSP = UNO.queryPropertySet( xDS );
        String[] aCurrentFilter = (String[])xDSP.getPropertyValue( "TableFilter" );

        // check if the table name is already part of it
        String sPureTableName = sTableName;										// the pure name, e.g. SALESMAN
        String sPrefixedTableName = m_aParameters.addTablePrefix( sTableName );	// the prefixed name, e.g. SCHEMA.SALESMAN
        String sAllTables = "*";												// all tables
        String sPrefixWildcard = m_aParameters.addTablePrefix( sAllTables );	// all tables in this schema, e.g. SCHEMA.*

        for ( int i=0; i<aCurrentFilter.length; ++i )
        {
            String sCurrentTableFilter = aCurrentFilter[i];

            if ( sCurrentTableFilter.equals( sPureTableName ) )
                return;
            if ( sCurrentTableFilter.equals( sPrefixedTableName ) )
                return;
            if ( sCurrentTableFilter.equals( sAllTables ) )
                return;
            if ( sCurrentTableFilter.equals( sPrefixWildcard ) )
                return;
        }

        // if we are here, we have to add our table to the filter sequence
        String[] aNewFilter = new String[ aCurrentFilter.length + 1 ];
        // copy the existent filter entries
        for ( int i=0; i<aCurrentFilter.length; ++i )
            aNewFilter[i] = aCurrentFilter[i];
        // add our table
        aNewFilter[ aCurrentFilter.length ] = sPrefixedTableName;
            // note that sPrefixedTableName equals sTableName in case there is no prefix

        xDSP.setPropertyValue( "TableFilter", aNewFilter );
    }

    /* ------------------------------------------------------------------ */
    /** executes the given statement on the given connection
    */
    protected boolean implExecuteStatement( XConnection xConn, String sStatement ) throws java.lang.Exception
    {
        try
        {
            XStatement xStatement = xConn.createStatement( );
            xStatement.execute( sStatement );
        }
        catch(com.sun.star.sdbc.SQLException e)
        {
            System.err.println( e );
            return false;
        }

        return true;
    }

    /* ------------------------------------------------------------------ */
    /** creates the table witht the given name, using the given statement
    */
    protected boolean implCreateTable( XConnection xConn, String sCreateStatement, String sTableName ) throws java.lang.Exception
    {
        if ( !implExecuteStatement( xConn, sCreateStatement ) )
        {
            System.out.println( "  could not create the table " + sTableName + "." );
            System.out.println( );
            return false;
        }

        return true;
    }

    /* ------------------------------------------------------------------ */
    /** creates the table SALESMAN

        @return
            <TRUE/> if and only if the creation succeeded
    */
    protected boolean createTableSalesman( XConnection xConn, String[] out_sTableName ) throws java.lang.Exception
    {
        out_sTableName[0] = "SALESMAN";

        String sCreateStatement = "CREATE TABLE SALESMAN ";
        sCreateStatement += "(SNR INTEGER NOT NULL, ";
        sCreateStatement += "FIRSTNAME VARCHAR(50), ";
        sCreateStatement += "LASTNAME VARCHAR(100), ";
        sCreateStatement += "STREET VARCHAR(50), ";
        sCreateStatement += "STATE VARCHAR(50), ";
        sCreateStatement += "ZIP INTEGER, ";
        sCreateStatement += "BIRTHDATE DATE, ";
        sCreateStatement += "PRIMARY KEY(SNR))";

        if ( implCreateTable( xConn, sCreateStatement, out_sTableName[0] ) )
        {
            String sInsertionPrefix = "INSERT INTO SALESMAN VALUES ";

            implExecuteStatement( xConn, sInsertionPrefix + "(1, 'Joseph', 'Smith', 'Bond Street', 'CA', 95460, '1946-07-02')" );
            implExecuteStatement( xConn, sInsertionPrefix + "(2, 'Frank', 'Jones', 'Lake silver', 'CA', 95460, '1963-12-24')" );
            implExecuteStatement( xConn, sInsertionPrefix + "(3, 'Jane', 'Esperansa', '23 Hollywood driver', 'CA', 95460, '1972-04-01')" );

            return true;
        }
        return false;
    }

    /* ------------------------------------------------------------------ */
    /** creates the table CUSTOMER

        @return
            <TRUE/> if and only if the creation succeeded
    */
    protected boolean createTableCustomer( XConnection xConn, String[] out_sTableName ) throws java.lang.Exception
    {
        out_sTableName[0] = "CUSTOMER";

        String sCreateStatement = "CREATE TABLE CUSTOMER ";
        sCreateStatement += "(COS_NR INTEGER NOT NULL, ";
        sCreateStatement += "LASTNAME VARCHAR(100), ";
        sCreateStatement += "STREET VARCHAR(50), ";
        sCreateStatement += "CITY VARCHAR(50), ";
        sCreateStatement += "STATE VARCHAR(50), ";
        sCreateStatement += "ZIP INTEGER, ";
        sCreateStatement += "PRIMARY KEY(COS_NR))";

        if ( implCreateTable( xConn, sCreateStatement, out_sTableName[0] ) )
        {
            String sInsertionPrefix = "INSERT INTO CUSTOMER VALUES ";

            implExecuteStatement( xConn, sInsertionPrefix + "(100, 'Acme, Inc.', '99 Market Street', 'Groundsville', 'CA', 95199)" );
            implExecuteStatement( xConn, sInsertionPrefix + "(101, 'Superior BugSoft', '1 Party Place', 'Mendocino', 'CA', 95460)");
            implExecuteStatement( xConn, sInsertionPrefix + "(102, 'WeKnowAll, Inc.', '100 Coffee Lane', 'Meadows', 'CA', 93699)");

            return true;
        }
        return false;
    }

    /* ------------------------------------------------------------------ */
    /** creates the table SALES

        @return
            <TRUE/> if and only if the creation succeeded
    */
    protected boolean createTableSales( XConnection xConn, String[] out_sTableName ) throws java.lang.Exception
    {
        out_sTableName[0] = "SALES";

        String sCreateStatement = "CREATE TABLE SALES ";
        sCreateStatement += "(SALENR INTEGER NOT NULL, ";
        sCreateStatement += "COS_NR INTEGER NOT NULL, ";
        sCreateStatement += "SNR INTEGER NOT NULL, ";
        sCreateStatement += "NAME VARCHAR(50), ";
        sCreateStatement += "SALEDATE DATE, ";
        sCreateStatement += "PRICE DECIMAL(8,2), ";
        sCreateStatement += "PRIMARY KEY(SALENR))";

        if ( implCreateTable( xConn, sCreateStatement, out_sTableName[0] ) )
        {
            String sInsertionPrefix = "INSERT INTO SALES VALUES ";

            implExecuteStatement( xConn, sInsertionPrefix + "(1, 100, 1, 'Fruits', '2005-02-12', 39.99)" );
            implExecuteStatement( xConn, sInsertionPrefix + "(2, 101, 3, 'Beef', '2005-10-18', 15.78)" );
            implExecuteStatement( xConn, sInsertionPrefix + "(3, 102, 3, 'Orange Juice', '2005-09-08', 25.63)" );
            implExecuteStatement( xConn, sInsertionPrefix + "(4, 101, 2, 'Oil', '2005-03-01', 12.30)" );

            return true;
        }

        return false;
    }

    /* ------------------------------------------------------------------ */
    /** ensures that the tables we need for our example exist
    */
    protected void ensureTables() throws java.lang.Exception
    {
        XNameAccess aDSContext = (XNameAccess)UnoRuntime.queryInterface( XNameAccess.class,
            m_xCtx.getServiceManager().createInstanceWithContext(
                "com.sun.star.sdb.DatabaseContext", m_xCtx ) );

        if ( !aDSContext.hasByName( m_aParameters.sDataSourceName ) )
        {
            String sError = new String( "There is no data source named '" );
            sError += m_aParameters.sDataSourceName;
            sError += new String( "'!" );
            System.out.println( sError );
            System.exit( 2 );
        }

        // get the data source
        XDataSource xDS = (XDataSource)UnoRuntime.queryInterface( XDataSource.class,
            aDSContext.getByName( m_aParameters.sDataSourceName ) );
        XPropertySet xDSProps = UNO.queryPropertySet( xDS );


        if ( ( 0 == m_aParameters.sUser.length() ) && ( 0 < m_aParameters.sPassword.length() ) )
        {	// the user gave us a password, but no user name
            m_aParameters.sUser = (String)xDSProps.getPropertyValue( "User" );
        }


        // connect to this data source
        XConnection xConn = xDS.getConnection( m_aParameters.sUser, m_aParameters.sPassword );
        XComponent xConnComp = UNO.queryComponent( xConn );

        // do we need do remember the password?
        if ( null != xConn )
        {	// connecting was a success
            if ( 0 != m_aParameters.sPassword.length() )
            {	// and we (resp. the user) supplied a password to establish the connection
                String sOldPassword = (String)xDSProps.getPropertyValue( "Password" );
                if ( 0 == sOldPassword.length() )
                {	// and the data source did not have a password before
                    String sOldUser = (String)xDSProps.getPropertyValue( "User" );
                    if ( sOldUser.equals( m_aParameters.sUser ) )
                    {	// and the user name is the same
                        // => remember the password for this session
                        xDSProps.setPropertyValue( "Password", m_aParameters.sPassword );
                    }
                }
            }
        }

        // get the tables of the data source
        XTablesSupplier xSuppTables = UNO.queryTablesSupplier( xConn );
        XNameAccess xTables = xSuppTables.getTables();

        boolean bFakedTablePrefix = false;
            // this will track if we faked the table prefix of our parameters

        boolean bHasAll = false;
        while ( !bHasAll )
        {
            // okay, check if there is a table for the salesmen ...
            String sSalesmanTable = m_aParameters.addTablePrefix( "SALESMAN" );
            boolean bHasSalesman = xTables.hasByName( sSalesmanTable );

            // ... and the customers
            String sCustomerTable = m_aParameters.addTablePrefix( "CUSTOMER" );
            boolean bHasCustomer = xTables.hasByName( sCustomerTable );

            // ... and the customers
            String sSalesTable = m_aParameters.addTablePrefix( "SALES" );
            boolean bHasSales = xTables.hasByName( sSalesTable );

            boolean bHasAny = bHasSalesman || bHasCustomer || bHasSales;
            bHasAll = bHasSalesman && bHasCustomer && bHasSales;

            if ( !bHasAll )
            {
                // perhaps the user just didn't give us a table prefix
                if	(	!bHasAny										// we do not have any of the tables
                    &&	( 0 == m_aParameters.sTablePrefix.length() )	// we do not have a table prefix
                    &&	!bFakedTablePrefix								// and we did not yet try to fake a prefix
                    )
                {
                    if ( 0 != m_aParameters.sUser.length() )
                    {
                        // assume the user name as table prefix
                        m_aParameters.sTablePrefix = m_aParameters.sUser;
                        bFakedTablePrefix = true;
                    }
                    else
                    {
                        String sDataSourceUserName = (String)xDSProps.getPropertyValue( "User" );
                        m_aParameters.sTablePrefix = sDataSourceUserName;
                        bFakedTablePrefix = true;
                    }
                    if ( 0 != m_aParameters.sTablePrefix.length() )
                    {
                        // normalize the prefix which we are assuming from now on
                        XDatabaseMetaData xMeta = xConn.getMetaData();
                        if ( xMeta.storesUpperCaseIdentifiers() )
                            m_aParameters.sTablePrefix = m_aParameters.sTablePrefix.toUpperCase();
                        else if ( xMeta.storesLowerCaseIdentifiers() )
                            m_aParameters.sTablePrefix = m_aParameters.sTablePrefix.toLowerCase();

                        // we have another thing we can try
                        System.out.println( "none of the required tables found - assuming table prefix \"" + m_aParameters.sTablePrefix + "\"" );
                        System.out.println();
                        continue;
                    }
                }

                // error message and outta here
                String sError = new String( "missing table " );
                if ( !bHasSalesman )
                    sError += sSalesmanTable;
                else if ( !bHasCustomer )
                    sError += sCustomerTable;
                else if ( !bHasSales )
                    sError += sSalesTable;
                else
                    sError += "<unknown>";
                sError += " in data source ";
                sError += m_aParameters.sDataSourceName;

                System.out.println( sError );

                // create the table (if we are allowed to by the user)
                boolean bCreationSuccess = false;

                System.out.print( "shall we create the table (Y)? " );
                int nShouldCreate = skipLineFeeds( System.in );

                if ( ( 'Y' == nShouldCreate ) || ( 'y' == nShouldCreate ) )
                {
                    String[] sTable = new String[] { new String() };

                    if ( !bHasSalesman )
                        bCreationSuccess = createTableSalesman( xConn, sTable );
                    else if ( !bHasCustomer )
                        bCreationSuccess = createTableCustomer( xConn, sTable );
                    else
                        bCreationSuccess = createTableSales( xConn, sTable );

                    if	(	!bHasAny				// we did not have any of the tables
                        &&	bFakedTablePrefix		// the user did not give us a table prefix, but we faked one
                        &&	bCreationSuccess		// we succeeded to create the table
                        )
                    {
                        // check if we really need to use this table prefix
                        // Above, we set the table prefix to the user name, and we did not find all of our tables
                        // neither without nor with this prefix.
                        // Thus, at the moment, it may still be possible that we do not need the table
                        // prefix at all
                        if ( !existsInvisibleTable( xConn, m_aParameters.addTablePrefix( sTable[0] ) ) )
                        {
                            m_aParameters.sTablePrefix = new String();
                        }
                    }

                    if ( bCreationSuccess )
                    {
                        System.out.println( "  successfully created table " + m_aParameters.addTablePrefix( sTable[0] ) );
                        System.out.println( );
                    }

                    // now that we created the table, make sure that it is in the table filter of the
                    // data source
                    makeTableVisible( xDS, xConn, sTable[0] );

                    // we added a table and changed the table filter, so we need to refresh the tables
                    // Normally, we would just call XRefreshable::refresh on the tables container.
                    XRefreshable xRefresh = (XRefreshable)UnoRuntime.queryInterface( XRefreshable.class, xTables );
                    xRefresh.refresh();

                    // Unfortunately, there is a bug that this does not work currently - simply nothing happens.
                    // So we dispose and re-open the connection.
                    xConnComp.dispose();

                    xConn = xDS.getConnection( m_aParameters.sUser, m_aParameters.sPassword );
                    xConnComp = UNO.queryComponent( xConn );
                    xSuppTables = UNO.queryTablesSupplier( xConn );
                    xTables = xSuppTables.getTables();
                }

                if ( !bCreationSuccess )
                {
                    xConnComp.dispose();
                    System.exit( 3 );
                }
            }
        }

        // free the resources acquired by the connection
        xConnComp.dispose();
    }

    /* ==================================================================
       = sample document handling
       ================================================================== */

    /* ------------------------------------------------------------------ */
    /** creates the button used for demonstrating (amonst others) event handling
        @param nXPos
            x-position of the to be inserted shape
        @param nYPos
            y-position of the to be inserted shape
        @param nXSize
            width of the to be inserted shape
        @param sName
            the name of the model in the form component hierarchy
        @param sLabel
            the label of the button control
        @param sActionURL
            the URL of the action which should be triggered by the button
        @return
            the model of the newly created button
    */
    protected XPropertySet createButton( int nXPos, int nYPos, int nXSize, String sName, String sLabel, String sActionURL ) throws java.lang.Exception
    {
        XPropertySet xButton = m_formLayer.createControlAndShape( "CommandButton", nXPos, nYPos, nXSize, 6 );
        // the name for referring to it later:
        xButton.setPropertyValue( "Name", sName );
        // the label
        xButton.setPropertyValue( "Label", sLabel );
        // use the name as help text
        xButton.setPropertyValue( "HelpText", sName );
        // don't want buttons to be accessible by the "tab" key - this would be uncomfortable when traveling
        // with records with "tab"
        xButton.setPropertyValue( "Tabstop", new Boolean( false ) );

        // create our button operator, if necessary
        if ( null == m_aOperator )
            m_aOperator = new ButtonOperator( m_xCtx, m_document );

        m_aOperator.addButton( xButton, sActionURL );

        return xButton;
    }

    /* ------------------------------------------------------------------ */
    /** creates a column in a grid
        @param xGridModel
            specifies the model of the grid where the new column should be inserted
        @param sColumnService
            specifies the service name of the column to create (e.g. "NumericField")
        @param sDataField
            specifies the database field to which the column should be bound
        @param nWidth
            specifies the column width (in mm). If 0, no width is set.
        @return
            the newly created column
    */
    XPropertySet createGridColumn( Object aGridModel, String sColumnService, String sDataField, int nWidth )
        throws com.sun.star.uno.Exception
    {
        // the container to insert columns into
        XIndexContainer xColumnContainer = UNO.queryIndexContainer( aGridModel );
        // the factory for creating column models
        XGridColumnFactory xColumnFactory = (XGridColumnFactory)UnoRuntime.queryInterface(
            XGridColumnFactory.class, aGridModel );

        // (let) create the new col
        XInterface xNewCol = (XInterface)xColumnFactory.createColumn( sColumnService );
        XPropertySet xColProps = UNO.queryPropertySet( xNewCol );

        // some props
        // the field the column is bound to
        xColProps.setPropertyValue( "DataField", sDataField );
        // the "display name" of the column
        xColProps.setPropertyValue( "Label", sDataField );
        // the name of the column within it's parent
        xColProps.setPropertyValue( "Name", sDataField );

        if ( nWidth > 0 )
            xColProps.setPropertyValue( "Width", new Integer( nWidth * 10 ) );

        // insert
        xColumnContainer.insertByIndex( xColumnContainer.getCount(), xNewCol );

        // outta here
        return xColProps;
    }

    /* ------------------------------------------------------------------ */
    /** creates a column in a grid
    */
    XPropertySet createGridColumn( Object aGridModel, String sColumnService, String sDataField )
        throws com.sun.star.uno.Exception
    {
        return createGridColumn( aGridModel, sColumnService, sDataField );
    }

    /* ------------------------------------------------------------------ */
    /** creates our sample document
    */
    protected void prepareDocument() throws com.sun.star.uno.Exception, java.lang.Exception
    {
        super.prepareDocument();

        // ensure that we have the tables needed for our example
        ensureTables();

        // --------------------------------------------------------------
        /* create some shapes */
        XPropertySet xSNRField =	m_formLayer.insertControlLine( "NumericField", "SNR", "", 3 );
                                    m_formLayer.insertControlLine( "TextField", "FIRSTNAME", "", 11);
                                    m_formLayer.insertControlLine( "TextField", "LASTNAME", "", 19 );
                                    m_formLayer.insertControlLine( "TextField", "STREET", "", 27 );
                                    m_formLayer.insertControlLine( "TextField", "STATE", "", 35 );
        XPropertySet xZipField =    m_formLayer.insertControlLine( "NumericField", "ZIP", "", 43 );
                                    m_formLayer.insertControlLine( "FormattedField", "BIRTHDATE", "", 51 );

        // for the salesman number / zip code, we don't want to have decimal places:
        xSNRField.setPropertyValue( "DecimalAccuracy", new Short( (short)0 ) );
        xZipField.setPropertyValue( "DecimalAccuracy", new Short( (short)0 ) );

        // --------------------------------------------------------------
        /** need the form the control models belong to
            for this, we simply obtain the parent for any of the control models we have

            Note that this involves knowledge about the implementation: If a control shape is
            inserted into a document, where the control model does not belong to the form component
            hierarchy, yet, it is automatically inserted into the first form, which is created
            if necessary.
        */
        m_xMasterForm = FLTools.getParent( xZipField );

        // set the data source signature at the form
        m_xMasterForm.setPropertyValue( "DataSourceName", m_aParameters.sDataSourceName );
        m_xMasterForm.setPropertyValue( "CommandType", new Integer( CommandType.TABLE ) );
        m_xMasterForm.setPropertyValue( "Command", m_aParameters.addTablePrefix( "SALESMAN" ) );

        // --------------------------------------------------------------
        // insert the buttons
        createButton( 2, 63, 8, "first", "<<", ".uno:FormSlots/moveToFirst#0\\0" );
        createButton( 12, 63, 8, "prev", "<", ".uno:FormSlots/moveToPrev#0\\0" );
        createButton( 22, 63, 8, "next", ">", ".uno:FormSlots/moveToNext#0\\0" );
        createButton( 32, 63, 8, "last", ">>", ".uno:FormSlots/moveToLast#0\\0" );
        createButton( 42, 63, 8, "new", ">*", ".uno:FormSlots/moveToNew#0\\0" );

        // NOTE:
        // The URLs above imply knowledge about the current implementation.
        // The part before the '#' is an official URL, the part after that means that we refer
        // to a functionallity in Form 1 of DrawPage 1 of the document.
        // If we would not have these implementation bugs which prevent us from calling "XResultSet::first"
        // and friends from Java, we would not need this implementation details.

        createButton( 58, 63, 13, "reload", "reload", "" );

        // --------------------------------------------------------------
        // create a sub for for the sales

        // for this, first create a sub form and bind it to the SALES table
        XIndexContainer xSalesForm = m_document.createSubForm( m_xMasterForm, "Sales" );
        XPropertySet xSalesFormProps = UNO.queryPropertySet( xSalesForm );

        xSalesFormProps.setPropertyValue( "DataSourceName", m_aParameters.sDataSourceName );
        xSalesFormProps.setPropertyValue( "CommandType", new Integer( CommandType.COMMAND ) );

        String sCommand = new String( "SELECT * FROM " );
        sCommand += m_aParameters.addTablePrefix( "SALES" );
        sCommand += " AS SALES WHERE SALES.SNR = :salesmen";
        xSalesFormProps.setPropertyValue( "Command", sCommand );

        // the master-details connection
        String[] aMasterFields = new String[] { "SNR" };		// the field in the master form
        String[] aDetailFields = new String[] { "salesmen" };	// the name in the detail form
        xSalesFormProps.setPropertyValue( "MasterFields", aMasterFields );
        xSalesFormProps.setPropertyValue( "DetailFields", aDetailFields );

        // the create thr grid model
        XPropertySet xSalesGridModel = m_formLayer.createControlAndShape( "GridControl", 2, 80, 162, 40, xSalesForm );
        xSalesGridModel.setPropertyValue( "Name", "SalesTable" );
        XPropertySet xKeyColumn		 =	createGridColumn( xSalesGridModel, "NumericField", "SALENR", 12 );
        XPropertySet xCustomerColumn =	createGridColumn( xSalesGridModel, "ListBox", "COS_NR", 40 );
        XPropertySet xSalesNameColumn =	createGridColumn( xSalesGridModel, "TextField", "NAME", 25 );
                                        createGridColumn( xSalesGridModel, "DateField", "SALEDATE", 24 );
                                        createGridColumn( xSalesGridModel, "CurrencyField", "PRICE", 16 );

            // please note that a better solution for the SALEDATE field would have been to use
            // a FormattedField. But we want to demonstrate some effects with DateFields here ...

        m_aSalesNameValidator = new GridFieldValidator( m_xCtx, xSalesNameColumn );
        m_aSalesNameValidator.enableColumnWatch( m_bAllowEmptySales );

        xKeyColumn.setPropertyValue( "DecimalAccuracy", new Short( (short)0 ) );

        // init the list box which is for choosing the customer a sale belongs to
        xCustomerColumn.setPropertyValue( "BoundColumn", new Short( (short)1 ) );
        xCustomerColumn.setPropertyValue( "Label", "Customer" );
        xCustomerColumn.setPropertyValue( "ListSourceType", ListSourceType.SQL );

        String sListSource = "SELECT LASTNAME, COS_NR FROM ";
        sListSource += m_aParameters.addTablePrefix( "CUSTOMER" );
        String[] aListSource = new String[] { sListSource };
        xCustomerColumn.setPropertyValue( "ListSource", aListSource );

        // We want to demonstrate how to reset fields to NULL, we do this with the SALEDATE field
        // above. For this, we add as reset listener to the form
        XReset xFormReset = UNO.queryReset( xSalesForm );
        xFormReset.addResetListener( this );


        // --------------------------------------------------------------
        // the option for filtering the sales form
        XIndexContainer xSalesFilterForm = m_document.createSiblingForm( xSalesForm, "SalesFilter" );
        XPropertySet xSFFProps = UNO.queryPropertySet( xSalesFilterForm );
        XPropertySet xLabel = m_formLayer.createControlAndShape( "FixedText", 2, 125, 35, 6, xSalesFilterForm );
        xLabel.setPropertyValue( "Label", "show only sales since" );
        xLabel.setPropertyValue( "Name", "FilterLabel" );

        XPropertySet xFilterSelection = m_formLayer.createControlAndShape( "ListBox", 40, 125, 59, 6, xSalesFilterForm );
        xFilterSelection.setPropertyValue( "Name", "FilterList" );
        xFilterSelection.setPropertyValue( "LabelControl", xLabel );
        XPropertySet xManualFilter = m_formLayer.createControlAndShape( "DateField", 104, 125, 30, 6, xSalesFilterForm );
        xManualFilter.setPropertyValue( "Name", "ManualFilter" );
        XPropertySet xApplyFilter = m_formLayer.createControlAndShape( "CommandButton", 139, 125, 25, 6, xSalesFilterForm );
        xApplyFilter.setPropertyValue( "Name", "ApplyFilter" );
        xApplyFilter.setPropertyValue( "DefaultButton", new Boolean( true ) );
        m_aSalesFilter = new SalesFilter( m_document, xSalesFormProps, xFilterSelection,
            xManualFilter, xApplyFilter );


        // --------------------------------------------------------------
        // the options section
        // for this, we need a form which is a sibling of our master form (don't want to interfere
        // the controls which represent options only with the controls which are used for data access)

        XIndexContainer xOptionsForm = m_document.createSiblingForm( m_xMasterForm, "Options" );

        xLabel = m_formLayer.createControlAndShape( "GroupBox", 98, 0, 66, 62, xOptionsForm );
        xLabel.setPropertyValue( "Name", "Options" );
        xLabel.setPropertyValue( "Label", "Options" );

        // radio buttons which controls how we generate unique keys
        xLabel = m_formLayer.createControlAndShape( "GroupBox", 103, 5, 56, 25, xOptionsForm );
        xLabel.setPropertyValue( "Label", "key generation" );
        xLabel.setPropertyValue( "Name", "KeyGeneration" );
        XPropertySet xKeyGen = m_formLayer.createControlAndShape( "RadioButton", 106, 11, 50, 6, xOptionsForm );
        xKeyGen.setPropertyValue( "Name", "KeyGen" );
        xKeyGen.setPropertyValue( "Label", "no automatic generation" );
        xKeyGen.setPropertyValue( "RefValue", "none" );
        xKeyGen.addPropertyChangeListener( "State", this );

        xKeyGen = m_formLayer.createControlAndShape( "RadioButton", 106, 17, 50, 6, xOptionsForm );
        xKeyGen.setPropertyValue( "Name", "KeyGen" );
        xKeyGen.setPropertyValue( "Label", "before inserting a record" );
        xKeyGen.setPropertyValue( "RefValue", "update" );
        xKeyGen.addPropertyChangeListener( "State", this );

        xKeyGen = m_formLayer.createControlAndShape( "RadioButton", 106, 23, 50, 6, xOptionsForm );
        xKeyGen.setPropertyValue( "Name", "KeyGen" );
        xKeyGen.setPropertyValue( "Label", "when moving to a new record" );
        xKeyGen.setPropertyValue( "RefValue", "reset" );
        xKeyGen.addPropertyChangeListener( "State", this );

        // initialize listeners
        // master form - key generation
        m_aSalesmanKeyGenerator = new KeyGenerator( m_xMasterForm, "SNR", m_xCtx );
        m_aSalesmanKeyGenerator.activateKeyGenerator( true );
        // master form - control locking
        m_aSalesmenLocker = new ControlLock( m_xMasterForm, "SNR" );
        m_aSalesmenLocker.enableLock( m_bProtectKeyFields );

        // details form - key generation
        m_aSalesKeyGenerator = new KeyGenerator( xSalesFormProps, "SALENR", m_xCtx );
        m_aSalesKeyGenerator.activateKeyGenerator( true );

        // details form - control locking
        m_aSalesLocker = new ControlLock( xSalesFormProps, "SALENR" );
        m_aSalesLocker.enableLock( m_bProtectKeyFields );

        // initally, we want to generate keys when moving to a new record
        xKeyGen.setPropertyValue( "DefaultState", new Short( (short)1 ) );

        // --------------------------------------------------------------
        // second options block
        xLabel = m_formLayer.createControlAndShape( "GroupBox", 103, 33, 56, 25, xOptionsForm  );
        xLabel.setPropertyValue( "Name", "Misc" );
        xLabel.setPropertyValue( "Label", "Miscellaneous" );

        XPropertySet xCheck = m_formLayer.createControlAndShape( "CheckBox", 106, 39, 60, 6, xOptionsForm  );
        xCheck.setPropertyValue( "Name", "defaultdate" );
        xCheck.setPropertyValue( "Label", "default sales date to \"today\"" );
        xCheck.setPropertyValue( "HelpText", "When checked, newly entered sales records are pre-filled with today's date, else left empty." );
        xCheck.addPropertyChangeListener( "State", this );

        xCheck = m_formLayer.createControlAndShape( "CheckBox", 106, 45, 60, 6, xOptionsForm  );
        xCheck.setPropertyValue( "Name", "protectkeys" );
        xCheck.setPropertyValue( "Label", "protect key fields from editing" );
        xCheck.setPropertyValue( "HelpText", "When checked, you cannot modify the values in the table's key fields (SNR and SALENR)" );
        xCheck.addPropertyChangeListener( "State", this );

        xCheck = m_formLayer.createControlAndShape( "CheckBox", 106, 51, 60, 6, xOptionsForm  );
        xCheck.setPropertyValue( "Name", "emptysales" );
        xCheck.setPropertyValue( "Label", "check for empty sales names" );
        xCheck.setPropertyValue( "HelpText", "When checked, you cannot enter empty values into the NAME column of the 'Sales' table." );
        xCheck.addPropertyChangeListener( "State", this );

        // dump the form component tree
        enumFormComponents( );
    }

    /* ------------------------------------------------------------------ */
    /** performs any cleanup before exiting the program
    */
    protected void cleanUp( ) throws java.lang.Exception
    {
        // remove the listeners at the buttons
        RevokeButtons aRevoke = new RevokeButtons( m_aOperator );
        aRevoke.handle( m_document.getFormComponentTreeRoot( ) );

        // remove the key generator listeners from the form
        m_aSalesmanKeyGenerator.stopGenerator( );
        m_aSalesKeyGenerator.stopGenerator( );

        // and the control lockers
        m_aSalesmenLocker.enableLock( false );
        m_aSalesLocker.enableLock( false );

        // the validator for the grid column
        m_aSalesNameValidator.enableColumnWatch( false );

        // remove our own reset listener from the form
        XNameAccess xMasterAsNames = (XNameAccess)UnoRuntime.queryInterface(
            XNameAccess.class, m_xMasterForm );
        XReset xFormReset = UNO.queryReset( xMasterAsNames.getByName( "Sales" ) );
        xFormReset.removeResetListener( this );

        super.cleanUp();
    }

    /* ------------------------------------------------------------------ */
    /** explains how to use this class
    */
    protected void explainUsage()
    {
        System.err.println( "usage: DataAwareness -d <data source name>" );
        System.err.println( "                [-u <data source user name>]" );
        System.err.println( "                [-p <data source password>]" );
        System.err.println( "                [-t <alternate table prefix>]\n" );
        System.err.println( "  -d    - specifies the name of the data source" );
        System.err.println( "          registered in OpenOffice.org where the sample tables" );
        System.err.println( "          can be found." );
        System.err.println( "  -u    - specifies a user name to use when logging on to the data source" );
        System.err.println( "  -p    - specifies a password to use when logging on to the data source" );
        System.err.println( "  -t    - specifies a prefix to use for the table names" );
    }

    /* ------------------------------------------------------------------ */
    /** collect the RuntimeArguments
    */
    protected void collectParameters(String argv[])
    {
        m_aParameters = new Parameters();

        System.out.println(  );

        // ........................................
        // mandatory: the -d and a data source name
        if ( ( argv.length < 2 ) || ( !argv[0].equals( "-d" ) ) )
        {
            explainUsage();
            System.exit( 1 );
        }

        m_aParameters.sDataSourceName	= new String( argv[1] );
        m_aParameters.sUser 			= new String();
        m_aParameters.sPassword 		= new String();
        m_aParameters.sTablePrefix		= new String();

        // ........................................
        // optional arguments
        if ( argv.length >= 3 )
        {
            // must be a even number of arguments (switch-value pair)
            if ( 0 != ( argv.length % 2 ) )
            {
                explainUsage();
                System.exit( 1 );
            }

            int nArgPos = 2;
            while ( argv.length > nArgPos )
            {
                String sValue = new String( argv[ nArgPos + 1 ] );
                // try to recognize the switch
                if ( argv[ nArgPos ].equals( "-t" ) )
                {
                    m_aParameters.sTablePrefix = sValue;
                }
                else if ( argv[ nArgPos ].equals( "-p" ) )
                {
                    m_aParameters.sPassword = sValue;
                }
                else if ( argv[ nArgPos ].equals( "-u" ) )
                {
                    m_aParameters.sUser = sValue;
                }
                else
                {
                    explainUsage();
                    System.exit( 1 );
                }
                nArgPos += 2;
            }
        }
    }

    /* ------------------------------------------------------------------ */
    /** class entry point
    */
    public static void main(String argv[]) throws java.lang.Exception
    {
        DataAwareness aSample = new DataAwareness();
        aSample.run( argv );
    }
}
