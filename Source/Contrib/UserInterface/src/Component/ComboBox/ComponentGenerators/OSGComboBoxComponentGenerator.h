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

#ifndef _OSGCOMBOBOXCOMPONENTGENERATOR_H_
#define _OSGCOMBOBOXCOMPONENTGENERATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGComboBoxComponentGeneratorBase.h"
#include "OSGComboBox.h"

OSG_BEGIN_NAMESPACE

/*! \brief ComboBoxComponentGenerator class. See \ref
           PageContribUserInterfaceComboBoxComponentGenerator for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING ComboBoxComponentGenerator : public ComboBoxComponentGeneratorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ComboBoxComponentGeneratorBase Inherited;
    typedef ComboBoxComponentGenerator     Self;

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

	virtual ComponentTransitPtr getComboBoxComponent(ComboBox* const Parent, const boost::any& Value, UInt32 Index, bool IsSelected, bool HasFocus) = 0;

	virtual ComponentTransitPtr getComponent(Component* const Parent, const boost::any& Value, Int32 PrimaryAxisIndex, Int32 SecondaryAxisIndex, bool IsSelected, bool HasFocus);

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
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ComboBoxComponentGeneratorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ComboBoxComponentGenerator &source);
};

typedef ComboBoxComponentGenerator *ComboBoxComponentGeneratorP;

OSG_END_NAMESPACE

#include "OSGComboBoxComponentGeneratorBase.inl"
#include "OSGComboBoxComponentGenerator.inl"

#endif /* _OSGCOMBOBOXCOMPONENTGENERATOR_H_ */
