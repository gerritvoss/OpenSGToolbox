/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
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

#ifndef _OSGTEXTDOMLAYOUTMANAGER_H_
#define _OSGTEXTDOMLAYOUTMANAGER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTextDomLayoutManagerBase.h"
#include "OSGTextDomLayoutManager.h"
#include "OSGTextDomView.h" // VisibleViews type
#include "OSGTextDomAreaFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief TextDomLayoutManager class. See \ref
           PageContribTextDomTextDomLayoutManager for a description.
*/

class OSG_CONTRIBTEXTDOM_DLLMAPPING TextDomLayoutManager : public TextDomLayoutManagerBase
{
	public:
	
	

  protected:

    /*==========================  PUBLIC  =================================*/


	

  public:

    typedef TextDomLayoutManagerBase Inherited;
    typedef TextDomLayoutManager     Self;

		
	virtual Vec2f getContentRequestedSize(void) const = 0;
	virtual void updateViews(void) = 0;
	virtual void printDebugInformation(void) const = 0;

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

    // Variables should all be in TextDomLayoutManagerBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TextDomLayoutManager(void);
    TextDomLayoutManager(const TextDomLayoutManager &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TextDomLayoutManager(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class TextDomLayoutManagerBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TextDomLayoutManager &source);
};

typedef TextDomLayoutManager *TextDomLayoutManagerP;

OSG_END_NAMESPACE

#include "OSGTextDomLayoutManagerBase.inl"
#include "OSGTextDomLayoutManager.inl"

#endif /* _OSGTEXTDOMLAYOUTMANAGER_H_ */
