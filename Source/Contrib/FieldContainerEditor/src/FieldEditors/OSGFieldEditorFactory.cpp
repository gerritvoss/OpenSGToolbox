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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include "OSGConfig.h"

#include "OSGFieldEditorFactory.h"
#include "OSGFactoryController.h"
#include "OSGSingletonHolder.ins"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::FieldEditorFactory
A FieldEditorFactory. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/
OSG_SINGLETON_INST(FieldEditorFactoryBase, addPostFactoryExitFunction)

template class SingletonHolder<FieldEditorFactoryBase>;

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool FieldEditorFactoryBase::setDefaultEditor(const DataType* type, const FieldContainerType* editorType)
{
    return setEditorType(type, editorType, "Default");
}

bool FieldEditorFactoryBase::addDefaultEditor(const DataType* type, const FieldContainerType* editorType)
{
    return addEditorType(type, editorType, "Default");
}

const FieldContainerType* FieldEditorFactoryBase::getDefaultEditorType(const DataType* type) const
{
    const FieldContainerType* editorType(getEditorType(type, "Default"));
    if(editorType == NULL)
    {
        EditorMap::const_iterator OuterMapItor(_Editors.find(type));
        if(OuterMapItor != _Editors.end() &&
            OuterMapItor->second.size() > 0)
        {
            editorType = OuterMapItor->second.begin()->second;
        }
    }
    return editorType;
}

bool FieldEditorFactoryBase::removeDefaultEditor(const DataType* type)
{
    return removeEditorType(type, "Default");
}

bool FieldEditorFactoryBase::setEditorType(const DataType* type, const FieldContainerType* editorType, const std::string& editorName)
{
    if(_Editors.find(type) == _Editors.end())
    {
        _Editors[type] = std::map<std::string, const FieldContainerType*>();
    }
    _Editors[type][editorName] = editorType;
    return true;
}

bool FieldEditorFactoryBase::addEditorType(const DataType* type, const FieldContainerType* editorType, const std::string& editorName)
{
    if(_Editors.find(type) == _Editors.end() ||
        _Editors[type].find(editorName) == _Editors[type].end() )
    {
        return setEditorType(type, editorType, editorName);
    }
    return false;
}

bool FieldEditorFactoryBase::removeEditorType(const DataType* type, const std::string& editorName)
{
    if(_Editors.find(type) == _Editors.end())
    {
        return false;
    }

    EditorStringMap::iterator Itor(_Editors[type].find(editorName));
    if(Itor == _Editors[type].end())
    {
        return false;
    }
    _Editors[type].erase(Itor);

    return true;
}

const FieldContainerType* FieldEditorFactoryBase::getEditorType(const DataType* type, const std::string& editorName) const
{
    EditorMap::const_iterator OuterMapItor(_Editors.find(type));
    if(OuterMapItor == _Editors.end())
    {
        return NULL;
    }

    EditorStringMap::const_iterator InnerMapItor(OuterMapItor->second.find(editorName));
    if(InnerMapItor == OuterMapItor->second.end())
    {
        return NULL;
    }
    
    return InnerMapItor->second;
}

UInt32 FieldEditorFactoryBase::getNumEditorTypes(const DataType* type) const
{
    if(_Editors.find(type) == _Editors.end())
    {
        return 0;
    }
    return _Editors.find(type)->second.size();
}

const FieldContainerType* FieldEditorFactoryBase::getEditorType(const DataType* type,  UInt32 Index) const
{
    EditorMap::const_iterator OuterMapItor(_Editors.find(type));
    if(OuterMapItor == _Editors.end())
    {
        return NULL;
    }

    EditorStringMap::const_iterator Itor(OuterMapItor->second.begin());
    for(UInt32 i(0) ; i<Index && Itor != OuterMapItor->second.end(); ++i) { }

    if(Itor == OuterMapItor->second.end())
    {
        return NULL;
    }

    return Itor->second;
}


FieldEditorComponentTransitPtr FieldEditorFactoryBase::createDefaultEditor(FieldContainer* fc, 
                                                                         UInt32 FieldId, 
                                                                         CommandManagerPtr CmdManager,
                                                                         UInt32 FieldIndex) const
{
    const FieldContainerType* EditorType(getDefaultEditorType(&(fc->getFieldDescription(FieldId)->getFieldType().getContentType())));

    if(EditorType == NULL)
    {
        return FieldEditorComponentTransitPtr(NULL);
    }

    FieldEditorComponentTransitPtr comp = dynamic_pointer_cast<FieldEditorComponent>(EditorType->createContainer());
    comp->setCommandManager(CmdManager);
    comp->attachField(fc,FieldId, FieldIndex);

    return comp;
}

FieldEditorComponentTransitPtr FieldEditorFactoryBase::createEditor(FieldContainer* fc, 
                                                                  UInt32 FieldId, 
                                                                  CommandManagerPtr CmdManager,
                                                                  UInt32 FieldIndex, 
                                                                  const std::string& editorName) const
{
    const FieldContainerType* EditorType(getEditorType(&(fc->getFieldDescription(FieldId)->getFieldType().getContentType()),editorName));

    if(EditorType == NULL)
    {
        return FieldEditorComponentTransitPtr(NULL);
    }

    FieldEditorComponentTransitPtr comp = dynamic_pointer_cast<FieldEditorComponent>(EditorType->createContainer());
    comp->setCommandManager(CmdManager);
    comp->attachField(fc,FieldId, FieldIndex);

    return comp;
}


/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/
FieldEditorFactoryBase::FieldEditorFactoryBase(void)
{
}

FieldEditorFactoryBase::~FieldEditorFactoryBase(void)
{
} 

/*----------------------------- class specific ----------------------------*/

