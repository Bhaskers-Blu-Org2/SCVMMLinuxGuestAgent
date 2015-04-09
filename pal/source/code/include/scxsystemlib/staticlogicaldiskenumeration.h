/**
 *  Copyright (c) Microsoft Corporation
 *
 *  All rights reserved.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may not
 *  use this file except in compliance with the License. You may obtain a copy
 *  of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 *  THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 *  KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED
 *  WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE,
 *  MERCHANTABLITY OR NON-INFRINGEMENT.
 *
 *  See the Apache Version 2.0 License for specific language governing
 *  permissions and limitations under the License.
 *
 **/

/**
    \file        

    \brief       Defines the static disk information enumeration PAL for logical disks.
    
    \date        2008-03-19 11:42:00

*/
/*----------------------------------------------------------------------------*/
#ifndef STATICLOGICALDISKENUMERATION_H
#define STATICLOGICALDISKENUMERATION_H

#include <scxsystemlib/entityenumeration.h>
#include <scxsystemlib/staticlogicaldiskinstance.h>
#include <scxsystemlib/diskdepend.h>
#include <scxcorelib/scxlog.h>
#include <scxcorelib/scxhandle.h>

namespace SCXSystemLib
{
#if defined(sun)
    /** Represents a single row in /etc/device.tab. Exists on Solaris only. 
     We are presently using only attrs field to get at drive removability but 
    the others are included for future use  ... */
    struct DevTabEntry
    {
      std::wstring    alias;       //!< Device alias
      std::wstring    cdevice;   //!< Pathname to inode for character device
      std::wstring    bdevice;   //!< Pathname to inode for block device
      std::wstring    pathName; //!< Pathname to inode for the device
      std::wstring    attrs; //!< Attributes of the device
    };
#endif

/*----------------------------------------------------------------------------*/
/**
    Represents a set of discovered logical disks and their static data.
*/
    class StaticLogicalDiskEnumeration : public EntityEnumeration<StaticLogicalDiskInstance>
    {
    public:
        StaticLogicalDiskEnumeration(SCXCoreLib::SCXHandle<DiskDepend> deps);
        virtual ~StaticLogicalDiskEnumeration();

        virtual void Init();
        virtual void Update(bool updateInstances=true);
        virtual void CleanUp();

        /**
            Check if a given disk is removable

            \param       Name of disk device.
            \returns     eDiskCapsSupportsRemovableMedia, eDiskCapOther (not removable), 
            eDiskCapUnknown (not found or information not supported). 
        */
        virtual int GetDiskRemovability(const std::wstring& name); 

    private:
        StaticLogicalDiskEnumeration();         //!< Private constructor (intentionally not implemented)
    protected:
        SCXCoreLib::SCXHandle<DiskDepend> m_deps; //!< Disk dependency object for dependency injection
        SCXCoreLib::SCXLogHandle m_log;         //!< Log handle

#if defined(sun)
        std::map<std::wstring, DevTabEntry> m_devTab; //!< A parsed dev tab object. 
#endif      

#if defined(sun)
        /**
            Get a parsed version of device tab.

            \returns a vector of DevTabEntry objects.
        */ 
        virtual const std::map<std::wstring, DevTabEntry>& GetDevTab() ;
#endif

        /**
            Refresh the device tab state.
        */ 
        virtual void RefreshDevTab();
    };

} /* namespace SCXSystemLib */
#endif /* STATICLOGICALDISKENUMERATION_H */
/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
