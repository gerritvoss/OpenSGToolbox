/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Game                                *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                  Authors: David Kabala, Eric Langkamp                     *
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

#ifndef _OSGDEFAULTINVENTORYLISTCOMPARITOR_H_
#define _OSGDEFAULTINVENTORYLISTCOMPARITOR_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGDefaultInventoryListComparitorBase.h"

OSG_BEGIN_NAMESPACE

/*! \brief DefaultInventoryListComparitor class. See \ref 
           PageGameDefaultInventoryListComparitor for a description.
*/

class OSG_GAMELIB_DLLMAPPING DefaultInventoryListComparitor : public DefaultInventoryListComparitorBase
{
  private:

    typedef DefaultInventoryListComparitorBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    virtual bool operator()(const UInt32& LeftIndex, const UInt32& RightIndex);
	virtual ComparitorFunc getComparitorFunc(void) const;


    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         UInt32     origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in DefaultInventoryListComparitorBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DefaultInventoryListComparitor(void);
    DefaultInventoryListComparitor(const DefaultInventoryListComparitor &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DefaultInventoryListComparitor(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class DefaultInventoryListComparitorBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const DefaultInventoryListComparitor &source);
};

typedef DefaultInventoryListComparitor *DefaultInventoryListComparitorP;

OSG_END_NAMESPACE

#include "OSGDefaultInventoryListComparitorBase.inl"
#include "OSGDefaultInventoryListComparitor.inl"

#define OSGDEFAULTINVENTORYLISTCOMPARITOR_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGDEFAULTINVENTORYLISTCOMPARITOR_H_ */
