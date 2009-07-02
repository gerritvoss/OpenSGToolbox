/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Toolbox                             *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                          Authors: David Kabala                            *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
#ifndef _OPENSG_RANDOM_POOL_MANAGER_H_
#define _OPENSG_RANDOM_POOL_MANAGER_H_

#include <OpenSG/OSGConfig.h>
#include "OSGToolboxDef.h"

#include <OpenSG/OSGVector.h>

#include <boost/random/linear_congruential.hpp> //Defines the rand48 Random generator

#include <vector>

OSG_BEGIN_NAMESPACE

class OSG_TOOLBOXLIB_DLLMAPPING RandomPoolManager
{
public:
    enum RandomNumberPools {GENERAL=0, NUM_DEFINED_POOLS};
private:
    typedef boost::rand48 RandomGeneratorType;
    static std::vector<RandomGeneratorType> _RandomPoolGenerators;
    static UInt32 _DefautlGeneratorPool;
    
    static std::vector<RandomGeneratorType> createPoolGenerators(void);
    RandomPoolManager(void);
    void operator=(const RandomPoolManager& val);
public:
    //Get Random Int uniformly distributed accross [Min, Max]
    static Int32 getRandomInt32(UInt32 RandomPool, Int32 Min, Int32 Max);
    static Int64 getRandomInt64(UInt32 RandomPool, Int64 Min, Int64 Max);
    static Int32 getRandomInt32(Int32 Min, Int32 Max);
    static Int64 getRandomInt64(Int64 Min, Int64 Max);

    //Get Random Real uniformly distributed accross [Min, Max)
    static Real32 getRandomReal32(UInt32 RandomPool, Real32 Min, Real32 Max);
    static Real64 getRandomReal64(UInt32 RandomPool, Real64 Min, Real64 Max);
    static Real32 getRandomReal32(Real32 Min, Real32 Max);
    static Real64 getRandomReal64(Real64 Min, Real64 Max);
    

    static void setDefaultGeneratorPool(const UInt32 Pool);

    static UInt32 getNumPools(void);
    static UInt32 createNewPool(void);
    static void seedPool(UInt32 RandomPool, RandomGeneratorType::result_type seed);
};

OSG_END_NAMESPACE


#include "OSGRandomPoolManager.inl"
#endif


