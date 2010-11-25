#include <iostream>

#include "platform.hh"
#include "lua.hh"

int main (int argc, char** argv)
{
  register_lua(argc, argv);
  
  platform_start(argc, argv);

  cleanup_lua();

	return 0;
}





