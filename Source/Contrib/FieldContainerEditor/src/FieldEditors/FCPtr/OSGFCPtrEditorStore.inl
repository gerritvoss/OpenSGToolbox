/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)                             *
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
OSG_BEGIN_NAMESPACE

inline
void FCPtrEditorStore::addExclude(FieldContainer* ptr)
{
    _ExcludedPtrs.push_back(ptr);
}

inline
void FCPtrEditorStore::removeExclude(FieldContainer* ptr)
{
    FieldContianerVector::iterator
        EraseItor(std::find(_ExcludedPtrs.begin(), _ExcludedPtrs.end(), ptr));
    if(EraseItor != _ExcludedPtrs.end())
    {
        _ExcludedPtrs.erase(EraseItor);
    }
}

inline
const FCPtrEditorStore::FieldContianerVector& FCPtrEditorStore::getList(void) const
{
    return _Store;
}

inline
void FCPtrEditorStore::removeExclude(UInt32 index)
{
    if(index < getExcludedTypeSize())
    {
        FieldContianerVector::iterator EraseItor(_ExcludedPtrs.begin());
        EraseItor = EraseItor + index;
        _ExcludedPtrs.erase(EraseItor);
        updateList();
    }
}

inline
const FCPtrEditorStore::FieldContianerVector& FCPtrEditorStore::getExcluded(void) const
{
    return _ExcludedPtrs;
}

inline
UInt32 FCPtrEditorStore::getExcludedSize(void) const
{
    return _ExcludedPtrs.size();
}

inline
void FCPtrEditorStore::addExcludeType(const FieldContainerType* type)
{
    _ExcludedTypes.push_back(type);
    updateList();
}

inline
void FCPtrEditorStore::removeExcludeType(const FieldContainerType* type)
{
    FieldContianerTypeVector::iterator
        EraseItor(std::find(_ExcludedTypes.begin(), _ExcludedTypes.end(), type));
    if(EraseItor != _ExcludedTypes.end())
    {
        _ExcludedTypes.erase(EraseItor);
        updateList();
    }
}

inline
void FCPtrEditorStore::removeExcludeType(UInt32 index)
{
    if(index < getExcludedTypeSize())
    {
        FieldContianerTypeVector::iterator EraseItor(_ExcludedTypes.begin());
        EraseItor = EraseItor + index;
        _ExcludedTypes.erase(EraseItor);
        updateList();
    }
}

inline
const FCPtrEditorStore::FieldContianerTypeVector& FCPtrEditorStore::getExcludedType(void) const
{
    return _ExcludedTypes;
}

inline
UInt32 FCPtrEditorStore::getExcludedTypeSize(void) const
{
    return _ExcludedTypes.size();
}

OSG_END_NAMESPACE
