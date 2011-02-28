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

#include "OSGSoundFieldContainerEditor.h"

#include "OSGFieldContainerFactory.h"
#include "OSGFieldContainerEditorFactory.h"
#include "OSGFieldEditorFactory.h"
#include "OSGSpringLayout.h"
#include "OSGSpringLayoutConstraints.h"
#include "OSGSplitPanel.h"
#include "OSGUIDrawObjectCanvas.h"
#include "OSGSound.h"
#include "OSGButton.h"
#include "OSGSlider.h"
#include "OSGPanel.h"
#include "OSGLabel.h"
#include "OSGScrollPanel.h"
#include "OSGBorderLayout.h"
#include "OSGBorderLayoutConstraints.h"
#include "OSGChangeEventDetails.h"
#include "OSGWindowEventProducer.h"
#include "OSGInternalWindow.h"
#include "OSGUIDrawingSurface.h"
#include "OSGFilePathAttachment.h"

#include <boost/format.hpp>

OSG_BEGIN_NAMESPACE

// Documentation for this class is emitted in the
// OSGSoundFieldContainerEditorBase.cpp file.
// To modify it, please change the .fcd file (OSGSoundFieldContainerEditor.fcd) and
// regenerate the base file.

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

std::vector<const FieldContainerType*>
SoundFieldContainerEditor::_EditableTypes = std::vector<const FieldContainerType*>();

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void SoundFieldContainerEditor::initMethod(InitPhase ePhase)
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
                if(type->isDerivedFrom(Sound::getClassType()))
                {
                    _EditableTypes.push_back(type);
                    FieldContainerEditorFactory::the()->setDefaultEditor(type,
                                                                         &getClassType());
                    FieldContainerEditorFactory::the()->setEditorType(type,
                                                                      &getClassType(),
                                                                      "Sound");
                }
            }
        }
    }
}


/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

const std::vector<const FieldContainerType*>& SoundFieldContainerEditor::getEditableTypes(void) const
{
    return _EditableTypes;
}

bool SoundFieldContainerEditor::attachFieldContainer(FieldContainer* fc)
{
    //Check that this is a valid FieldContainer
    if(!Inherited::attachFieldContainer(fc))
    {
        return false;
    }

    //Attach the sound
    attachSound(dynamic_cast<Sound*>(fc));
    return true;
}

bool SoundFieldContainerEditor::dettachFieldContainer(void)
{
    //Dettach the sound
    dettachSound();

    return Inherited::dettachFieldContainer();
}

bool SoundFieldContainerEditor::getScrollableTracksViewportHeight(void)
{
    return true;
}

bool SoundFieldContainerEditor::getScrollableTracksViewportWidth(void)
{
    return true;
}

bool SoundFieldContainerEditor::getScrollableHeightMinTracksViewport(void)
{
    return true;
}

