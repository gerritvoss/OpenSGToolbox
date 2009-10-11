/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
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

#ifndef _OSGPROGRESSBAR_H_
#define _OSGPROGRESSBAR_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGProgressBarBase.h"
#include "Event/OSGChangeListener.h"
#include <set>
#include <OpenSG/Input/OSGUpdateListener.h>

#include <OpenSG/Toolbox/OSGEventConnection.h>

OSG_BEGIN_NAMESPACE

/*! \brief ProgressBar class. See \ref 
           PageUserInterfaceProgressBar for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING ProgressBar : public ProgressBarBase
{
  private:

    typedef ProgressBarBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
      enum Orientation{VERTICAL_ORIENTATION=0, HORIZONTAL_ORIENTATION};

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         UInt32     origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */

	//Adds the specified ChangeListener to the progress bar.
	EventConnection addChangeListener(ChangeListenerPtr Listener);
	bool isChangeListenerAttached(ChangeListenerPtr Listener) const;

	//Removes a ChangeListener from the progress bar.
	void removeChangeListener(ChangeListenerPtr Listener);

	//Returns the progress bar's maximum value, which is stored in the progress bar's BoundedRangeModel.
	Int32 getMaximum(void) const;

	//Returns the progress bar's minimum value, which is stored in the progress bar's BoundedRangeModel.
	Int32 getMinimum(void) const;

	//Returns the percent complete for the progress bar.
	Real32 getPercentComplete(void) const;

	//Returns the progress bar's current value, which is stored in the progress bar's BoundedRangeModel.
	Int32 getValue(void) const;

	//Sets the progress bar's maximum value (stored in the progress bar's data model) to n.
	void setMaximum(const Int32& n);

	//Sets the progress bar's minimum value (stored in the progress bar's data model) to n.
	void setMinimum(const Int32& n);

	//Sets the progress bar's current value (stored in the progress bar's data model) to n
	void setValue(const Int32& n);


    void startIndeterminate(void);
    void endIndeterminate(void);

    virtual void detachFromEventProducer(void);
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in ProgressBarBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ProgressBar(void);
    ProgressBar(const ProgressBar &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ProgressBar(void); 

    /*! \}                                                                 */
	virtual void drawInternal(const GraphicsPtr Graphics) const;
    virtual Color4f getDrawnTextColor(void) const;
    virtual UIDrawObjectCanvasPtr getDrawnDrawObject(void) const;

	void setupProgressBar();
	void setupIndeterminateProgressBar(const Time& Elps);
    
    //Listener for getting change updates of the UIViewport
	class ModelChangeListener : public ChangeListener
	{
	public:
		ModelChangeListener(ProgressBarPtr TheProgressBar);
        virtual void stateChanged(const ChangeEventPtr e);
	private:
		ProgressBarPtr _ProgressBar;
	};

	friend class ModelChangeListener;

	ModelChangeListener _ModelChangeListener;
    EventConnection _RangeModelConnection;

	class IndeterminateUpdateListener : public UpdateListener
	{
	public:
		IndeterminateUpdateListener(ProgressBarPtr TheProgressBar);
        virtual void update(const UpdateEventPtr e);
	private:
		ProgressBarPtr _ProgressBar;
	};

	friend class IndeterminateUpdateListener;

	IndeterminateUpdateListener _IndeterminateUpdateListener;
	Real32 _IndeterminateBarPosition;

    Pnt2f _ProgressBarPosition;
    Vec2f _ProgressBarSize;
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ProgressBarBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const ProgressBar &source);
};

typedef ProgressBar *ProgressBarP;

OSG_END_NAMESPACE

#include "OSGProgressBarBase.inl"
#include "OSGProgressBar.inl"

#define OSGPROGRESSBAR_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGPROGRESSBAR_H_ */
