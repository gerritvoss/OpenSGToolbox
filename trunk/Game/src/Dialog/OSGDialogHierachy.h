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

#ifndef _OSGDIALOGHIERACHY_H_
#define _OSGDIALOGHIERACHY_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>

#include "OSGDialogHierachyBase.h"
#include "OSGDialog.h"
#include "Event/OSGDialogListener.h"


OSG_BEGIN_NAMESPACE

/*! \brief DialogHierachy class. See \ref 
           PageGameDialogHierachy for a description.
*/

class OSG_GAMELIB_DLLMAPPING DialogHierachy : public DialogHierachyBase
{
  private:

    typedef DialogHierachyBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         UInt32     origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */

    void reset();
    void start();
    DialogPtr addDialog(std::string response, Real32 delayResponses, SoundPtr dialogSound, bool interactive, DialogPtr parentDialog);
    void retrieveReponses();
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/
  protected:

    // Variables should all be in DialogHierachyBase.

    class DialogHierachyListener : public DialogListener
    {
	public :
		DialogHierachyListener(DialogHierachyPtr TheDialogHierachy);
		
        virtual void started(const DialogEvent& e);
        virtual void ended(const DialogEvent& e);
        virtual void responseSelected(const DialogEvent& e);
        virtual void responsesReady(const DialogEvent& e);
        virtual void terminated(const DialogEvent& e);

	protected :

        DialogHierachyPtr _DialogHierachy;
	};

    DialogHierachyListener _DialogHierachyListener;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    DialogHierachy(void);
    DialogHierachy(const DialogHierachy &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~DialogHierachy(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class DialogHierachyBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const DialogHierachy &source);
};

typedef DialogHierachy *DialogHierachyP;

OSG_END_NAMESPACE

#include "OSGDialogHierachyBase.inl"
#include "OSGDialogHierachy.inl"

#define OSGDIALOGHIERACHY_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGDIALOGHIERACHY_H_ */