bool SoundFieldContainerEditor::getScrollableWidthMinTracksViewport(void)
{
    return true;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

void SoundFieldContainerEditor::onCreate(const SoundFieldContainerEditor *Id)
{
	Inherited::onCreate(Id);

    if(GlobalSystemState != Startup)
    {
        //Create the Panel for the sound preview
        PanelRecPtr SoundPanel = createSoundPreviewPanel();

        ScrollPanelRecPtr EditorScrollPanel = ScrollPanel::create();
        EditorScrollPanel->setViewComponent(_GenericEditor);

        _MainSplitPanel = SplitPanel::create();
        _MainSplitPanel->setOrientation(SplitPanel::VERTICAL_ORIENTATION);
        _MainSplitPanel->setDividerPosition(150.0f); 
        _MainSplitPanel->setMinComponent(SoundPanel);
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

void SoundFieldContainerEditor::onDestroy()
{
}

void SoundFieldContainerEditor::resolveLinks(void)
{
    Inherited::resolveLinks();

    _PlayPauseActionConnection.disconnect();
    _StopActionConnection.disconnect();
    _LoadActionConnection.disconnect();
    dettachSound();

    _MainSplitPanel = NULL;
    _FileNameLabel = NULL;
    _TotalTimeLabel = NULL;
    _PlaybackTimeLabel = NULL;
    _PlayPauseButton = NULL;
    _StopButton = NULL;
    _LocationSlider = NULL;
    _AttachedSound = NULL;
}

void SoundFieldContainerEditor::updateSoundPreviewPanel(void)
{
    if(_AttachedSound != NULL)
    {
        _PlayPauseButton->setEnabled(true);
        _LocationSlider->setEnabled(true);

        _FileNameLabel->setText(_AttachedSound->getFile().filename());

        updateTimeInterface();
    }
    else
    {
        _FileNameLabel->setText("<<No file loaded>>");
        _PlayPauseButton->setEnabled(false);
        _StopButton->setEnabled(false);
        _LocationSlider->setEnabled(false);
    }
}

void SoundFieldContainerEditor::attachSound(Sound* const TheSound)
{
    if(_AttachedSound != NULL)
    {
        dettachSound();
    }

    _AttachedSound = TheSound;

    if(_AttachedSound != NULL)
    {
        _LocationSlider->getRangeModel()->setRangeProperties(0, 0, 0, 1000, false);

        _SoundPlayedConnection = _AttachedSound->connectSoundPlayed(boost::bind(&SoundFieldContainerEditor::handleSoundPlayed, this,   _1));
        _SoundStoppedConnection = _AttachedSound->connectSoundStopped(boost::bind(&SoundFieldContainerEditor::handleSoundStopped, this,  _1));
        _SoundPausedConnection = _AttachedSound->connectSoundPaused(boost::bind(&SoundFieldContainerEditor::handleSoundPaused, this,   _1));
        _SoundUnpausedConnection = _AttachedSound->connectSoundUnpaused(boost::bind(&SoundFieldContainerEditor::handleSoundUnpaused, this, _1));
        _SoundSeekedConnection = _AttachedSound->connectSoundSeeked(boost::bind(&SoundFieldContainerEditor::handleSoundSeeked, this, _1));
        _SoundEndedConnection = _AttachedSound->connectSoundEnded(boost::bind(&SoundFieldContainerEditor::handleSoundEnded, this, _1));
    }
    updateSoundPreviewPanel();
}

void SoundFieldContainerEditor::dettachSound(void)
{
    if(_AttachedSound != NULL)
    {
        //Stop the sound
        _AttachedSound->stop(_PlayingChannel);
    }

    _AttachedSound = NULL;

    _SoundPlayedConnection.disconnect();
    _SoundStoppedConnection.disconnect();
    _SoundPausedConnection.disconnect();
    _SoundUnpausedConnection.disconnect();
    _SoundSeekedConnection.disconnect();
    _SoundEndedConnection.disconnect();
    _SoundPlayingUpdateConnection.disconnect();
}

PanelTransitPtr SoundFieldContainerEditor::createSoundPreviewPanel(void)
{
    //Filename Label
    _FileNameLabel = Label::create();
    _FileNameLabel->setAlignment(Vec2f(0.5f, 0.5f));

    //Total time Label
    _TotalTimeLabel = Label::create();
    _TotalTimeLabel->setAlignment(Vec2f(0.0f, 1.0f));
    _TotalTimeLabel->setBorders(NULL);
    _TotalTimeLabel->setBackgrounds(NULL);
    _TotalTimeLabel->setPreferredSize(Vec2f(50.0f,_TotalTimeLabel->getPreferredSize().y()));

    //Playback time Label
    _PlaybackTimeLabel = Label::create();
    _PlaybackTimeLabel->setAlignment(Vec2f(1.0f, 1.0f));
    _PlaybackTimeLabel->setPreferredSize(Vec2f(50.0f,_TotalTimeLabel->getPreferredSize().y()));
    _PlaybackTimeLabel->setBorders(NULL);
    _PlaybackTimeLabel->setBackgrounds(NULL);

    LabelRecPtr TimeSeparatorLabel = Label::create();
    TimeSeparatorLabel->setAlignment(Vec2f(0.5f, 1.0f));
    TimeSeparatorLabel->setPreferredSize(Vec2f(8.0f,_TotalTimeLabel->getPreferredSize().y()));
    TimeSeparatorLabel->setBorders(NULL);
    TimeSeparatorLabel->setBackgrounds(NULL);
    TimeSeparatorLabel->setText("/");

    //PlayPause Button
    _PlayPauseButton = Button::create();
    _PlayPauseButton->setText("Play");
    _PlayPauseButton->setPreferredSize(Vec2f(40.0f,40.0f));
    _PlayPauseButton->connectActionPerformed(boost::bind(&SoundFieldContainerEditor::handlePlayPauseAction, this,   _1));

    //Stop Button
    _StopButton = Button::create();
    _StopButton->setText("Stop");
    _StopButton->setPreferredSize(Vec2f(40.0f,40.0f));
    _StopButton->connectActionPerformed(boost::bind(&SoundFieldContainerEditor::handleStopAction, this,   _1));

    //Load Button
    ButtonRecPtr LoadButton = Button::create();
    LoadButton->setText("Load");
    LoadButton->setPreferredSize(Vec2f(40.0f,40.0f));
    LoadButton->connectActionPerformed(boost::bind(&SoundFieldContainerEditor::handleLoadAction, this,   _1));

    //Playback position slider
    _LocationSlider = Slider::create();
    _LocationSlider->setOrientation(Slider::HORIZONTAL_ORIENTATION);
    _LocationSlider->setDrawLabels(false);
    _LocationSlider->setDrawMajorTicks(false);
    _LocationSlider->setDrawMinorTicks(false);
    _LocationSlider->setBorders(NULL);
    _LocationSlider->setBackgrounds(NULL);
    //_LocationSlider->getKnobButton()->setPreferredSize(Vec2f(15.0f, 8.0f));
    _LocationSlider->getRangeModel()->connectStateChanged(boost::bind(&SoundFieldContainerEditor::handlePlaybackLocationStateChanged, this,   _1));


    //Layout
    PanelRecPtr SoundPanel = Panel::createEmpty();
    SpringLayoutRecPtr MainLayout = SpringLayout::create();


    //Filename Label
    MainLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _FileNameLabel, 0,
                              SpringLayoutConstraints::EAST_EDGE, SoundPanel);
    MainLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, _FileNameLabel, 0,
                              SpringLayoutConstraints::WEST_EDGE, SoundPanel);
    MainLayout->putConstraint(SpringLayoutConstraints::NORTH_EDGE, _FileNameLabel, 0,
                              SpringLayoutConstraints::NORTH_EDGE, SoundPanel);

    //Play/pause Button
    MainLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _PlayPauseButton, -3,
                              SpringLayoutConstraints::WEST_EDGE, _StopButton);
    MainLayout->putConstraint(SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _PlayPauseButton, 0,
                              SpringLayoutConstraints::VERTICAL_CENTER_EDGE, SoundPanel);

    //Stop Button
    MainLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _StopButton, -3,
                              SpringLayoutConstraints::WEST_EDGE, _LocationSlider);
    MainLayout->putConstraint(SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _StopButton, 0,
                              SpringLayoutConstraints::VERTICAL_CENTER_EDGE, SoundPanel);

    //Playback Slider
    MainLayout->putConstraint(SpringLayoutConstraints::HORIZONTAL_CENTER_EDGE, _LocationSlider, 0,
                              SpringLayoutConstraints::HORIZONTAL_CENTER_EDGE, SoundPanel);
    MainLayout->putConstraint(SpringLayoutConstraints::VERTICAL_CENTER_EDGE, _LocationSlider, 0,
                              SpringLayoutConstraints::VERTICAL_CENTER_EDGE, SoundPanel);

    //Total sound length label
    MainLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _TotalTimeLabel, 0,
                              SpringLayoutConstraints::SOUTH_EDGE, LoadButton);
    MainLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _TotalTimeLabel, 0,
                              SpringLayoutConstraints::EAST_EDGE, _LocationSlider);

    //Separator label
    MainLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, TimeSeparatorLabel, 0,
                              SpringLayoutConstraints::SOUTH_EDGE, LoadButton);
    MainLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, TimeSeparatorLabel, -2,
                              SpringLayoutConstraints::WEST_EDGE, _TotalTimeLabel);

    //Playback time label
    MainLayout->putConstraint(SpringLayoutConstraints::SOUTH_EDGE, _PlaybackTimeLabel, 0,
                              SpringLayoutConstraints::SOUTH_EDGE, LoadButton);
    MainLayout->putConstraint(SpringLayoutConstraints::EAST_EDGE, _PlaybackTimeLabel, -2,
                              SpringLayoutConstraints::WEST_EDGE, TimeSeparatorLabel);

    //Load Button
    MainLayout->putConstraint(SpringLayoutConstraints::WEST_EDGE, LoadButton, 3,
                              SpringLayoutConstraints::EAST_EDGE, _LocationSlider);
    MainLayout->putConstraint(SpringLayoutConstraints::VERTICAL_CENTER_EDGE, LoadButton, 0,
                              SpringLayoutConstraints::VERTICAL_CENTER_EDGE, SoundPanel);

    //Main Sound Panel
    SoundPanel->setLayout(MainLayout);
    SoundPanel->pushToChildren(_FileNameLabel);
    SoundPanel->pushToChildren(_PlayPauseButton);
    SoundPanel->pushToChildren(_StopButton);
    SoundPanel->pushToChildren(LoadButton);
    SoundPanel->pushToChildren(_PlaybackTimeLabel);
    SoundPanel->pushToChildren(TimeSeparatorLabel);
    SoundPanel->pushToChildren(_TotalTimeLabel);
    SoundPanel->pushToChildren(_LocationSlider);

    return PanelTransitPtr(SoundPanel);
}

