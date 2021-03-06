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

#ifndef _OSGCARETEVENTDETAILS_H_
#define _OSGCARETEVENTDETAILS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGCaretEventDetailsBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief CaretEventDetails class. See \ref
           PageContribUserInterfaceCaretEventDetails for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING CaretEventDetails : public CaretEventDetailsBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef CaretEventDetailsBase Inherited;
    typedef CaretEventDetails     Self;

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

    static  CaretEventDetailsTransitPtr      create(  FieldContainer* const Source,
                                               Time TimeStamp,
                                               UInt32 ThePos); 

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in CaretEventDetailsBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    CaretEventDetails(void);
    CaretEventDetails(const CaretEventDetails &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~CaretEventDetails(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class CaretEventDetailsBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const CaretEventDetails &source);
};

typedef CaretEventDetails *CaretEventDetailsP;

OSG_END_NAMESPACE

#include "OSGCaretEventDetailsBase.inl"
#include "OSGCaretEventDetails.inl"

#endif /* _OSGCARETEVENTDETAILS_H_ */
