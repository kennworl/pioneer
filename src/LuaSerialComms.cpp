// Copyright © 2008-2017 Pioneer Developers. See AUTHORS.txt for details
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "LuaSerialComms.h"
#include "LuaObject.h"
#include "LuaUtils.h"
#include "Pi.h"
#include "SerialClass.h"

/*
* Interface: Serial Comms
*
* Player communication functions to custom hardware.
*/



/*
* Function: WriteData
*
* Post a message to the COM3 Serial Port.
*
* > Comms.Message(message)
*
* Parameters:
*
*   message - the message text to post
*
* Example:
*
* > SerialComms.WriteData("123")
*
* Availability:
*
*   ???
*
* Status:
*
*   experimental
*/

static int l_serial_comms_write_data(lua_State *l)
{
	if (!Pi::SP || !Pi::SP->IsConnected())
		luaL_error(l, "COM3 is not connected.");

	std::string msg = luaL_checkstring(l, 1);
	if (msg.compare(heading) != 0) {
		heading.assign(msg);
		if (!Pi::SP->WriteData(msg.c_str(), msg.length()))
			luaL_error(l, "Could not write to COM3.");
	}
	return 0;
}


void LuaSerialComms::Register()
{
	lua_State *l = Lua::manager->GetLuaState();

	LUA_DEBUG_START(l);

	static const luaL_Reg l_methods[] = {
		{ "WriteData",          l_serial_comms_write_data },
		{ 0, 0 }
	};

	lua_getfield(l, LUA_REGISTRYINDEX, "CoreImports");
	LuaObjectBase::CreateObject(l_methods, 0, 0);
	lua_setfield(l, -2, "SerialComms");
	lua_pop(l, 1);

	LUA_DEBUG_END(l, 0);
}
