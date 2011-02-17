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

#ifndef _OSGPLAINDOCUMENT_H_
#define _OSGPLAINDOCUMENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGPlainDocumentBase.h"
#include "OSGPlainDocumentBranchElementFields.h"
#include "OSGPlainDocumentLeafElementFields.h"
#include "OSGDocumentElementAttributes.h"

OSG_BEGIN_NAMESPACE

/*! \brief PlainDocument class. See \ref
           PageContribTextDomPlainDocument for a description.
*/

class OSG_CONTRIBTEXTDOM_DLLMAPPING PlainDocument : public PlainDocumentBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef PlainDocumentBase Inherited;
    typedef PlainDocument     Self;

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

	
	//This method allows an application to mark a place in a sequence of character content.
    UInt32 createPosition(Int32 offs);

    //Returns the root element that views should be based upon, unless some other mechanism for assigning views to element structures is provided.
    Element* getDefaultRootElement(void) const;

    //Returns a position that represents the end of the document.
    UInt32 getEndPosition(void) const;

    //Returns number of characters of content currently in the document.(including endlines)
    UInt32 getLength(void) const;

    //Gets the properties associated with the document.
    //UInt32 getProperty(const std::string& key) const;

    //Returns all of the root elements that are defined.
    std::vector<Element*> getRootElements(void);

    //Returns a position that represents the start of the document.
    UInt64 getStartPosition(void) const;

    //Fetches the text contained within the given portion of the document.
    std::string getText(Int32 offset, Int32 length) const;

    //Fetches the text contained within the given portion of the document.
    void getText(Int32 offset, Int32 length, std::string& txt) const;


	void deleteCharacter(UInt32 elementIndex,UInt32 offsetInChild);

	void addTextAsNewElementToDocument(const std::string& str, DocumentElementAttribute& properties,bool createFreshDocument);
    //Inserts a string of content.
    void insertString(UInt32 offset, const std::string& str, DocumentElementAttribute& properties);

	void insertCharacter(UInt32 offset, const char character, DocumentElementAttribute& properties);

	void insertCharacter(UInt32 offsetInElement,UInt32 elementIndex, const char character, DocumentElementAttribute& properties);


	void removeElement(UInt32 leafElementIndex,PlainDocumentBranchElement* const rootElement);

	void addElements(Int32 theLeafElementIndex,std::string theCharactersBefore,std::string theCharactersAfter,std::vector<std::string> &setOfWords,PlainDocumentBranchElement* const rootElement);

	void deleteCharacters(UInt32 lesserIndex,UInt32 lesserOffset,UInt32 greaterIndex,UInt32 greaterOffset);
    //Associates a property with the document.
    //void putProperty(const std::string& key, UInt32 value);

    //Removes a portion of the content of the document.
    void remove(Int32 offs, Int32 len);
    //Gets the asynchronous loading priority.
    //int getAsynchronousLoadPriority(void);

	

    //Returns the root element of the bidirectional structure for this document.
    //Element getBidiRootElement(void);

    //Returns the DocumentFilter that is responsible for filtering of insertion/removal.
    //DocumentFilter getDocumentFilter(void);

    //Supports managing a set of properties.
    //const std::map<std::string,UInt32>& getDocumentProperties(void) const;

    //Get the paragraph element containing the given position.
    //Element* getParagraphElement(UInt32 pos) const;

    //Acquires a lock to begin reading some state from the document.
    //void readLock(void);

    //Does a read unlock.
    //void readUnlock(void);

    //Deletes the region of text from offset to offset + length, and replaces it with text.
    void replace(Int32 offset, Int32 length, const std::string& str, DocumentElementAttribute& properties);

    //Sets the asynchronous loading priority.
    //void setAsynchronousLoadPriority(int p);

    //Sets the DocumentFilter.
    //void setDocumentFilter(DocumentFilter filter);

    //Replaces the document properties dictionary for this document.
    //void setDocumentProperties(const std::map<std::string,UInt32>& properties);


    /*=========================  PROTECTED  ===============================*/

  protected:

	  
	void tokenize(std::string sentence,std::vector<std::string> & setOfWords);

    //Creates a document branch element, that can contain other elements.
    //Element* createBranchElement(Element* const parent, const std::map<std::string,UInt32>& a) const;

    //Creates a document leaf element.
    //Element* createLeafElement(Element* const parent, const std::map<std::string,UInt32>& a, Int32 p0, Int32 p1) const;


    // Variables should all be in PlainDocumentBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PlainDocument(void);
    PlainDocument(const PlainDocument &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PlainDocument(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

  	UInt32 _DocumentSize;

    friend class FieldContainer;
    friend class PlainDocumentBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const PlainDocument &source);
};

typedef PlainDocument *PlainDocumentP;

OSG_END_NAMESPACE

#include "OSGPlainDocumentBase.inl"
#include "OSGPlainDocument.inl"

#endif /* _OSGPLAINDOCUMENT_H_ */
