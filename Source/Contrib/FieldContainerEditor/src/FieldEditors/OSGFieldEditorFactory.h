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

#ifndef _OSGFIELDEDITITORFACTORY_H_
#define _OSGFIELDEDITITORFACTORY_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribFieldContainerEditorDef.h"

#include "OSGFieldEditorComponent.h"
#include "OSGSingletonHolder.h"
#include "OSGCommandManager.h"
#include <map>
#include <vector>

OSG_BEGIN_NAMESPACE

class OSG_CONTRIBFIELDCONTAINEREDITOR_DLLMAPPING FieldEditorFactoryBase
{
protected:
    typedef std::map<std::string, const FieldContainerType*> EditorStringMap;
    typedef std::map<const DataType*, EditorStringMap > EditorMap;
    EditorMap _Editors;

    FieldEditorFactoryBase(void);

    virtual ~FieldEditorFactoryBase(void);

    template <class SingletonT>
    friend class SingletonHolder;

public:
    FieldEditorComponentTransitPtr createDefaultEditor(FieldContainer* fc, 
                                                       UInt32 FieldId, 
                                                       CommandManagerPtr CmdManager,
                                                       UInt32 FieldIndex = 0) const;

    //Single field default editors
    bool                setSingleDefaultEditor        (const DataType* type,
                                                       const FieldContainerType* editorType);
    bool                addSingleDefaultEditor        (const DataType* type,
                                                       const FieldContainerType* editorType);
    bool                removeSingleDefaultEditor     (const DataType* type);
    const FieldContainerType* getSingleDefaultEditorType    (const DataType* type) const;

    FieldEditorComponentTransitPtr createSingleDefaultEditor(FieldContainer* fc, 
                                                             UInt32 FieldId, 
                                                             CommandManagerPtr CmdManager,
                                                             UInt32 FieldIndex = 0) const;

    //Multi field default editors
    bool                setMultiDefaultEditor        (const DataType* type,
                                                      const FieldContainerType* editorType);
    bool                addMultiDefaultEditor        (const DataType* type,
                                                      const FieldContainerType* editorType);
    bool                removeMultiDefaultEditor     (const DataType* type);
    const FieldContainerType* getMultiDefaultEditorType    (const DataType* type) const;

    FieldEditorComponentTransitPtr createMultiDefaultEditor(FieldContainer* fc, 
                                                            UInt32 FieldId, 
                                                            CommandManagerPtr CmdManager) const;

          bool                setEditorType    (const DataType* type,
                                                const FieldContainerType* editorType,
                                                const std::string& editorName);
          bool                addEditorType    (const DataType* type,
                                                const FieldContainerType* editorType,
                                                const std::string& editorName);
          bool                removeEditorType (const DataType* type,
                                                const std::string& editorName);
    const FieldContainerType* getEditorType    (const DataType* type,
                                                const std::string& editorName) const;
          UInt32              getNumEditorTypes(const DataType* type) const;
    const FieldContainerType* getEditorType    (const DataType* type,
                                                UInt32 Index) const;

    FieldEditorComponentTransitPtr createEditor       (FieldContainer* fc, 
                                                       UInt32 FieldId, 
                                                       CommandManagerPtr CmdManager,
                                                       UInt32 FieldIndex = 0, 
                                                       const std::string& editorName = "") const;
};

typedef OSG::SingletonHolder<OSG::FieldEditorFactoryBase> FieldEditorFactory;

OSG_END_NAMESPACE

#include "OSGFieldEditorFactory.inl"

#endif /* _OSGFIELDEDITITORFACTORY_H_ */
