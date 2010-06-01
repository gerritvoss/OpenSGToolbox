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

#ifndef _OSGABSTRACTDOCUMENT_H_
#define _OSGABSTRACTDOCUMENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGAbstractDocumentBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief AbstractDocument class. See \ref
           PageContribTextDomAbstractDocument for a description.
*/

class OSG_CONTRIBTEXTDOM_DLLMAPPING AbstractDocument : public AbstractDocumentBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef AbstractDocumentBase Inherited;
    typedef AbstractDocument     Self;

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

    //Registers the given observer to begin receiving notifications when changes are made to the document.
    virtual EventConnection addDocumentListener(DocumentListenerPtr Listener);
    virtual void removeDocumentListener(DocumentListenerPtr Listener);
    virtual bool isDocumentListenerAttached(DocumentListenerPtr Listener) const;

    //Registers the given observer to begin receiving notifications when undoable edits are made to the document.
    virtual EventConnection addUndoableEditListener(UndoableEditListenerPtr Listener);
    virtual void removeUndoableEditListener(UndoableEditListenerPtr Listener);
    virtual bool isUndoableEditListenerAttached(UndoableEditListenerPtr Listener) const;
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in AbstractDocumentBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    AbstractDocument(void);
    AbstractDocument(const AbstractDocument &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~AbstractDocument(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	
	typedef std::set<DocumentListenerPtr> DocumentListenerSet;
    typedef DocumentListenerSet::iterator DocumentListenerSetItor;
    typedef DocumentListenerSet::const_iterator DocumentListenerSetConstItor;
	
    DocumentListenerSet       _DocumentListeners;
    
    void produceChangedUpdate(const DocumentEventUnrecPtr e);
    void produceInsertUpdate(const DocumentEventUnrecPtr e);
    void produceRemoveUpdate(const DocumentEventUnrecPtr e);
	
	typedef std::set<UndoableEditListenerPtr> UndoableEditListenerSet;
    typedef UndoableEditListenerSet::iterator UndoableEditListenerSetItor;
    typedef UndoableEditListenerSet::const_iterator UndoableEditListenerSetConstItor;
	
    UndoableEditListenerSet       _UndoableEditListeners;

    void produceUndoableEditHappened(const UndoableEditEventUnrecPtr e);
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class AbstractDocumentBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const AbstractDocument &source);
};

typedef AbstractDocument *AbstractDocumentP;

OSG_END_NAMESPACE

#include "OSGAbstractDocumentBase.inl"
#include "OSGAbstractDocument.inl"

#endif /* _OSGABSTRACTDOCUMENT_H_ */
