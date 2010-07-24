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
#ifndef _OSGFCPTREDITORALLSTORE_H_
#define _OSGFCPTREDITORALLSTORE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribFieldContainerEditorDef.h"

#include "OSGFCPtrEditorStore.h"

OSG_BEGIN_NAMESPACE

class FCPtrEditorRootedStore;
typedef boost::shared_ptr<FCPtrEditorRootedStore> FCPtrEditorRootedStorePtr;

class OSG_CONTRIBFIELDCONTAINEREDITOR_DLLMAPPING FCPtrEditorRootedStore : public FCPtrEditorStore
{
  public:
    typedef FCPtrEditorStore Inherited;

    virtual ~FCPtrEditorRootedStore(void);

    void operator =(const FCPtrEditorRootedStore& source);
    virtual FCPtrEditorStorePtr clone(void) const;

    virtual const FieldContainerType* getTypeToStore(void) const;
    virtual void setTypeToStore(const FieldContainerType* type);

    const FieldContianerVector& getRoots(void) const;
    void setRoots(const FieldContianerVector& roots);

    static FCPtrEditorRootedStorePtr create(void);
  protected:
    FCPtrEditorRootedStore(void);

    FCPtrEditorRootedStore(const FieldContainerType* type,
                           const FieldContianerVector& roots,
                        const FieldContianerVector& Exclude = FieldContianerVector(),
                        const FieldContianerTypeVector& ExcludeTypes = FieldContianerTypeVector());

    FCPtrEditorRootedStore(const FCPtrEditorRootedStore& source);

    virtual void updateList(void);

    const FieldContainerType* _TypeToStore;
    FieldContianerVector _Roots;
};

OSG_END_NAMESPACE

#include "OSGFCPtrEditorRootedStore.inl"

#endif /* _OSGFCPTREDITORALLSTORE_H_ */
