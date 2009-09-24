/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *            Copyright (C) 2000-2002,2002 by the OpenSG Forum               *
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

#ifndef _OSGLISTENERTYPE_INL_
#define _OSGLISTENERTYPE_INL_

OSG_BEGIN_NAMESPACE

/*-------------------------------------------------------------------------*/
/*                                Get                                      */

inline
UInt16 ListenerType::getGroupId (void) const
{
    return _uiGroupId;
}

inline
ListenerType *ListenerType::getParent(void) const
{
    return _pParent;
}

inline
MethodDescription *ListenerType::getMethodDescription(UInt32 uiMethodId)
{
    if(uiMethodId - 1 < _vDescVec.size())
        return _vDescVec[uiMethodId - 1];
    else
        return NULL;
}

inline
const MethodDescription *ListenerType::getMethodDescription(
    UInt32 uiMethodId) const
{
    if(uiMethodId - 1 < _vDescVec.size())
        return _vDescVec[uiMethodId - 1];
    else
        return NULL;
}

inline
MethodDescription *ListenerType::findMethodDescription(
    const Char8 *szMethodName)
{
    DescMapIt descIt = _mDescMap.find(IDStringLink(szMethodName));

    return (descIt == _mDescMap.end()) ? NULL : (*descIt).second;
}

inline
const MethodDescription *ListenerType::findMethodDescription(
    const Char8 *szMethodName) const
{
    DescMapConstIt descIt = _mDescMap.find(IDStringLink(szMethodName));

    return (descIt == _mDescMap.end()) ? NULL : (*descIt).second;
}

inline
UInt32 ListenerType::getNumMethodDescs(void) const
{
    return _vDescVec.size();
}


/*-------------------------------------------------------------------------*/
/*                                 Is                                      */

inline
bool ListenerType::isInitialized(void) const
{
    return _bInitialized;
}

inline
bool ListenerType::isDerivedFrom(const TypeBase &other) const
{
    return Inherited::isDerivedFrom(other);
}

inline
bool ListenerType::isDerivedFrom(const ListenerType &other) const
{
    if(_uiTypeId == other._uiTypeId)
    {
        return true;
    }
    else
    {
        ListenerType *pCurrType   = _pParent;
        while(pCurrType != NULL)
        {
            if(other._uiTypeId == pCurrType->_uiTypeId)
            {
                return true;
            }
            pCurrType = pCurrType->_pParent;
        }
    }
    return false;
}

OSG_END_NAMESPACE


#endif /* _OSGLISTENERTYPE_INL_ */
