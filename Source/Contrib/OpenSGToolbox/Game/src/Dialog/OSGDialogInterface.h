/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Game                                *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *                          Authors: David Kabala                            *
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

#ifndef _OSGDIALOGINTERFACE_H_
#define _OSGDIALOGINTERFACE_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGGameDef.h"

#include "OSGDialogInterfaceBase.h"
#include "Event/OSGDialogHierarchyListener.h"
#include <OpenSG/UserInterface/OSGInternalWindow.h>
#include <OpenSG/Input/OSGWindowUtils.h>
#include <OpenSG/UserInterface/OSGButton.h>
#include "OSGDefaultDialogComponentGenerator.h"
#include <OpenSG/UserInterface/OSGActionListener.h>


OSG_BEGIN_NAMESPACE

/*! \brief DialogInterface class. See \ref 
           PageGameDialogInterface for a description.
*/

class OSG_GAMELIB_DLLMAPPING DialogInterface : public DialogInterfaceBase
{
  private:

    typedef DialogInterfaceBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

      /**************************************************************************//**
       * @fn	void setHierarchy()
       * 
       * @brief	.
       * 
       * @author	Langkamp. 
       * @date		6/24/2009. 
       *****************************************************************************/
      void setHierarchy();

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

      
std::map<ButtonPtr, DialogPtr> _ButtonToResponseMap;

    // Variables should all be in DialogInterfaceBase.

    class DialogInterfaceListener : public DialogHierarchyListener, public ActionListener
    {
	public :
		DialogInterfaceListener(DialogInterfacePtr TheDialogInterface);
		
    virtual void newDialogStarted(const DialogHierarchyEventPtr e);
    virtual void dialogEnded(const DialogHierarchyEventPtr e);
    virtual void dialogResponseSelected(const DialogHierarchyEventPtr e);
    virtual void dialogResponsesReady(const DialogHierarchyEventPtr e);
    virtual void terminated(const DialogHierarchyEventPtr e);
    virtual void actionPerformed(const ActionEventPtr e);


	protected :

        DialogInterfacePtr _DialogInterface;
	};

    
    DialogInterfaceListener          _DialogInterfaceListener;


    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DialogInterface(void);
    DialogInterface(const DialogInterface &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DialogInterface(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class DialogInterfaceBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const DialogInterface &source);
};

typedef DialogInterface *DialogInterfaceP;

OSG_END_NAMESPACE

#include "OSGDialogInterfaceBase.inl"
#include "OSGDialogInterface.inl"

#define OSGDIALOGINTERFACE_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGDIALOGINTERFACE_H_ */
