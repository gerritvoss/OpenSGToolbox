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

#ifndef _OSGDOCUMENTEVENTDETAILS_H_
#define _OSGDOCUMENTEVENTDETAILS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGDocumentEventDetailsBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief DocumentEventDetails class. See \ref
           PageContribTextDomDocumentEventDetails for a description.
*/

class OSG_CONTRIBTEXTDOM_DLLMAPPING DocumentEventDetails : public DocumentEventDetailsBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef DocumentEventDetailsBase Inherited;
    typedef DocumentEventDetails     Self;

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
    static  DocumentEventDetailsTransitPtr create(FieldContainer* const Source,
                                                  Time TimeStamp,
                                                  Document* const TheDocument,
                                                  Int32 Offset,
                                                  UInt32 Length); 
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in DocumentEventDetailsBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DocumentEventDetails(void);
    DocumentEventDetails(const DocumentEventDetails &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DocumentEventDetails(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class DocumentEventDetailsBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const DocumentEventDetails &source);
};

typedef DocumentEventDetails *DocumentEventDetailsP;

OSG_END_NAMESPACE

#include "OSGDocument.h"
#include "OSGDocumentEventDetailsBase.inl"
#include "OSGDocumentEventDetails.inl"

#endif /* _OSGDOCUMENTEVENTDETAILS_H_ */
