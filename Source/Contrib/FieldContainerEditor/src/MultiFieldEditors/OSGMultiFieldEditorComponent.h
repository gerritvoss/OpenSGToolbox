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

#ifndef _OSGMULTIFIELDEDITORCOMPONENT_H_
#define _OSGMULTIFIELDEDITORCOMPONENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGMultiFieldEditorComponentBase.h"
#include "OSGCommandManager.h"

OSG_BEGIN_NAMESPACE

/*! \brief MultiFieldEditorComponent class. See \ref
           PageContribFieldContainerEditorMultiFieldEditorComponent for a description.
*/

class OSG_CONTRIBFIELDCONTAINEREDITOR_DLLMAPPING MultiFieldEditorComponent : public MultiFieldEditorComponentBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef MultiFieldEditorComponentBase Inherited;
    typedef MultiFieldEditorComponent     Self;

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
    virtual UInt32 getNumRequestedRows(void) const;
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in MultiFieldEditorComponentBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    MultiFieldEditorComponent(void);
    MultiFieldEditorComponent(const MultiFieldEditorComponent &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MultiFieldEditorComponent(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class MultiFieldEditorComponentBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const MultiFieldEditorComponent &source);
};

typedef MultiFieldEditorComponent *MultiFieldEditorComponentP;

OSG_END_NAMESPACE

#include "OSGMultiFieldEditorComponentBase.inl"
#include "OSGMultiFieldEditorComponent.inl"

#endif /* _OSGMULTIFIELDEDITORCOMPONENT_H_ */
