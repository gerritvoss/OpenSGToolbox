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

#ifndef _OSGACTIVITY_H_
#define _OSGACTIVITY_H_

#include "OSGActivityBase.h"
#include "OSGEventDetails.h"

OSG_BEGIN_NAMESPACE

/*! \brief Activity class. See \ref
           PageBaseActivity for a description.
*/

class OSG_BASE_DLLMAPPING Activity : public ActivityBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ActivityBase Inherited;
    typedef Activity     Self;

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

    virtual void eventProduced(EventDetails* const details,
                               UInt32 producedEventId) = 0;

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ActivityBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Activity(void);
    Activity(const Activity &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Activity(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

    //Connected Signals
    //* to the container, EventId
    std::list< std::pair< ReflexiveContainer const *, UInt32> > _EventsConnectedTo;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ActivityBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const Activity &source);
};

typedef Activity *ActivityP;

OSG_END_NAMESPACE

#include "OSGActivityBase.inl"
#include "OSGActivity.inl"

#endif /* _OSGACTIVITY_H_ */
