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

#ifndef _OSGDOCUMENT_H_
#define _OSGDOCUMENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDocumentBase.h"
#include "OSGDocumentListener.h"
#include "OSGUndoableEditListener.h"
#include "OSGElement.h"
#include "styleddocumentattributes.h"

OSG_BEGIN_NAMESPACE

/*! \brief Document class. See \ref
           PageContribTextDomDocument for a description.
*/

class OSG_CONTRIBTEXTDOM_DLLMAPPING Document : public DocumentBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef DocumentBase Inherited;
    typedef Document     Self;

	virtual bool isA(std::string) = 0;
		   //Registers the given observer to begin receiving notifications when changes are made to the document.
    virtual EventConnection addDocumentListener(DocumentListenerPtr Listener) = 0;

	virtual bool isDocumentListenerAttached(DocumentListenerPtr Listener) const = 0;

    //Unregisters the given observer from the notification list so it will no longer receive change updates.
    virtual void removeDocumentListener(DocumentListenerPtr Listener) = 0;

    //Registers the given observer to begin receiving notifications when undoable edits are made to the document.
    virtual EventConnection addUndoableEditListener(UndoableEditListenerPtr Listener) = 0;

	virtual bool isUndoableEditListenerAttached(UndoableEditListenerPtr Listener) const = 0;

    //Unregisters the given observer from the notification list so it will no longer receive updates.
    virtual void removeUndoableEditListener(UndoableEditListenerPtr Listener) = 0;

    //This method allows an application to mark a place in a sequence of character content.
    virtual UInt32 createPosition(Int32 offs) = 0;

    //Returns the root element that views should be based upon, unless some other mechanism for assigning views to element structures is provided.
    virtual ElementRefPtr getDefaultRootElement(void) const = 0;

    //Returns a position that represents the end of the document.
    virtual UInt32 getEndPosition(void) const = 0;

    //Returns number of characters of content currently in the document.
    virtual UInt32 getLength(void) const = 0;

    //Gets the properties associated with the document.
    //virtual UInt32 getProperty(const std::string& key) const = 0;

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
    //virtual void putProperty(const std::string& key, UInt32 value) = 0;

    //Removes a portion of the content of the document.
    virtual void remove(Int32 offs, Int32 len) = 0;

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

    // Variables should all be in DocumentBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Document(void);
    Document(const Document &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Document(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class DocumentBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const Document &source);
};

typedef Document *DocumentP;

OSG_END_NAMESPACE

#include "OSGDocumentBase.inl"
#include "OSGDocument.inl"

#endif /* _OSGDOCUMENT_H_ */
