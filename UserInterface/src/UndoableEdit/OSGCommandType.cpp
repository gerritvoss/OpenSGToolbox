#include <OpenSG/OSGConfig.h>

#include <iostream>

#include "OSGCommandType.h"
#include "OSGCommandFactory.h"

OSG_USING_NAMESPACE

bool CommandType::isDerivedFrom( const TypeBase & other ) const
{
	return Inherited::isDerivedFrom(other);
}

bool CommandType::isDerivedFrom( const CommandType & other ) const
{
	bool                returnValue = false;
	TypeBase *pCurrType   = TypeFactory::the()->findType(_szParentName.str());

	if(_uiTypeId == other._uiTypeId)
	{
		returnValue = true;
	}
	else
	{
		while(pCurrType != NULL && returnValue == false)
		{
			if(other._uiTypeId == pCurrType->getId())
			{
				returnValue = true;
			}
			else
			{
				pCurrType = TypeFactory::the()->findType(pCurrType->getCParentName());
			}
		}
	}

	return returnValue;
}

/*-------------------------------------------------------------------------*/
/*                            Constructors                                 */

CommandType::CommandType(const Char8  *szName,
                   const Char8  *szParentName,
                   const UInt32  uiNameSpace ) :
    Inherited(szName, szParentName, uiNameSpace),
    _uiCommandTypeId(0),
    _uiCommandTypeRootId(0)
{
    _uiCommandTypeId = CommandFactory::the()->registerType(this);
}

CommandType::CommandType(const CommandType &source) :
    Inherited(source),
    _uiCommandTypeId(source._uiCommandTypeId),
    _uiCommandTypeRootId(source._uiCommandTypeRootId)
{
}


/*-------------------------------------------------------------------------*/
/*                             Destructor                                  */

CommandType::~CommandType(void)
{
}

/*-------------------------------------------------------------------------*/
/*                             Comparison                                  */

bool CommandType::operator ==(const CommandType &other) const
{
    return *(static_cast<const Inherited *>(this)) == other;
}

bool CommandType::operator !=(const CommandType &other) const
{
    return ! (*this == other);
}
