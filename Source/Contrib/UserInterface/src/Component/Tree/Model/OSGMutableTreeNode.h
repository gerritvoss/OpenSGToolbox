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

#ifndef _OSGMUTABLETREENODE_H_
#define _OSGMUTABLETREENODE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGMutableTreeNodeBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief MutableTreeNode class. See \ref
           PageContribUserInterfaceMutableTreeNode for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING MutableTreeNode : public MutableTreeNodeBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef MutableTreeNodeBase Inherited;
    typedef MutableTreeNode     Self;

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
	
	//Adds child to the receiver at index.
	virtual void insert(MutableTreeNode* const child, const UInt32& index) = 0;

	//Removes the child at index from the receiver.
	virtual void remove(const UInt32& index) = 0;

	//Removes node from the receiver.
	virtual void remove(MutableTreeNode* const node) = 0;

	//Removes the receiver from its parent.
	virtual void removeFromParent(void) = 0;

	//Sets the parent of the receiver to newParent.
	virtual void setParent(MutableTreeNode* const newParent) = 0;

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
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class MutableTreeNodeBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const MutableTreeNode &source);
};

typedef MutableTreeNode *MutableTreeNodeP;

OSG_END_NAMESPACE

#include "OSGMutableTreeNodeBase.inl"
#include "OSGMutableTreeNode.inl"

#endif /* _OSGMUTABLETREENODE_H_ */
