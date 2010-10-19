/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *               Copyright (C) 2000-2006 by the OpenSG Forum                 *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact:  David Kabala (djkabala@gmail.com)*
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

#ifndef _OSGDOCUMENTMODELCHANGEDEVENT_H_
#define _OSGDOCUMENTMODELCHANGEDEVENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDocumentModelChangedEventBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief DocumentModelChangedEvent class. See \ref
           PageContribTextDomDocumentModelChangedEvent for a description.
*/

class OSG_CONTRIBTEXTDOM_DLLMAPPING DocumentModelChangedEvent : public DocumentModelChangedEventBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef DocumentModelChangedEventBase Inherited;
    typedef DocumentModelChangedEvent     Self;

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

    // Variables should all be in DocumentModelChangedEventBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DocumentModelChangedEvent(void);
    DocumentModelChangedEvent(const DocumentModelChangedEvent &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DocumentModelChangedEvent(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class DocumentModelChangedEventBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const DocumentModelChangedEvent &source);
};

typedef DocumentModelChangedEvent *DocumentModelChangedEventP;

OSG_END_NAMESPACE

#include "OSGDocumentModelChangedEventBase.inl"
#include "OSGDocumentModelChangedEvent.inl"

#endif /* _OSGDOCUMENTMODELCHANGEDEVENT_H_ */
