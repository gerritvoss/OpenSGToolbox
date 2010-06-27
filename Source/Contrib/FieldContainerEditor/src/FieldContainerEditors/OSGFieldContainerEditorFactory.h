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

#ifndef _OSGFIELDCONTAINEREDITITORFACTORY_H_
#define _OSGFIELDCONTAINEREDITITORFACTORY_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribFieldContainerEditorDef.h"

#include "OSGFieldContainerEditorComponent.h"
#include "OSGSingletonHolder.h"
#include "OSGCommandManager.h"
#include <map>
#include <vector>

OSG_BEGIN_NAMESPACE

class OSG_CONTRIBFIELDCONTAINEREDITOR_DLLMAPPING FieldContainerEditorFactoryBase
{
protected:
    typedef std::map<std::string, const FieldContainerType*> EditorStringMap;
    typedef std::map<const FieldContainerType*, EditorStringMap > EditorMap;
    EditorMap _Editors;

    FieldContainerEditorFactoryBase(void);

    virtual ~FieldContainerEditorFactoryBase(void);

    template <class SingletonT>
    friend class SingletonHolder;

public:

          bool                setDefaultEditor        (const FieldContainerType* type,
                                                       const FieldContainerType* editorType);
          bool                addDefaultEditor        (const FieldContainerType* type,
                                                       const FieldContainerType* editorType);
          bool                removeDefaultEditor     (const FieldContainerType* type);
    const FieldContainerType* getDefaultEditorType    (const FieldContainerType* type) const;

          bool                setEditorType    (const FieldContainerType* type,
                                                const FieldContainerType* editorType,
                                                const std::string& editorName);
          bool                addEditorType    (const FieldContainerType* type,
                                                const FieldContainerType* editorType,
                                                const std::string& editorName);
          bool                removeEditorType (const FieldContainerType* type,
                                                const std::string& editorName);
    const FieldContainerType* getEditorType    (const FieldContainerType* type,
                                                const std::string& editorName) const;
          UInt32              getNumEditorTypes(const FieldContainerType* type) const;
    const FieldContainerType* getEditorType    (const FieldContainerType* type,
                                                UInt32 Index) const;

    FieldContainerEditorComponentTransitPtr createDefaultEditor(FieldContainer* fc, 
                                                       CommandManagerPtr CmdManager) const;
    FieldContainerEditorComponentTransitPtr createEditor       (FieldContainer* fc, 
                                                       CommandManagerPtr CmdManager,
                                                       const std::string& editorName = "") const;
};

typedef OSG::SingletonHolder<OSG::FieldContainerEditorFactoryBase> FieldContainerEditorFactory;

OSG_END_NAMESPACE

#include "OSGFieldContainerEditorFactory.inl"

#endif /* _OSGFIELDCONTAINEREDITITORFACTORY_H_ */
