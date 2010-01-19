/*---------------------------------------------------------------------------*\
 *                          OpenSG ToolBox Input                             *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala                            *
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

#ifndef _OSGWINDOWACTIVITY_H_
#define _OSGWINDOWACTIVITY_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGWindowActivityBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief WindowActivity class. See \ref 
           PageInputWindowActivity for a description.
*/

class OSG_INPUTLIB_DLLMAPPING WindowActivity : public WindowActivityBase
{
  private:

    typedef WindowActivityBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
      enum ActivityType {
        WINDOW_CLOSE = 0,
        WINDOW_FOCUS = 1,
        WINDOW_UNFOCUS = 2,
        WINDOW_FOCUS_TOGGLE = 3,
        WINDOW_VISIBLE = 4,
        WINDOW_HIDDEN = 5,
        WINDOW_VISIBLE_TOGGLE = 6,
        WINDOW_ICONIFY = 7,
        WINDOW_DEICONIFY = 8,
        WINDOW_ICONIFY_TOGGLE = 9,
        WINDOW_FULLSCREEN = 10,
        WINDOW_DEFULLSCREEN = 11,
        WINDOW_FULLSCREEN_TOGGLE = 12,
      };

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

    virtual void eventProduced(const EventPtr EventDetails, UInt32 ProducedEventId);

    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in WindowActivityBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    WindowActivity(void);
    WindowActivity(const WindowActivity &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~WindowActivity(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class WindowActivityBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const WindowActivity &source);
};

typedef WindowActivity *WindowActivityP;

OSG_END_NAMESPACE

#include "OSGWindowActivityBase.inl"
#include "OSGWindowActivity.inl"

#endif /* _OSGWINDOWACTIVITY_H_ */
