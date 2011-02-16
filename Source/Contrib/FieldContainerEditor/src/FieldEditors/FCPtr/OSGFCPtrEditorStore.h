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
#ifndef _OSGFCPTREDITORSTORE_H_
#define _OSGFCPTREDITORSTORE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribFieldContainerEditorDef.h"

#include <boost/shared_ptr.hpp>
#include <vector>
#include "OSGFieldContainer.h"

OSG_BEGIN_NAMESPACE

class FCPtrEditorStore;
typedef boost::shared_ptr<FCPtrEditorStore> FCPtrEditorStorePtr;

class OSG_CONTRIBFIELDCONTAINEREDITOR_DLLMAPPING FCPtrEditorStore
{
  public:
    typedef std::vector<FieldContainerUnrecPtr> FieldContianerVector;
    typedef std::vector<const FieldContainerType*> FieldContianerTypeVector;

    virtual ~FCPtrEditorStore(void);

    void operator =(const FCPtrEditorStore& source);

    virtual FCPtrEditorStorePtr clone(void) const = 0;

    const FieldContianerVector& getList(void) const;

    virtual const FieldContainerType* getTypeToStore(void) const;
    virtual void setTypeToStore(const FieldContainerType* type);

    virtual bool isExcluded(FieldContainer* ptr) const;

    void addExclude(FieldContainer* ptr);
    void removeExclude(FieldContainer* ptr);
    void removeExclude(UInt32 index);
    const FieldContianerVector& getExcluded(void) const;
    UInt32 getExcludedSize(void) const;

    void addExcludeType(const FieldContainerType* type);
    void removeExcludeType(const FieldContainerType* type);
    void removeExcludeType(UInt32 index);
    const FieldContianerTypeVector& getExcludedType(void) const;
    UInt32 getExcludedTypeSize(void) const;

  protected:
    virtual void updateList(void) = 0;

    FCPtrEditorStore(const FieldContianerVector& Store = FieldContianerVector(),
                     const FieldContianerVector& Exclude = FieldContianerVector(),
                     const FieldContianerTypeVector& ExcludeTypes = FieldContianerTypeVector());

    FCPtrEditorStore(const FCPtrEditorStore& source);

    FieldContianerVector _Store;
    FieldContianerVector _ExcludedPtrs;
    FieldContianerTypeVector _ExcludedTypes;

};

OSG_END_NAMESPACE

#include "OSGFCPtrEditorStore.inl"

#endif /* _OSGFCPTREDITORSTORE_H_ */
