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

#include <cstdlib>
#include <cstdio>

#include <OSGConfig.h>

#include "OSGMaterialFieldContainerEditor.h"
#include "OSGFieldContainerFactory.h"
#include "OSGFieldContainerEditorFactory.h"
#include "OSGFieldEditorFactory.h"
#include "OSGSpringLayout.h"
#include "OSGSpringLayoutConstraints.h"

#include "OSGNode.h"
#include "OSGGroup.h"
#include "OSGViewport.h"
#include "OSGPerspectiveCamera.h"
#include "OSGGradientBackground.h"
#include "OSGSimpleGeometry.h"
#include "OSGPointLight.h"
#include "OSGMatrix.h"
#include "OSGTransform.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGMaterialFieldContainerEditorBase.cpp file.
// To modify it, please change the .fcd file (OSGMaterialFieldContainerEditor.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

std::vector<const FieldContainerType*> MaterialFieldContainerEditor::_EditableTypes = std::vector<const FieldContainerType*>();

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void MaterialFieldContainerEditor::initMethod(InitPhase ePhase)
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
                if(type->isDerivedFrom(Material::getClassType()))
                {
                    _EditableTypes.push_back(type);
                    FieldContainerEditorFactory::the()->setDefaultEditor(type,
                                                                         &getClassType());
                    FieldContainerEditorFactory::the()->setEditorType(type,
                                                                      &getClassType(),
                                                                      "Material");
                }
            }
        }
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Vec2f MaterialFieldContainerEditor::getContentRequestedSize(void) const
{
    return _GenericEditor->getContentRequestedSize() +
        Vec2f(0.0f,_MaterialViewport->getPreferredSize().y());
}

const std::vector<const FieldContainerType*>& MaterialFieldContainerEditor::getEditableTypes(void) const
{
    return _EditableTypes;
}

bool MaterialFieldContainerEditor::attachFieldContainer(FieldContainer* fc)
{
    //Check that this is a valid FieldContainer
    if(!Inherited::attachFieldContainer(fc))
    {
        return false;
    }

    //Attach the material
    _MaterialGeometry->setMaterial(dynamic_cast<Material*>(fc));
    commitChanges();
	_MaterialViewport->showAll();

    return true;
}

