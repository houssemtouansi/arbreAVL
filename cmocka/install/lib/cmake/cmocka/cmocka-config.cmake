get_filename_component(CMOCKA_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)

if (EXISTS "${CMOCKA_CMAKE_DIR}/CMakeCache.txt")
    # In build tree
    include(${CMOCKA_CMAKE_DIR}/cmocka-build-tree-settings.cmake)
else()
    set(CMOCKA_INCLUDE_DIR /home/houssem/tp_noté_c/ArbreAVL/cmocka-1.1.1/install/include)
endif()

set(CMOCKA_LIBRARY /home/houssem/tp_noté_c/ArbreAVL/cmocka-1.1.1/install/lib/libcmocka.so)
set(CMOCKA_LIBRARIES /home/houssem/tp_noté_c/ArbreAVL/cmocka-1.1.1/install/lib/libcmocka.so)
