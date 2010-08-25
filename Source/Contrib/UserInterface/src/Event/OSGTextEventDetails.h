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

#ifndef _OSGTEXTEVENTDETAILS_H_
#define _OSGTEXTEVENTDETAILS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTextEventDetailsBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief TextEventDetails class. See \ref
           PageContribUserInterfaceTextEventDetails for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING TextEventDetails : public TextEventDetailsBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef TextEventDetailsBase Inherited;
    typedef TextEventDetails     Self;

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

    static  TextEventDetailsTransitPtr      create(  FieldContainer* const Source,
                                              Time TimeStamp); 

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in TextEventDetailsBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TextEventDetails(void);
    TextEventDetails(const TextEventDetails &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TextEventDetails(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class TextEventDetailsBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TextEventDetails &source);
};

typedef TextEventDetails *TextEventDetailsP;

OSG_END_NAMESPACE

#include "OSGTextEventDetailsBase.inl"
#include "OSGTextEventDetails.inl"

#endif /* _OSGTEXTEVENTDETAILS_H_ */