bool MaterialFieldContainerEditor::dettachFieldContainer(void)
{
    //Dettach the material
    _MaterialGeometry->setMaterial(NULL);

    return Inherited::dettachFieldContainer();
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/
void MaterialFieldContainerEditor::createGeometry(void)
{
    // Make Torus Node (creates Torus in background of scene)
    switch(getMaterialShape())
    {
    case PLANE_SHAPE:
        _MaterialGeometry = makePlaneGeo(5.0f,5.0f, 5, 5);
        break;
    case BOX_SHAPE:
        _MaterialGeometry = makeBoxGeo(5.0f,5.0f,5.0f, 5, 5, 5);
        break;
    case TEAPOT_SHAPE:
        _MaterialGeometry = makeTeapotGeo(2, 1.0f);
        break;
    case CONE_SHAPE:
        _MaterialGeometry = makeConeGeo(5.0f, 1.0f, 24, true, true);
        break;
    case CYLINDER_SHAPE:
        _MaterialGeometry = makeCylinderGeo(5.0f, 1.0f, 24, true, true, true);
        break;
    case TORUS_SHAPE:
        _MaterialGeometry = makeTorusGeo(.6, 2.5f, 32, 32);
        break;
    case SPHERE_SHAPE:
    default:
        _MaterialGeometry = makeSphereGeo(3, 2.5f);
        break;
    }
}

void MaterialFieldContainerEditor::createGLViewport(void)
{
    //Create the nessicary parts for a viewport
    Matrix TransformMatrix;
    TransformMatrix.setTranslate(0.0f,0.0f, -38.0f);
    TransformRefPtr CameraBeaconTransform = Transform::create();
    CameraBeaconTransform->setMatrix(TransformMatrix);

    NodeRefPtr CameraBeaconNode = Node::create();
    CameraBeaconNode->setCore(CameraBeaconTransform);

    createGeometry();
    
    NodeRefPtr GeometryNode = Node::create();
    GeometryNode->setCore(_MaterialGeometry);

    //Camera
    PerspectiveCameraRefPtr DefaultCamera = PerspectiveCamera::create();
    DefaultCamera->setBeacon(CameraBeaconNode);
    DefaultCamera->setFov   (osgDegree2Rad(60.f));
    DefaultCamera->setNear  (0.1f);
    DefaultCamera->setFar   (30.f);

    //Light
    TransformMatrix.setTranslate(4.0f,4.0f,5.0f);
    TransformRefPtr LightBeaconTransform = Transform::create();
    LightBeaconTransform->setMatrix(TransformMatrix);

    NodeRefPtr LightBeaconNode = Node::create();
    LightBeaconNode->setCore(LightBeaconTransform);

    PointLightRefPtr DefaultLight = PointLight::create();
    DefaultLight->setBeacon(LightBeaconNode);

    NodeRefPtr LightNode = Node::create();
    LightNode->setCore(DefaultLight);
    LightNode->addChild(GeometryNode);

    // Make Main Scene Node and add the Torus
    NodeRefPtr DefaultRootNode = OSG::Node::create();
    DefaultRootNode->setCore(OSG::Group::create());
    DefaultRootNode->addChild(LightBeaconNode);
    DefaultRootNode->addChild(LightNode);
    DefaultRootNode->addChild(CameraBeaconNode);

    //Background
    GradientBackgroundRefPtr DefaultBackground = GradientBackground::create();
    DefaultBackground->addLine(Color3f(0.2f,0.2f,0.2f), 0.0f);
    DefaultBackground->addLine(Color3f(0.4f,0.4f,0.4f), 1.0f);

    //Viewport
    ViewportRefPtr DefaultViewport = Viewport::create();
    DefaultViewport->setCamera                  (DefaultCamera);
    DefaultViewport->setRoot                    (DefaultRootNode);
    DefaultViewport->setSize                    (0.0f,0.0f, 1.0f,1.0f);
    DefaultViewport->setBackground              (DefaultBackground);

    _MaterialViewport = GLViewport::create();
    _MaterialViewport->setPort(DefaultViewport);
}

void MaterialFieldContainerEditor::onCreate(const MaterialFieldContainerEditor *Id)
{
	Inherited::onCreate(Id);
    if(Id != NULL)
    {
        pushToChildren(_GenericEditor);

        //Create the Viewport, geometry, camera, light
        createGLViewport();

        //Create the viewport to view the material in
        _MaterialViewport->setPreferredSize(Vec2f(150.0f,150.0f));

        SpringLayoutRefPtr TheLayout = SpringLayout::create();

        TheLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE,_MaterialViewport, 0,SpringLayoutConstraints::NORTH_EDGE, this);
        TheLayout->putConstraint(SpringLayoutConstraints::HORIZONTAL_CENTER_EDGE,_MaterialViewport, 0,SpringLayoutConstraints::HORIZONTAL_CENTER_EDGE, this);

        TheLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE,_GenericEditor, 1,SpringLayoutConstraints::SOUTH_EDGE, _MaterialViewport);
        TheLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE,_GenericEditor, 0,SpringLayoutConstraints::SOUTH_EDGE, this);
        TheLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE,_GenericEditor, 0,SpringLayoutConstraints::EAST_EDGE, this);
        TheLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _GenericEditor, 0,SpringLayoutConstraints::WEST_EDGE, this);

        setLayout(TheLayout);
        pushToChildren(_MaterialViewport);
    }
}

void MaterialFieldContainerEditor::onDestroy()
{
}

void MaterialFieldContainerEditor::resolveLinks(void)
{
    Inherited::resolveLinks();

    _MaterialViewport = NULL;

    _MaterialGeometry = NULL;
}

/*----------------------- constructors & destructors ----------------------*/

MaterialFieldContainerEditor::MaterialFieldContainerEditor(void) :
    Inherited()
{
}

MaterialFieldContainerEditor::MaterialFieldContainerEditor(const MaterialFieldContainerEditor &source) :
    Inherited(source)
{
}

MaterialFieldContainerEditor::~MaterialFieldContainerEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void MaterialFieldContainerEditor::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    if(whichField & MaterialShapeFieldMask)
    {
        createGeometry();
    }
}

void MaterialFieldContainerEditor::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump MaterialFieldContainerEditor NI" << std::endl;
}

OSG_END_NAMESPACE
