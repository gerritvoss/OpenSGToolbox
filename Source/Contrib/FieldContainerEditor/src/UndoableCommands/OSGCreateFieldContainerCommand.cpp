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
//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include "OSGConfig.h"

#include "OSGCreateFieldContainerCommand.h"
#include "OSGFieldContainerFactory.h"

OSG_USING_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class OSG::CreateFieldContainerCommand
A CreateFieldContainerCommand. 
*/

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CommandType CreateFieldContainerCommand::_Type("CreateFieldContainerCommand", "Command");

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

CreateFieldContainerCommandPtr CreateFieldContainerCommand::create(const std::string& typeName)
{
    const FieldContainerType* type = FieldContainerFactory::the()->findType(typeName.c_str());
	return create(type);
}

CreateFieldContainerCommandPtr CreateFieldContainerCommand::create(const FieldContainerType* type)
{
	return RefPtr(new CreateFieldContainerCommand(type));
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void CreateFieldContainerCommand::execute(void)
{
    //Check for a valid Field Container
    if(_TypeToCreate == NULL)
    {
        SWARNING << "Type of field container to create is NULL." << std::endl;
        return;
    }

    //Create the FieldContainer
    _CreatedFC = _TypeToCreate->createContainer();
}

std::string CreateFieldContainerCommand::getCommandDescription(void) const
{
	std::string Description("");

    Description = Description + "Create " + _TypeToCreate->getName();
	
	return Description;
}

const CommandType &CreateFieldContainerCommand::getType(void) const
{
	return _Type;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

CreateFieldContainerCommand::~CreateFieldContainerCommand(void)
{
}

/*----------------------------- class specific ----------------------------*/

void CreateFieldContainerCommand::operator =(const CreateFieldContainerCommand& source)
{
    assert("Should never reach operator=");
}

