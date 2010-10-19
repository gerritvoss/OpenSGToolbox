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

#ifndef _OSGSTYLEDDOCUMENTLEAFELEMENT_H_
#define _OSGSTYLEDDOCUMENTLEAFELEMENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGStyledDocumentLeafElementBase.h"
#include "styleddocumentattributes.h"

OSG_BEGIN_NAMESPACE

/*! \brief StyledDocumentLeafElement class. See \ref
           PageContribTextDomStyledDocumentLeafElement for a description.
*/

class OSG_CONTRIBTEXTDOM_DLLMAPPING StyledDocumentLeafElement : public StyledDocumentLeafElementBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef StyledDocumentLeafElementBase Inherited;
    typedef StyledDocumentLeafElement     Self;

	
  	UInt32 getTextLength(void);
	std::string getText(void);
	void setText(std::string);
	TextWithProps& getProperties(void);
	void setProperties(TextWithProps&);

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

    // Variables should all be in StyledDocumentLeafElementBase.

	  TextWithProps _Properties;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    StyledDocumentLeafElement(void);
    StyledDocumentLeafElement(const StyledDocumentLeafElement &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~StyledDocumentLeafElement(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class StyledDocumentLeafElementBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const StyledDocumentLeafElement &source);
};

typedef StyledDocumentLeafElement *StyledDocumentLeafElementP;

OSG_END_NAMESPACE

#include "OSGStyledDocumentLeafElementBase.inl"
#include "OSGStyledDocumentLeafElement.inl"

#endif /* _OSGSTYLEDDOCUMENTLEAFELEMENT_H_ */
