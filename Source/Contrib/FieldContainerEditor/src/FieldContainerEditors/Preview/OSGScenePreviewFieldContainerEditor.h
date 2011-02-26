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

#ifndef _OSGSCENEPREVIEWFIELDCONTAINEREDITOR_H_
#define _OSGSCENEPREVIEWFIELDCONTAINEREDITOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGScenePreviewFieldContainerEditorBase.h"
#include "OSGGLViewportFields.h"
#include "OSGSplitPanelFields.h"
#include "OSGViewportFields.h"
#include "OSGBackgroundFields.h"
#include "OSGCameraFields.h"
#include "OSGNodeFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief ScenePreviewFieldContainerEditor class. See \ref
           PageContribFieldContainerEditorScenePreviewFieldContainerEditor for a description.
*/

class OSG_CONTRIBFIELDCONTAINEREDITOR_DLLMAPPING ScenePreviewFieldContainerEditor : public ScenePreviewFieldContainerEditorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ScenePreviewFieldContainerEditorBase Inherited;
    typedef ScenePreviewFieldContainerEditor     Self;

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

	virtual Vec2f getContentRequestedSize(void) const;

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

    // Variables should all be in ScenePreviewFieldContainerEditorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ScenePreviewFieldContainerEditor(void);
    ScenePreviewFieldContainerEditor(const ScenePreviewFieldContainerEditor &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ScenePreviewFieldContainerEditor(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const ScenePreviewFieldContainerEditor *Id = NULL);
	void onDestroy();
	
	/*! \}                                                                 */
	/*---------------------------------------------------------------------*/
    /*! \name                       Sync                                   */
    /*! \{                                                                 */
    virtual void resolveLinks(void);

    /*! \}                                                                 */
    virtual GLViewportTransitPtr createDefaultGLViewport(void);
    virtual ViewportTransitPtr createDefaultViewport(void);
    virtual CameraTransitPtr createDefaultCamera(void);
    virtual NodeTransitPtr createDefaultCameraBeacon(void);
    virtual NodeTransitPtr createDefaultRoot(void);
    virtual BackgroundTransitPtr createDefaultBackground(void);


    SplitPanelRecPtr _MainSplitPanel;
    ViewportRecPtr   _PrimaryViewport;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ScenePreviewFieldContainerEditorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ScenePreviewFieldContainerEditor &source);
};

typedef ScenePreviewFieldContainerEditor *ScenePreviewFieldContainerEditorP;

OSG_END_NAMESPACE

#include "OSGGLViewport.h"
#include "OSGScenePreviewFieldContainerEditorBase.inl"
#include "OSGScenePreviewFieldContainerEditor.inl"

#endif /* _OSGSCENEPREVIEWFIELDCONTAINEREDITOR_H_ */
