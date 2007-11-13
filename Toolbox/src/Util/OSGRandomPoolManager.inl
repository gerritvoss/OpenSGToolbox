#include "OSGRandomPoolManager.h"

OSG_USING_NAMESPACE

inline
RandomPoolManager::RandomPoolManager(void)
{
}

inline
void RandomPoolManager::operator=(const RandomPoolManager& val)
{
}

inline
UInt32 RandomPoolManager::getNumPools(void)
{
    return _RandomPoolGenerators.size();
}

inline
UInt32 RandomPoolManager::createNewPool(void)
{
    _RandomPoolGenerators.push_back(RandomGeneratorType());
    return getNumPools()-1;
}

inline
void RandomPoolManager::seedPool(UInt32 RandomPool, RandomGeneratorType::result_type seed)
{
    _RandomPoolGenerators[RandomPool].seed(seed);
}

inline
Int32 RandomPoolManager::getRandomInt32(Int32 Min, Int32 Max)
{
    return getRandomInt32(_DefautlGeneratorPool, Min, Max);
}

inline
Int64 RandomPoolManager::getRandomInt64(Int64 Min, Int64 Max)
{
    return getRandomInt64(_DefautlGeneratorPool, Min, Max);
}

inline
Real32 RandomPoolManager::getRandomReal32(Real32 Min, Real32 Max)
{
    return getRandomReal32(_DefautlGeneratorPool, Min, Max);
}

inline
Real64 RandomPoolManager::getRandomReal64(Real64 Min, Real64 Max)
{
    return getRandomReal64(_DefautlGeneratorPool, Min, Max);
}

inline
void RandomPoolManager::setDefaultGeneratorPool(const UInt32 Pool)
{
    _DefautlGeneratorPool = Pool;
}
