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

#ifndef _OSGCOMMANDEVENT_H_
#define _OSGCOMMANDEVENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGCommandEventBase.h"
#include "OSGCommand.h"

OSG_BEGIN_NAMESPACE

/*! \brief CommandEvent class. See \ref
           PageContribUserInterfaceCommandEvent for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING CommandEvent : public CommandEventBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef CommandEventBase Inherited;
    typedef CommandEvent     Self;

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

    static  CommandEventTransitPtr      create(  FieldContainerRefPtr Source,
                                                 Time TimeStamp,
                                                 CommandPtr TheCommand); 

    const CommandPtr getCommand(void) const;

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in CommandEventBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    CommandEvent(void);
    CommandEvent(const CommandEvent &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CommandEvent(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

    CommandPtr _Command;

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class CommandEventBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const CommandEvent &source);
};

typedef CommandEvent *CommandEventP;

OSG_END_NAMESPACE

#include "OSGCommandEventBase.inl"
#include "OSGCommandEvent.inl"

#endif /* _OSGCOMMANDEVENT_H_ */
