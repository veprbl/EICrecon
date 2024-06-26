# * Locate FastJet library Defines:
#
# FASTJET_FOUND FASTJET_INCLUDE_DIR FASTJET_INCLUDE_DIRS (not cached)
# FASTJET_LIBRARY FASTJET_LIBRARIES (not cached) FASTJET_LIBRARY_DIRS (not
# cached)

find_path(FASTJET_INCLUDE_DIR fastjet/version.hh
          HINTS $ENV{FASTJET_ROOT}/include ${FASTJET_ROOT_DIR}/include)

find_library(
  FASTJET_LIBRARY
  NAMES fastjet
  HINTS $ENV{FASTJET_ROOT}/lib ${FASTJET_ROOT_DIR}/lib)

# handle the QUIETLY and REQUIRED arguments and set FASTJET_FOUND to TRUE if all
# listed variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(FastJet DEFAULT_MSG FASTJET_INCLUDE_DIR
                                  FASTJET_LIBRARY)

mark_as_advanced(FASTJET_FOUND FASTJET_INCLUDE_DIR FASTJET_LIBRARY)

set(FASTJET_INCLUDE_DIRS ${FASTJET_INCLUDE_DIR})
set(FASTJET_LIBRARIES ${FASTJET_LIBRARY})
get_filename_component(FASTJET_LIBRARY_DIRS ${FASTJET_LIBRARY} PATH)