void SoundFieldContainerEditor::handlePlayPauseAction(ActionEventDetails* const details)
{
    if(_AttachedSound != NULL)
    {
        if(!_AttachedSound->isPlaying(_PlayingChannel))
        {
            //Play the sound
            _PlayingChannel = _AttachedSound->play();
            //if(_LocationSlider->getRangeModel()->getValue() != 0)
            //{
                //_AttachedSound->pause(_PlayingChannel);
                //_AttachedSound->seek(static_cast<Real32>(_LocationSlider->getRangeModel()->getValue())/1000.0f * _AttachedSound->getLength(),
                                     //_PlayingChannel);
                //_AttachedSound->unpause(_PlayingChannel);
            //}
        }
        else
        {
            //Toggle Pause
            _AttachedSound->pauseToggle(_PlayingChannel);
        }
    }
}

void SoundFieldContainerEditor::handleStopAction(ActionEventDetails* const details)
{
    if(_AttachedSound != NULL)
    {
        //Stop the sound
        _AttachedSound->stop(_PlayingChannel);
    }
}

void SoundFieldContainerEditor::handleLoadAction(ActionEventDetails* const details)
{
    if(_AttachedSound != NULL)
    {
        //Stop the sound
        _AttachedSound->stop(_PlayingChannel);
    }

    //Have the user select the file to import
    std::vector<WindowEventProducer::FileDialogFilter> Filters;

    Filters.push_back(WindowEventProducer::FileDialogFilter("All (*.*)","*"));

	std::vector<BoostPath> FilesToOpen;
    FilesToOpen =
        getParentWindow()->getParentDrawingSurface()->getEventProducer()->openFileDialog("Load a sound file.",
                                                                          Filters,
                                                                          BoostPath("."),
                                                                          false);

    if(FilesToOpen.size() > 0)
    {
        _AttachedSound->setFile(FilesToOpen[0]);
    }
    updateSoundPreviewPanel();
}

