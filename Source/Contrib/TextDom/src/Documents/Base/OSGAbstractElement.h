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

#ifndef _OSGABSTRACTELEMENT_H_
#define _OSGABSTRACTELEMENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGAbstractElementBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief AbstractElement class. See \ref
           PageContribTextDomAbstractElement for a description.
*/

class OSG_CONTRIBTEXTDOM_DLLMAPPING AbstractElement : public AbstractElementBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef AbstractElementBase Inherited;
    typedef AbstractElement     Self;

	
	//    Adds an attribute to the element.
	void 	addAttribute(std::string name,UInt32 value);

	//    Adds a set of attributes to the element.
	void 	addAttributes(std::map<std::string,UInt32> &attr);
      
	//   Returns the children of the receiver as an Enumeration.
	//virtual   std::vector<std::string> 	children(void);
       
	//  Checks whether a given attribute name/value is defined.
	bool	containsAttribute(std::string name, UInt32 value) const;
    
	//  Checks whether the element contains all the attributes.
	bool	containsAttributes(std::map<std::string,UInt32>& attrs) const;
       
	//   Copies a set of attributes.
	std::map<std::string,UInt32> copyAttributes(void) const;
       
	//   Dumps a debugging representation of the element hierarchy.
	void dump(std::ostream &OutputStream, UInt32 indentAmount) const;
       
	//   Returns true if the receiver allows children.
	virtual  bool 	getAllowsChildren(void) const = 0;
       
	//   Gets the value of an attribute.
	UInt32 	getAttribute(std::string attrName) const;
       
	//   Gets the number of attributes that are defined.
	UInt32 getAttributeCount(void) const;
       
	//   Gets the names of all attributes.
	std::vector<std::string>	getAttributeNames() const;
       
	//  Gets the attributes for the element.
	std::map<std::string,UInt32>& getAttributes() const;
       
	//   Returns the child TreeNode at index childIndex.
	Element* 	getChildAt(UInt32 childIndex) const;
       
	//   Returns the number of children TreeNode's receiver contains.
	UInt32	getChildCount(void) const;
       
	//  Retrieves the underlying model.
	Document*	getDocument(void) const;
        
	// Returns the index of node in the receivers children.
	UInt32 getIndex(Element* const node) const;
         
	// Gets the name of the element.
	std::string	getName(void) const;
         
	//Returns the parent TreeNode of the receiver.
	Element* getParent(void) const;
          
	//Gets the parent of the element.
	Element* 	getParentElement(void) const;
          
	 //Gets the resolving parent.
	//std::map<std::string,UInt32>& getResolveParent();
          
	//Gets the starting offset in the model for the element.
	virtual UInt32 getStartOffset(void) const=0;
          
	//Checks whether a given attribute is defined.
	bool	isDefined(std::string attrName) const;

	//Checks whether two attribute sets are equal.
	bool	isEqual(std::map<std::string,UInt32> attr) const;
    
    //Checks whether the element is a leaf.
	virtual	 bool	isLeaf(void) const=0;
    
	//Removes an attribute from the set.
	void 	removeAttribute(std::string name);
          
	//Removes a set of attributes for the element.
	void 	removeAttributes(std::map<std::string,UInt32> attrs);
          
	//Removes a set of attributes for the element.
	void 	removeAttributes(std::vector<std::string> names);
          
	//Sets the resolving parent.
	//void 	setResolveParent(std::map<std::string,UInt32> parent);
          

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

    // Variables should all be in AbstractElementBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    AbstractElement(void);
    AbstractElement(const AbstractElement &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~AbstractElement(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class AbstractElementBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const AbstractElement &source);
};

typedef AbstractElement *AbstractElementP;

OSG_END_NAMESPACE

#include "OSGAbstractElementBase.inl"
#include "OSGAbstractElement.inl"

#endif /* _OSGABSTRACTELEMENT_H_ */
