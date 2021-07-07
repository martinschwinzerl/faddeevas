set( FADDEEVAS_ALG680_HEADERS ErrorFunctions.h definitions.h )
set( FADDEEVAS_ALG680_SOURCES ErrorFunctions.c )

add_library( faddeevas_alg680 OBJECT
    ${FADDEEVAS_ALG680_HEADERS} ${FADDEEVAS_ALG680_SOURCES} )

target_include_directories( faddeevas_alg680 PRIVATE ${CMAKE_SOURCE_DIR} )
set( FADDEEVAS_MODULES ${FADDEEVAS_MODULES}
     $<TARGET_OBJECTS:faddeevas_alg680> PARENT_SCOPE )
