/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala                            *
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

#include <OpenSG/OSGConfig.h>
#include <set>

#include "OSGAbstractDocumentBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief AbstractDocument class. See \ref 
           PageUserInterfaceAbstractDocument for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING AbstractDocument : public AbstractDocumentBase
{
  private:

    typedef AbstractDocumentBase Inherited;

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
    virtual UInt32 createPosition(Int32 offs);

    //Returns the root element that views should be based upon, unless some other mechanism for assigning views to element structures is provided.
    virtual ElementPtr getDefaultRootElement(void) const;

    //Returns a position that represents the end of the document.
    virtual UInt32 getEndPosition(void) const;

    //Returns number of characters of content currently in the document.
    virtual UInt32 getLength(void) const;

    //Gets the properties associated with the document.
    virtual UInt32 getProperty(const std::string& key) const;

    //Returns all of the root elements that are defined.
    virtual std::vector<ElementPtr> getRootElements(void);

    //Returns a position that represents the start of the document.
    virtual UInt64 getStartPosition(void) const;

    //Fetches the text contained within the given portion of the document.
    virtual std::string getText(Int32 offset, UInt32 length) const;

    //Fetches the text contained within the given portion of the document.
    virtual void getText(Int32 offset, UInt32 length, std::string& txt) const;

    //Inserts a string of content.
    virtual void insertString(Int32 offset, const std::string& str, std::map<std::string,UInt32> properties);

    //Associates a property with the document.
    virtual void putProperty(const std::string& key, UInt32 value);

    //Removes a portion of the content of the document.
    virtual void remove(Int32 offs, UInt32 len);

    //Gets the asynchronous loading priority.
    //int getAsynchronousLoadPriority(void);

    //Returns the root element of the bidirectional structure for this document.
    //Element getBidiRootElement(void);

    //Returns the DocumentFilter that is responsible for filtering of insertion/removal.
    //DocumentFilter getDocumentFilter(void);

    //Supports managing a set of properties.
    const std::map<std::string,UInt32>& getDocumentProperties(void) const;

    //Get the paragraph element containing the given position.
    virtual  ElementPtr getParagraphElement(UInt32 pos) const = 0;

    //Acquires a lock to begin reading some state from the document.
    void readLock(void);

    //Does a read unlock.
    void readUnlock(void);

    //Deletes the region of text from offset to offset + length, and replaces it with text.
    void replace(Int32 offset, UInt32 length, const std::string& str, const std::map<std::string,UInt32>& properties);

    //Sets the asynchronous loading priority.
    //void setAsynchronousLoadPriority(int p);

    //Sets the DocumentFilter.
    //void setDocumentFilter(DocumentFilter filter);

    //Replaces the document properties dictionary for this document.
    void setDocumentProperties(const std::map<std::string,UInt32>& properties);

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

    //Creates a document branch element, that can contain other elements.
    ElementPtr createBranchElement(ElementPtr parent, const std::map<std::string,UInt32>& a) const;

    //Creates a document leaf element.
    ElementPtr createLeafElement(ElementPtr parent, const std::map<std::string,UInt32>& a, Int32 p0, Int32 p1) const;

    //Notifies all listeners that have registered interest for notification on this event type.
    virtual void produceChangedUpdate(const DocumentEvent& e);

    //Notifies all listeners that have registered interest for notification on this event type.
    virtual void produceInsertUpdate(const DocumentEvent& e);

    //Notifies all listeners that have registered interest for notification on this event type.
    virtual void produceRemoveUpdate(const DocumentEvent& e);

    //Notifies all listeners that have registered interest for notification on this event type.
    virtual void produceUndoableEditHappened(UndoableEditEvent& e);

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
    void writeLock(void);

    //Releases a write lock previously obtained via writeLock.
    void writeUnlock(void);
    
	typedef std::set<DocumentListenerPtr> DocumentListenerSet;
    typedef DocumentListenerSet::iterator DocumentListenerSetItor;
    typedef DocumentListenerSet::const_iterator DocumentListenerSetConstItor;
	
    DocumentListenerSet       _DocumentListeners;

	typedef std::set<UndoableEditListenerPtr> UndoableEditListenerSet;
    typedef UndoableEditListenerSet::iterator UndoableEditListenerSetItor;
    typedef UndoableEditListenerSet::const_iterator UndoableEditListenerSetConstItor;
	
    UndoableEditListenerSet       _UndoableEditListeners;
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class AbstractDocumentBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const AbstractDocument &source);
};

typedef AbstractDocument *AbstractDocumentP;

OSG_END_NAMESPACE

#include "OSGAbstractDocumentBase.inl"
#include "OSGAbstractDocument.inl"

#endif /* _OSGABSTRACTDOCUMENT_H_ */
