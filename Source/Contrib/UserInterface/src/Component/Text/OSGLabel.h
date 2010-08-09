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

#ifndef _OSGLABEL_H_
#define _OSGLABEL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGLabelBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief Label class. See \ref
           PageContribUserInterfaceLabel for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING Label : public LabelBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef LabelBase Inherited;
    typedef Label     Self;

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

	Vec2f getContentRequestedSize(void) const;
	virtual void mouseClicked(MouseEventDetails* const e);
	virtual void mousePressed(MouseEventDetails* const e);
	virtual void mouseDragged(MouseEventDetails* const e);

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in LabelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Label(void);
    Label(const Label &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Label(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

	virtual void drawInternal(Graphics* const Graphics, Real32 Opacity = 1.0f) const;
	void calculateTextBounds(const UInt32 StartIndex, const UInt32 EndIndex, Pnt2f& TopLeft, Pnt2f& BottomRight);
    
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class LabelBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const Label &source);
};

typedef Label *LabelP;

OSG_END_NAMESPACE

#include "OSGLabelBase.inl"
#include "OSGLabel.inl"

#endif /* _OSGLABEL_H_ */
