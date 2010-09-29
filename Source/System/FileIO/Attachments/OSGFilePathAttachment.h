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

#ifndef _OSGFILEPATHATTACHMENT_H_
#define _OSGFILEPATHATTACHMENT_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGFilePathAttachmentBase.h"
#include <boost/function.hpp>
#include <map>

OSG_BEGIN_NAMESPACE

/*! \brief FilePathAttachment class. See \ref
           PageFileIOFilePathAttachment for a description.
*/

class OSG_SYSTEM_DLLMAPPING FilePathAttachment : public FilePathAttachmentBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef FilePathAttachmentBase Inherited;
    typedef FilePathAttachment     Self;

    typedef boost::function<FieldContainerUnrecPtr ( const BoostPath& FilePath )> FileAttachmentHandler;

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
    static const BoostPath* getFilePath(const AttachmentContainer*  container);
    static FieldContainerUnrecPtr loadFromFilePath(BoostPath &LoadFilePath, const FieldContainerType &FCType);
    static bool shouldUseOnlyFileHandler(const FieldContainerType &FCType);

    static void   setFilePath(      AttachmentContainer*  container, 
                                    const BoostPath            &ThePath     );

     static bool registerHandler(const FieldContainerType& TheType,
                                 FileAttachmentHandler TheHandler,
                                 bool UseOnlyFileHandler = false);
     static bool unregisterHandler(const FieldContainerType& TheType);
    /*=========================  PROTECTED  ===============================*/

  protected:

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
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    typedef std::pair<FileAttachmentHandler, bool> HandlerPair;
    typedef std::map<std::string, HandlerPair > FileAttachmentHandlerMap;
     static FileAttachmentHandlerMap  _HandlerMap;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class FilePathAttachmentBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const FilePathAttachment &source);
};

typedef FilePathAttachment *FilePathAttachmentP;

OSG_END_NAMESPACE

#include "OSGFilePathAttachmentBase.inl"
#include "OSGFilePathAttachment.inl"

#endif /* _OSGFILEPATHATTACHMENT_H_ */
