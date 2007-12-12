/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
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

#ifndef _OSGDEFAULTLISTCELLRENDERER_H_
#define _OSGDEFAULTLISTCELLRENDERER_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGUserInterfaceDef.h"

#include "OSGListCellRenderer.h"

OSG_BEGIN_NAMESPACE

/*! \brief DefaultListCellRenderer class. See \ref 
           PageUserInterfaceDefaultListCellRenderer for a description.
*/

class OSG_USERINTERFACELIB_DLLMAPPING DefaultListCellRenderer : public ListCellRenderer
{
    /*==========================  PUBLIC  =================================*/
  public:
    virtual ComponentPtr getListCellRendererComponent(ListPtr list, SharedFieldPtr value, UInt32 index, bool isSelected, bool cellHasFocus);

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DefaultListCellRenderer(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DefaultListCellRenderer(void); 

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in DefaultListCellRendererBase.

    
    /*==========================  PRIVATE  ================================*/
  private:
};

typedef DefaultListCellRenderer *DefaultListCellRendererP;

OSG_END_NAMESPACE

#include "OSGDefaultListCellRenderer.inl"

#endif /* _OSGDEFAULTLISTCELLRENDERER_H_ */
