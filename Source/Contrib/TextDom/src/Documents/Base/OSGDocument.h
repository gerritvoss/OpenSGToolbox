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
#include "OSGElement.h"
#include "OSGUndoableEditListener.h"
#include <boost/any.hpp>

OSG_BEGIN_NAMESPACE

/*! \brief Document class. See \ref
           PageContribTextDomDocument for a description.
*/

class OSG_CONTRIBTEXTDOM_DLLMAPPING Document : public DocumentBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
    class Position
    {
      public:
        virtual UInt32 getOffset(void) const = 0;
    };

    class AttributeSet
    {
      public:
        //Returns true if this set contains this attribute with an equal value.
        virtual bool    containsAttribute(const std::string& name, boost::any value) const = 0; 

        //Returns true if this set contains all the attributes with equal values.
        virtual bool    containsAttributes(const AttributeSet& attributes) const = 0; 

        //Returns an attribute set that is guaranteed not to change over time.
        virtual AttributeSet*   copyAttributes(void) const = 0; 

        //Fetches the value of the given attribute.
        virtual boost::any     getAttribute(const std::string& key) const = 0; 

        //Returns the number of attributes contained in this set.
        virtual int    getAttributeCount(void) const = 0; 

        //Returns an enumeration over the names of the attributes in the set.
        //virtual Enumeration    getAttributeNames(void) = 0; 

        //Gets the resolving parent.
        virtual const AttributeSet&   getResolveParent(void) = 0; 

        //Checks whether the named attribute has a value specified in the set without resolving through another attribute set.
        virtual bool    isDefined(const std::string& attrName) const = 0; 

        //Determines if the two attribute sets are equivalent.
        virtual bool    operator=(const AttributeSet& attr) const = 0; 

    };

    typedef DocumentBase Inherited;
    typedef Document     Self;

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
    virtual EventConnection addDocumentListener(DocumentListenerPtr Listener) = 0;
    virtual void removeDocumentListener(DocumentListenerPtr Listener) = 0;
    virtual bool isDocumentListenerAttached(DocumentListenerPtr Listener) const = 0;

    //Registers the given observer to begin receiving notifications when undoable edits are made to the document.
    virtual EventConnection addUndoableEditListener(UndoableEditListenerPtr Listener) = 0;
    virtual void removeUndoableEditListener(UndoableEditListenerPtr Listener) = 0;
    virtual bool isUndoableEditListenerAttached(UndoableEditListenerPtr Listener) const = 0;

    //This method allows an application to mark a place in a sequence of character content.
    virtual Document::Position*   createPosition(UInt32 offs) const = 0;

    //Returns the root element that views should be based upon, unless some other mechanism for assigning views to element structures is provided.
    virtual ElementUnrecPtr    getDefaultRootElement(void) const = 0;

    //Returns a position that represents the end of the document.
    virtual const Document::Position*   getEndPosition(void) const = 0;

    //Returns number of characters of content currently in the document.
    virtual UInt32    getLength(void) const = 0;

    //Gets the properties associated with the document.
    virtual const boost::any&     getProperty(const std::string& key) const = 0;

    //Returns all of the root elements that are defined.
    virtual std::vector<ElementUnrecPtr>  getRootElements(void) const = 0;

    //Returns a position that represents the start of the document.
    virtual const Document::Position*   getStartPosition(void) const = 0;

    //Fetches the text contained within the given portion of the document.
    virtual std::string     getText(UInt32 offset, UInt32 length) const = 0;

    //Fetches the text contained within the given portion of the document.
    //virtual void   getText(UInt32 offset, UInt32 length, Segment txt) const = 0;

    //Inserts a string of content.
    virtual void   insertString(UInt32 offset, std::string str, const AttributeSet& a) = 0;

    //Associates a property with the document.
    virtual void   putProperty(const std::string& key, boost::any value) = 0;

    //Removes a portion of the content of the document.
    virtual void   remove(UInt32 offs, UInt32 len) = 0;

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
