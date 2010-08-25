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

#ifndef _OSGTREEMODELLAYOUTEVENTDETAILS_H_
#define _OSGTREEMODELLAYOUTEVENTDETAILS_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTreeModelLayoutEventDetailsBase.h"
#include "OSGTreePath.h"

OSG_BEGIN_NAMESPACE

/*! \brief TreeModelLayoutEventDetails class. See \ref
           PageContribUserInterfaceTreeModelLayoutEventDetails for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING TreeModelLayoutEventDetails : public TreeModelLayoutEventDetailsBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef TreeModelLayoutEventDetailsBase Inherited;
    typedef TreeModelLayoutEventDetails     Self;

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

    static  TreeModelLayoutEventDetailsTransitPtr      create(  FieldContainer* const Source,
                                                         Time TimeStamp,
                                                         const TreePath& path); 

	const TreePath& getPath(void) const;

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in TreeModelLayoutEventDetailsBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TreeModelLayoutEventDetails(void);
    TreeModelLayoutEventDetails(const TreeModelLayoutEventDetails &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TreeModelLayoutEventDetails(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */

    TreePath _Path;

    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class TreeModelLayoutEventDetailsBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TreeModelLayoutEventDetails &source);
};

typedef TreeModelLayoutEventDetails *TreeModelLayoutEventDetailsP;

OSG_END_NAMESPACE

#include "OSGTreeModelLayoutEventDetailsBase.inl"
#include "OSGTreeModelLayoutEventDetails.inl"

#endif /* _OSGTREEMODELLAYOUTEVENTDETAILS_H_ */
