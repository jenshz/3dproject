#ifndef _LUA_HH_
#define _LUA_HH_

#include "stdafx.h"

namespace System {
  extern bool exiting;
}

extern lua_State *lua;

void register_lua(int argc, char*argv[]);
void cleanup_lua();

#endif
