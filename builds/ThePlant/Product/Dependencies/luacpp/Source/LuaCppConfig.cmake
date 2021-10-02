set(LuaCpp_VERSION 0.1.0)

#
# Provides the following configuration variables
#    LUACPP_INCLUDE_DIR  -> Containing the LuaCpp and Lua include folders
#    LUACPP_LIBRARIES    -> The shared libraries for LuaCpp na Lua
#



####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was LuaCppConfig.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

macro(set_and_check _var _file)
  set(${_var} "${_file}")
  if(NOT EXISTS "${_file}")
    message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
  endif()
endmacro()

macro(check_required_components _NAME)
  foreach(comp ${${_NAME}_FIND_COMPONENTS})
    if(NOT ${_NAME}_${comp}_FOUND)
      if(${_NAME}_FIND_REQUIRED_${comp})
        set(${_NAME}_FOUND FALSE)
      endif()
    endif()
  endforeach()
endmacro()

####################################################################################

set_and_check(LuaCpp_INCLUDE_DIR "${PACKAGE_PREFIX_DIR}/include/LuaCpp")
set_and_check(LuaCpp_INSTALL_LIBDIR "${PACKAGE_PREFIX_DIR}/lib")

find_package(Lua REQUIRED)

set(LUACPP_INCLUDE_DIR "${LuaCpp_INCLUDE_DIR};${LUA_INCLUDE_DIR}")
set(LUACPP_LIBRARIES "${LuaCpp_INSTALL_LIBDIR}/libluacpp.so;${LUA_LIBRARIES}")

check_required_components(LuaCpp)
