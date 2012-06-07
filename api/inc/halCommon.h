/*
 * Copyright (C) 2012 by Glenn Hickey (hickey@soe.ucsc.edu)
 *
 * Released under the MIT license, see LICENSE.txt
 */

#ifndef _HALCOMMON_H
#define _HALCOMMON_H

#include <map>
#include <string>
#include <vector>
#include <locale>
#include <cassert>

namespace hal {

/** C++ style strtok-type function.  Can't remember why I wrote it */
std::vector<std::string> chopString(const std::string& inString,
                                    const std::string& separator);

/** Get the DNA reverse complement of a character.
 * If the input is not a nucleotide, then just return it as is
 * (ie no error checking) */
inline hal_dna_t reverseComplement(hal_dna_t c)
{
  switch (c)
  {
  case 'A' : return 'T'; 
  case 'a' : return 't'; 
  case 'C' : return 'G'; 
  case 'c' : return 'g';
  case 'G' : return 'C';
  case 'g' : return 'c';
  case 'T' : return 'A';
  case 't' : return 'a';
  default : break;
  }
  return c;
}

/** Check if a DNA character is a valid base (or n-chracter) */
inline hal_bool_t isNucleotide(hal_dna_t c)
{
  hal_bool_t result = false;
  switch (c)
  {
  case 'A' : 
  case 'a' : 
  case 'C' : 
  case 'c' : 
  case 'G' : 
  case 'g' : 
  case 'T' : 
  case 't' : 
  case 'N' :
  case 'n' :
    result = true;
  default : break;
  }
  return result;
}

/** Count the mutations between two DNA strings */
inline hal_size_t hammingDistance(const std::string& s1, const std::string& s2)
{
  assert(s1.length() == s2.length());
  hal_size_t dist = 0;
  for (size_t i = 0; i < s1.length(); ++i)
  {
    if (std::toupper(s1[i]) != std::toupper(s2[i]))
    {
      ++dist;
    }
  }
  return dist;
}

}
#endif
