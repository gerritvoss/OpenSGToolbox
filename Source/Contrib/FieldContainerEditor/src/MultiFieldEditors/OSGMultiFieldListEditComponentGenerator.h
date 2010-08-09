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

#ifndef _OSGMULTIFIELDLISTEDITCOMPONENTGENERATOR_H_
#define _OSGMULTIFIELDLISTEDITCOMPONENTGENERATOR_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGMultiFieldListEditComponentGeneratorBase.h"
#include "OSGCommandManager.h"
#include "OSGUIDrawingSurfaceFields.h"
#include "OSGDialogWindowEventDetailsFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief MultiFieldListEditComponentGenerator class. See \ref
           PageContribFieldContainerEditorMultiFieldListEditComponentGenerator for a description.
*/

class OSG_CONTRIBFIELDCONTAINEREDITOR_DLLMAPPING MultiFieldListEditComponentGenerator : public MultiFieldListEditComponentGeneratorBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef MultiFieldListEditComponentGeneratorBase Inherited;
    typedef MultiFieldListEditComponentGenerator     Self;

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
	
	virtual ComponentTransitPtr getListComponent(List* const Parent, const boost::any& Value, UInt32 Index, bool IsSelected, bool HasFocus);

    void              setCommandManager(CommandManagerPtr manager);
    CommandManagerPtr getCommandManager(void                     ) const;

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in MultiFieldListEditComponentGeneratorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    MultiFieldListEditComponentGenerator(void);
    MultiFieldListEditComponentGenerator(const MultiFieldListEditComponentGenerator &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~MultiFieldListEditComponentGenerator(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    CommandManagerPtr _CmdManager;

    void handleRemoveButtonAction(EventDetails* const details,
                     FieldContainer* const fc,
                     UInt32 fieldID,
                     UInt32 index);

    void handleInsertButtonAction(EventDetails* const details,
                       FieldContainer* const fc,
                       UInt32 fieldID,
                       UInt32 index);
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class MultiFieldListEditComponentGeneratorBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const MultiFieldListEditComponentGenerator &source);
};

typedef MultiFieldListEditComponentGenerator *MultiFieldListEditComponentGeneratorP;

OSG_END_NAMESPACE

#include "OSGMultiFieldListEditComponentGeneratorBase.inl"
#include "OSGMultiFieldListEditComponentGenerator.inl"

#endif /* _OSGMULTIFIELDLISTEDITCOMPONENTGENERATOR_H_ */
