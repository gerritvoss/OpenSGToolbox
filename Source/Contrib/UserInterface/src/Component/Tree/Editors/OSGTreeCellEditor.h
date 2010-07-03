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

#ifndef _OSGTREECELLEDITOR_H_
#define _OSGTREECELLEDITOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTreeCellEditorBase.h"
#include <Component/Tree/OSGTreeFields.h>

OSG_BEGIN_NAMESPACE

/*! \brief TreeCellEditor class. See \ref
           PageContribUserInterfaceTreeCellEditor for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING TreeCellEditor : public TreeCellEditorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef TreeCellEditorBase Inherited;
    typedef TreeCellEditor     Self;

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

    // Variables should all be in TreeCellEditorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TreeCellEditor(void);
    TreeCellEditor(const TreeCellEditor &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TreeCellEditor(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

	virtual ComponentTransitPtr getTreeCellEditorComponent(Tree* const TheTree,
                                                       const boost::any& Value,
                                                       bool IsSelected,
                                                       bool IsExpanded,
                                                       UInt32 row) = 0;
    
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class TreeCellEditorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TreeCellEditor &source);
};

typedef TreeCellEditor *TreeCellEditorP;

OSG_END_NAMESPACE

#include "OSGTreeCellEditorBase.inl"
#include "OSGTreeCellEditor.inl"

#endif /* _OSGTREECELLEDITOR_H_ */
