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

#ifndef _OSGADJUSTMENTEVENTDETAILS_H_
#define _OSGADJUSTMENTEVENTDETAILS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGAdjustmentEventDetailsBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief AdjustmentEventDetails class. See \ref
           PageContribUserInterfaceAdjustmentEventDetails for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING AdjustmentEventDetails : public AdjustmentEventDetailsBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef AdjustmentEventDetailsBase Inherited;
    typedef AdjustmentEventDetails     Self;

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

    static  AdjustmentEventDetailsTransitPtr      create( FieldContainer* const Source,
                                                   Time TimeStamp,
                                                   UInt32 Value,
                                                   bool ValueIsAdjusting); 

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in AdjustmentEventDetailsBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    AdjustmentEventDetails(void);
    AdjustmentEventDetails(const AdjustmentEventDetails &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~AdjustmentEventDetails(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class AdjustmentEventDetailsBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const AdjustmentEventDetails &source);
};

typedef AdjustmentEventDetails *AdjustmentEventDetailsP;

OSG_END_NAMESPACE

#include "OSGAdjustmentEventDetailsBase.inl"
#include "OSGAdjustmentEventDetails.inl"

#endif /* _OSGADJUSTMENTEVENTDETAILS_H_ */
