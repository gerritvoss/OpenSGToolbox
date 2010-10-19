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
#include "styleddocumentattributes.h"

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

	virtual bool isA(std::string) = 0;

	    //Registers the given observer to begin receiving notifications when changes are made to the document.
    virtual EventConnection addDocumentListener(DocumentListenerPtr Listener);

	virtual bool isDocumentListenerAttached(DocumentListenerPtr Listener) const;

    //Unregisters the given observer from the notification list so it will no longer receive change updates.
    virtual void removeDocumentListener(DocumentListenerPtr Listener);

    //Registers the given observer to begin receiving notifications when undoable edits are made to the document.
    virtual EventConnection addUndoableEditListener(UndoableEditListenerPtr Listener);

	virtual bool isUndoableEditListenerAttached(UndoableEditListenerPtr Listener) const;

    //Unregisters the given observer from the notification list so it will no longer receive updates.
    virtual void removeUndoableEditListener(UndoableEditListenerPtr Listener);


    //This method allows an application to mark a place in a sequence of character content.
    virtual UInt32 createPosition(Int32 offs) = 0 ;

    //Returns the root element that views should be based upon, unless some other mechanism for assigning views to element structures is provided.
    virtual ElementRefPtr getDefaultRootElement(void) const = 0;

    //Returns a position that represents the end of the document.
    virtual UInt32 getEndPosition(void) const = 0;

    //Returns number of characters of content currently in the document.
    virtual UInt32 getLength(void) const = 0;

    //Gets the properties associated with the document.
    //virtual UInt32 getProperty(const std::string& key) const;

    //Returns all of the root elements that are defined.
    virtual std::vector<ElementRefPtr> getRootElements(void) = 0;

    //Returns a position that represents the start of the document.
    virtual UInt64 getStartPosition(void) const = 0;

    //Fetches the text contained within the given portion of the document.
    virtual std::string getText(Int32 offset, Int32 length) const = 0;

    //Fetches the text contained within the given portion of the document.
    virtual void getText(Int32 offset, Int32 length, std::string& txt) const = 0;

	virtual void deleteCharacter(UInt32 elementIndex,UInt32 offsetInChild) = 0;

	virtual void addTextAsNewElementToDocument(const std::string& str, TextWithProps& properties,bool createFreshDocument) = 0;

    //Inserts a string of content.
    virtual void insertString(UInt32 offset, const std::string& str, TextWithProps& properties) = 0;

	virtual void insertCharacter(UInt32 offset, const char character, TextWithProps& properties) = 0;

	virtual void insertCharacter(UInt32 offsetInElement,UInt32 elementIndex, const char character, TextWithProps& properties) = 0;

	virtual void deleteCharacters(UInt32 lesserIndex,UInt32 lesserOffset,UInt32 greaterIndex,UInt32 greaterOffset)=0;
    //Associates a property with the document.
    //virtual void putProperty(const std::string& key, UInt32 value);

    //Removes a portion of the content of the document.
    virtual void remove(Int32 offs, Int32 len) = 0;

    //Gets the asynchronous loading priority.
    //int getAsynchronousLoadPriority(void);

    //Returns the root element of the bidirectional structure for this document.
    //Element getBidiRootElement(void);

    //Returns the DocumentFilter that is responsible for filtering of insertion/removal.
    //DocumentFilter getDocumentFilter(void);

    //Supports managing a set of properties.
    //const std::map<std::string,UInt32>& getDocumentProperties(void) const;

    //Get the paragraph element containing the given position.
    //virtual  ElementRefPtr getParagraphElement(UInt32 pos) const;

    //Acquires a lock to begin reading some state from the document.
    //void readLock(void);

    //Does a read unlock.
    //void readUnlock(void);

    //Deletes the region of text from offset to offset + length, and replaces it with text.
    virtual void replace(Int32 offset, Int32 length, const std::string& str, TextWithProps& properties) = 0;

    //Sets the asynchronous loading priority.
    //void setAsynchronousLoadPriority(int p);

    //Sets the DocumentFilter.
    //void setDocumentFilter(DocumentFilter filter);

    //Replaces the document properties dictionary for this document.
    //void setDocumentProperties(const std::map<std::string,UInt32>& properties);

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

	    //Creates a document branch element, that can contain other elements.
    //ElementRefPtr createBranchElement(ElementRefPtr parent, const std::map<std::string,UInt32>& a) const;

    //Creates a document leaf element.
    //ElementRefPtr createLeafElement(ElementRefPtr parent, const std::map<std::string,UInt32>& a, Int32 p0, Int32 p1) const;

    //Notifies all listeners that have registered interest for notification on this event type.
    virtual void produceChangedUpdate(const DocumentEventP e);

    //Notifies all listeners that have registered interest for notification on this event type.
    virtual void produceInsertUpdate(const DocumentEventP e);

    //Notifies all listeners that have registered interest for notification on this event type.
    virtual void produceRemoveUpdate(const DocumentEventP e);

    //Notifies all listeners that have registered interest for notification on this event type.
    virtual void produceUndoableEditHappened(const UndoableEditEventUnrecPtr e);

    //Fetches the context for managing attributes.
    //AbstractDocument.AttributeContext getAttributeContext(void) const;

    //Gets the content for the document.
    //AbstractDocument.Content getContent(void) const;

    //Fetches the current writing thread if there is one.
    //Thread getCurrentWriter(void);

    //Updates document structure as a result of text insertion.
    //void insertUpdate(AbstractDocument.DefaultDocumentEvent chng, AttributeSet attr);

    //Updates any document structure as a result of text removal.
    //void postRemoveUpdate(AbstractDocument.DefaultDocumentEvent chng);

    //Updates any document structure as a result of text removal.
    //void removeUpdate(AbstractDocument.DefaultDocumentEvent chng);

    //Acquires a lock to begin mutating the document this lock protects.
    //void writeLock(void);

    //Releases a write lock previously obtained via writeLock.
    //void writeUnlock(void);
    
	typedef std::set<DocumentListenerPtr> DocumentListenerSet;
    typedef DocumentListenerSet::iterator DocumentListenerSetItor;
    typedef DocumentListenerSet::const_iterator DocumentListenerSetConstItor;
	
    DocumentListenerSet       _DocumentListeners;

	typedef std::set<UndoableEditListenerPtr> UndoableEditListenerSet;
    typedef UndoableEditListenerSet::iterator UndoableEditListenerSetItor;
    typedef UndoableEditListenerSet::const_iterator UndoableEditListenerSetConstItor;
	
    UndoableEditListenerSet       _UndoableEditListeners;
    
    /*! \}                                                                 */
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
