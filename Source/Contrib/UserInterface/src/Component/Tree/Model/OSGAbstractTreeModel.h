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

#ifndef _OSGABSTRACTTREEMODEL_H_
#define _OSGABSTRACTTREEMODEL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGAbstractTreeModelBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief AbstractTreeModel class. See \ref
           PageContribUserInterfaceAbstractTreeModel for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING AbstractTreeModel : public AbstractTreeModelBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef AbstractTreeModelBase Inherited;
    typedef AbstractTreeModel     Self;

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
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in AbstractTreeModelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    AbstractTreeModel(void);
    AbstractTreeModel(const AbstractTreeModel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~AbstractTreeModel(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

	void produceTreeNodesChanged(TreePath Parent, const std::vector<UInt32>& ChildIndices, const std::vector<boost::any>& Children);
	void produceTreeNodesInserted(TreePath Parent, const std::vector<UInt32>& ChildIndices, const std::vector<boost::any>& Children);
	void produceTreeNodesRemoved(TreePath Parent, const std::vector<UInt32>& ChildIndices, const std::vector<boost::any>& Children);
	void produceTreeNodesWillBeRemoved(TreePath Parent, const std::vector<UInt32>& ChildIndices, const std::vector<boost::any>& Children);
	void produceTreeStructureChanged(TreePath Parent, const std::vector<UInt32>& ChildIndices, const std::vector<boost::any>& Children);
    
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class AbstractTreeModelBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const AbstractTreeModel &source);
};

typedef AbstractTreeModel *AbstractTreeModelP;

OSG_END_NAMESPACE

#include "OSGAbstractTreeModelBase.inl"
#include "OSGAbstractTreeModel.inl"

#endif /* _OSGABSTRACTTREEMODEL_H_ */
