set( FADDEEVAS_CERNLIB_C_REV3_HEADERS ErrorFunctions.h definitions.h )
set( FADDEEVAS_CERNLIB_C_REV3_SOURCES ErrorFunctions.c )

add_library( faddeevas_cernlib_c_rev3 OBJECT
    ${FADDEEVAS_CERNLIB_C_REV3_HEADERS} ${FADDEEVAS_CERNLIB_C_REV3_SOURCES} )

target_include_directories( faddeevas_cernlib_c_rev3 PRIVATE ${CMAKE_SOURCE_DIR} )
set( FADDEEVAS_MODULES ${FADDEEVAS_MODULES}
     $<TARGET_OBJECTS:faddeevas_cernlib_c_rev3> PARENT_SCOPE )
