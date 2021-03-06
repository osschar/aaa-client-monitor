
FIND_PATH(PCRE_INCLUDES pcre.h
  HINTS
  ${PCRE_INCLUDE_DIR}
  $ENV{PCRE_INCLUDE_DIR}
  /usr
  PATH_SUFFIXES include
)

FIND_LIBRARY(PCRE_LIB pcre
  HINTS
  ${PCRE_LIB_DIR}
  $ENV{PCRE_LIB_DIR}
  /usr
  PATH_SUFFIXES lib
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Pcre DEFAULT_MSG PCRE_LIB PCRE_INCLUDES)

