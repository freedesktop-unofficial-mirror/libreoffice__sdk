/*************************************************************************
 *
 *  $RCSfile: ConfigExamples.java,v $
 *
 *  $Revision: 1.3 $
 *
 *  last change: $Author: hr $ $Date: 2003-06-30 15:16:23 $
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

// Import everything we use

import com.sun.star.beans.XPropertySet;
import com.sun.star.beans.XMultiPropertySet;
import com.sun.star.beans.XHierarchicalPropertySet;
import com.sun.star.beans.XMultiHierarchicalPropertySet;
import com.sun.star.beans.XPropertyState;
import com.sun.star.beans.XMultiPropertyStates;

import com.sun.star.bridge.XUnoUrlResolver;

import com.sun.star.configuration.XTemplateInstance;

import com.sun.star.container.XNameAccess;
import com.sun.star.container.XNameReplace;
import com.sun.star.container.XNameContainer;
import com.sun.star.container.XNamed;
import com.sun.star.container.XChild;
import com.sun.star.container.XHierarchicalNameAccess;
import com.sun.star.container.XHierarchicalName;

import com.sun.star.lang.XComponent;
import com.sun.star.lang.XMultiComponentFactory;
import com.sun.star.lang.XSingleServiceFactory;
import com.sun.star.lang.XMultiServiceFactory;
import com.sun.star.lang.XServiceInfo;
import com.sun.star.lang.EventObject;

import com.sun.star.uno.UnoRuntime;
import com.sun.star.uno.XComponentContext;
import com.sun.star.uno.XInterface;
import com.sun.star.uno.XNamingService;
import com.sun.star.uno.AnyConverter;

import com.sun.star.util.XChangesBatch;
import com.sun.star.util.XChangesNotifier;
import com.sun.star.util.XChangesListener;
import com.sun.star.util.ChangesEvent;
/** Config examples
    @author Joerg Barfurth
 */

/* These examples show how to use the following features of the Config API:

    o Accessing data
    o Updating data synchronously and asynchronously
    o Updating properties in groups
    o Adding and removing items in sets
    o Resetting data to their defaults

   Each example is in a separate method call.

   It accepts one command line parameter in the form of a connection string,
   if no connection string is specified it uses the default of
   "socket,host=localhost,port=8100"
*/ 
public class ConfigExamples  
{
    // The MultiServiceFactory interface of the ServiceManager
    private XMultiServiceFactory mxServiceManager = null;

    // The MultiServiceFactory interface of the ConfigurationProvider
    private XMultiServiceFactory mxProvider = null;

    public static void main(String args[]) 
    {
        String sConnection;
        // Get the connect string, defaulting to localhost, port 8100
        // if non supplied as command line arguments
        if( args.length == 0 )
        {
            sConnection = "socket,host=localhost,port=8100";
            System.out.println( "Using default connect string: " + sConnection );
        }
        else 
        {
            sConnection = args[0];
            System.out.println( "Using connect string: " + sConnection );
        }

        // Call connect, to get the MultiServiceFactory
        // of a running office and execute the examples.
        // If something goes wrong, print a stack trace and exit.
        try 
        {
            XMultiServiceFactory xServiceManager = connect( sConnection );
            if (xServiceManager == null)
            {
                System.out.println( "ERROR: Cannot connect - no service manager available." );
                return;
            }
            // Create an instance of the class and call it's run method
            ConfigExamples aExample = new ConfigExamples(xServiceManager);
            aExample.run ( );

            // if you own the service manager dispose it here 
            // to ensure that the default provider is properly disposed and flushed

            System.exit(0);
        } 
        catch( Exception e ) 
        {
            e.printStackTrace ( System.out );
            System.exit(-1);
        }
    }

    /** Create a ConfigExamples instance supplying a service factory
    */
    public ConfigExamples(XMultiServiceFactory xServiceManager)
    {
        mxServiceManager = xServiceManager;
    }

    /** Run the examples with a default ConfigurationProvider
    */
    public void run() 
        throws com.sun.star.uno.Exception
    {
        mxProvider = createProvider(); 

        runExamples( );

        // we are using the default ConfigurationProvider, so we must not dispose it
        mxProvider = null;
    }

    /** Run the examples with an AdministrationProvider
    */
    public void runForAdmin(Object [] aAdminArgs) 
        throws com.sun.star.uno.Exception
    {
        mxProvider = createAdminProvider(aAdminArgs);

        runExamples( );

        // this is not the default ConfigurationProvider, so we can dispose it
        ((XComponent)UnoRuntime.queryInterface( XComponent.class, mxProvider )).dispose();
        mxProvider = null;
    }

    /** Run the examples with a given ConfigurationProvider
    */
    public void runExamples( ) 
    {
        if (checkProvider(mxProvider))
        {
            System.out.println("\nStarting examples.");

            readDataExample();

            browseDataExample();

            updateGroupSyncExample();

            resetGroupExample();

            updateSetAsyncExample();

            System.out.println("\nAll Examples completed.");
        }
        else
            System.out.println("ERROR: Cannot run examples without ConfigurationProvider.");

    } 

