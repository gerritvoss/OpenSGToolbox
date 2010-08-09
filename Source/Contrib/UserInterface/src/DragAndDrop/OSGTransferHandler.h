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

#ifndef _OSGTRANSFERHANDLER_H_
#define _OSGTRANSFERHANDLER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGTransferHandlerBase.h"
#include "OSGComponentFields.h"
#include "OSGTransferableFields.h"
#include "OSGDataFlavorFields.h"
#include "OSGInputEventDetails.h"
#include <vector>

OSG_BEGIN_NAMESPACE

/*! \brief TransferHandler class. See \ref
           PageContribUserInterfaceTransferHandler for a description.
*/

class OSG_CONTRIBUSERINTERFACE_DLLMAPPING TransferHandler : public TransferHandlerBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:
	enum TranferActions
    {
        TRANSFER_NONE         = 0,
        TRANSFER_COPY         = 1,
        TRANSFER_MOVE         = 2,
        TRANSFER_COPY_OR_MOVE = 3
    };

    typedef TransferHandlerBase Inherited;
    typedef TransferHandler     Self;

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

	//Indicates whether a component would accept an import of the given set of data flavors prior to actually attempting to import it.
	virtual bool canImport(Component* comp, std::vector<DataFlavor*> transferFlavors) const = 0;

	//Creates a Transferable to use as the source for a data transfer.
	virtual TransferableRefPtr createTransferable(Component* c) const = 0;

	//Causes the Swing drag support to be initiated.
	virtual void exportAsDrag(ComponentRefPtr comp, InputEventDetails* const e, UInt32 action) const = 0;

	//Invoked after data has been exported.
	virtual void exportDone(ComponentRefPtr source, TransferableRefPtr data, UInt32 action) const = 0;

	//Causes a transfer from the given component to the given clipboard.
	virtual void exportToClipboard(ComponentRefPtr comp, UInt32 action) const = 0;

	//Returns an Action that behaves like a 'copy' operation.
	//static Action getCopyAction(void) = 0;

	//Returns an Action that behaves like a 'cut' operation.
	//static Action getCutAction(void) = 0;

	//Returns an Action that behaves like a 'paste' operation.
	//static Action getPasteAction(void) = 0;

	//Returns the type of transfer actions supported by the source.
	virtual UInt32 getSourceActions(Component* c) const = 0;

	//Returns an object that establishes the look of a transfer.
	virtual ComponentRefPtr getVisualRepresentation(TransferableRefPtr t) const = 0;

	//Causes a transfer to a component from a clipboard or a DND drop operation.
	virtual bool importData(ComponentRefPtr comp, TransferableRefPtr t) const = 0;

    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in TransferHandlerBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    TransferHandler(void);
    TransferHandler(const TransferHandler &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~TransferHandler(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class TransferHandlerBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const TransferHandler &source);
};

typedef TransferHandler *TransferHandlerP;

OSG_END_NAMESPACE

#include "OSGTransferHandlerBase.inl"
#include "OSGTransferHandler.inl"

#endif /* _OSGTRANSFERHANDLER_H_ */
