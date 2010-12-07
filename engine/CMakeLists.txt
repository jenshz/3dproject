
if(${WIN32})
  set(platform_sources win32/platform.cc)
else(${WIN32})
  set(platform_sources linux/font.cc)
endif(${WIN32})

add_library(engine ${platform_sources} engine.cc object.cc nurbs.cc lua.cc gl.cc
  quaternion.cc camera.cc texture.cc pngread.cc)

