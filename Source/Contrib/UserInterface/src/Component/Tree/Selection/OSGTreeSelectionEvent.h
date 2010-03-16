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

#ifndef _OSGTREESELECTIONEVENT_H_
#define _OSGTREESELECTIONEVENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTreeSelectionEventBase.h"
#include "OSGNumberRangeSet.h"

OSG_BEGIN_NAMESPACE

/*! \brief TreeSelectionEvent class. See \ref
           PageContribUserInterfaceTreeSelectionEvent for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING TreeSelectionEvent : public TreeSelectionEventBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef TreeSelectionEventBase Inherited;
    typedef TreeSelectionEvent     Self;

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

    static  TreeSelectionEventTransitPtr      create(  FieldContainerRefPtr Source,
                                                       Time TimeStamp,
                                                       const std::vector<NumberRange>& ElementsChanged,
                                                       Int32 NewLeadSelectionPath,
                                                       Int32 OldLeadSelectionPath); 

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in TreeSelectionEventBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TreeSelectionEvent(void);
    TreeSelectionEvent(const TreeSelectionEvent &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TreeSelectionEvent(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class TreeSelectionEventBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TreeSelectionEvent &source);
};

typedef TreeSelectionEvent *TreeSelectionEventP;

OSG_END_NAMESPACE

#include "OSGTreeSelectionEventBase.inl"
#include "OSGTreeSelectionEvent.inl"

#endif /* _OSGTREESELECTIONEVENT_H_ */
