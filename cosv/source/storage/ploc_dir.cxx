/*************************************************************************
 *
 *  OpenOffice.org - a multi-platform office productivity suite
 *
 *  $RCSfile: ploc_dir.cxx,v $
 *
 *  $Revision: 1.8 $
 *
 *  last change: $Author: hr $ $Date: 2006-06-19 14:30:38 $
 *
 *  The Contents of this file are made available subject to
 *  the terms of GNU Lesser General Public License Version 2.1.
 *
 *
 *    GNU Lesser General Public License Version 2.1
 *    =============================================
 *    Copyright 2005 by Sun Microsystems, Inc.
 *    901 San Antonio Road, Palo Alto, CA 94303, USA
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License version 2.1, as published by the Free Software Foundation.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *    MA  02111-1307  USA
 *
 ************************************************************************/

#include <precomp.h>
#include <cosv/ploc_dir.hxx>

// NOT FULLY DECLARED SERVICES
#include <cosv/ploc.hxx>


namespace csv
{
namespace ploc
{

Directory::Directory()
{
}

Directory::Directory( const Path & i_rPath )
    :   aPath(i_rPath)
        // sPath
{
}

Directory::Directory( const Directory & i_rDir )
    :   Persistent(), aPath(i_rDir.aPath)
        // sPath
{
}

Directory::Directory( const char * i_rLocation )
    :   aPath(i_rLocation, true)
{
}

Directory::Directory( const String & i_rLocation )
    :   aPath(i_rLocation.c_str(), true)
{
}

Directory::~Directory()
{
}

Directory &
Directory::operator+=( const String & i_sName )
{
    InvalidatePath();
    aPath.DirChain() += i_sName;
    return *this;
}

Directory &
Directory::operator+=( const DirectoryChain & i_sDirChain )
{
    InvalidatePath();
    aPath.DirChain() += i_sDirChain;
    return *this;
}

Directory &
Directory::operator-=( uintt i_nLevels )
{
    InvalidatePath();
    aPath.DirChain().PopBack(i_nLevels);
    return *this;
}

bool
Directory::PhysicalCreate( bool i_bCreateParentsIfNecessary ) const
{
    bool ret = PhysicalCreate_Dir( StrPath() );
    if ( ret OR NOT i_bCreateParentsIfNecessary )
        return ret;

    ret = Check_Parent();
    if (ret)
           ret = PhysicalCreate_Dir( StrPath() );
    return ret;
}

bool
Directory::Check_Parent() const
{
    // There is no parent of root directories:
    if ( aPath.DirChain().Size() == 0 )
        return false;

    // Become my own parent:
    String sLastToken = aPath.DirChain().Back();
    const_cast< Directory* >(this)->operator-=(1);

    // Begin behaving as parent:
    bool ret = Exists();
    if (NOT ret)
    {
        ret = Check_Parent();
        if (ret)
               ret = PhysicalCreate_Dir( StrPath() );
    }
    // End behaving as parent.

    // Become myself again:
    const_cast< Directory* >(this)->operator+=(sLastToken);
    return ret;
}

} // namespace ploc
} // namespace csv


#ifdef WNT
#include <direct.h>
#include <io.h>

namespace csv
{
namespace ploc
{

bool
Directory::PhysicalCreate_Dir( const char * i_sStr ) const
{
    return mkdir( i_sStr ) == 0;
}

void
Directory::GetContainedDirectories( StringVector & o_rResult ) const
{
    const char *    c_sANYDIR = "\\*.*";
    String          sNew;

    StreamStr       sFilter(200);
    sFilter << StrPath()
            << c_sANYDIR;

    struct _finddata_t
                    aEntry;
    long            hFile = _findfirst( sFilter.c_str(), &aEntry );

    for ( int bFindMore = (hFile == -1 ? 1 : 0);
          bFindMore == 0;
          bFindMore = _findnext( hFile, &aEntry ) )
    {
        if ( (aEntry.attrib & _A_SUBDIR) AND *aEntry.name != '.' )
        {
            sNew = aEntry.name;
            o_rResult.push_back( sNew );
        }
    }   // end for
    _findclose(hFile);
}

void
Directory::GetContainedFiles( StringVector &    o_rResult,
                              const char *	    i_sFilter,
                              E_Recursivity     i_eRecursivity ) const
{
    StreamStr       sNew(240);
    sNew << aPath;
    StreamStr::size_type
                    nStartFilename = sNew.tellp();

    StreamStr       sFilter(200);
    sFilter << StrPath()
            << "\\"
            << i_sFilter;

    struct _finddata_t
                    aEntry;
    long            hFile = _findfirst( sFilter.c_str(), &aEntry );
    for ( int bFindMore = (hFile == -1 ? 1 : 0);
          bFindMore == 0;
          bFindMore = _findnext( hFile, &aEntry ) )
    {
        sNew.seekp(nStartFilename);
        sNew << aEntry.name;
        String sNewAsString( sNew.c_str() );
        o_rResult.push_back(sNewAsString);
    }	// end for

    _findclose(hFile);
    if ( i_eRecursivity == flat )
        return;

    //  gathering from subdirectories:
    StringVector    aSubDirectories;
    GetContainedDirectories( aSubDirectories );

    StringVector::const_iterator dEnd = aSubDirectories.end();
    for ( StringVector::const_iterator d = aSubDirectories.begin();
          d != dEnd;
          ++d )
    {
        Directory       aSub(*this);
        aSub += *d;
        aSub.GetContainedFiles( o_rResult,
                                i_sFilter,
                                i_eRecursivity );
    }
}

} // namespace ploc
} // namespace csv


