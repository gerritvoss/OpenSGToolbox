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

#ifndef _OSGLISTCOMPONENTGENERATOR_H_
#define _OSGLISTCOMPONENTGENERATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGListComponentGeneratorBase.h"
#include "OSGListFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief ListComponentGenerator class. See \ref
           PageContribUserInterfaceListComponentGenerator for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING ListComponentGenerator : public ListComponentGeneratorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ListComponentGeneratorBase Inherited;
    typedef ListComponentGenerator     Self;

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

	virtual ComponentTransitPtr getComponent(Component* const Parent, const boost::any& Value, Int32 PrimaryAxisIndex, Int32 SecondaryAxisIndex, bool IsSelected, bool HasFocus);

	virtual ComponentTransitPtr getListComponent(List* const Parent, const boost::any& Value, UInt32 Index, bool IsSelected, bool HasFocus) = 0;

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in ListComponentGeneratorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ListComponentGenerator(void);
    ListComponentGenerator(const ListComponentGenerator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ListComponentGenerator(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ListComponentGeneratorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const ListComponentGenerator &source);
};

typedef ListComponentGenerator *ListComponentGeneratorP;

OSG_END_NAMESPACE

#include "OSGListComponentGeneratorBase.inl"
#include "OSGListComponentGenerator.inl"

#endif /* _OSGLISTCOMPONENTGENERATOR_H_ */
