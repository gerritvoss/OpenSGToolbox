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

#ifndef _OSGDEFAULTLISTCOMPONENTGENERATOR_H_
#define _OSGDEFAULTLISTCOMPONENTGENERATOR_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGDefaultListComponentGeneratorBase.h"
#include "Component/Text/OSGTextComponent.h"

OSG_BEGIN_NAMESPACE

/*! \brief DefaultListComponentGenerator class. See \ref 
           PageUserInterfaceDefaultListComponentGenerator for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING DefaultListComponentGenerator : public DefaultListComponentGeneratorBase
{
  private:

    typedef DefaultListComponentGeneratorBase Inherited;

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
	
	virtual ComponentPtr getListComponent(ListPtr Parent, const boost::any& Value, UInt32 Index, bool IsSelected, bool HasFocus);
	virtual ComponentPtr getListComponent(ListPtr Parent, std::string& Value, UInt32 Index, bool IsSelected, bool HasFocus);

    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in DefaultListComponentGeneratorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DefaultListComponentGenerator(void);
    DefaultListComponentGenerator(const DefaultListComponentGenerator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DefaultListComponentGenerator(void); 

    /*! \}                                                                 */
	virtual void applyBordersAndBackground(ComponentPtr TheComponent, ListPtr Parent, std::string& Value, UInt32 Index, bool IsSelected, bool HasFocus) const;
	virtual void applyTextColor(TextComponentPtr TheComponent, ListPtr Parent, std::string& Value, UInt32 Index, bool IsSelected, bool HasFocus) const;
    virtual std::string getText(ListPtr Parent, const boost::any& Value, UInt32 Index, bool IsSelected, bool HasFocus) const;

    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class DefaultListComponentGeneratorBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const DefaultListComponentGenerator &source);
};

typedef DefaultListComponentGenerator *DefaultListComponentGeneratorP;

OSG_END_NAMESPACE

#include "OSGDefaultListComponentGeneratorBase.inl"
#include "OSGDefaultListComponentGenerator.inl"

#define OSGDEFAULTLISTCOMPONENTGENERATOR_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGDEFAULTLISTCOMPONENTGENERATOR_H_ */