    /** Do some simple checks, if tehre is a valid ConfigurationProvider
    */
    public static boolean checkProvider(XMultiServiceFactory xProvider)
    {
        // check the provider we have
        if (xProvider == null)
        {
            System.out.println("No provider available. Cannot access configuration data.");
            return false;

        }

        try
        {
            // check the provider implementation
            XServiceInfo xProviderServices = 
                (XServiceInfo) UnoRuntime.queryInterface( XServiceInfo.class, xProvider );

            if (xProviderServices == null || 
                !xProviderServices.supportsService("com.sun.star.configuration.ConfigurationProvider"))
            {
                System.out.println("WARNING: The provider is not a com.sun.star.configuration.ConfigurationProvider");
            }

            if (xProviderServices != null)
            {
                System.out.println("Using provider implementation: " + xProviderServices.getImplementationName());
            }

            return true;
        }
        catch (com.sun.star.uno.RuntimeException e)
        {
            System.out.println("ERROR: Failure while checking the provider services.");
            e.printStackTrace( System.out );
            return false;
        }
    }

    /** Connect to a specified host which is running office and accepting
        connections on the requested port. Set up a ServiceManager of the office 
     */

    public static XMultiServiceFactory connect( String sConnection )
        throws com.sun.star.uno.Exception, Exception
    {
        XComponentContext xContext = 
            com.sun.star.comp.helper.Bootstrap.createInitialComponentContext( null );
        XMultiComponentFactory xLocalServiceManager = xContext.getServiceManager();
        
        Object  xUrlResolver  = xLocalServiceManager.createInstanceWithContext( 
            "com.sun.star.bridge.UnoUrlResolver", xContext );
        XUnoUrlResolver urlResolver = (XUnoUrlResolver)UnoRuntime.queryInterface( XUnoUrlResolver.class, xUrlResolver );
        Object rInitialObject = urlResolver.resolve( "uno:" + sConnection + ";urp;StarOffice.NamingService" );
        XNamingService rName = (XNamingService)UnoRuntime.queryInterface(XNamingService.class, rInitialObject );

        XMultiServiceFactory xFactory = null;
        if( rName != null ) 
        {
            Object rXsmgr = rName.getRegisteredObject("StarOffice.ServiceManager" );
            xFactory = (XMultiServiceFactory)
                UnoRuntime.queryInterface( XMultiServiceFactory.class, rXsmgr );
        }
        return xFactory;
    }

    /** Get the service manager in use 
     */
    public XMultiServiceFactory getServiceManager( )
    {
        return mxServiceManager;
    }

    /** Get the provider we have 
     */
    public XMultiServiceFactory getProvider( )
    {
        return mxProvider;
    }

    /** Create a default configuration provider 
     */
    public XMultiServiceFactory createProvider( )
        throws com.sun.star.uno.Exception
    {
        XMultiServiceFactory xServiceManager = getServiceManager();

        final String sProviderService = "com.sun.star.configuration.ConfigurationProvider";

        // create the provider and return it as a XMultiServiceFactory
        XMultiServiceFactory xProvider = (XMultiServiceFactory)
            UnoRuntime.queryInterface(XMultiServiceFactory.class, 
                                      xServiceManager.createInstance(sProviderService));	

        return xProvider;
    }

    /** Create an administration provider 

        @param aAdminArguments
            An array of extra arguments to be used to create the provider
     */
    public XMultiServiceFactory createAdminProvider(Object[] aAdminArguments)
        throws com.sun.star.uno.Exception
    {
        XMultiServiceFactory xServiceManager = getServiceManager();

        final String sAdminService = "com.sun.star.configuration.AdministrationProvider";

        // create the provider and remember it as a XMultiServiceFactory
        XMultiServiceFactory xAdminProvider = (XMultiServiceFactory)
            UnoRuntime.queryInterface(XMultiServiceFactory.class,
                           xServiceManager.createInstanceWithArguments(sAdminService,aAdminArguments));

        return xAdminProvider;
    }

    /** Create a specified read-only configuration view
     */
    public Object createConfigurationView( String sPath )
        throws com.sun.star.uno.Exception
    {
        XMultiServiceFactory xProvider = getProvider();

        // The service name: Need only read access:
        final String sReadOnlyView = "com.sun.star.configuration.ConfigurationAccess";

        // creation arguments: nodepath   
        com.sun.star.beans.PropertyValue aPathArgument = new com.sun.star.beans.PropertyValue();
        aPathArgument.Name = "nodepath";
        aPathArgument.Value = sPath;

        Object[] aArguments = new Object[1];
        aArguments[0] = aPathArgument;

        // create the view
        Object xViewRoot = xProvider.createInstanceWithArguments(sReadOnlyView, aArguments);

        return xViewRoot;
    }

