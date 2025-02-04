# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_chase_object_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED chase_object_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(chase_object_FOUND FALSE)
  elseif(NOT chase_object_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(chase_object_FOUND FALSE)
  endif()
  return()
endif()
set(_chase_object_CONFIG_INCLUDED TRUE)

# output package information
if(NOT chase_object_FIND_QUIETLY)
  message(STATUS "Found chase_object: 0.0.0 (${chase_object_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'chase_object' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${chase_object_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(chase_object_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${chase_object_DIR}/${_extra}")
endforeach()
