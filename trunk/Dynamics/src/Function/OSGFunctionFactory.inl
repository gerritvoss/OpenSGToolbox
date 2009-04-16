#ifndef _OSGFUNCTIONFACTORYIMPL_INL_
#define _OSGFUNCTIONFACTORYIMPL_INL_

#ifdef OSG_DOC_FILES_IN_MODULE

#endif

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/*                              Mapper                                     */

inline
void FunctionFactory::setMapper(FieldContainerMapper *pMapper)
{
    _pMapper = pMapper;
}

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

inline
FunctionPtr FunctionFactory::getFunction(
    UInt32 uiContainerId) const
{
    FunctionPtr returnValue = NullFC;

    _pStoreLock->aquire();

    if(uiContainerId < _pFunctionStore->size())
    {
        returnValue = (*_pFunctionStore)[uiContainerId];
    }

    _pStoreLock->release();

    return returnValue;
}

inline
FunctionPtr FunctionFactory::getMappedFunction(
    UInt32 uiContainerId) const
{
    if(_pMapper != NULL)
    {
        return getFunction(_pMapper->map(uiContainerId));
    }
    else
    {
        return getFunction(uiContainerId);
    }
}

/*-------------------------------------------------------------------------*/
/*                              Register                                   */

inline
UInt32 FunctionFactory::registerFunction(
    const FunctionPtr &pFieldContainer)
{
    UInt32 returnValue = 0;

    if(_pStoreLock != NULL)
        _pStoreLock->aquire();

    if(_pFunctionStore == NULL)
    {
        _pFunctionStore = new FunctionStore;

        _pFunctionStore->push_back(NullFC);
    }

    _pFunctionStore->push_back(pFieldContainer);

    returnValue = _pFunctionStore->size() - 1;

    if(_pStoreLock != NULL)
        _pStoreLock->release();

    return returnValue;
}

inline
bool FunctionFactory::unregisterFunction(
    const FunctionPtr &pFieldContainer)
{
    if(pFieldContainer == NullFC)
        return false;

    if(_pStoreLock != NULL)
        _pStoreLock->aquire();

    if(_pFunctionStore != NULL)
    {
#ifdef OSG_DEBUG
        if (pFieldContainer.getFieldContainerId() >=
                    (*_pFunctionStore).size())
        {
            FWARNING(("FunctionFactory::unregisterFieldContainer:"
                "id %d inconsistent with store size %d!\n", 
                pFieldContainer.getFieldContainerId(), 
                (*_pFunctionStore).size() ));   
            return true;         
        }
        else
#endif

        (*_pFunctionStore)[pFieldContainer.getFieldContainerId()] =
            NullFC;
    }

    if(_pStoreLock != NULL)
        _pStoreLock->release();
    
    return false;
}

OSG_END_NAMESPACE

#define OSGFUNCTIONFACTORY_INLINE_CVSID "@(#)$Id: $"

#endif /* _OSGFUNCTIONFACTORYIMPL_INL_ */
