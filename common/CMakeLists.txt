set( FADDEEVAS_COMMON_C99_HEADERS definitions.h helper_functions.h )
set( FADDEEVAS_COMMON_C99_SOURCES helper_functions.c )

add_library( faddeevas_common_c99 OBJECT
    ${FADDEEVAS_COMMON_C99_HEADERS} ${FADDEEVAS_COMMON_C99_SOURCES} )

target_include_directories( faddeevas_common_c99 PRIVATE ${CMAKE_SOURCE_DIR} )

set( FADDEEVAS_MODULES ${FADDEEVAS_MODULES}
     $<TARGET_OBJECTS:faddeevas_common_c99> PARENT_SCOPE )
