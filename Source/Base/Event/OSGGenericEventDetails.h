/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  Robert Goetz                                                  *
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

#ifndef _OSGGENERICEVENTDETAILS_H_
#define _OSGGENERICEVENTDETAILS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGGenericEventDetailsBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief GenericEventDetails class. See \ref
           PageBaseGenericEventDetails for a description.
*/

class OSG_BASE_DLLMAPPING GenericEventDetails : public GenericEventDetailsBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef GenericEventDetailsBase Inherited;
    typedef GenericEventDetails     Self;

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

    static GenericEventDetailsTransitPtr create(   FieldContainerRefPtr Source,
                                            Time TimeStamp,
                                            const StringToUInt32Map& strToIntMap = StringToUInt32Map(),
                                            const FieldContainerMap& fcMap = FieldContainerMap());

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in GenericEventDetailsBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    GenericEventDetails(void);
    GenericEventDetails(const GenericEventDetails &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~GenericEventDetails(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class GenericEventDetailsBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const GenericEventDetails &source);
};

typedef GenericEventDetails *GenericEventDetailsP;

OSG_END_NAMESPACE

#include "OSGGenericEventDetailsBase.inl"
#include "OSGGenericEventDetails.inl"

#endif /* _OSGGENERICEVENTDETAILS_H_ */
