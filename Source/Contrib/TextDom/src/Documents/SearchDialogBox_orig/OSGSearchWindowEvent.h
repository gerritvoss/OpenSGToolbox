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

#ifndef _OSGSEARCHWINDOWEVENT_H_
#define _OSGSEARCHWINDOWEVENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGSearchWindowEventBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief SearchWindowEvent class. See \ref
           PageContribTextDomSearchWindowEvent for a description.
*/

class OSG_CONTRIBTEXTDOM_DLLMAPPING SearchWindowEvent : public SearchWindowEventBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

	enum Options
    {
        DIALOG_OPTION_SEARCH = 0,
        DIALOG_OPTION_CANCEL = 1
    };

    typedef SearchWindowEventBase Inherited;
    typedef SearchWindowEvent     Self;

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


	static  SearchWindowEventTransitPtr      create( FieldContainerRefPtr Source,
                                                     Time TimeStamp,
                                                     UInt32 Option,
                                                     const std::string& SearchText,
													 const std::string& ReplaceText); 


    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in SearchWindowEventBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    SearchWindowEvent(void);
    SearchWindowEvent(const SearchWindowEvent &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~SearchWindowEvent(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class SearchWindowEventBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const SearchWindowEvent &source);
};

typedef SearchWindowEvent *SearchWindowEventP;

OSG_END_NAMESPACE

#include "OSGSearchWindowEventBase.inl"
#include "OSGSearchWindowEvent.inl"

#endif /* _OSGSEARCHWINDOWEVENT_H_ */
