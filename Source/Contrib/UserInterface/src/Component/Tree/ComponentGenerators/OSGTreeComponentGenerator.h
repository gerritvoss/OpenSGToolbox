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

#ifndef _OSGTREECOMPONENTGENERATOR_H_
#define _OSGTREECOMPONENTGENERATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTreeComponentGeneratorBase.h"
#include "OSGTreeFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief TreeComponentGenerator class. See \ref
           PageContribUserInterfaceTreeComponentGenerator for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING TreeComponentGenerator : public TreeComponentGeneratorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef TreeComponentGeneratorBase Inherited;
    typedef TreeComponentGenerator     Self;

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

    virtual ComponentTransitPtr getTreeExpandedComponent(Tree* const Parent,
                                                     const boost::any& Value,
                                                     bool IsSelected,
                                                     bool Expanded,
                                                     bool Leaf,
                                                     UInt32 Row,
                                                     bool HasFocus) = 0;
    
	virtual ComponentTransitPtr getTreeComponent(Tree* const Parent,
                                             const boost::any& Value,
                                             bool IsSelected,
                                             bool Expanded,
                                             bool Leaf,
                                             UInt32 Row,
                                             bool HasFocus) = 0;
    
	virtual ComponentTransitPtr getComponent(Component* const Parent,
                                         const boost::any& Value,
                                         Int32 PrimaryAxisIndex,
                                         Int32 SecondaryAxisIndex,
                                         bool IsSelected,
                                         bool HasFocus);
    
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in TreeComponentGeneratorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TreeComponentGenerator(void);
    TreeComponentGenerator(const TreeComponentGenerator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TreeComponentGenerator(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class TreeComponentGeneratorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TreeComponentGenerator &source);
};

typedef TreeComponentGenerator *TreeComponentGeneratorP;

OSG_END_NAMESPACE

#include "OSGTreeComponentGeneratorBase.inl"
#include "OSGTreeComponentGenerator.inl"

#endif /* _OSGTREECOMPONENTGENERATOR_H_ */
