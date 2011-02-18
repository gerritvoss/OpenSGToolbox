/*---------------------------------------------------------------------------*\
 *                          OpenSG Toolbox Lua                               *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala                                                   *
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


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define OSG_COMPILELUALIB
//#define OSG_WITH_LUA_DEBUGGER


#include "OSGConfig.h"

#include "OSGLuaUtils.h"
#include "OSGLuaManager.h"
#include <boost/lexical_cast.hpp>

#ifdef OSG_WITH_LUA_DEBUGGER

OSG_BEGIN_NAMESPACE

lua_details::popStackElements::popStackElements(lua_State* L, int num) : L_(L), num_(num)
{
}

void lua_details::popStackElements::dec(void)
{
    --num_;
}

lua_details::popStackElements::~popStackElements(void)
{
    try
    {
        if (num_ > 0)
            lua_pop(L_, num_);
    }
    catch (...)
    {}
}

lua_details::popStackElements::popStackElements(void)
{
    assert(false);
}

lua_details::popStackElements::popStackElements(const popStackElements&)
{
    assert(false);
}

UInt32 lua_details::getNumFields(lua_State* L, int idx)
{
    UInt32 count(0);
    if(lua_istable(L, idx))
    {
        /* table is in the stack at index 'idx' */
        lua_pushnil(L);  /* first key */
	    int table= lua_gettop(L) - 1;
        while (lua_next(L, table) != 0)
        {
            /* uses 'key' (at index -2) and 'value' (at index -1) */
            ++count;
            /* removes 'value'; keeps 'key' for next iteration */
            lua_pop(L, 1);
        }
    }
    
    return count;
}

bool lua_details::listTable(lua_State* L, int idx, TableInfo& out, int recursive)
{
	out.clear();

	if (lua_type(L, idx) != LUA_TTABLE)
		return false;

	UInt32 size= getNumFields(L, idx);

	out.reserve(size);

	// table to traverse
	lua_pushvalue(L, idx);

	// push a key
	lua_pushnil(L);

	popStackElements pop(L, 2);	// remove key & table off the stack at the end of this fn
//	popStackElements pop(L, 1);	// remove table off the stack at the end of this fn

	int table= lua_gettop(L) - 1;

	// traverse a table
	while (lua_next(L, table))
	{
		popStackElements pop(L, 1);

        Value Key(L, -2);
        Value Val(L, -1, recursive);
		LuaField field(Key,Val);

		out.push_back(field);
	}

	pop.dec();	// final lua_next call removed key

	return true;
}


std::string lua_details::tableAsString(const TableInfo& table, size_t limit)
{
	std::ostringstream ost;

	ost << "{ ";

	const size_t count= table.size();

	for (size_t i= 0; i < count; ++i)
	{
		const LuaField& f= table[i];

		if (i > 0)
			ost << ", ";

		ost << f.getKey().getValue() << " = " << f.getValue().getValue();

		if (i + 1 == limit)
		{
			ost << ", ... ";
			break;
		}
	}

	if (count > 0)
		ost << ' ';

	ost << "}";

	return ost.str();
}


bool lua_details::listVirtualStack(lua_State* L, ValueStack& stack, size_t table_size_limit)
{
	int size= lua_gettop(L);

	stack.clear();
	stack.reserve(size);

	for (int idx= size - 1; idx > 0; --idx)
	{
		Value v(L, idx, 1, table_size_limit);

		stack.push_back(v);
	}

	return true;
}


bool lua_details::pushFieldOntoStack(lua_State* L, const FieldStack& theFieldStack)
{

    if(theFieldStack.size() == 0)
    {
        lua_pushstring(L,"_G");
        lua_gettable(L, LUA_GLOBALSINDEX);  //Push The global table onto the stack
    }
    else
    {
        //Get the Lua value
        for(UInt32 i(0) ; i<theFieldStack.size() ; ++i)
        {
            if(i == 0)
            {
                if(!theFieldStack[i].getKey().push(L))//push the key of the table on the stack
                {
                    return false;
                }
                lua_gettable(L, LUA_GLOBALSINDEX);  //Push The table onto the stack
            }
            else
            {
                //Check if the the value given is a table
                if(!lua_istable(L, -1))
                {
                    //Pop the value, and the original table from the stack
                    lua_pop(L, 2);

                    return false;
                }
            
                
                if(!theFieldStack[i].getKey().push(L))//push the key of the table on the stack
                {
                    return false;
                }
                lua_gettable(L, -2);  //Push The table onto the stack

                //Remove the original table from the stack
                lua_remove(L, -2);
            }
        }
    }
    return true;
}


OSG_END_NAMESPACE
#endif /* OSG_WITH_LUA_DEBUGGER */