void SoundFieldContainerEditor::handlePlaybackLocationStateChanged(ChangeEventDetails* const details)
{
    BoundedRangeModel* const Model(dynamic_cast<BoundedRangeModel* const>(details->getSource()));

    if(_AttachedSound != NULL &&
       _AttachedSound->isPlaying(_PlayingChannel) &&
       !Model->getValueIsAdjusting())
    {
        _AttachedSound->pause(_PlayingChannel);
        //Move the sound playback position
        _AttachedSound->seek(static_cast<Real32>(Model->getValue())/1000.0f * _AttachedSound->getLength(),
                             _PlayingChannel);
    }
}

void SoundFieldContainerEditor::handleSoundPlayed(SoundEventDetails* const details)
{
    //Play/pause button
    _PlayPauseButton->setText("Pause");

    //Stop Button
    _StopButton->setEnabled(true);
    _LocationSlider->getRangeModel()->setRangeProperties(_AttachedSound->getTime(_PlayingChannel)/_AttachedSound->getLength() * 1000.0f,
                                                             0, 0, 1000, true);

    _SoundPlayingUpdateConnection =
        getParentWindow()->getParentDrawingSurface()->getEventProducer()->connectUpdate(boost::bind(&SoundFieldContainerEditor::handleSoundPlayingUpdate, this,   _1));
}

