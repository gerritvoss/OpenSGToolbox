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

#ifndef _OSGCOMBOBOXCOMPONENTGENERATOR_H_
#define _OSGCOMBOBOXCOMPONENTGENERATOR_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGComboBoxComponentGeneratorBase.h"
#include "Component/ComboBox/OSGComboBoxFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief ComboBoxComponentGenerator class. See \ref 
           PageUserInterfaceComboBoxComponentGenerator for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING ComboBoxComponentGenerator : public ComboBoxComponentGeneratorBase
{
  private:

    typedef ComboBoxComponentGeneratorBase Inherited;

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
	virtual ComponentPtr getComboBoxComponent(ComboBoxPtr Parent, const boost::any& Value, UInt32 Index, bool IsSelected, bool HasFocus) = 0;

	virtual ComponentPtr getComponent(ComponentPtr Parent, const boost::any& Value, Int32 PrimaryAxisIndex, Int32 SecondaryAxisIndex, bool IsSelected, bool HasFocus);

    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in ComboBoxComponentGeneratorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ComboBoxComponentGenerator(void);
    ComboBoxComponentGenerator(const ComboBoxComponentGenerator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ComboBoxComponentGenerator(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ComboBoxComponentGeneratorBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const ComboBoxComponentGenerator &source);
};

typedef ComboBoxComponentGenerator *ComboBoxComponentGeneratorP;

OSG_END_NAMESPACE

#include "OSGComboBoxComponentGeneratorBase.inl"
#include "OSGComboBoxComponentGenerator.inl"

#define OSGCOMBOBOXCOMPONENTGENERATOR_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGCOMBOBOXCOMPONENTGENERATOR_H_ */
