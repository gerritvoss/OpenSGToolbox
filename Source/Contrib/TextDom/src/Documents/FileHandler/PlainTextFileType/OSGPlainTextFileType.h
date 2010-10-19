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
#ifndef _OSGPLAINTEXTFILETYPE_H_
#define _OSGPLAINTEXTFILETYPE_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGContribTextDomDef.h"

#include <boost/function.hpp>
#include <utility>
#include "OSGTextFileType.h"
#include "OSGTextFileHandler.h"
#include "OSGEventProducer.h"
#include "OSGEventListener.h"
#include "OSGContainerIdMapper.h"
#include "OSGFieldContainer.h"


#include "OSGPlainDocument.h"
#include "OSGPlainDocumentBranchElement.h"
#include "OSGPlainDocumentLeafElement.h"

#include "string"

OSG_BEGIN_NAMESPACE


class OSG_CONTRIBTEXTDOM_DLLMAPPING PlainTextFileType : public TextFileType
{
/*==========================  PUBLIC  =================================*/
public:

    /*---------------------------------------------------------------------*/
    static PlainTextFileType *the(void);

    /*---------------------------------------------------------------------*/
    virtual std::string getName(void) const;

    /*---------------------------------------------------------------------*/
    virtual ~PlainTextFileType(void);

    /*---------------------------------------------------------------------*/
     virtual DocumentRefPtr read(std::istream &is,
		                     const std::string& FileNameOrExtension);

    /*---------------------------------------------------------------------*/
     virtual bool write(DocumentRefPtr Doc, std::ostream &os,
                        const std::string& FileNameOrExtension);

    
    /*=========================  PROTECTED  ===============================*/
protected:

	void removeSlashRandSlashN(std::string& word);

    typedef TextFileType Inherited;
    static       PlainTextFileType*  _the;

    /*---------------------------------------------------------------------*/
    PlainTextFileType(void);

    PlainTextFileType(const PlainTextFileType &obj);

    /*==========================  PRIVATE  ================================*/
private:

    void operator =(const PlainTextFileType &source);
};

typedef PlainTextFileType* PlainTextFileTypeP;

OSG_END_NAMESPACE

#include "OSGPlainTextFileType.inl"

#endif /* _OSGPLAINTEXTFILETYPE_H_ */


