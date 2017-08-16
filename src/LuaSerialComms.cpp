﻿// Copyright © 2008-2017 Pioneer Developers. See AUTHORS.txt for details
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
	boolean writeData = false;

	if (!(!Pi::SP || !Pi::SP->IsConnected())) {
		std::string msg = luaL_checkstring(l, 1);
		if (!writeData && msg[0] == 'h' && msg[1] == 'd' && msg.compare(heading) != 0) {
			heading.assign(msg);
			writeData = true;
		}
		if (!writeData && msg[0] == 'l' && msg[1] == 'g' && msg.compare(landingGear) != 0) {
			landingGear.assign(msg);
			writeData = true;
		}
		if (writeData && !Pi::SP->WriteData(msg.c_str(), msg.length())) {
				luaL_error(l, "Could not write to COM3.");
		}
	}
	return 0;
}


static int l_is_landing_gear_button_released(lua_State *l)
{

	bool status = Pi::isUnhandledLandingGearButtonReleased();
	lua_pushboolean(l, status);

	return 1;
}

static int l_is_level_pitch_button_released(lua_State *l)
{

	bool status = Pi::isUnhandledLevelPitchButtonReleased();
	lua_pushboolean(l, status);

	return 1;
}

static int l_is_pitch_up(lua_State *l)
{

	bool status = Pi::isPitchUp();
	lua_pushboolean(l, status);

	return 1;
}

static int l_is_pitch_down(lua_State *l)
{

	bool status = Pi::isPitchDown();
	lua_pushboolean(l, status);

	return 1;
}

static int l_is_yaw_left(lua_State *l)
{

	bool status = Pi::isYawLeft();
	lua_pushboolean(l, status);

	return 1;
}

static int l_is_yaw_right(lua_State *l)
{

	bool status = Pi::isYawRight();
	lua_pushboolean(l, status);

	return 1;
}


void LuaSerialComms::Register()
{
	lua_State *l = Lua::manager->GetLuaState();

	LUA_DEBUG_START(l);

	static const luaL_Reg l_methods[] = {
		{ "WriteData",          l_serial_comms_write_data },
		{ "isLandingGearButtonReleased",          l_is_landing_gear_button_released },
		{ "isLevelPitchButtonReleased",          l_is_level_pitch_button_released },
		{ "isPitchUp",          l_is_pitch_up },
		{ "isPitchDown",          l_is_pitch_down },
		{ "isYawRight",          l_is_yaw_left },
		{ "isYawRight",          l_is_yaw_right },
		{ 0, 0 }
	};

	lua_getfield(l, LUA_REGISTRYINDEX, "CoreImports");
	LuaObjectBase::CreateObject(l_methods, 0, 0);
	lua_setfield(l, -2, "SerialComms");
	lua_pop(l, 1);

	LUA_DEBUG_END(l, 0);
}
