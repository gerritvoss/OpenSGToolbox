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

#include "OSGFieldContainerEditorFactory.h"
#include "OSGFactoryController.h"
#include "OSGSingletonHolder.ins"

OSG_BEGIN_NAMESPACE

OSG_SINGLETON_INST(FieldContainerEditorFactoryBase, addPostFactoryExitFunction)

template class SingletonHolder<FieldContainerEditorFactoryBase>;

OSG_END_NAMESPACE

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::FieldContainerEditorFactory
A FieldContainerEditorFactory. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

bool FieldContainerEditorFactoryBase::setDefaultEditor(const FieldContainerType* type, const FieldContainerType* editorType)
{
    return setEditorType(type, editorType, "Default");
}

bool FieldContainerEditorFactoryBase::addDefaultEditor(const FieldContainerType* type, const FieldContainerType* editorType)
{
    return addEditorType(type, editorType, "Default");
}

const FieldContainerType* FieldContainerEditorFactoryBase::getDefaultEditorType(const FieldContainerType* type) const
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

bool FieldContainerEditorFactoryBase::removeDefaultEditor(const FieldContainerType* type)
{
    return removeEditorType(type, "Default");
}

bool FieldContainerEditorFactoryBase::setEditorType(const FieldContainerType* type, const FieldContainerType* editorType, const std::string& editorName)
{
    if(_Editors.find(type) == _Editors.end())
    {
        _Editors[type] = std::map<std::string, const FieldContainerType*>();
    }
    _Editors[type][editorName] = editorType;
    return true;
}

bool FieldContainerEditorFactoryBase::addEditorType(const FieldContainerType* type, const FieldContainerType* editorType, const std::string& editorName)
{
    if(_Editors.find(type) == _Editors.end() ||
        _Editors[type].find(editorName) == _Editors[type].end() )
    {
        return setEditorType(type, editorType, editorName);
    }
    return false;
}

bool FieldContainerEditorFactoryBase::removeEditorType(const FieldContainerType* type, const std::string& editorName)
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

const FieldContainerType* FieldContainerEditorFactoryBase::getEditorType(const FieldContainerType* type, const std::string& editorName) const
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

UInt32 FieldContainerEditorFactoryBase::getNumEditorTypes(const FieldContainerType* type) const
{
    if(_Editors.find(type) == _Editors.end())
    {
        return 0;
    }
    return _Editors.find(type)->second.size();
}

const FieldContainerType* FieldContainerEditorFactoryBase::getEditorType(const FieldContainerType* type,  UInt32 Index) const
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


FieldContainerEditorComponentTransitPtr FieldContainerEditorFactoryBase::createDefaultEditor(FieldContainer* fc,
                                                                         CommandManagerPtr CmdManager) const
{
    const FieldContainerType* EditorType(getDefaultEditorType(&(fc->getType())));

    if(EditorType == NULL)
    {
        return FieldContainerEditorComponentTransitPtr(NULL);
    }

    FieldContainerEditorComponentTransitPtr comp = dynamic_pointer_cast<FieldContainerEditorComponent>(EditorType->createContainer());
    comp->setCommandManager(CmdManager);
    comp->attachFieldContainer(fc);

    return comp;
}

FieldContainerEditorComponentTransitPtr FieldContainerEditorFactoryBase::createEditor(FieldContainer* fc, 
                                                                  CommandManagerPtr CmdManager,
                                                                  const std::string& editorName) const
{
    const FieldContainerType* EditorType(getEditorType(&(fc->getType()),editorName));

    if(EditorType == NULL)
    {
        return FieldContainerEditorComponentTransitPtr(NULL);
    }

    FieldContainerEditorComponentTransitPtr comp = dynamic_pointer_cast<FieldContainerEditorComponent>(EditorType->createContainer());
    comp->setCommandManager(CmdManager);
    comp->attachFieldContainer(fc);

    return comp;
}


/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/
FieldContainerEditorFactoryBase::FieldContainerEditorFactoryBase(void)
{
}

FieldContainerEditorFactoryBase::~FieldContainerEditorFactoryBase(void)
{
} 

/*----------------------------- class specific ----------------------------*/