void SoundFieldContainerEditor::handleSoundStopped(SoundEventDetails* const details)
{
    _PlayPauseButton->setText("Play");
    _StopButton->setEnabled(false);
    updateTimeInterface();
    _SoundPlayingUpdateConnection.disconnect();
}

void SoundFieldContainerEditor::handleSoundPaused(SoundEventDetails* const details)
{
    _PlayPauseButton->setText("Play");

    _SoundPlayingUpdateConnection.disconnect();
}

void SoundFieldContainerEditor::handleSoundUnpaused(SoundEventDetails* const details)
{
    _PlayPauseButton->setText("Pause");

    _SoundPlayingUpdateConnection =
        getParentWindow()->getParentDrawingSurface()->getEventProducer()->connectUpdate(boost::bind(&SoundFieldContainerEditor::handleSoundPlayingUpdate, this,   _1));
}

void SoundFieldContainerEditor::handleSoundSeeked(SoundEventDetails* const details)
{
    updateTimeInterface();
}

void SoundFieldContainerEditor::handleSoundEnded(SoundEventDetails* const details)
{
    _PlayPauseButton->setText("Play");
    _StopButton->setEnabled(false);

    _SoundPlayingUpdateConnection.disconnect();
}

void SoundFieldContainerEditor::updateTimeInterface(void)
{
    if(_AttachedSound != NULL)
    {
        Real32 Time(_AttachedSound->getTime(_PlayingChannel));

        UInt32 Min(osgFloor(Time/60.0f)),
               Sec(osgFloor(Time - Min*60.0f));
        boost::format TimeFormatter("%d:%02d");
        _PlaybackTimeLabel->setText(boost::str(TimeFormatter % Min  % Sec ));

        Time = _AttachedSound->getLength();
        Min  = osgFloor(Time/60.0f);
        Sec  = osgFloor(Time - Min*60.0f);
        _TotalTimeLabel->setText(boost::str(TimeFormatter % Min  % Sec ));

        _LocationSlider->getRangeModel()->setRangeProperties(_AttachedSound->getTime(_PlayingChannel)/_AttachedSound->getLength() * 1000.0f,
                                                             0, 0, 1000, true);
    }
    else
    {
        _TotalTimeLabel->setText("");
        _PlaybackTimeLabel->setText("");
        _LocationSlider->getRangeModel()->setValue(0);
    }
}

void SoundFieldContainerEditor::handleSoundPlayingUpdate(UpdateEventDetails* const details)
{
    updateTimeInterface();
}

/*----------------------- constructors & destructors ----------------------*/

SoundFieldContainerEditor::SoundFieldContainerEditor(void) :
    Inherited()
{
}

SoundFieldContainerEditor::SoundFieldContainerEditor(const SoundFieldContainerEditor &source) :
    Inherited(source)
{
}

SoundFieldContainerEditor::~SoundFieldContainerEditor(void)
{
}

/*----------------------------- class specific ----------------------------*/

void SoundFieldContainerEditor::changed(ConstFieldMaskArg whichField, 
                            UInt32            origin,
                            BitVector         details)
{
    Inherited::changed(whichField, origin, details);
}

void SoundFieldContainerEditor::dump(      UInt32    ,
                         const BitVector ) const
{
    SLOG << "Dump SoundFieldContainerEditor NI" << std::endl;
}

OSG_END_NAMESPACE
