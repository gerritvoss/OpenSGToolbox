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

#ifndef _OSGSKELETONEVENTDETAILS_H_
#define _OSGSKELETONEVENTDETAILS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSkeletonEventDetailsBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief SkeletonEventDetails class. See \ref
           PageDynamicsSkeletonEventDetails for a description.
*/

class OSG_TBANIMATION_DLLMAPPING SkeletonEventDetails : public SkeletonEventDetailsBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef SkeletonEventDetailsBase Inherited;
    typedef SkeletonEventDetails     Self;

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
    static  SkeletonEventDetailsTransitPtr      create( FieldContainer* const Source,
                                                        Time TimeStamp); 
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in SkeletonEventDetailsBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SkeletonEventDetails(void);
    SkeletonEventDetails(const SkeletonEventDetails &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SkeletonEventDetails(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SkeletonEventDetailsBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SkeletonEventDetails &source);
};

typedef SkeletonEventDetails *SkeletonEventDetailsP;

OSG_END_NAMESPACE

#include "OSGSkeletonEventDetailsBase.inl"
#include "OSGSkeletonEventDetails.inl"

#endif /* _OSGSKELETONEVENTDETAILS_H_ */
