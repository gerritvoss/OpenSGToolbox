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

#ifndef _OSGABSTRACTBRANCHELEMENT_H_
#define _OSGABSTRACTBRANCHELEMENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGAbstractBranchElementBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief AbstractBranchElement class. See \ref
           PageContribTextDomAbstractBranchElement for a description.
*/

class OSG_CONTRIBTEXTDOM_DLLMAPPING AbstractBranchElement : public AbstractBranchElementBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef AbstractBranchElementBase Inherited;
    typedef AbstractBranchElement     Self;

	
	////   Returns the children of the receiver as an Enumeration.
	//std::vector<std::string> children(void);
	
	//   Returns true if the receiver allows children.
	bool getAllowsChildren(void) const;
	
	//  Gets a child element.
	ElementRefPtr	getElement(UInt32 index) const;
    
	//  Gets the number of children for the element.
	UInt32 getElementCount(void) const;
    
	//  Gets the child element index closest to the given model offset.
	UInt32 getElementIndex(UInt32 offset) const;
    
	//  Gets the ending offset in the model for the element.
	UInt32 getEndOffset(void) const;
    
	// Gets the element name.
	std::string getName(void) const;
     
	// Gets the starting offset in the model for the element.
	UInt32 getStartOffset(void) const;
     
	// Checks whether the element is a leaf.
	bool	isLeaf(void) const;
     
	//Gets the child element that contains the given model position.
	ElementRefPtr positionToElement(UInt32 pos) const;
      
	//Replaces content with a new set of elements.
	void replace(int offset, int length, MFRecElementPtr elems);
      
	//Converts the element to a string.
	std::string toString(void) const;
      
	void removeChildElement(UInt32 index);

	void addChildElement(UInt32 index,ElementRefPtr newPtr);

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

    // Variables should all be in AbstractBranchElementBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    AbstractBranchElement(void);
    AbstractBranchElement(const AbstractBranchElement &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~AbstractBranchElement(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class AbstractBranchElementBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const AbstractBranchElement &source);
};

typedef AbstractBranchElement *AbstractBranchElementP;

OSG_END_NAMESPACE

#include "OSGAbstractBranchElementBase.inl"
#include "OSGAbstractBranchElement.inl"

#endif /* _OSGABSTRACTBRANCHELEMENT_H_ */
