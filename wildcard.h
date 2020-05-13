//=============================================================================
// Author: Louka Dlagnekov
// File: wildcard.cpp
// Description: This code compares a file name with a filter to determine
//              whether the filter properly matches the file name.
//              Some of this code is downloaded from
//              http://www.1cplusplusstreet.com/ It has been extended to include
//              multiple filters separated by a ';'
//
// Original copyright notice:
//**************************************
//     
// Name: ^NEW^ -- wildcard string compar
//     e (globbing)
// Description:matches a string against 
//     a wildcard string such as "*.*" or "bl?h
//     .*" etc. This is good for file globbing 
//     or to match hostmasks.
// By: Jack Handy
//
// Returns:1 on match, 0 on no match.
//
//This code is copyrighted and has// limited warranties.Please see http://
//     www.1CPlusPlusStreet.com/xq/ASP/txtCodeI
//     d.1680/lngWId.3/qx/vb/scripts/ShowCode.h
//     tm//for details.//**************************************
// 
//=============================================================================

#include <string>

using namespace std;

class wildcard
{
private:

    // check string for substring
    static bool find(const wchar_t *s1,const wchar_t *s2);

    // replacement for strncmp, allows for '?'
    static bool wc_cmp(const wchar_t *s1,const wchar_t *s2,int len);

    static bool EndCmp(wchar_t *src,const wchar_t *cmp);

    static bool StartCmp(wchar_t *src,const wchar_t *cmp);


public:

    // Allows multiple filters separated by ';'
    static bool match (wstring file, wstring filter);
    
    // the main wildcard compare function
    static bool wildcmp(wstring _findstr, wstring _cmp);
};




 
