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

#ifndef _OSGSearchWindowEventDetails_H_
#define _OSGSearchWindowEventDetails_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSearchWindowEventDetailsBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief SearchWindowEventDetails class. See \ref
           PageContribTextDomSearchWindowEventDetails for a description.
*/

class OSG_CONTRIBTEXTDOM_DLLMAPPING SearchWindowEventDetails : public SearchWindowEventDetailsBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

	enum Options
    {
        DIALOG_OPTION_SEARCH = 0,
        DIALOG_OPTION_CANCEL = 1
    };

    typedef SearchWindowEventDetailsBase Inherited;
    typedef SearchWindowEventDetails     Self;

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


	static  SearchWindowEventDetailsTransitPtr      create( FieldContainerRefPtr Source,
                                                     Time TimeStamp); 


    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in SearchWindowEventDetailsBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SearchWindowEventDetails(void);
    SearchWindowEventDetails(const SearchWindowEventDetails &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SearchWindowEventDetails(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SearchWindowEventDetailsBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SearchWindowEventDetails &source);
};

typedef SearchWindowEventDetails *SearchWindowEventDetailsP;

OSG_END_NAMESPACE

#include "OSGSearchWindowEventDetailsBase.inl"
#include "OSGSearchWindowEventDetails.inl"

#endif /* _OSGSearchWindowEventDetails_H_ */
