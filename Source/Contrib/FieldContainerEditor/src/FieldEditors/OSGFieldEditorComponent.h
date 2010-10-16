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

#ifndef _OSGFIELDEDITORCOMPONENT_H_
#define _OSGFIELDEDITORCOMPONENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGFieldEditorComponentBase.h"
#include "OSGCommandManager.h"

OSG_BEGIN_NAMESPACE

/*! \brief FieldEditorComponent class. See \ref
           PageContribFieldContainerEditorFieldEditorComponent for a description.
*/

class OSG_CONTRIBFIELDCONTAINEREDITOR_DLLMAPPING FieldEditorComponent : public FieldEditorComponentBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef FieldEditorComponentBase Inherited;
    typedef FieldEditorComponent     Self;

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

    virtual void startEditing (void);
    virtual void stopEditing  (void);
    virtual void cancelEditing(void);
    virtual bool isEditing    (void) const;

    virtual const std::vector<const DataType*>& getEditableTypes(void) const = 0;
    bool isTypeEditable(const DataType& type) const;

    bool attachField (FieldContainer* fc, UInt32 fieldId, UInt32 index = 0);
    bool dettachField(void);

    void              setCommandManager(CommandManagerPtr manager);
    CommandManagerPtr getCommandManager(void                     ) const;

    virtual UInt32 getNumRequestedRows(void) const = 0;

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in FieldEditorComponentBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    FieldEditorComponent(void);
    FieldEditorComponent(const FieldEditorComponent &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~FieldEditorComponent(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */
            void fieldChanged         (FieldContainer *fc, 
                                       ConstFieldMaskArg whichField);
    virtual void internalFieldChanged (void                        ) = 0;
    virtual void internalStartEditing (void                        ) = 0;
    virtual void internalStopEditing  (void                        ) = 0;
    virtual void internalCancelEditing(void                        ) = 0;

    virtual bool internalAttachField (FieldContainer* fc, UInt32 fieldId, UInt32 index);
    virtual bool internalDettachField(void);


    void attachFieldCallback (void);
    void dettachFieldCallback(void);

    CommandManagerPtr _CmdManager;
    bool              _isEditing;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class FieldEditorComponentBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const FieldEditorComponent &source);
};

typedef FieldEditorComponent *FieldEditorComponentP;

OSG_END_NAMESPACE

#include "OSGFieldEditorComponentBase.inl"
#include "OSGFieldEditorComponent.inl"

#endif /* _OSGFIELDEDITORCOMPONENT_H_ */
