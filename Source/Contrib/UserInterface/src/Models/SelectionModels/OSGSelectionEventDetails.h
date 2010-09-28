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

#ifndef _OSGSELECTIONEVENTDETAILS_H_
#define _OSGSELECTIONEVENTDETAILS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSelectionEventDetailsBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief SelectionEventDetails class. See \ref
           PageContribUserInterfaceSelectionEventDetails for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING SelectionEventDetails : public SelectionEventDetailsBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef SelectionEventDetailsBase Inherited;
    typedef SelectionEventDetails     Self;

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

    static  SelectionEventDetailsTransitPtr      create(  FieldContainer* const Source,
                                                   Time TimeStamp,
                                                   const std::vector<UInt32>& Selected,
                                                   const std::vector<UInt32>& PreviouslySelected,
                                                   bool ValueIsAdjusting); 

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in SelectionEventDetailsBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SelectionEventDetails(void);
    SelectionEventDetails(const SelectionEventDetails &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SelectionEventDetails(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SelectionEventDetailsBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SelectionEventDetails &source);
};

typedef SelectionEventDetails *SelectionEventDetailsP;

OSG_END_NAMESPACE

#include "OSGSelectionEventDetailsBase.inl"
#include "OSGSelectionEventDetails.inl"

#endif /* _OSGSELECTIONEVENTDETAILS_H_ */
