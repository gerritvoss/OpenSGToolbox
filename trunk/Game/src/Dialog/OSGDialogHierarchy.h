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

#ifndef _OSGDIALOGHIERARCHY_H_
#define _OSGDIALOGHIERARCHY_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGDialogHierarchyBase.h"
#include "OSGDialog.h"
#include "Event/OSGDialogListener.h"
#include "Event/OSGDialogHierarchyListener.h"
#include "OSGDialogInterface.h"


OSG_BEGIN_NAMESPACE

/*! \brief DialogHierarchy class. See \ref 
           PageGameDialogHierarchy for a description.
*/

class OSG_GAMELIB_DLLMAPPING DialogHierarchy : public DialogHierarchyBase
{
  private:

    typedef DialogHierarchyBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         UInt32     origin    );

    DialogInterfacePtr _ParentDialogInterface;

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */

    void reset();
    void start();
    DialogPtr addDialog(std::string response, Real32 delayResponses, SoundPtr dialogSound, bool interactive, DialogPtr parentDialog);
    void retrieveReponses();
    /*! \{                                                                 */

    EventConnection addDialogHierarchyListener(DialogHierarchyListenerPtr Listener);
	bool isDialogHierarchyListenerAttached(DialogHierarchyListenerPtr Listener) const;
    void removeDialogHierarchyListener(DialogHierarchyListenerPtr Listener);


    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;
	
	class DialogHierarchyListener : public DialogListener
    {
	public :
		DialogHierarchyListener(DialogHierarchyPtr TheDialogHierarchy);
		
        virtual void started(const DialogEvent& e);
        virtual void ended(const DialogEvent& e);
        virtual void responseSelected(const DialogEvent& e);
        virtual void responsesReady(const DialogEvent& e);
        virtual void terminated(const DialogEvent& e);

	protected :

        DialogHierarchyPtr _DialogHierarchy;
	};

	DialogHierarchyListener          _DialogHierarchyListener;


    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in DialogHierarchyBase.

    typedef std::set<DialogHierarchyListenerPtr> DialogHierarchyListenerSet;
    typedef DialogHierarchyListenerSet::iterator DialogHierarchyListenerSetItor;
    typedef DialogHierarchyListenerSet::const_iterator DialogHierarchyListenerSetConstItor;


    

    
    DialogHierarchyListenerSet       _DialogHierarchyListeners;

    virtual void produceNewDialogStarted(const DialogHierarchyEvent& e);
    virtual void produceDialogEnded(const DialogHierarchyEvent& e);
    virtual void produceDialogResponseSelected(const DialogHierarchyEvent& e);
    virtual void produceDialogResponsesReady(const DialogHierarchyEvent& e);
    virtual void produceTerminated(const DialogHierarchyEvent& e);

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DialogHierarchy(void);
    DialogHierarchy(const DialogHierarchy &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DialogHierarchy(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class DialogHierarchyBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const DialogHierarchy &source);
};

typedef DialogHierarchy *DialogHierarchyP;

OSG_END_NAMESPACE

#include "OSGDialogHierarchyBase.inl"
#include "OSGDialogHierarchy.inl"

#define OSGDIALOGHIERARCHY_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGDIALOGHIERARCHY_H_ */
