set( FADDEEVAS_CERNLIB_C_REV2_HEADERS ErrorFunctions.h definitions.h )
set( FADDEEVAS_CERNLIB_C_REV2_SOURCES ErrorFunctions.c )

add_library( faddeevas_cernlib_c_rev2 OBJECT
    ${FADDEEVAS_CERNLIB_C_REV2_HEADERS} ${FADDEEVAS_CERNLIB_C_REV2_SOURCES} )

target_include_directories( faddeevas_cernlib_c_rev2 PRIVATE ${CMAKE_SOURCE_DIR} )
set( FADDEEVAS_MODULES ${FADDEEVAS_MODULES}
     $<TARGET_OBJECTS:faddeevas_cernlib_c_rev2> PARENT_SCOPE )
