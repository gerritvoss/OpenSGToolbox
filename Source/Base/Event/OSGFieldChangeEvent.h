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

#ifndef _OSGFIELDCHANGEEVENT_H_
#define _OSGFIELDCHANGEEVENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGFieldChangeEventBase.h"

#include "OSGField.h"
#include "OSGFieldDescriptionBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief FieldChangeEvent class. See \ref
           PageBaseFieldChangeEvent for a description.
*/

class OSG_BASE_DLLMAPPING FieldChangeEvent : public FieldChangeEventBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef FieldChangeEventBase Inherited;
    typedef FieldChangeEvent     Self;

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
    static  FieldChangeEventTransitPtr      create(  FieldContainerRefPtr Source,
                                                     Time TimeStamp,
                                                     const FieldDescriptionBase* TheDescription); 

    EditFieldHandlePtr getEditFieldFieldHandle(void) const;
    GetFieldHandlePtr getGetFieldFieldHandle(void) const;

    const FieldDescriptionBase* getFieldDescription(void) const;
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in FieldChangeEventBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    FieldChangeEvent(void);
    FieldChangeEvent(const FieldChangeEvent &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~FieldChangeEvent(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class FieldChangeEventBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const FieldChangeEvent &source);

    const FieldDescriptionBase* _FieldDescription;
};

typedef FieldChangeEvent *FieldChangeEventP;

OSG_END_NAMESPACE

#include "OSGFieldChangeEventBase.inl"
#include "OSGFieldChangeEvent.inl"

#endif /* _OSGFIELDCHANGEEVENT_H_ */
