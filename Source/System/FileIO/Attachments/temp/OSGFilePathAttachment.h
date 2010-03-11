/*---------------------------------------------------------------------------*\
 *                        OpenSG ToolBox Toolbox                             *
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

#ifndef _OSGFILEPATHATTACHMENT_H_
#define _OSGFILEPATHATTACHMENT_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "OSGToolboxDef.h"

#include "OSGFilePathAttachmentBase.h"
#include <boost/function.hpp>
#include <map>

OSG_BEGIN_NAMESPACE

/*! \brief FilePathAttachment class. See \ref 
           PageToolboxFilePathAttachment for a description.
*/

class OSG_TOOLBOXLIB_DLLMAPPING FilePathAttachment : public FilePathAttachmentBase
{
  private:

    typedef FilePathAttachmentBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:
    typedef boost::function<FieldContainerPtr ( const Path& FilePath )> FileAttachmentHandler;

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
    static const Path* getFilePath(      AttachmentContainerPtr  container);
    static FieldContainerPtr loadFromFilePath(Path &LoadFilePath, const FieldContainerType &FCType);

    static void   setFilePath(      AttachmentContainerPtr  container, 
                         const Path            &ThePath     );

     static bool registerHandler(const FieldContainerType& TheType, FileAttachmentHandler TheHandler);
     static bool unregisterHandler(const FieldContainerType& TheType);
    /*=========================  PROTECTED  ===============================*/
  protected:
     typedef std::map<std::string, FileAttachmentHandler> FileAttachmentHandlerMap;
     static FileAttachmentHandlerMap  _HandlerMap;

    // Variables should all be in FilePathAttachmentBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    FilePathAttachment(void);
    FilePathAttachment(const FilePathAttachment &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~FilePathAttachment(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class FilePathAttachmentBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const FilePathAttachment &source);
};

typedef FilePathAttachment *FilePathAttachmentP;


OSG_END_NAMESPACE

#include "OSGFilePathAttachmentBase.inl"
#include "OSGFilePathAttachment.inl"

#define OSGFILEPATHATTACHMENT_HEADER_CVSID "@(#)$Id: FCTemplate_h.h,v 1.23 2005/03/05 11:27:26 dirk Exp $"

#endif /* _OSGFILEPATHATTACHMENT_H_ */


