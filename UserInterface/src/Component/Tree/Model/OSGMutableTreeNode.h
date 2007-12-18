/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
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

#ifndef _OSGMUTABLETREENODE_H_
#define _OSGMUTABLETREENODE_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGMutableTreeNodeBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief MutableTreeNode class. See \ref 
           PageUserInterfaceMutableTreeNode for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING MutableTreeNode : public MutableTreeNodeBase
{
  private:

    typedef MutableTreeNodeBase Inherited;

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
	
	//Adds child to the receiver at index.
	virtual void insert(MutableTreeNodePtr child, const UInt32& index) = 0;

	//Removes the child at index from the receiver.
	virtual void remove(const UInt32& index) = 0;

	//Removes node from the receiver.
	virtual void remove(MutableTreeNodePtr node) = 0;

	//Removes the receiver from its parent.
	virtual void removeFromParent(void) = 0;

	//Sets the parent of the receiver to newParent.
	virtual void setParent(MutableTreeNodePtr newParent) = 0;

    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in MutableTreeNodeBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    MutableTreeNode(void);
    MutableTreeNode(const MutableTreeNode &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MutableTreeNode(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class MutableTreeNodeBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const MutableTreeNode &source);
};

typedef MutableTreeNode *MutableTreeNodeP;

OSG_END_NAMESPACE

#include "OSGMutableTreeNodeBase.inl"
#include "OSGMutableTreeNode.inl"

#define OSGMUTABLETREENODE_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGMUTABLETREENODE_H_ */