    /** Create a specified updatable configuration view using default synchronicity
     */
    Object createUpdatableView( String sPath )
        throws com.sun.star.uno.Exception
    {
        XMultiServiceFactory xProvider = getProvider();

        // The service name: Need update access:
        final String cUpdatableView = "com.sun.star.configuration.ConfigurationUpdateAccess";

        // creation arguments: nodepath   
        com.sun.star.beans.PropertyValue aPathArgument = new com.sun.star.beans.PropertyValue();
        aPathArgument.Name = "nodepath";
        aPathArgument.Value = sPath;

        Object[] aArguments = new Object[1];
        aArguments[0] = aPathArgument;

        // create the view
        Object xViewRoot = xProvider.createInstanceWithArguments(cUpdatableView, aArguments);

        return xViewRoot;
    }

    /** Create a specified updatable configuration view
     */
    Object createUpdatableView( String sPath, boolean bAsync )
        throws com.sun.star.uno.Exception
    {
        XMultiServiceFactory xProvider = getProvider();

        // The service name: Need update access:
        final String cUpdatableView = "com.sun.star.configuration.ConfigurationUpdateAccess";

        // creation arguments: nodepath   
        com.sun.star.beans.PropertyValue aPathArgument = new com.sun.star.beans.PropertyValue();
        aPathArgument.Name = "nodepath";
        aPathArgument.Value = sPath;

        // creation arguments: commit mode - write-through or write-back  
        com.sun.star.beans.PropertyValue aModeArgument = new com.sun.star.beans.PropertyValue();
        aModeArgument.Name = "lazywrite";
        aModeArgument.Value = new Boolean(bAsync);

        Object[] aArguments = new Object[2];
        aArguments[0] = aPathArgument;
        aArguments[1] = aModeArgument;

        // create the view
        Object xViewRoot = xProvider.createInstanceWithArguments(cUpdatableView, aArguments);

        return xViewRoot;
    }

    /** This method demonstrates read access to data
     */
    protected void readDataExample ()
    {
        try
        {
            System.out.println("\n--- starting example: read grid option settings --------------------");
            Object aData = readGridConfiguration( );
            System.out.println("Read grid options: " + aData);

        }
        catch ( Exception e )
        {
            e.printStackTrace ( System.out );
        }
    }

    /** This method demonstrates browsing access to data
     */
    protected void browseDataExample ()
    {
        try
        {
            System.out.println("\n--- starting example: browse filter configuration ------------------");
            printRegisteredFilters( );
        }
        catch ( Exception e )
        {
            e.printStackTrace ( System.out );
        }
    }

    /** This method demonstrates synchronous update access to group data
     */
    protected void updateGroupSyncExample ()
    {
        try
        {
            System.out.println("\n--- starting example: update group data synchronously --------------");
            editGridOptions( );
        }   
        catch ( Exception e )
        {
            e.printStackTrace ( System.out );
        }
    }

    /** This method demonstrates resetting data to its default state
     */
    protected void resetGroupExample ()
    {
        try
        {
            System.out.println("\n--- starting example: reset group data -----------------------------");
            Object aOldData = readGridConfiguration( );
            resetGridConfiguration( );
            Object aNewData = readGridConfiguration( );
            System.out.println("Before reset:   user grid options: " + aOldData);
            System.out.println("After reset: default grid options: " + aNewData);
        }   
        catch ( Exception e )
        {
            e.printStackTrace ( System.out );
        }
    }

    /** This method demonstrates asynchronous update access to set data
     */
    protected void updateSetAsyncExample ()
    {
        try
        {
            System.out.println("\n--- starting example: update set data asynchronously ---------------");
            storeSampleDataSource( );
        }
        catch ( Exception e )
        {
            e.printStackTrace ( System.out );
        }
    }

// READ example
    /// class to hold information about grid settings
    public static class GridOptions
    {
        public boolean visible;
        public int resolution_x;
        public int resolution_y;
        public int subdivision_x;
        public int subdivision_y;

        public String toString() {
            StringBuffer aBuffer = new StringBuffer();
            aBuffer.append("[ Grid is "); aBuffer.append(visible ? "VISIBLE" : "HIDDEN");
            aBuffer.append("; resolution  = (" + resolution_x  + "," + resolution_y  + ")");
            aBuffer.append("; subdivision = (" + subdivision_x + "," + subdivision_y + ")");
            aBuffer.append(" ]");
            return aBuffer.toString();
        }
    };

