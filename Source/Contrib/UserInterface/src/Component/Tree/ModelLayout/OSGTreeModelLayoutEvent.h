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

#ifndef _OSGTREEMODELLAYOUTEVENT_H_
#define _OSGTREEMODELLAYOUTEVENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTreeModelLayoutEventBase.h"
#include "OSGTreePath.h"

OSG_BEGIN_NAMESPACE

/*! \brief TreeModelLayoutEvent class. See \ref
           PageContribUserInterfaceTreeModelLayoutEvent for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING TreeModelLayoutEvent : public TreeModelLayoutEventBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef TreeModelLayoutEventBase Inherited;
    typedef TreeModelLayoutEvent     Self;

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

    static  TreeModelLayoutEventTransitPtr      create(  FieldContainerRefPtr Source,
                                                         Time TimeStamp,
                                                         const TreePath& path); 

	const TreePath& getPath(void) const;

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in TreeModelLayoutEventBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TreeModelLayoutEvent(void);
    TreeModelLayoutEvent(const TreeModelLayoutEvent &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TreeModelLayoutEvent(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

    TreePath _Path;

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class TreeModelLayoutEventBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TreeModelLayoutEvent &source);
};

typedef TreeModelLayoutEvent *TreeModelLayoutEventP;

OSG_END_NAMESPACE

#include "OSGTreeModelLayoutEventBase.inl"
#include "OSGTreeModelLayoutEvent.inl"

#endif /* _OSGTREEMODELLAYOUTEVENT_H_ */
