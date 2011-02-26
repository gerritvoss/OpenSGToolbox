/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 * contact: David Kabala (djkabala@gmail.com)                                *
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

#include <cstdlib>
#include <cstdio>

#include "OSGConfig.h"

#include "OSGNodeFieldContainerEditor.h"
#include "OSGFieldContainerEditorFactory.h"
#include "OSGViewport.h"
#include "OSGVisitSubTree.h"
#include "OSGDirectionalLight.h"
#include "OSGTransform.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGNodeFieldContainerEditorBase.cpp file.
// To modify it, please change the .fcd file (OSGNodeFieldContainerEditor.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

std::vector<const FieldContainerType*>
NodeFieldContainerEditor::_EditableTypes = std::vector<const FieldContainerType*>();

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void NodeFieldContainerEditor::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
        //Fill in all of the editable types
        UInt32 NumTypes(FieldContainerFactory::the()->getNumTypes());
        UInt32 FoundTypes(0);
        FieldContainerType* type;
        for(UInt32 i(0) ; FoundTypes<NumTypes; ++i)
        {
            type = FieldContainerFactory::the()->findType(i);
            if(type != NULL)
            {
                ++FoundTypes;
                if(type->isDerivedFrom(Node::getClassType()))
                {
                    _EditableTypes.push_back(type);
                    FieldContainerEditorFactory::the()->setDefaultEditor(type,
                                                                         &getClassType());
                    FieldContainerEditorFactory::the()->setEditorType(type,
                                                                      &getClassType(),
                                                                      "Node");
                }
            }
        }
    }
}


const std::vector<const FieldContainerType*>& NodeFieldContainerEditor::getEditableTypes(void) const
{
    return _EditableTypes;
}

bool NodeFieldContainerEditor::attachFieldContainer(FieldContainer* fc)
{
    //Check that this is a valid FieldContainer
    if(!Inherited::attachFieldContainer(fc))
    {
        return false;
    }

    //Attach the node
    _VisitCore->setSubTreeRoot(dynamic_cast<Node*>(fc));
	getGUIViewport()->showAll();

    return true;
}

bool NodeFieldContainerEditor::dettachFieldContainer(void)
{
    //Dettach the node
    _VisitCore->setSubTreeRoot(NULL);

    return Inherited::dettachFieldContainer();
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void NodeFieldContainerEditor::onCreate(const NodeFieldContainerEditor *Id)
{
	Inherited::onCreate(Id);
}

void NodeFieldContainerEditor::onDestroy()
{
}

void NodeFieldContainerEditor::resolveLinks(void)
{
    Inherited::resolveLinks();

    _VisitCore = NULL;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/
NodeTransitPtr NodeFieldContainerEditor::createDefaultRoot(void)
{
    //Visit node
    _VisitCore = VisitSubTree::create();
    NodeRecPtr VisitNode = makeNodeFor(_VisitCore);

    //Light
    TransformRefPtr LightBeaconTransform = Transform::create();

    NodeRefPtr LightBeaconNode = Node::create();
    LightBeaconNode->setCore(LightBeaconTransform);

    DirectionalLightRefPtr DefaultLight = DirectionalLight::create();
    DefaultLight->setBeacon(LightBeaconNode);

    NodeRefPtr LightNode = Node::create();
    LightNode->setCore(DefaultLight);
    LightNode->addChild(VisitNode);

    //Root Node
    NodeRecPtr Root = Inherited::createDefaultRoot();
    Root->addChild(LightBeaconNode);
    Root->addChild(LightNode);

    return NodeTransitPtr(Root);
}


/*----------------------- constructors & destructors ----------------------*/

NodeFieldContainerEditor::NodeFieldContainerEditor(void) :
    Inherited()
{
}

NodeFieldContainerEditor::NodeFieldContainerEditor(const NodeFieldContainerEditor &source) :
    Inherited(source)
{
}

NodeFieldContainerEditor::~NodeFieldContainerEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void NodeFieldContainerEditor::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void NodeFieldContainerEditor::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump NodeFieldContainerEditor NI" << std::endl;
}

OSG_END_NAMESPACE