    /// This method reads information about grid settings
    protected GridOptions readGridConfiguration()
        throws com.sun.star.uno.Exception
    {
        // The path to the root element 
        final String cGridOptionsPath = "/org.openoffice.Office.Calc/Grid";

        // create the view
        Object xViewRoot = createConfigurationView(cGridOptionsPath);

        // the result structure
        GridOptions options = new GridOptions();
   
      // accessing a single nested value
        XHierarchicalPropertySet xProperties = 
            (XHierarchicalPropertySet)UnoRuntime.queryInterface(XHierarchicalPropertySet.class, xViewRoot);

        Object aVisible = xProperties.getHierarchicalPropertyValue("Option/VisibleGrid");
        options.visible = ((Boolean) aVisible).booleanValue();

      // accessing a nested object and its subproperties
        Object xSubdivision = xProperties.getHierarchicalPropertyValue("Subdivision");

        XMultiPropertySet xSubdivProperties =
            (XMultiPropertySet)UnoRuntime.queryInterface(XMultiPropertySet.class, xSubdivision);
    
        // variables for multi-element access 
        String[] aElementNames = new String[2];

        aElementNames[0] = "XAxis";
        aElementNames[1] = "YAxis";

        Object[] aElementValues = xSubdivProperties.getPropertyValues(aElementNames);

        options.subdivision_x = ((Integer) aElementValues[0]).intValue();
        options.subdivision_y = ((Integer) aElementValues[1]).intValue();

      // accessing deeply nested subproperties
        Object xResolution = xProperties.getHierarchicalPropertyValue("Resolution");

        XMultiHierarchicalPropertySet xResolutionProperties = 
            (XMultiHierarchicalPropertySet)
                UnoRuntime.queryInterface(XMultiHierarchicalPropertySet.class, xResolution);
    
        aElementNames[0] = "XAxis/Metric";
        aElementNames[1] = "YAxis/Metric";

        aElementValues = xResolutionProperties.getHierarchicalPropertyValues(aElementNames);

        options.resolution_x = ((Integer) aElementValues[0]).intValue();
        options.resolution_y = ((Integer) aElementValues[1]).intValue();

      // all options have been retrieved - clean up and return
        // we are done with the view - dispose it 

        ((XComponent)UnoRuntime.queryInterface(XComponent.class, xViewRoot)).dispose();

        return options;
    }

// BROWSE example
    /// Interface to procees information when browsing the configuration tree
    public static interface IConfigurationProcessor
    {
        /// process a value item
       public abstract void processValueElement( String sPath_, Object aValue_ );
        /// process a structural item
       public abstract void processStructuralElement( String sPath_, XInterface xElement_);
    };

    /// Internal method to recursively browse a structural element in preorder
    public void browseElementRecursively( XInterface xElement, IConfigurationProcessor aProcessor )
        throws com.sun.star.uno.Exception
    {
        // First process this as an element (preorder traversal)
        XHierarchicalName xElementPath = 
            (XHierarchicalName) UnoRuntime.queryInterface(XHierarchicalName.class, xElement);

        String sPath = xElementPath.getHierarchicalName();

        aProcessor.processStructuralElement( sPath, xElement);

        // now process this as a container
        XNameAccess xChildAccess =
            (XNameAccess) UnoRuntime.queryInterface(XNameAccess.class, xElement);
    
        // get a list of child elements
        String[] aElementNames = xChildAccess.getElementNames();

        // and process them one by one
        for(int i=0; i< aElementNames.length; ++i)
        {
            Object aChild = xChildAccess.getByName( aElementNames[i] );
            AnyConverter aAnyConv = new AnyConverter();
            // is it a structural element (object) ...
            if ( aAnyConv.isObject(aChild) )
            {
                // then get an interface 
                XInterface xChildElement = (XInterface)UnoRuntime.queryInterface(XInterface.class, aChild);

                // and continue processing child elements recursively
                browseElementRecursively( xChildElement, aProcessor );
            }
            // ... or is it a simple value
            else
            {
                // Build the path to it from the path of 
                // the element and the name of the child
                String sChildPath;
                sChildPath = 
                    xElementPath.composeHierarchicalName(aElementNames[i]);

                // and process the value
                aProcessor.processValueElement( sChildPath, aChild );
            }
        }
    }

    /** Method to browse the part rooted at sRootPath 
        of the configuration that the Provider provides.

        All nodes will be processed by the IConfigurationProcessor passed.
    */
    public void browseConfiguration( String sRootPath, IConfigurationProcessor aProcessor )
        throws com.sun.star.uno.Exception
    {
        // create the root element
        XInterface xViewRoot = (XInterface)createConfigurationView( sRootPath );
   
        // now do the processing
        browseElementRecursively( xViewRoot, aProcessor );

        // we are done with the view - dispose it 
        //   This assumes that the processor 
        //   does not keep a reference to the elements in processStructuralElement

        ((XComponent) UnoRuntime.queryInterface(XComponent.class,xViewRoot)).dispose();
        xViewRoot = null;
    }

    /** Method to browse the filter configuration.

        Information about installed filters will be printed.
    */
    public void printRegisteredFilters()
        throws com.sun.star.uno.Exception
    {
        final String sProviderService = "com.sun.star.configuration.ConfigurationProvider";
        final String sFilterKey = "/org.openoffice.Office.TypeDetection/Filters";

       // browse the configuration, dumping filter information
        browseConfiguration( sFilterKey, 
           new IConfigurationProcessor () {
               /// prints Path and Value of properties
               public void processValueElement( String sPath_, Object aValue_ ) {
                   System.out.println("\tValue: " + sPath_ + " = " + aValue_);
               }
               /// prints the Filter entries
               public void processStructuralElement( String sPath_, XInterface xElement_) {
                   // get template information, to detect instances of the 'Filter' template
                   XTemplateInstance xInstance = 
                       ( XTemplateInstance )UnoRuntime.queryInterface( XTemplateInstance .class,xElement_);

                   // only select the Filter entries 
                   if (xInstance != null && xInstance.getTemplateName().endsWith("Filter")) {
                        XNamed xNamed = (XNamed)UnoRuntime.queryInterface(XNamed.class,xElement_);
                        System.out.println("Filter " + xNamed.getName() + " (" + sPath_ + ")");
                   }
               }
           } );
    }

// GROUP UPDATE example

