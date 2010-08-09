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

#ifndef _OSGFIELDCONTAINEREDITORCOMPONENT_H_
#define _OSGFIELDCONTAINEREDITORCOMPONENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGFieldContainerEditorComponentBase.h"
#include "OSGCommandManager.h"
#include "OSGFieldEditorComponent.h"

OSG_BEGIN_NAMESPACE

/*! \brief FieldContainerEditorComponent class. See \ref
           PageContribFieldContainerEditorFieldContainerEditorComponent for a description.
*/

class OSG_CONTRIBFIELDCONTAINEREDITOR_DLLMAPPING FieldContainerEditorComponent : public FieldContainerEditorComponentBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef FieldContainerEditorComponentBase Inherited;
    typedef FieldContainerEditorComponent     Self;

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

    virtual const std::vector<const FieldContainerType*>& getEditableTypes(void) const = 0;
    bool isTypeEditable(const FieldContainerType& type) const;

    virtual bool attachFieldContainer(FieldContainer* fc);
    virtual bool dettachFieldContainer(void);
    FieldContainer* getAttachedFieldContainer(void) const;

    virtual void              setCommandManager(CommandManagerPtr manager);
    CommandManagerPtr getCommandManager(void                     ) const;

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in FieldContainerEditorComponentBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    FieldContainerEditorComponent(void);
    FieldContainerEditorComponent(const FieldContainerEditorComponent &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~FieldContainerEditorComponent(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

    CommandManagerPtr _CmdManager;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class FieldContainerEditorComponentBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const FieldContainerEditorComponent &source);
};

typedef FieldContainerEditorComponent *FieldContainerEditorComponentP;

OSG_END_NAMESPACE

#include "OSGFieldContainerEditorComponentBase.inl"
#include "OSGFieldContainerEditorComponent.inl"

#endif /* _OSGFIELDCONTAINEREDITORCOMPONENT_H_ */
