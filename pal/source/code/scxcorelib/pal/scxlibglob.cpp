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

#if defined(linux)

#include <scxcorelib/scxglob.h>
#include <scxcorelib/scxlibglob.h>

#include <algorithm>
#include <vector>

using namespace std;

namespace SCXCoreLib
{
    SCXLibGlob::SCXLibGlob(wstring name, vector<wstring> paths)
        : m_name(name)
          , m_paths(paths)
    {
        // if directory paths are non-existant, provide default system library paths
        if (paths.size() == 0)
        {
            m_paths.push_back(L"/lib");
            m_paths.push_back(L"/usr/lib");
#if PF_WIDTH == 64
            m_paths.push_back(L"/lib64");
            m_paths.push_back(L"/usr/lib64");
#endif          
        }
    }
    
    bool SCXLibGlob::IsGoodFileName(SCXCoreLib::SCXFilePath path)
    {
        std::wstring str_filename = path.GetFilename(); 
        
        if (str_filename.length() == 0)
        {
            return false; 
        }
        
        size_t offset; 
        
        offset = str_filename.find_last_of('.');
        
        // No dots, there needs to be at least one
        if (offset == std::wstring::npos)
        {
            return false;
        }
        
        // Do not want dot at end of name
        if (offset == str_filename.length() - 1)
        {
            return false;
        }
        
        return true;
    }
    
    /*----------------------------------------------------------------------------*/
    /**
       Static comparator method for a sort routine. This compares the filenames of any
       two given paths, and determines which has a greater version number than the other by 
       using the "strverscmp" function (a GNU extension function).
       
       \param path1 : full path of a file
       \param path2 : full path of a file
       \return true if path1's filename is a greater version than path2's filename
    */
    static bool CompareVersions (SCXCoreLib::SCXFilePath path1, SCXCoreLib::SCXFilePath path2)
    {
        // if the path1's filename has a greater version than path2's filename, 
        // then put path1 before path2 in the sort.
        if (strverscmp(StrToMultibyte(path1.GetFilename()).c_str(),
                       StrToMultibyte(path2.GetFilename()).c_str()) > 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    vector<SCXCoreLib::SCXFilePath> SCXLibGlob::Get()
    {
        SCXCoreLib::SCXFilePath dirpath;
        SCXCoreLib::SCXFilePath curfile;
        
        vector<SCXFilePath> matchedFiles;
        // check each directory for libs that match this
        for (vector<wstring>::iterator curDir = m_paths.begin(); curDir != m_paths.end(); curDir++)
        {
            dirpath.SetDirectory(*curDir);
            dirpath.SetFilename(wstring(m_name));
            SCXGlob glob(dirpath.Get());
            glob.DoGlob();
            while (glob.Next())
            {
                curfile = glob.Current();                
                
                // Validate for nice file names .. 
                if(IsGoodFileName(curfile))
                {
                    matchedFiles.push_back(curfile);
                }
            }
        }
        
        // at this point, matchedFiles contains all libraries that match.  Now let's sort it
        sort (matchedFiles.begin(), matchedFiles.end(), CompareVersions);

        return matchedFiles;
    }  
}

#endif // defined(linux)