    /** This method simulates editing configuration data using a GridEditor dialog class  
    */
    public void editGridOptions( )
        throws com.sun.star.uno.Exception
    {
        // The path to the root element 
        final String cGridOptionsPath = "/org.openoffice.Office.Calc/Grid";

      // create the SYNCHRONOUS view for better error handling
        Object xViewRoot = createUpdatableView( cGridOptionsPath, false);

        // the 'editor'
        GridOptionsEditor dialog = new GridOptionsEditor();

      // set up the initial values and register listeners
        // get a data access interface, to supply the view with a model 
        XMultiHierarchicalPropertySet xProperties =
            (XMultiHierarchicalPropertySet)
                UnoRuntime.queryInterface(XMultiHierarchicalPropertySet.class, xViewRoot);

        dialog.setModel( xProperties );

        // get a listener object (probably an adapter) that notifies
        // the dialog of external changes to its model 
        XChangesListener xListener = dialog.createChangesListener( );
    
        XChangesNotifier xNotifier = 
            (XChangesNotifier)UnoRuntime.queryInterface(XChangesNotifier.class, xViewRoot);

        xNotifier.addChangesListener( xListener );

        // trigger the listener
        changeSomeData( cGridOptionsPath + "/Subdivision" );

        if (dialog.execute() == GridOptionsEditor.SAVE_SETTINGS)
        {
            // changes have been applied to the view here
            XChangesBatch xUpdateControl = 
                (XChangesBatch) UnoRuntime.queryInterface(XChangesBatch.class,xViewRoot);
        
            try
            {
               xUpdateControl.commitChanges();
            }
            catch (Exception e)
            {
                dialog.informUserOfError( e );
            }
        }
   
      // all changes have been handled - clean up and return
        // listener is done now
        xNotifier.removeChangesListener( xListener );

        // we are done with the view - dispose it 
        ((XComponent)UnoRuntime.queryInterface(XComponent.class, xViewRoot)).dispose();
    }

    /** A class that changes some grid options settings

        The interface of this class is chose to resemble a possible UI dialog class
    */
    private class GridOptionsEditor {
        /// the data this editor edits
        XMultiHierarchicalPropertySet mxModel;

        public static final int CANCELED = 0;
        public static final int SAVE_SETTINGS = 1;

        // sets a model and updates the display
        public void setModel(XMultiHierarchicalPropertySet xModel) {
            mxModel = xModel;
            updateDisplay();
        }

        // this method 'runs' the 'dialog'
        public int execute() {
            try
            {
                System.out.println("-- GridEditor executing --");
                // simulate a user action changing some data
                toggleVisibility();
                System.out.println("-- GridEditor done      --");
                return SAVE_SETTINGS;
            }
            catch (Exception e)
            {
                informUserOfError(e);
                return CANCELED;
            }
        }

        /// this method is called to report an error during dialog execution to the zuser
        public void informUserOfError(Exception e) {
            System.out.println("ERROR in GridEditor:");
            e.printStackTrace(System.out);
        }

        /// this method is called to allow the dialog to get feedback about changes occurring elsewhere
        public XChangesListener createChangesListener() {
            if (mxModel == null) return null;

            return (new XChangesListener () {
                public void changesOccurred( ChangesEvent event ) {
                    System.out.println("GridEditor - Listener received changes event containing " +
                                        event.Changes.length + " change(s).");
                    updateDisplay();
                }

                public void disposing(EventObject event) {
                    System.out.println("GridEditor - Listener received disposed event: releasing model");
                    setModel(null);
                }
            });
        }
        /// this method is called when data has changed to display the updated data
        private void updateDisplay()  { 
            if (mxModel != null)
                System.out.println("Grid options editor: data=" + readModel());
            else
                System.out.println("Grid options editor: no model set");
        }

        // this method is used to read all relevant data from the model
        private GridOptions readModel() 
        {
            try
            {
                String [] aOptionNames = new String [5];
                aOptionNames[0] = "Option/VisibleGrid";
                aOptionNames[1] = "Subdivision/XAxis";
                aOptionNames[2] = "Subdivision/YAxis";
                aOptionNames[3] = "Resolution/XAxis/Metric";
                aOptionNames[4] = "Resolution/YAxis/Metric";

                Object [] aValues = mxModel.getHierarchicalPropertyValues(aOptionNames);

                GridOptions result = new GridOptions();
                result.visible = ((Boolean)aValues[0]).booleanValue();
                result.subdivision_x = ((Integer)aValues[1]).intValue();
                result.subdivision_y = ((Integer)aValues[2]).intValue();
                result.resolution_x  = ((Integer)aValues[3]).intValue();
                result.resolution_y  = ((Integer)aValues[4]).intValue();

                return result;
            }
            catch (Exception e)
            {
                informUserOfError(e);
                return null;
            }
        }

