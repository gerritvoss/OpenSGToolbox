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

#ifndef _OSGPROGRESSBAR_H_
#define _OSGPROGRESSBAR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGProgressBarBase.h"
#include "OSGBoundedRangeModel.h"

OSG_BEGIN_NAMESPACE

/*! \brief ProgressBar class. See \ref
           PageContribUserInterfaceProgressBar for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING ProgressBar : public ProgressBarBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
    enum Orientation
    {
        VERTICAL_ORIENTATION   = 0,
        HORIZONTAL_ORIENTATION = 1
    };

    typedef ProgressBarBase Inherited;
    typedef ProgressBar     Self;

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
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    virtual void drawInternal(Graphics* const Graphics, Real32 Opacity = 1.0f) const;
    virtual Color4f getDrawnTextColor(void) const;
    virtual UIDrawObjectCanvas* getDrawnDrawObject(void) const;

    void setupProgressBar();
    void setupIndeterminateProgressBar(const Time& Elps);

    void handleProgressStateChanged(ChangeEventDetails* const e);
    boost::signals2::connection _ProgressStateChangedConnection;

    void handleProgressUpdate(UpdateEventDetails* const e);
    boost::signals2::connection _ProgressUpdateConnection;

    Real32 _IndeterminateBarPosition;

    Pnt2f _ProgressBarPosition;
    Vec2f _ProgressBarSize;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ProgressBarBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ProgressBar &source);
};

typedef ProgressBar *ProgressBarP;

OSG_END_NAMESPACE

#include "OSGProgressBarBase.inl"
#include "OSGProgressBar.inl"

#endif /* _OSGPROGRESSBAR_H_ */
