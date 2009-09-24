/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *           Copyright (C) 2000-2002,2002 by the OpenSG Forum                *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

#ifndef _OSGFIELDCONTAINERFACTORYIMPL_INL_
#define _OSGFIELDCONTAINERFACTORYIMPL_INL_

#ifdef OSG_DOC_FILES_IN_MODULE
/*! \file OSGFieldContainerFactoryImpl.inl
    \ingroup GrpSystemFieldContainer
 */
#endif

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/*                              Mapper                                     */

inline
void FieldContainerFactory::setMapper(FieldContainerMapper *pMapper)
{
    _pMapper = pMapper;
}

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

inline
FieldContainerPtr FieldContainerFactory::getContainer(
    UInt32 uiContainerId) const
{
    FieldContainerPtr returnValue = NullFC;

    _pStoreLock->aquire();

    if(uiContainerId < _pFieldContainerStore->size())
    {
        returnValue = (*_pFieldContainerStore)[uiContainerId];
    }

    _pStoreLock->release();

    return returnValue;
}

inline
FieldContainerPtr FieldContainerFactory::getMappedContainer(
    UInt32 uiContainerId) const
{
    if(_pMapper != NULL)
    {
        return getContainer(_pMapper->map(uiContainerId));
    }
    else
    {
        return getContainer(uiContainerId);
    }
}

/*-------------------------------------------------------------------------*/
/*                              Register                                   */

inline
UInt32 FieldContainerFactory::registerFieldContainer(
    const FieldContainerPtr &pFieldContainer)
{
    UInt32 returnValue = 0;

    if(_pStoreLock != NULL)
        _pStoreLock->aquire();

    if(_pFieldContainerStore == NULL)
    {
        _pFieldContainerStore = new FieldContainerStore;

        _pFieldContainerStore->push_back(NullFC);
    }

    _pFieldContainerStore->push_back(pFieldContainer);

    returnValue = _pFieldContainerStore->size() - 1;

    if(_pStoreLock != NULL)
        _pStoreLock->release();

    return returnValue;
}

inline
bool FieldContainerFactory::unregisterFieldContainer(
    const FieldContainerPtr &pFieldContainer)
{
    if(pFieldContainer == NullFC)
        return false;

    if(_pStoreLock != NULL)
        _pStoreLock->aquire();

    if(_pFieldContainerStore != NULL)
    {
#ifdef OSG_DEBUG
        if (pFieldContainer.getFieldContainerId() >=
                    (*_pFieldContainerStore).size())
        {
            FWARNING(("FieldContainerFactory::unregisterFieldContainer:"
                "id %d inconsistent with store size %d!\n", 
                pFieldContainer.getFieldContainerId(), 
                (*_pFieldContainerStore).size() ));   
            return true;         
        }
        else
#endif

        (*_pFieldContainerStore)[pFieldContainer.getFieldContainerId()] =
            NullFC;
    }

    if(_pStoreLock != NULL)
        _pStoreLock->release();
    
    return false;
}

/*-------------------------------------------------------------------------*/
/*                            Invalid Pointer                              */

inline
void FieldContainerFactory::setThrowInvalidPointerException(bool s)
{
#ifndef OSG_INVALID_PTR_CHECK
    FFATAL(("FieldContainerFactory::setThrowInvalidPointerException: invalid pointer check is not enabled, use the 'invalid_pointer_check' option in the scons build system!\n"));
#else
    _throw_invalid_pointer_exception = s;
#endif
}

inline
bool FieldContainerFactory::getThrowInvalidPointerException(void) const
{
    return _throw_invalid_pointer_exception;
}

inline
void FieldContainerFactory::checkThrowInvalidPointerException(void) const
{
    if(!_throw_invalid_pointer_exception)
        return;

    throw InvalidPointerException();
}

OSG_END_NAMESPACE

#define OSGFIELDCONTAINERFACTORY_INLINE_CVSID "@(#)$Id: $"

#endif /* _OSGFIELDCONTAINERFACTORYIMPL_INL_ */