#elif defined(UNX)
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

namespace csv
{
namespace ploc
{

bool
Directory::PhysicalCreate_Dir( const char * i_sStr ) const
{
    return mkdir( i_sStr, 00777 ) == 0;
}

void
Directory::GetContainedDirectories( StringVector & o_rResult ) const
{
    StreamStr       sNew(240);
    sNew << aPath;
    StreamStr::size_type
                    nStartFilename = sNew.tellp();

    DIR *           pDir = opendir( StrPath() );
    dirent *        pEntry = 0;
    struct stat 	aEntryStatus;

    while ( (pEntry = readdir(pDir)) != 0 )
    {
        sNew.seekp(nStartFilename);
        sNew << pEntry->d_name;

        stat(sNew.c_str(), &aEntryStatus);
        if ( (aEntryStatus.st_mode & S_IFDIR) == S_IFDIR
             AND *pEntry->d_name != '.' )
        {
            String sNew2(pEntry->d_name);
            o_rResult.push_back(sNew2);
        }   // endif (aEntry.attrib == _A_SUBDIR)
    }	// end while
    closedir( pDir );
}

void
Directory::GetContainedFiles( StringVector &    o_rResult,
                              const char *	    i_sFilter,
                              E_Recursivity     i_eRecursivity ) const
{
    StreamStr       sNew(240);
    sNew << aPath;
    StreamStr::size_type
                    nStartFilename = sNew.tellp();

    bool            bUseFilter = strcmp( i_sFilter, "*.*" ) != 0
                                 AND strncmp( i_sFilter, "*.", 2) == 0;

    DIR *           pDir = opendir( StrPath() );
    dirent *        pEntry = 0;
    struct stat 	aEntryStatus;

    while ( (pEntry = readdir(pDir)) != 0 )
    {
        sNew.seekp(nStartFilename);
        sNew << pEntry->d_name;

        stat(sNew.c_str(), &aEntryStatus);
        if ( (aEntryStatus.st_mode & S_IFDIR) == S_IFDIR )
            continue;   // Don't gather directories.

        if ( bUseFilter )
        {
            const char * pEnding = strrchr(pEntry->d_name,'.');
            if (pEnding == 0)
                continue;
            if ( strcasecmp( pEnding + 1, i_sFilter + 2 ) != 0 )
                continue;
        }

        sNew.seekp(nStartFilename);
        sNew << pEntry->d_name;
        String sNewAsString( sNew.c_str() );
        o_rResult.push_back(sNewAsString);
    }	// end while

    closedir( pDir );
    if ( i_eRecursivity == flat )
        return;

    //  gathering from subdirectories:
    StringVector    aSubDirectories;
    GetContainedDirectories( aSubDirectories );

    StringVector::const_iterator dEnd = aSubDirectories.end();
    for ( StringVector::const_iterator d = aSubDirectories.begin();
          d != dEnd;
          ++d )
    {
        Directory       aSub(*this);
        aSub += *d;
        aSub.GetContainedFiles( o_rResult,
                                i_sFilter,
                                i_eRecursivity );
    }
}

} // namespace ploc
} // namespace csv


#else
#error  For using csv::ploc there has to be defined: WNT or UNX.
#endif


namespace csv
{
namespace ploc
{

const Path &
Directory::inq_MyPath() const
{
    return aPath;
}



} // namespace ploc
} // namespace csv



