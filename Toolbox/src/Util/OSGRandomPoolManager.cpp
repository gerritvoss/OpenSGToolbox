#include "OSGRandomPoolManager.h"

#include "boost/random/uniform_int.hpp"
#include "boost/random/uniform_real.hpp"

OSG_USING_NAMESPACE

std::vector<RandomPoolManager::RandomGeneratorType> RandomPoolManager::_RandomPoolGenerators = RandomPoolManager::createPoolGenerators();

UInt32 RandomPoolManager::_DefautlGeneratorPool = RandomPoolManager::GENERAL;

std::vector<RandomPoolManager::RandomGeneratorType> RandomPoolManager::createPoolGenerators(void)
{
    std::vector<RandomGeneratorType> Generators;
    Generators.reserve(NUM_DEFINED_POOLS);

    for(UInt32 i(0) ; i<NUM_DEFINED_POOLS ; ++i)
    {
        Generators.push_back(RandomGeneratorType());
    }
    return Generators;
}

Int32 RandomPoolManager::getRandomInt32(UInt32 RandomPool, Int32 Min, Int32 Max)
{
    boost::uniform_int<Int32> Distribution(Min,Max);
    return Distribution(_RandomPoolGenerators[RandomPool]);
}

Int64 RandomPoolManager::getRandomInt64(UInt32 RandomPool, Int64 Min, Int64 Max)
{
    boost::uniform_int<Int64> Distribution(Min,Max);
    return Distribution(_RandomPoolGenerators[RandomPool]);
}

Real32 RandomPoolManager::getRandomReal32(UInt32 RandomPool, Real32 Min, Real32 Max)
{
    boost::uniform_real<Real32> Distribution(Min,Max);
    return Distribution(_RandomPoolGenerators[RandomPool]);
}

Real64 RandomPoolManager::getRandomReal64(UInt32 RandomPool, Real64 Min, Real64 Max)
{
    boost::uniform_real<Real64> Distribution(Min,Max);
    return Distribution(_RandomPoolGenerators[RandomPool]);
}
