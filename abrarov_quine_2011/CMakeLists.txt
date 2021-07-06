set( FADDEEVAS_ABRAROV_QUINE_HEADERS definitions.h coefficients.h ErrorFunctions.h )
set( FADDEEVAS_ABRAROV_QUINE_SOURCES ErrorFunctions.c )

add_library( faddeevas_abrarov_quine OBJECT
    ${FADDEEVAS_ABRAROV_QUINE_HEADERS} ${FADDEEVAS_ABRAROV_QUINE_SOURCES} )

target_include_directories( faddeevas_abrarov_quine PRIVATE ${CMAKE_SOURCE_DIR} )
set( FADDEEVAS_MODULES ${FADDEEVAS_MODULES}
     $<TARGET_OBJECTS:faddeevas_abrarov_quine> PARENT_SCOPE )
