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

#ifndef _OSGSPLITPANEL_H_
#define _OSGSPLITPANEL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSplitPanelBase.h"
#include "OSGMouseListener.h"
#include "OSGMouseMotionListener.h"

OSG_BEGIN_NAMESPACE

/*! \brief SplitPanel class. See \ref
           PageContribUserInterfaceSplitPanel for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING SplitPanel : public SplitPanelBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
    enum Orientation
    {
        VERTICAL_ORIENTATION   = 0,
        HORIZONTAL_ORIENTATION = 1
    };

    typedef SplitPanelBase Inherited;
    typedef SplitPanel     Self;

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

	virtual void setDividerDrawObject( const UIDrawObjectCanvasRefPtr &value );

	virtual void drawInternal(const GraphicsWeakPtr Graphics, Real32 Opacity = 1.0f) const;

    virtual void detachFromEventProducer(void);

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in SplitPanelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SplitPanel(void);
    SplitPanel(const SplitPanel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SplitPanel(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
	/*! \name                   Class Specific                             */
	/*! \{                                                                 */
	void onCreate(const SplitPanel *Id = NULL);
	void onDestroy();
	
	/*! \}                                                                 */

    virtual void updateLayout(void);

    class DividerListener : public MouseListener
    {
      public :
        DividerListener(SplitPanelRefPtr ptr);
        virtual void mouseClicked(const MouseEventUnrecPtr e);
        virtual void mouseEntered(const MouseEventUnrecPtr e);
        virtual void mouseExited(const MouseEventUnrecPtr e);
        virtual void mousePressed(const MouseEventUnrecPtr e);
        virtual void mouseReleased(const MouseEventUnrecPtr e);

        void cancel(void);
      protected :
        SplitPanelRefPtr _SplitPanel;
    };

    friend class DividerListener;

    DividerListener _DividerListener;
    class DividerDraggedListener : public MouseMotionListener, public MouseListener
    {
      public :
        DividerDraggedListener(SplitPanelRefPtr ptr);
        virtual void mouseMoved(const MouseEventUnrecPtr e);
        virtual void mouseDragged(const MouseEventUnrecPtr e);

        virtual void mouseClicked(const MouseEventUnrecPtr e);
        virtual void mouseEntered(const MouseEventUnrecPtr e);
        virtual void mouseExited(const MouseEventUnrecPtr e);
        virtual void mousePressed(const MouseEventUnrecPtr e);
        virtual void mouseReleased(const MouseEventUnrecPtr e);

        void cancel(void);
      protected :
        SplitPanelRefPtr _SplitPanel;
    };

    friend class DividerDraggedListener;

    DividerDraggedListener _DividerDraggedListener;

    void updateChildren(void);
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SplitPanelBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SplitPanel &source);
};

typedef SplitPanel *SplitPanelP;

OSG_END_NAMESPACE

#include "OSGSplitPanelBase.inl"
#include "OSGSplitPanel.inl"

#endif /* _OSGSPLITPANEL_H_ */
