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

#ifndef _OSGSINGLEFIELDEDITORCOMPONENT_H_
#define _OSGSINGLEFIELDEDITORCOMPONENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSingleFieldEditorComponentBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief SingleFieldEditorComponent class. See \ref
           PageContribFieldContainerEditorSingleFieldEditorComponent for a description.
*/

class OSG_CONTRIBFIELDCONTAINEREDITOR_DLLMAPPING SingleFieldEditorComponent : public SingleFieldEditorComponentBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef SingleFieldEditorComponentBase Inherited;
    typedef SingleFieldEditorComponent     Self;

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

    // Variables should all be in SingleFieldEditorComponentBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SingleFieldEditorComponent(void);
    SingleFieldEditorComponent(const SingleFieldEditorComponent &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SingleFieldEditorComponent(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    virtual bool internalAttachField (FieldContainer* fc, UInt32 fieldId, UInt32 index);
    virtual bool internalDettachField(void);
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SingleFieldEditorComponentBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SingleFieldEditorComponent &source);
};

typedef SingleFieldEditorComponent *SingleFieldEditorComponentP;

OSG_END_NAMESPACE

#include "OSGSingleFieldEditorComponentBase.inl"
#include "OSGSingleFieldEditorComponent.inl"

#endif /* _OSGSINGLEFIELDEDITORCOMPONENT_H_ */
