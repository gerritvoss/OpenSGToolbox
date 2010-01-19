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

#ifndef _OSGCOMPONENTTREEMODEL_H_
#define _OSGCOMPONENTTREEMODEL_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGComponentTreeModelBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief ComponentTreeModel class. See \ref 
           PageUserInterfaceComponentTreeModel for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING ComponentTreeModel : public ComponentTreeModelBase
{
  private:

    typedef ComponentTreeModelBase Inherited;

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
	//Returns the child of parent at index index in the parent's child array.
	virtual boost::any getChild(const boost::any& parent, const UInt32& index) const;

	//Returns the number of children of parent.
	virtual UInt32 getChildCount(const boost::any& parent) const;

	//Returns the index of child in parent.
	virtual UInt32 getIndexOfChild(const boost::any& parent, const boost::any& child) const;

	//Returns the root of the tree.
	virtual boost::any getRoot(void) const;

	//Returns true if node is a leaf.
	virtual bool isLeaf(const boost::any& node) const;
    
    //Returns the Parent of this node
    virtual boost::any getParent(const boost::any& node) const;

	//Messaged when the user has altered the value for the item identified by path to newValue.
	virtual void valueForPathChanged(TreePath path, const boost::any& newValue);

    //Sets the root to root.
    void setRoot(ComponentPtr root);

    //Get the NodePtr to the Root Node
    ComponentPtr getRootComponent(void) const;

    //Returns true if these objects represent the same node in the tree
    virtual bool isEqual(const boost::any& left, const boost::any& right) const;
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in ComponentTreeModelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ComponentTreeModel(void);
    ComponentTreeModel(const ComponentTreeModel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ComponentTreeModel(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ComponentTreeModelBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const ComponentTreeModel &source);
};

typedef ComponentTreeModel *ComponentTreeModelP;

OSG_END_NAMESPACE

#include "OSGComponentTreeModelBase.inl"
#include "OSGComponentTreeModel.inl"

#endif /* _OSGCOMPONENTTREEMODEL_H_ */
