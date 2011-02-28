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

#ifndef _OSGSOUNDFIELDCONTAINEREDITOR_H_
#define _OSGSOUNDFIELDCONTAINEREDITOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSoundFieldContainerEditorBase.h"
#include "OSGSplitPanelFields.h"
#include "OSGChangeEventDetailsFields.h"
#include "OSGActionEventDetailsFields.h"
#include "OSGSoundFields.h"
#include "OSGButtonFields.h"
#include "OSGPanelFields.h"
#include "OSGLabelFields.h"
#include "OSGSliderFields.h"
#include "OSGSoundEventDetailsFields.h"
#include "OSGUpdateEventDetailsFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief SoundFieldContainerEditor class. See \ref
           PageContribFieldContainerEditorSoundFieldContainerEditor for a description.
*/

class OSG_CONTRIBFIELDCONTAINEREDITOR_DLLMAPPING SoundFieldContainerEditor : public SoundFieldContainerEditorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef SoundFieldContainerEditorBase Inherited;
    typedef SoundFieldContainerEditor     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    virtual const std::vector<const FieldContainerType*>& getEditableTypes(void) const;

    virtual bool attachFieldContainer(FieldContainer* fc);
    virtual bool dettachFieldContainer(void);

    //Return true if a viewport should always force the height of this
    //Scrollable to match the height of the viewport.
    virtual bool getScrollableTracksViewportHeight(void);

    //Return true if a viewport should always force the width of this
    //Scrollable to match the width of the viewport.
    virtual bool getScrollableTracksViewportWidth(void);

    //Return true if a viewport should always force the height of this
    //Scrollable to be at at least the height of the viewport.
    virtual bool getScrollableHeightMinTracksViewport(void);

    //Return true if a viewport should always force the width of this
    //Scrollable to be at at least the width of the viewport.
    virtual bool getScrollableWidthMinTracksViewport(void);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in SoundFieldContainerEditorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SoundFieldContainerEditor(void);
    SoundFieldContainerEditor(const SoundFieldContainerEditor &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SoundFieldContainerEditor(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const SoundFieldContainerEditor *Id = NULL);
	void onDestroy();
	
	/*! \}                                                                 */
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */
    static std::vector<const FieldContainerType*> _EditableTypes;
    PanelTransitPtr createSoundPreviewPanel(void);
    void updateSoundPreviewPanel(void);
    void updateTimeInterface(void);

    SplitPanelRecPtr _MainSplitPanel;
    SoundRecPtr      _AttachedSound;
    LabelRecPtr      _FileNameLabel;
    LabelRecPtr      _PlaybackTimeLabel;
    LabelRecPtr      _TotalTimeLabel;
    ButtonRecPtr     _PlayPauseButton;
    ButtonRecPtr     _StopButton;
    SliderRecPtr     _LocationSlider;
    UInt32           _PlayingChannel;

    void attachSound(Sound* const TheSound);
    void dettachSound(void);

    void handlePlayPauseAction(ActionEventDetails* const details);
    void handleStopAction(ActionEventDetails* const details);
    void handleLoadAction(ActionEventDetails* const details);
    void handlePlaybackLocationStateChanged(ChangeEventDetails* const details);

    void handleSoundPlayed(SoundEventDetails* const details);
    void handleSoundStopped(SoundEventDetails* const details);
    void handleSoundPaused(SoundEventDetails* const details);
    void handleSoundUnpaused(SoundEventDetails* const details);
    void handleSoundSeeked(SoundEventDetails* const details);
    void handleSoundEnded(SoundEventDetails* const details);
    void handleSoundPlayingUpdate(UpdateEventDetails* const details);

    boost::signals2::connection _PlayPauseActionConnection,
                                _StopActionConnection,
                                _LoadActionConnection,
                                _PlaybackLocationStateChangedConnection,
                                _SoundPlayedConnection,
                                _SoundStoppedConnection,
                                _SoundEndedConnection,
                                _SoundPausedConnection,
                                _SoundUnpausedConnection,
                                _SoundSeekedConnection,
                                _SoundPlayingUpdateConnection;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SoundFieldContainerEditorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SoundFieldContainerEditor &source);
};

typedef SoundFieldContainerEditor *SoundFieldContainerEditorP;

OSG_END_NAMESPACE

#include "OSGSoundFieldContainerEditorBase.inl"
#include "OSGSoundFieldContainerEditor.inl"

#endif /* _OSGSOUNDFIELDCONTAINEREDITOR_H_ */
