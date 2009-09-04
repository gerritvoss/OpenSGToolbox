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

#ifndef _OSGDOCUMENT_H_
#define _OSGDOCUMENT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include <vector>
#include <map>

#include "OSGDocumentBase.h"
#include "OSGElementFields.h"
#include "UndoableEdit/OSGUndoableEditListener.h"
#include "OSGDocumentListener.h"
#include <OpenSG/Input/OSGEventConnection.h>

OSG_BEGIN_NAMESPACE

/*! \brief Document class. See \ref 
           PageUserInterfaceDocument for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING Document : public DocumentBase
{
  private:

    typedef DocumentBase Inherited;

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
    virtual ElementPtr getDefaultRootElement(void) const = 0;

    //Returns a position that represents the end of the document.
    virtual UInt32 getEndPosition(void) const = 0;

    //Returns number of characters of content currently in the document.
    virtual UInt32 getLength(void) const = 0;

    //Gets the properties associated with the document.
    virtual UInt32 getProperty(const std::string& key) const = 0;

    //Returns all of the root elements that are defined.
    virtual std::vector<ElementPtr> getRootElements(void) = 0;

    //Returns a position that represents the start of the document.
    virtual UInt64 getStartPosition(void) const = 0;

    //Fetches the text contained within the given portion of the document.
    virtual std::string getText(Int32 offset, UInt32 length) const = 0;

    //Fetches the text contained within the given portion of the document.
    virtual void getText(Int32 offset, UInt32 length, std::string& txt) const = 0;

    //Inserts a string of content.
    virtual void insertString(Int32 offset, const std::string& str, std::map<std::string,UInt32> properties) = 0;

    //Associates a property with the document.
    virtual void putProperty(const std::string& key, UInt32 value) = 0;

    //Removes a portion of the content of the document.
    virtual void remove(Int32 offs, UInt32 len) = 0;

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
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class DocumentBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const Document &source);
};

typedef Document *DocumentP;

OSG_END_NAMESPACE

#include "OSGDocumentBase.inl"
#include "OSGDocument.inl"

#endif /* _OSGDOCUMENT_H_ */
