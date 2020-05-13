//=============================================================================
// Author: Louka Dlagnekov UNICODE support: Michael Haephrati
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
 
#include "stdafx.h"
#include "wildcard.h"

// Allows multiple filters separated by ';'
bool wildcard::match (wstring file, wstring _filter)
{
    wstring subfilter;
    wstring filter = _filter;

    if (_filter == L"")
        return false;

    while (filter.find(L";") != -1)
    {
        subfilter = filter.substr(0, filter.find(L";"));
        filter.erase(0, filter.find(L";")+1);
        if (wildcmp (subfilter, file))
            return true;
    }
    return wildcmp (filter, file);
}
//----------------------------------------------------------------------------

/* the main wildcard compare function */
bool wildcard::wildcmp(wstring _findstr, wstring _cmp)
{
  bool retval = true;
  wchar_t findstr[1024], cmp[1024];

  wcscpy (findstr, _findstr.c_str());
  wcscpy (cmp, _cmp.c_str());
  
  int len = (int) wcslen(findstr);

  //we alter the search string, so lets make a copy here
  //and alter it instead
  wchar_t *srch = new wchar_t[len+1*sizeof(wchar_t)];
  wcscpy(srch,findstr);

  if (*srch != '*' && !StartCmp(srch,cmp))
    retval = false;
  else if (srch[len-1] != '*' && !EndCmp(srch,cmp))
    retval = false;
  else {
    //srch may have been changed in StartCmp and/or EndCmp
    //so we need to reset 'len' to the new length
    len = (int) wcslen(srch);

    //get space for the new search string
    wchar_t *s = new wchar_t[len+1];
    int j=0;

    for (int i=0;i<len && retval;++i)
      if (srch[i] != L'*') 
	  {
        //build the new search string
        s[j++] = srch[i];
        s[j] = L'\0';

        //make sure it's found in the source string
        if (!find(s,cmp))
          retval = false;

        //if we reach a * in the middle of the search
        //string, reset string s to start building
        //the next part of the search string after the *
        if (srch[i+1] == L'*') 
		{
          *s = L'\0';
          j=0;
        }
      }
    delete [] s;
  }
  delete [] srch;
  return retval;
}
//----------------------------------------------------------------------------

/* Helper Functions */

//check string for substring
bool wildcard::find(const wchar_t* s1,const wchar_t *s2)
{
  int srchlen=(int)wcslen(s1);
  int cmplen=(int)wcslen(s2);

  for (int i=0;i<cmplen;++i)
    if(wc_cmp(s1,s2+i,srchlen))
      return true;

  return false;
}
//----------------------------------------------------------------------------

//replacement for strncmp, allows for '?'
bool wildcard::wc_cmp(const wchar_t *s1,const wchar_t *s2,int len)
{
  for (int i=0;i<len;++i)
    if (s1[i] != s2[i] && s1[i] != L'?')
      return false;
  return true;
}
//----------------------------------------------------------------------------

//if there's no * at end of the search string, it
//is checked to be identical to the end of the source string
bool wildcard::EndCmp(wchar_t *src,const wchar_t *cmp)
{
  int slen=(int) wcslen(src);
  int clen=(int) wcslen(cmp);

  int j=slen-1;
  for (int i=clen-1;i>0 && src[j] != L'*';--i,--j)
    if(src[j] != cmp[i] && src[j] != L'?')
      return false;
  src[j] = L'\0';

  return true;
}
//----------------------------------------------------------------------------

//if there's no * at head of search string, it
//is checked to be identical to the start of the source string
bool wildcard::StartCmp(wchar_t *src,const wchar_t *cmp)
{
  int len = (int)wcslen(cmp);

  int i=0;
  for ( ;i<len && src[i] != '*';++i)
    if (src[i] != cmp[i] && src[i] != '?')
      return false;

  if (i < len)
    wcsncpy(src,src+i,wcslen(src)-i+1);

  return true;
}
//----------------------------------------------------------------------------

