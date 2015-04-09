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

    \brief       Defines the product-specific dependencies for SCXCore
    \date        2013-02-25 11:20:00
*/
/*----------------------------------------------------------------------------*/
#ifndef SCXCOREPRODUCTDEPENDENCIES_H
#define SCXCOREPRODUCTDEPENDENCIES_H

#include <scxcorelib/scxcmn.h>
#include <scxcorelib/scxhandle.h>
#include <scxcorelib/scxlogitem.h>

#include <fstream>
#include <string>

namespace SCXCoreLib
{
    namespace SCXProductDependencies
    {
        //
        // Needed for logging subsystem
        //

        /*----------------------------------------------------------------------------*/
        /**
           The developer must implement this function to write the "header" to the log
           file.  The header is written whenever a new log file is generated, or when
           the agent restarts.
           
           \param[in] stream    The stream to write the head to
           \param[in] runNum    Number of rotations of the log file
           \param[in] procStart Timestamp when first log from process was made
        */
        void WriteLogFileHeader( SCXHandle<std::wfstream> &stream, int runNum, SCXCalendarTime& procStart );

        /*----------------------------------------------------------------------------*/
        /**
           The developer must implement this function to modify log file lines as they
           are written to the log file.  If no changes are needed, then simply implement
           as something like:
               stream << message << std::endl;

           This method provides a hook if log lines must be written in some particular
           format, or must be modified in some way.
           
           \param[in] stream    The stream to write the head to
           \param[in] item      Log file item to be written (if needed for context)
           \param[in] message   Formatted message to be written to the log file
        */
        void WrtieItemToLog( SCXHandle<std::wfstream> &stream, const SCXLogItem& item, const std::wstring& message );
    }
}

#endif // SCXCOREPRODUCTDEPENDENCIES_H