        // this method executes an edit
        private void toggleVisibility()
        {
            try
            {
                XHierarchicalPropertySet xHPS = 
                    (XHierarchicalPropertySet)UnoRuntime.queryInterface(XHierarchicalPropertySet.class, mxModel);

                final String sSetting = "Option/VisibleGrid";

                System.out.println("GridEditor: toggling Visibility");

                Boolean bOldValue = (Boolean)xHPS.getHierarchicalPropertyValue(sSetting);

                Boolean bNewValue = new Boolean( ! bOldValue.booleanValue() );
            
                xHPS.setHierarchicalPropertyValue(sSetting,bNewValue);
            }
            catch (Exception e)
            {
                informUserOfError(e);
            }
        }
    }

    /** This method creates an extra updatable view to change some data 
        and trigger the listener of the GridEditor  
    */
    void changeSomeData(String xKey) 
    {
        try
        {
            Object xOtherViewRoot = createUpdatableView(xKey, false);

            XNameReplace aReplace = (XNameReplace)UnoRuntime.queryInterface(XNameReplace.class, xOtherViewRoot);

            String aItemNames [] = aReplace.getElementNames();
            for (int i=0; i < aItemNames.length; ++i) {
                Object aItem = aReplace.getByName( aItemNames [i] );
                AnyConverter aAnyConv = new AnyConverter();
                // replace integers by a 'complement' value
                if ( aAnyConv.isInt(aItem) )
                {
                    int nOld = aAnyConv.toInt(aItem);
                    int nNew = 9999 - nOld;

                    System.out.println("Replacing integer value: " + aItemNames [i]);
                    aReplace.replaceByName( aItemNames [i], new Integer( nNew ) );
                }

                // and booleans by their negated value
                else if ( aAnyConv.isBoolean(aItem) )
                {
                    boolean bOld = aAnyConv.toBoolean(aItem);
                    boolean bNew = ! bOld;

                    System.out.println("Replacing boolean value: " + aItemNames [i]);
                    aReplace.replaceByName( aItemNames [i], new Boolean( bNew ) );
                }
            }

            // commit the changes
            XChangesBatch xUpdateControl = 
                (XChangesBatch) UnoRuntime.queryInterface(XChangesBatch.class,xOtherViewRoot);
        
            xUpdateControl.commitChanges();

            // we are done with the view - dispose it 
            ((XComponent)UnoRuntime.queryInterface(XComponent.class, xOtherViewRoot)).dispose();
        }
        catch (Exception e)
        {
            System.out.println("Could not change some data in a different view. An exception occurred:");
            e.printStackTrace( System.out );
        }
    }

// GROUP RESET EXAMPLE
    /// This method resets the grid settings to their default values
    protected void resetGridConfiguration()
        throws com.sun.star.uno.Exception
    {
        // The path to the root element 
        final String cGridOptionsPath = "/org.openoffice.Office.Calc/Grid";

        // create the view
        Object xViewRoot = createUpdatableView(cGridOptionsPath);

     // resetting a single nested value
        XHierarchicalNameAccess xHierarchicalAccess = 
            (XHierarchicalNameAccess)UnoRuntime.queryInterface(XHierarchicalNameAccess.class, xViewRoot);

        // get using absolute name
        Object xOptions = xHierarchicalAccess.getByHierarchicalName(cGridOptionsPath + "/Option");

        XPropertyState xOptionState = 
            (XPropertyState)UnoRuntime.queryInterface(XPropertyState.class, xOptions);

        xOptionState.setPropertyToDefault("VisibleGrid");

     // resetting more deeply nested values
        Object xResolutionX = xHierarchicalAccess.getByHierarchicalName("Resolution/XAxis");
        Object xResolutionY = xHierarchicalAccess.getByHierarchicalName("Resolution/YAxis");

        XPropertyState xResolutionStateX = 
            (XPropertyState)UnoRuntime.queryInterface(XPropertyState.class, xResolutionX);
        XPropertyState xResolutionStateY = 
            (XPropertyState)UnoRuntime.queryInterface(XPropertyState.class, xResolutionY);

        xResolutionStateX.setPropertyToDefault("Metric");
        xResolutionStateY.setPropertyToDefault("Metric");

     // resetting multiple sibling values
        Object xSubdivision = xHierarchicalAccess.getByHierarchicalName("Subdivision");

        XMultiPropertyStates xSubdivisionStates =
            (XMultiPropertyStates)UnoRuntime.queryInterface(XMultiPropertyStates.class, xSubdivision);
    
        xSubdivisionStates.setAllPropertiesToDefault();

        // commit the changes
        XChangesBatch xUpdateControl = 
            (XChangesBatch) UnoRuntime.queryInterface(XChangesBatch.class,xViewRoot);
    
        xUpdateControl.commitChanges();

       // we are done with the view - dispose it 
        ((XComponent)UnoRuntime.queryInterface(XComponent.class, xViewRoot)).dispose();
    }


// SET UPDATE EXAMPLE
    /** This method stores a sample data source given some connection data
    */
    void storeSampleDataSource()
        throws com.sun.star.uno.Exception
    {
        String sSampleDataSourceName = "SampleTextDatabase";

        String sSampleDataSourceURL = "sdbc:flat:$(userurl)/database/SampleTextDatabase";
        // String sSampleDataSourceURL = "sdbc:flat:file:///usr/local/database/SampleTextDatabase";
        // String sSampleDataSourceURL = "sdbc:flat:file:///C:/data/database/SampleTextDatabase";

        com.sun.star.beans.NamedValue [] aSettings = new com.sun.star.beans.NamedValue [2];
        aSettings[0] = new com.sun.star.beans.NamedValue("HeaderLine",new Boolean(true));
        aSettings[1] = new com.sun.star.beans.NamedValue("FieldDelimiter",";");

        String [] aTableFilter = new String[2];
        aTableFilter[0] = "table.txt";
        aTableFilter[1] = "othertable.txt";

        storeDataSource(sSampleDataSourceName,sSampleDataSourceURL,"",false,0,aSettings,aTableFilter);
    }

