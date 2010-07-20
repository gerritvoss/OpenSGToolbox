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
#ifndef _OSGFCPTREDITORLISTSTORE_H_
#define _OSGFCPTREDITORLISTSTORE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribFieldContainerEditorDef.h"

#include "OSGFCPtrEditorStore.h"

OSG_BEGIN_NAMESPACE

class FCPtrEditorListStore;
typedef boost::shared_ptr<FCPtrEditorListStore> FCPtrEditorListStorePtr;

class OSG_CONTRIBFIELDCONTAINEREDITOR_DLLMAPPING FCPtrEditorListStore : public FCPtrEditorStore
{
  public:
    typedef FCPtrEditorStore Inherited;

    virtual ~FCPtrEditorListStore(void);

    void operator =(const FCPtrEditorListStore& source);

    virtual std::vector<FieldContainer*> getList(void) const;

    const FieldContianerVector& getTypeToStore(void) const;
    void setTypeToStore(const FieldContianerVector& store);

  protected:
    FCPtrEditorListStore(const FieldContianerVector& Store);

    FCPtrEditorListStore(const FCPtrEditorListStore& source);

    FieldContianerVector _Store;
};

OSG_END_NAMESPACE

#include "OSGFCPtrEditorListStore.inl"

#endif /* _OSGFCPTREDITORLISTSTORE_H_ */
