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

#ifndef _OSGPLAINDOCUMENTLEAFELEMENT_H_
#define _OSGPLAINDOCUMENTLEAFELEMENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGPlainDocumentLeafElementBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief PlainDocumentLeafElement class. See \ref
           PageContribTextDomPlainDocumentLeafElement for a description.
*/

class OSG_CONTRIBTEXTDOM_DLLMAPPING PlainDocumentLeafElement : public PlainDocumentLeafElementBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef PlainDocumentLeafElementBase Inherited;
    typedef PlainDocumentLeafElement     Self;

		  
	UInt32 getTextLength(void);
	std::string& getText(void);
	void setText(const std::string& value);


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

	std::string _Content;

    // Variables should all be in PlainDocumentLeafElementBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    PlainDocumentLeafElement(void);
    PlainDocumentLeafElement(const PlainDocumentLeafElement &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~PlainDocumentLeafElement(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class PlainDocumentLeafElementBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const PlainDocumentLeafElement &source);
};

typedef PlainDocumentLeafElement *PlainDocumentLeafElementP;

OSG_END_NAMESPACE

#include "OSGPlainDocumentLeafElementBase.inl"
#include "OSGPlainDocumentLeafElement.inl"

#endif /* _OSGPLAINDOCUMENTLEAFELEMENT_H_ */
