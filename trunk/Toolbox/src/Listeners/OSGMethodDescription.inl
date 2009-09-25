/*---------------------------------------------------------------------------*\
 *                            OpenSGToolbox                                  *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala                                                   *
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

#ifndef _OSGMETHODDESCRIPTIONIMPL_INL_
#define _OSGMETHODDESCRIPTIONIMPL_INL_

OSG_BEGIN_NAMESPACE
inline
MethodDescription::MethodDescription(const Char8                  *szName,
                  const UInt32                  uiMethodId,
                  const std::vector<const TypeBase*>  &ArgumentTypes,
                  const std::vector<const TypeBase*>  &ReturnTypes,
                        MethodAccessFunctor     fAccessFunctor) :

    _szName             (szName       ),

    _MethodId           (uiMethodId    ),
    _ArgumentTypes      (ArgumentTypes   ),

    _ReturnTypes        (ReturnTypes    ),

    _fAccessFunctor     (fAccessFunctor)
{
}

inline
MethodDescription::MethodDescription(const MethodDescription &source) :

    _szName             (source._szName              ),

    _MethodId           (source._MethodId           ),
    _ArgumentTypes      (source._ArgumentTypes          ),

    _ReturnTypes        (source._ReturnTypes           ),

    _fAccessFunctor     (source._fAccessFunctor       )
{
}

inline
MethodDescription::~MethodDescription(void)
{
} 

inline
const Char8 *MethodDescription::getCName(void) const
{
    return _szName.str();
}

inline
const IDString &MethodDescription::getName(void) const
{
    return _szName;
}

inline
UInt32 MethodDescription::getMethodId(void) const
{
    return _MethodId;
}

inline
void MethodDescription::setMethodId(UInt32 uiMethodId)
{
    _MethodId = uiMethodId;
}

inline
const std::vector<const TypeBase*> &MethodDescription::getArgumentTypes   (void) const
{
    return _ArgumentTypes;
}

inline
const std::vector<const TypeBase*> &MethodDescription::getReturnTypes   (void) const
{
    return _ReturnTypes;
}

inline
void MethodDescription::setAccessFunctor(MethodAccessFunctor fAccessFunctor)
{
    _fAccessFunctor = fAccessFunctor;
}
inline
MethodAccessFunctor MethodDescription::getAccessFunctor(void)
{
    return _fAccessFunctor;
}

inline
bool MethodDescription::isValid(void)  const
{
    return (this != NULL && _szName.getLength()) ? true : false;
}

OSG_END_NAMESPACE

#endif /* _OSGMETHODDESCRIPTIONIMPL_INL_ */
