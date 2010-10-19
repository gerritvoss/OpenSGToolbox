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

#ifndef _OSGELEMENT_H_
#define _OSGELEMENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGElementBase.h"
#include "OSGDocument.h"

OSG_BEGIN_NAMESPACE

/*! \brief Element class. See \ref
           PageContribTextDomElement for a description.
*/

class OSG_CONTRIBTEXTDOM_DLLMAPPING Element : public ElementBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ElementBase Inherited;
    typedef Element     Self;

		//Fetches the collection of attributes this element contains.
	virtual	 const std::map<std::string,UInt32>& getAttributes(void) const = 0;

	//Fetches the document associated with this element.
	virtual DocumentRefPtr	getDocument(void) const = 0;

	//Fetches the child element at the given index.  
	virtual ElementRefPtr	getElement(UInt32 index) const = 0;

	//Gets the number of child elements contained by this element.  
	virtual UInt32	getElementCount(void) const = 0;

	//Gets the child element index closest to the given offset.  
	virtual UInt32	getElementIndex(UInt32 offset) const = 0;

	//Fetches the offset from the beginning of the document that this element ends at.  
	virtual UInt32	getEndOffset(void) const = 0;

	//Fetches the name of the element.  
	virtual std::string	getName(void) const = 0;

	//Fetches the parent element.  
	virtual ElementRefPtr getParentElement(void) const = 0;

	//Fetches the offset from the beginning of the document that this element begins at.  
	virtual UInt32	getStartOffset(void) const = 0;

	//Is this element a leaf element? An element that may have children, even if it currently has no children, would return false.  
	virtual bool isLeaf(void) const = 0;
      


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

    // Variables should all be in ElementBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Element(void);
    Element(const Element &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Element(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class ElementBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const Element &source);
};

typedef Element *ElementP;

OSG_END_NAMESPACE


#include "OSGElementBase.inl"
#include "OSGElement.inl"

#endif /* _OSGELEMENT_H_ */
