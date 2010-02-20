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

#ifndef _OSGXMLLOOKANDFEEL_H_
#define _OSGXMLLOOKANDFEEL_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGXMLLookAndFeelBase.h"
#include "OSGPathType.h"
#include "OSGFCFileHandler.h"

OSG_BEGIN_NAMESPACE

/*! \brief XMLLookAndFeel class. See \ref
           PageContribUserInterfaceXMLLookAndFeel for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING XMLLookAndFeel : public XMLLookAndFeelBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef XMLLookAndFeelBase Inherited;
    typedef XMLLookAndFeel     Self;

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

	virtual void init(void);

    static  XMLLookAndFeelUnrecPtr      create          (const BoostPath& LoadFile);

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in XMLLookAndFeelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    XMLLookAndFeel(void);
    XMLLookAndFeel(const XMLLookAndFeel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~XMLLookAndFeel(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class XMLLookAndFeelBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const XMLLookAndFeel &source);
};

typedef XMLLookAndFeel *XMLLookAndFeelP;

OSG_END_NAMESPACE

#include "OSGXMLLookAndFeelBase.inl"
#include "OSGXMLLookAndFeel.inl"

#endif /* _OSGXMLLOOKANDFEEL_H_ */