    /// This method stores a data source given some connection data
    void storeDataSource(
        String sDataSourceName,
        String sDataSourceURL,
        String sUser,
        boolean bNeedsPassword,
        int nTimeout,
        com.sun.star.beans.NamedValue [] aDriverSettings,
        String [] aTableFilter
    )
        throws com.sun.star.uno.Exception
    {
      // create the view and get the data source element 
        Object xDataSource = createDataSourceDescription(getProvider(),sDataSourceName);

      // set the values 
        XPropertySet xDataSourceProperties =
            (XPropertySet)UnoRuntime.queryInterface(XPropertySet.class, xDataSource);

        xDataSourceProperties.setPropertyValue("URL",  sDataSourceURL  );
        xDataSourceProperties.setPropertyValue("User", sUser  );
        xDataSourceProperties.setPropertyValue("IsPasswordRequired", new Boolean( bNeedsPassword ) );
        xDataSourceProperties.setPropertyValue("LoginTimeout", new Integer( nTimeout ) );

        if ( aTableFilter != null )
            xDataSourceProperties.setPropertyValue("TableFilter",  aTableFilter  );
    
      // store the driver-specific settings
        if (aDriverSettings != null)
        {
            Object xSettingsSet = xDataSourceProperties.getPropertyValue("DataSourceSettings");
            storeSettings( xSettingsSet, aDriverSettings);
        }

      // save the data and dispose the view
        // recover the view root
        Object xViewRoot = getViewRoot(xDataSource);

        // commit the changes
        XChangesBatch xUpdateControl = 
            (XChangesBatch) UnoRuntime.queryInterface(XChangesBatch.class,xViewRoot);
        
        xUpdateControl.commitChanges();

        // now clean up
        ((XComponent) UnoRuntime.queryInterface(XComponent.class, xViewRoot)).dispose();
    }

    /** This method gets the DataSourceDescription for a data source.
        It either gets the existing entry or creates a new instance.

        The method attempts to keep the view used as small as possible. In particular there
        is no view created, that contains data for all data source that are registered.
    */
    Object createDataSourceDescription(XMultiServiceFactory xProvider, String sDataSourceName )
        throws com.sun.star.uno.Exception
    {
        // The service name: Need an update access:
        final String cUpdatableView = "com.sun.star.configuration.ConfigurationUpdateAccess";

         // The path to the DataSources set node 
        final String cDataSourcesPath = "/org.openoffice.Office.DataAccess/DataSources";

       // creation arguments: nodepath   
        com.sun.star.beans.PropertyValue aPathArgument = new com.sun.star.beans.PropertyValue();
        aPathArgument.Name = "nodepath";
        aPathArgument.Value = cDataSourcesPath ;

        // creation arguments: commit mode   
        com.sun.star.beans.PropertyValue aModeArgument = new com.sun.star.beans.PropertyValue();
        aModeArgument.Name = "lazywrite";
        aModeArgument.Value = new Boolean( true );

        // creation arguments: depth   
        com.sun.star.beans.PropertyValue aDepthArgument = new com.sun.star.beans.PropertyValue();
        aDepthArgument.Name = "depth";
        aDepthArgument.Value = new Integer( 1 );

        Object[] aArguments = new Object[3];
        aArguments[0] = aPathArgument;
        aArguments[1] = aModeArgument;
        aArguments[2] = aDepthArgument;

        // create the view: asynchronously updatable, with depth 1
        Object xViewRoot = 
            xProvider.createInstanceWithArguments(cUpdatableView, aArguments);

        XNameAccess xSetOfDataSources =
            (XNameAccess) UnoRuntime.queryInterface(XNameAccess.class,xViewRoot);

        Object xDataSourceDescriptor = null; // the result
        if ( xSetOfDataSources .hasByName( sDataSourceName ))
        {
            // the element is there, but it is loaded only with depth zero !
            try 
            {
                // the view should point to the element directly, so we need to extend the path
                XHierarchicalName xComposePath = (XHierarchicalName)
                    UnoRuntime.queryInterface(XHierarchicalName.class, xSetOfDataSources );
            
                String sElementPath = xComposePath.composeHierarchicalName( sDataSourceName );

                // use the name of the element now
                aPathArgument.Value = sElementPath;

                // create another view now (without depth limit)
                Object[] aDeepArguments = new Object[2];
                aDeepArguments[0] = aPathArgument;
                aDeepArguments[1] = aModeArgument;

                // create the view: asynchronously updatable, with unlimited depth
                xDataSourceDescriptor  = 
                      xProvider.createInstanceWithArguments(cUpdatableView, aDeepArguments);

                if ( xDataSourceDescriptor != null) // all went fine 
                {
                    // dispose the other view
                    ((XComponent)UnoRuntime.queryInterface(XComponent.class, xViewRoot)).dispose();
                    xViewRoot = null;
                }
            }
            catch (Exception e) 
            {
              // something went wrong, we retry with a new element 
               System.out.println("WARNING: An exception occurred while creating a view for an existing data source: " + e);
               xDataSourceDescriptor  = null;
            }
        }

        // do we have a result element yet ?
        if ( xDataSourceDescriptor == null)
        {
            // get the container 
            XNameContainer xSetUpdate = 
                (XNameContainer)UnoRuntime.queryInterface(XNameContainer.class, xViewRoot);

            // create a new detached set element (instance of DataSourceDescription)
            XSingleServiceFactory xElementFactory =
                (XSingleServiceFactory)UnoRuntime.queryInterface(XSingleServiceFactory.class, xSetUpdate);

            // the new element is the result !
             xDataSourceDescriptor  = xElementFactory.createInstance();

            // insert it - this also names the element 
            xSetUpdate.insertByName( sDataSourceName ,  xDataSourceDescriptor  );
        }

        return xDataSourceDescriptor ;
    }

