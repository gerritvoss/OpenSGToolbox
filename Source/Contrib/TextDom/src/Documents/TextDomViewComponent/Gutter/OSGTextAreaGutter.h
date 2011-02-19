/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 * contact: David Kabala (djkabala@gmail.com)                                *
 *          Achyuthan Vasanth (vasanth.achyuthan@gmail.com)                  *
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

#ifndef _OSGTEXTAREAGUTTER_H_
#define _OSGTEXTAREAGUTTER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTextAreaGutterBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief TextAreaGutter class. See \ref
           PageContribTextDomTextAreaGutter for a description.
*/

class OSG_CONTRIBTEXTDOM_DLLMAPPING TextAreaGutter : public TextAreaGutterBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef TextAreaGutterBase Inherited;
    typedef TextAreaGutter     Self;

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

    // Variables should all be in TextAreaGutterBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TextAreaGutter(void);
    TextAreaGutter(const TextAreaGutter &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TextAreaGutter(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
	void drawInternal(Graphics * const TheGraphics, Real32 Opacity) const;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class TextAreaGutterBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TextAreaGutter &source);
};

typedef TextAreaGutter *TextAreaGutterP;

OSG_END_NAMESPACE

#include "OSGTextAreaGutterBase.inl"
#include "OSGTextAreaGutter.inl"

#endif /* _OSGTEXTAREAGUTTER_H_ */
