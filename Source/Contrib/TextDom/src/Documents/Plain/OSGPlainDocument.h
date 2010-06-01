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

OSG_BEGIN_NAMESPACE

/*! \brief PlainDocument class. See \ref
           PageContribTextDomPlainDocument for a description.
*/

class OSG_CONTRIBTEXTDOM_DLLMAPPING PlainDocument : public PlainDocumentBase
{
  protected:
    class PlainDocPosition : public Document::Position
    {
      private:
        UInt32 _Pos;
      public:
        virtual UInt32 getOffset(void) const;
    };

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
    virtual Document::Position*   createPosition(UInt32 offs) const;

    //Returns the root element that views should be based upon, unless some other mechanism for assigning views to element structures is provided.
    virtual ElementUnrecPtr    getDefaultRootElement(void) const;

    //Returns a position that represents the end of the document.
    virtual const Document::Position*   getEndPosition(void) const;

    //Returns number of characters of content currently in the document.
    virtual UInt32    getLength(void) const;

    //Gets the properties associated with the document.
    virtual const boost::any&     getProperty(const std::string& key) const;

    //Returns all of the root elements that are defined.
    virtual std::vector<ElementUnrecPtr>  getRootElements(void) const;

    //Returns a position that represents the start of the document.
    virtual const Document::Position*   getStartPosition(void) const;

    //Fetches the text contained within the given portion of the document.
    virtual std::string     getText(UInt32 offset, UInt32 length) const;

    //Inserts a string of content.
    virtual void   insertString(UInt32 offset, std::string str, const AttributeSet& a);

    //Associates a property with the document.
    virtual void   putProperty(const std::string& key, boost::any value);

    //Removes a portion of the content of the document.
    virtual void   remove(UInt32 offs, UInt32 len);
    /*=========================  PROTECTED  ===============================*/

  protected:

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
    PlainDocPosition _StartPos;
    PlainDocPosition _EndPos;
    /*==========================  PRIVATE  ================================*/

  private:

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
