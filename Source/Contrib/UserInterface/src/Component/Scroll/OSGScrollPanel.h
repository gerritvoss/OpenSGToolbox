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
#include "OSGButtonFields.h"
#include "OSGChangeEventDetailsFields.h"

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

    void setViewComponent(Component* const TheComponent);
    Component * getViewComponent  (void) const;

    //Mouse Wheel Events
    virtual void mouseWheelMoved(MouseWheelEventDetails* const e);

    //Scrolling
    void scrollHorizontalUnit(Int32 Units);
    void scrollHorizontalBlock(Int32 Blocks);
    void scrollVerticalUnit(Int32 Units);
    void scrollVerticalBlock(Int32 Blocks);
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

    //UIViewport Changes
    void handleViewportStateChanged(ChangeEventDetails* const e);
    boost::signals2::connection _ViewportStateChangedConnection;

    //RangeModel Changes
    void handleRangeModelStateChanged(ChangeEventDetails* const e);
    boost::signals2::connection _VertRangeModelStateChangedConnection,
                                _HorzRangeModelStateChangedConnection;

    void updateRangeModels(void);

    ScrollBar* getVerticalScrollBar(void);

    ScrollBar* getHorizontalScrollBar(void);
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
#include "OSGDefaultBoundedRangeModel.h"

#include "OSGScrollPanelBase.inl"
#include "OSGScrollPanel.inl"

#endif /* _OSGSCROLLPANEL_H_ */
