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

#ifndef _OSGTREENODE_H_
#define _OSGTREENODE_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGTreeNodeBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief TreeNode class. See \ref 
           PageUserInterfaceTreeNode for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING TreeNode : public TreeNodeBase
{
  private:

    typedef TreeNodeBase Inherited;

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
	
	//Returns the children of the receiver as an Enumeration.
	//virtual Enumeration children(void) const = 0;

	//Returns true if the receiver allows children.
	virtual bool getAllowsChildren(void) const = 0;

	//Returns the child TreeNode at index childIndex.
	virtual TreeNodePtr getChildAt(const UInt32& childIndex) const = 0;

	//Returns the number of children TreeNodes the receiver contains.
	virtual UInt32 getChildCount(void) const = 0;

	//Returns the index of node in the receivers children.
	virtual Int32 getIndex(TreeNodePtr node) const = 0;

	//Returns the parent TreeNode of the receiver.
	virtual TreeNodePtr getParent(void) const = 0;

	//Returns true if the receiver is a leaf.
	virtual bool isLeaf(void) const = 0;

    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in TreeNodeBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TreeNode(void);
    TreeNode(const TreeNode &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TreeNode(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class TreeNodeBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const TreeNode &source);
};

typedef TreeNode *TreeNodeP;

OSG_END_NAMESPACE

#include "OSGTreeNodeBase.inl"
#include "OSGTreeNode.inl"

#define OSGTREENODE_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGTREENODE_H_ */
