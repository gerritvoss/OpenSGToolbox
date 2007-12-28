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

#ifndef _OSGTREECOMPONENTGENERATOR_H_
#define _OSGTREECOMPONENTGENERATOR_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGTreeComponentGeneratorBase.h"
#include "Component/Tree/OSGTreeFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief TreeComponentGenerator class. See \ref 
           PageUserInterfaceTreeComponentGenerator for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING TreeComponentGenerator : public TreeComponentGeneratorBase
{
  private:

    typedef TreeComponentGeneratorBase Inherited;

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
    
	virtual ComponentPtr getTreeComponent(TreePtr Parent, SharedFieldPtr Value, bool IsSelected, bool Expanded, bool Leaf, UInt32 Row, bool HasFocus) = 0;
    
	virtual ComponentPtr getComponent(ComponentPtr Parent, SharedFieldPtr Value, bool IsSelected, bool HasFocus);
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
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class TreeComponentGeneratorBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const TreeComponentGenerator &source);
};

typedef TreeComponentGenerator *TreeComponentGeneratorP;

OSG_END_NAMESPACE

#include "OSGTreeComponentGeneratorBase.inl"
#include "OSGTreeComponentGenerator.inl"

#define OSGTREECOMPONENTGENERATOR_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGTREECOMPONENTGENERATOR_H_ */
