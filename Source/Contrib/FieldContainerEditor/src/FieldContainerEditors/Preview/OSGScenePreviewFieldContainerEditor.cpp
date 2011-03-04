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

#include "OSGScenePreviewFieldContainerEditor.h"
#include "OSGBorderLayout.h"
#include "OSGBorderLayoutConstraints.h"
#include "OSGSplitPanel.h"
#include "OSGScrollPanel.h"
#include "OSGUIDrawObjectCanvas.h"

#include "OSGNode.h"
#include "OSGGroup.h"
#include "OSGViewport.h"
#include "OSGPerspectiveCamera.h"
#include "OSGGradientBackground.h"
#include "OSGTransform.h"

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGScenePreviewFieldContainerEditorBase.cpp file.
// To modify it, please change the .fcd file (OSGScenePreviewFieldContainerEditor.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void ScenePreviewFieldContainerEditor::initMethod(InitPhase ePhase)
{
    Inherited::initMethod(ePhase);

    if(ePhase == TypeObject::SystemPost)
    {
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

Vec2f ScenePreviewFieldContainerEditor::getContentRequestedSize(void) const
{
    return _GenericEditor->getContentRequestedSize() +
        Vec2f(0.0f,getPreviewPanelSize());
}

bool ScenePreviewFieldContainerEditor::getScrollableTracksViewportHeight(void)
{
    return true;
}

bool ScenePreviewFieldContainerEditor::getScrollableTracksViewportWidth(void)
{
    return true;
}

bool ScenePreviewFieldContainerEditor::getScrollableHeightMinTracksViewport(void)
{
    return true;
}

bool ScenePreviewFieldContainerEditor::getScrollableWidthMinTracksViewport(void)
{
    return true;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void ScenePreviewFieldContainerEditor::onCreate(const ScenePreviewFieldContainerEditor *Id)
{
	Inherited::onCreate(Id);

    if(GlobalSystemState != Startup)
    {
        //Create the Viewport, geometry, camera, light
        GLViewportRecPtr GUIViewport = createDefaultGLViewport();
        setGUIViewport(GUIViewport);

        ScrollPanelRecPtr EditorScrollPanel = ScrollPanel::create();
        EditorScrollPanel->setViewComponent(_GenericEditor);

        _MainSplitPanel = SplitPanel::create();
        _MainSplitPanel->setOrientation(SplitPanel::VERTICAL_ORIENTATION);
        _MainSplitPanel->setDividerPosition(getPreviewPanelSize()); 
        _MainSplitPanel->setMinComponent(getGUIViewport());
        _MainSplitPanel->setMaxComponent(EditorScrollPanel);

        //Add the SplitPanel
        pushToChildren(_MainSplitPanel);

        //Set the layout constraints for the SplitPanel
        BorderLayoutConstraintsRecPtr CenterConstraints = BorderLayoutConstraints::create();
        CenterConstraints->setRegion(BorderLayoutConstraints::BORDER_CENTER);
        _MainSplitPanel->setConstraints(CenterConstraints);

        //Set the layout
        BorderLayoutRecPtr MainLayout = BorderLayout::create();
        setLayout(MainLayout);
    }
}

void ScenePreviewFieldContainerEditor::onDestroy()
{
}

void ScenePreviewFieldContainerEditor::resolveLinks(void)
{
    Inherited::resolveLinks();

    _MainSplitPanel = NULL;
    _PrimaryViewport = NULL;
}

GLViewportTransitPtr ScenePreviewFieldContainerEditor::createDefaultGLViewport(void)
{
    _PrimaryViewport = createDefaultViewport();

    GLViewportRecPtr DefaultGUIViewport = GLViewport::create();
    DefaultGUIViewport->setPort(_PrimaryViewport);

    return GLViewportTransitPtr(DefaultGUIViewport);
}

ViewportTransitPtr ScenePreviewFieldContainerEditor::createDefaultViewport(void)
{
    //Create the necessary parts for a viewport
    NodeRefPtr CameraBeaconNode = createDefaultCameraBeacon();

    //Camera
    CameraRefPtr DefaultCamera = createDefaultCamera();
    DefaultCamera->setBeacon(CameraBeaconNode);

    // Make Default Scene Node
    NodeRefPtr DefaultRootNode = createDefaultRoot();
    DefaultRootNode->addChild(CameraBeaconNode);

    //Background
    BackgroundRefPtr DefaultBackground = createDefaultBackground();

    //Viewport
    ViewportRecPtr DefaultViewport = Viewport::create();
    DefaultViewport->setCamera    (DefaultCamera);
    DefaultViewport->setRoot      (DefaultRootNode);
    DefaultViewport->setSize      (0.0f,0.0f, 1.0f,1.0f);
    DefaultViewport->setBackground(DefaultBackground);

    return ViewportTransitPtr(DefaultViewport);
}

CameraTransitPtr ScenePreviewFieldContainerEditor::createDefaultCamera(void)
{
    PerspectiveCameraRefPtr DefaultCamera = PerspectiveCamera::create();
    DefaultCamera->setFov   (osgDegree2Rad(60.f));
    DefaultCamera->setNear  (0.1f);
    DefaultCamera->setFar   (30.f);

    return CameraTransitPtr(DefaultCamera);
}

NodeTransitPtr ScenePreviewFieldContainerEditor::createDefaultCameraBeacon(void)
{
    TransformRefPtr CameraBeaconTransform = Transform::create();

    NodeRefPtr CameraBeaconNode = Node::create();
    CameraBeaconNode->setCore(CameraBeaconTransform);

    return NodeTransitPtr(CameraBeaconNode);
}

NodeTransitPtr ScenePreviewFieldContainerEditor::createDefaultRoot(void)
{
    NodeRefPtr DefaultRootNode = makeCoredNode<Group>();

    return NodeTransitPtr(DefaultRootNode);
}

BackgroundTransitPtr ScenePreviewFieldContainerEditor::createDefaultBackground(void)
{
    GradientBackgroundRefPtr DefaultBackground = GradientBackground::create();
    DefaultBackground->addLine(Color3f(0.2f,0.2f,0.2f), 0.0f);
    DefaultBackground->addLine(Color3f(0.4f,0.4f,0.4f), 1.0f);

    return BackgroundTransitPtr(DefaultBackground);
}

/*----------------------- constructors & destructors ----------------------*/

ScenePreviewFieldContainerEditor::ScenePreviewFieldContainerEditor(void) :
    Inherited()
{
}

ScenePreviewFieldContainerEditor::ScenePreviewFieldContainerEditor(const ScenePreviewFieldContainerEditor &source) :
    Inherited(source)
{
}

ScenePreviewFieldContainerEditor::~ScenePreviewFieldContainerEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void ScenePreviewFieldContainerEditor::changed(ConstFieldMaskArg whichField, 
                                               UInt32            origin,
                                               BitVector         details)
{
    Inherited::changed(whichField, origin, details);

    //Do not respond to changes that have a Sync origin
    if(origin & ChangedOrigin::Sync)
    {
        return;
    }

    if((whichField & PreviewPanelSizeFieldMask) &&
       _MainSplitPanel != NULL)
    {
        _MainSplitPanel->setDividerPosition(getPreviewPanelSize()); 
    }
}

void ScenePreviewFieldContainerEditor::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump ScenePreviewFieldContainerEditor NI" << std::endl;
}

OSG_END_NAMESPACE
