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

#ifndef _OSGSCROLLPANEL_H_
#define _OSGSCROLLPANEL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGScrollPanelBase.h"
#include "OSGAdjustmentListener.h"
#include "OSGChangeListener.h"
#include "OSGScrollPanelBase.h"
#include "OSGButton.h"
#include "OSGDefaultBoundedRangeModel.h"

OSG_BEGIN_NAMESPACE

/*! \brief ScrollPanel class. See \ref
           PageContribUserInterfaceScrollPanel for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING ScrollPanel : public ScrollPanelBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
    enum ScrollBarDisplayPolicy
    {
        SCROLLBAR_AS_NEEDED = 0,
        SCROLLBAR_AS_ALWAYS = 1,
        SCROLLBAR_AS_NEVER  = 2
    };

    enum ResizePolicy
    {
        NO_RESIZE      = 0,
        RESIZE_TO_VIEW = 1
    };

    enum HorizontalAlign
    {
        SCROLLBAR_ALIGN_TOP    = 0,
        SCROLLBAR_ALIGN_BOTTOM = 1
    };

    enum VerticalAlign
    {
        SCROLLBAR_ALIGN_LEFT  = 0,
        SCROLLBAR_ALIGN_RIGHT = 1
    };

    typedef ScrollPanelBase Inherited;
    typedef ScrollPanel     Self;

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
    
    virtual void updateLayout(void);

    void setViewComponent(ComponentRefPtr TheComponent);
    Component * getViewComponent  (void) const;

    //Mouse Wheel Events
    virtual void mouseWheelMoved(const MouseWheelEventUnrecPtr e);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ScrollPanelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ScrollPanel(void);
    ScrollPanel(const ScrollPanel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ScrollPanel(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	/*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const ScrollPanel *Id = NULL);
	void onDestroy();
	
	/*! \}                                                                 */

    //Listener for getting change updates of the UIViewport
    class ViewportChangeListener : public ChangeListener
    {
      public:
        ViewportChangeListener(ScrollPanelRefPtr TheScrollPanel);
        virtual void stateChanged(const ChangeEventUnrecPtr e);
      private:
        ScrollPanelRefPtr _ScrollPanel;
    };

    friend class ViewportChangeListener;

    ViewportChangeListener _ViewportChangeListener;

    //Listener for getting change updates of the UIViewport Range Model
    class ViewportRangeModelChangeListener : public ChangeListener
    {
      public:
        ViewportRangeModelChangeListener(ScrollPanelRefPtr TheScrollPanel);
        virtual void stateChanged(const ChangeEventUnrecPtr e);
      private:
        ScrollPanelRefPtr _ScrollPanel;
    };

    friend class ViewportRangeModelChangeListener;

    ViewportRangeModelChangeListener _ViewportRangeModelChangeListener;

    void updateRangeModels(void);

    ScrollBarRefPtr getVerticalScrollBar(void);

    ScrollBarRefPtr getHorizontalScrollBar(void);
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ScrollPanelBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ScrollPanel &source);
};

typedef ScrollPanel *ScrollPanelP;

OSG_END_NAMESPACE

#include "OSGUIViewport.h"
#include "OSGScrollBar.h"

#include "OSGScrollPanelBase.inl"
#include "OSGScrollPanel.inl"

#endif /* _OSGSCROLLPANEL_H_ */
