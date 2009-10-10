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

#ifndef _OSGCURSORACTIVITY_H_
#define _OSGCURSORACTIVITY_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGCursorActivityBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief CursorActivity class. See \ref 
           PageInputCursorActivity for a description.
*/

class OSG_INPUTLIB_DLLMAPPING CursorActivity : public CursorActivityBase
{
  private:

    typedef CursorActivityBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
      enum ActivityType {
        CURSOR_HIDE = 0,
        CURSOR_SHOW = 1,
        CURSOR_SHOW_TOGGLE = 2,
        CURSOR_ATTACH_MOUSE_TO_CURSOR = 3,
        CURSOR_DETACH_MOUSE_FROM_CURSOR = 4,
        CURSOR_ATTACH_MOUSE_TO_CURSOR_TOGGLE = 5,
        CURSOR_SET_TYPE = 6,
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

    // Variables should all be in CursorActivityBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    CursorActivity(void);
    CursorActivity(const CursorActivity &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CursorActivity(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class CursorActivityBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const CursorActivity &source);
};

typedef CursorActivity *CursorActivityP;

OSG_END_NAMESPACE

#include "OSGCursorActivityBase.inl"
#include "OSGCursorActivity.inl"

#endif /* _OSGCURSORACTIVITY_H_ */
