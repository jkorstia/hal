/*
 * Copyright (C) 2013 by Glenn Hickey (hickey@soe.ucsc.edu)
 *
 * Released under the MIT license, see LICENSE.txt
 */

#ifndef _HALBLOCKMAPPER_H
#define _HALBLOCKMAPPER_H

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <map>
#include "hal.h"

namespace hal{

// helper class to make blocks for snake display
// keeps a map of segments in reference genome to sets of segments
// in query genome that map to it.  
// can optionally toggle dupes
class BlockMapper
{
public:

   typedef std::set<MappedSegmentConstPtr> MSSet;
   typedef std::set<MappedSegmentConstPtr, MappedSegment::Less> MSFlipSet;

   BlockMapper();
   virtual ~BlockMapper();

   void init(const Genome* refGenome, const Genome* queryGenome, 
             hal_index_t absRefFirst, hal_index_t absRefLast,
             bool doDupes, hal_size_t minLength,
             bool mapTargetAdjacencies);
   void map();

   const MSSet& getMap() const;

protected:
   
   void erase();
   void mapAdjacencies(const MSFlipSet& flipSet,
                       MSFlipSet::const_iterator flipIt);

   static SegmentIteratorConstPtr makeIterator(
     MappedSegmentConstPtr mappedSegment, 
     hal_index_t& minIndex,
     hal_index_t& maxIndex);

   static void cutByNext(SegmentIteratorConstPtr queryIt, 
                         SlicedSegmentConstPtr nextSeg,
                         bool right);

   
protected:

   MSSet _segMap;
   std::set<const Genome*> _spanningTree;
   const Genome* _refGenome;
   const Sequence* _refSequence;
   const Genome* _queryGenome;
   hal_index_t _refChildIndex;
   hal_index_t _queryChildIndex;
   bool _doDupes;
   hal_size_t _minLength;
   hal_index_t _absRefFirst;
   hal_index_t _absRefLast;
   bool _mapAdj;

   static hal_size_t _maxAdjScan;
};

inline const BlockMapper::MSSet& BlockMapper::getMap() const
{
  return _segMap;
}

}

#endif
