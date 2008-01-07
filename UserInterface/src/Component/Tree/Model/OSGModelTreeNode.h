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

#ifndef _OSGMODELTREENODE_H_
#define _OSGMODELTREENODE_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGModelTreeNodeBase.h"
#include "Component/Tree/OSGTreePath.h"
#include <OpenSG/Toolbox/OSGSharedFieldPtr.h>
#include <vector>

OSG_BEGIN_NAMESPACE

/*! \brief ModelTreeNode class. See \ref 
           PageUserInterfaceModelTreeNode for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING ModelTreeNode : public ModelTreeNodeBase
{
  private:

    typedef ModelTreeNodeBase Inherited;

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
	
	//Returns the children of the receiver as a Vector.
    virtual std::vector<ModelTreeNodePtr> getChildren(void) const;

	//Returns true if the receiver allows children.
	virtual bool getAllowsChildren(void) const = 0;

	//Returns the child ModelTreeNode at index childIndex.
	virtual ModelTreeNodePtr getChildAt(const UInt32& childIndex) const = 0;

	//Returns the number of children ModelTreeNodes the receiver contains.
	virtual UInt32 getChildCount(void) const = 0;

	//Returns the index of node in the receivers children.
	virtual Int32 getIndex(ModelTreeNodePtr node) const = 0;

	//Returns the parent ModelTreeNode of the receiver.
	virtual ModelTreeNodePtr getParent(void) const = 0;

	//Returns true if the receiver is a leaf.
	virtual bool isLeaf(void) const = 0;

	//Resets the user object of the receiver to object.
	virtual void setUserObject(SharedFieldPtr object) = 0;
    
	//Returns this node's user object.
	virtual SharedFieldPtr getUserObject(void) const = 0;
    
    //Find the decendent node that uses object as it's UserObject
    ModelTreeNodePtr getNodeFromUserObject(SharedFieldPtr object);

    //Get the Path from the Root to this node
    TreePath getPath(void) const;
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in ModelTreeNodeBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ModelTreeNode(void);
    ModelTreeNode(const ModelTreeNode &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ModelTreeNode(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ModelTreeNodeBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const ModelTreeNode &source);
};

typedef ModelTreeNode *ModelTreeNodeP;

OSG_END_NAMESPACE

#include "OSGModelTreeNodeBase.inl"
#include "OSGModelTreeNode.inl"

#define OSGMODELTREENODE_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGMODELTREENODE_H_ */
