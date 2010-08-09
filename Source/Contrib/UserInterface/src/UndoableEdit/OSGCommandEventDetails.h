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

#ifndef _OSGCOMMANDEVENTDETAILS_H_
#define _OSGCOMMANDEVENTDETAILS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGCommandEventDetailsBase.h"
#include "OSGCommand.h"

OSG_BEGIN_NAMESPACE

/*! \brief CommandEventDetails class. See \ref
           PageContribUserInterfaceCommandEventDetails for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING CommandEventDetails : public CommandEventDetailsBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef CommandEventDetailsBase Inherited;
    typedef CommandEventDetails     Self;

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

    static  CommandEventDetailsTransitPtr      create(  FieldContainer* const Source,
                                                 Time TimeStamp,
                                                 CommandPtr TheCommand); 

    const CommandPtr getCommand(void) const;

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in CommandEventDetailsBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    CommandEventDetails(void);
    CommandEventDetails(const CommandEventDetails &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CommandEventDetails(void);

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
    friend class CommandEventDetailsBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const CommandEventDetails &source);
};

typedef CommandEventDetails *CommandEventDetailsP;

OSG_END_NAMESPACE

#include "OSGCommandEventDetailsBase.inl"
#include "OSGCommandEventDetails.inl"

#endif /* _OSGCOMMANDEVENTDETAILS_H_ */
