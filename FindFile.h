//==========================================================================
// FindFile.h
//
// Searches for files and folders with a variety of different options in 
// a given location
//
// Author: Louka Dlagnekov
//
// This source code is free software; you can redistribute it and/or
// modify it any way you see fit as long as this statement and the original
// author's name remains.
//
//==========================================================================

#include <stdio.h>
#include <windows.h>
#include <string>
#include <vector>

using namespace std;


// Specifies settings to use for searching for files
struct FindFileOptions_t
{
    bool recursive;         // Whether to look inside subdirectories
    bool returnFolders;     // Return folder names as results too

    bool *terminateValue;   // Value to check to see whether search should be
                            // terminated

    wstring location;        // Where to search for files

    wstring filter;          // Filter for files to be included

    wstring excludeFile;     // Exclude filter for files
    wstring excludeDir;      // Exclude filter for directories
};

// Holds information on a found file
struct FileInformation
{
    WIN32_FIND_DATA fileinfo;
    wstring path;
};

// A list of found files
typedef vector<FileInformation> FileList_t;


class FindFile
{
private:

    FindFileOptions_t m_opts;

    // Scans a path for files as according to 
    void scanPath(wstring path);

    // Finds a single file and returns true if there are more to come
    bool getFiles(HANDLE &searchHandle, WIN32_FIND_DATA &filedata, wstring path);

    // Returns true if given file information matches requested criteria
    bool matchCriteria(WIN32_FIND_DATA &filedata);

public:

    FileList_t filelist;        // List of files found in search
    __int64 listsize;           // Size in bytes of all files in found list

    FindFile(FindFileOptions_t &opts);
    ~FindFile ();

    // Clears list of found files, file handle and so on
    void clear();

    // Finds all files as specified in the initial options
    void search ();

    // Concatenates 2 paths
    static wstring combinePath(wstring path1, wstring path2);
};