    /// this method stores a number of settings in a set node containing DataSourceSetting objects
    void storeSettings(Object xSettingsSet, com.sun.star.beans.NamedValue [] aSettings )
        throws com.sun.star.uno.Exception
    {
        if (aSettings == null) 
            return;

        // get the settings set as a container
        XNameContainer xSettingsContainer = 
            (XNameContainer) UnoRuntime.queryInterface( XNameContainer.class, xSettingsSet);

        // and get a factory interface for creating the entries
        XSingleServiceFactory xSettingsFactory = 
            (XSingleServiceFactory) UnoRuntime.queryInterface(XSingleServiceFactory.class, xSettingsSet);

        // now insert the individual settings
        for (int i = 0; i < aSettings.length; ++i) {
            // create a DataSourceSetting object
            XPropertySet xSetting = (XPropertySet) 
                UnoRuntime.queryInterface( XPropertySet.class, xSettingsFactory.createInstance() );

            // can set the value before inserting
            xSetting.setPropertyValue( "Value", aSettings[i].Value );

            // and now insert or replace as appropriate
            if (xSettingsContainer.hasByName( aSettings[i].Name ))
                xSettingsContainer.replaceByName( aSettings[i].Name, xSetting );
            else
                xSettingsContainer.insertByName( aSettings[i].Name, xSetting );
        }
    }

    /// This method get the view root node given an interface to any node in the view
    public static Object getViewRoot(Object xElement)
    {
        Object xResult = xElement; 
      
        // set the result to its parent until that would be null  
        Object xParent;
        do
        {
            XChild xParentAccess =
                (XChild) UnoRuntime.queryInterface(XChild.class,xResult);

            if (xParentAccess != null)
                xParent = xParentAccess.getParent();
            else
                xParent = null;

            if (xParent != null)
                xResult = xParent;
         }
         while (xParent != null);

         return xResult;
    }

// workaround methods for unimplemented functionality

    /// WORKAROUND: does the same as xNamedItem.setName(sNewName) should do
    void renameSetItem(XNamed xNamedItem, String sNewName) 
        throws com.sun.star.uno.Exception
    {
        XChild xChildItem = (XChild) 
            UnoRuntime.queryInterface(XChild.class, xNamedItem);

        XNameContainer xParentSet = (XNameContainer) 
            UnoRuntime.queryInterface( XNameContainer.class, xChildItem.getParent() );

        String sOldName = xNamedItem.getName();

        // now rename the item
        xParentSet.removeByName(sOldName);
        xParentSet.insertByName(sNewName,xNamedItem);
    }  

    /// WORKAROUND: does the same as xChildItem.setParent( xNewParent ) should do
    void moveSetItem(XChild xChildItem, XNameContainer xNewParent) 
        throws com.sun.star.uno.Exception
    {
        XNamed xNamedItem = (XNamed) 
            UnoRuntime.queryInterface(XNamed.class, xChildItem);

        XNameContainer xOldParent = (XNameContainer) 
            UnoRuntime.queryInterface( XNameContainer.class, xChildItem.getParent() );

        String sItemName = xNamedItem.getName();

        // now rename the item
        xOldParent.removeByName(sItemName);
        xNewParent.insertByName(sItemName,xChildItem);
    }


// ------- the end -----------
}
