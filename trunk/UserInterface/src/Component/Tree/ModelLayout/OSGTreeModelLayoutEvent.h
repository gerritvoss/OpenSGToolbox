/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala                            *
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

#include <OpenSG/OSGConfig.h>

#include "OSGTreeModelLayoutEventBase.h"
#include "Component/Tree/OSGTreePath.h"

OSG_BEGIN_NAMESPACE

/*! \brief TreeModelLayoutEvent class. See \ref 
           PageUserInterfaceTreeModelLayoutEvent for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING TreeModelLayoutEvent : public TreeModelLayoutEventBase
{
  private:

    typedef TreeModelLayoutEventBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         UInt32     origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */

    static  TreeModelLayoutEventPtr      create(  FieldContainerPtr Source,
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
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class TreeModelLayoutEventBase;

    TreePath _Path;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const TreeModelLayoutEvent &source);
};

typedef TreeModelLayoutEvent *TreeModelLayoutEventP;

OSG_END_NAMESPACE

#include "OSGTreeModelLayoutEventBase.inl"
#include "OSGTreeModelLayoutEvent.inl"

#endif /* _OSGTREEMODELLAYOUTEVENT_H_ */
