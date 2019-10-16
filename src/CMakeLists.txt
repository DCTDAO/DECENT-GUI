if( APPLE)
    find_program( BREW_PROGRAM brew )
    if( BREW_PROGRAM )
        execute_process( COMMAND "${BREW_PROGRAM}" "--prefix" OUTPUT_VARIABLE HOMEBREW_PREFIX OUTPUT_STRIP_TRAILING_WHITESPACE )
        message( STATUS "Homebrew prefix: ${HOMEBREW_PREFIX}")
        list( APPEND CMAKE_PREFIX_PATH "${HOMEBREW_PREFIX}/opt/qt" )
    endif()
endif()

find_package(nlohmann_json REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5LinguistTools REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(MACOSX_BUNDLE_ICON_FILE desktop)
set(MACOSX_BUNDLE_BUNDLE_NAME ${CMAKE_PROJECT_NAME})

set(GUI_WALLET_ICON ${CMAKE_CURRENT_SOURCE_DIR}/desktop.icns)
set_source_files_properties(${GUI_WALLET_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

set(GUI_WALLET_TS_FILES ${CMAKE_CURRENT_SOURCE_DIR}/languages/decent_en.ts)
set_source_files_properties(${GUI_WALLET_TS_FILES} PROPERTIES OUTPUT_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/languages)

set(GUI_WALLET_RESOURCES resources.qrc)
set(GUI_WALLET_PRECOMPILED_SOURCE_FILE "")
set(GUI_WALLET_PRECOMPILED_HEADER_FILE stdafx.h)
if( WIN32 )
    list(APPEND GUI_WALLET_RESOURCES DECENT.rc)
    list(APPEND GUI_WALLET_PRECOMPILED_SOURCE_FILE stdafx.cpp)
    qt5_add_translation(GUI_WALLET_QM_FILES ${GUI_WALLET_TS_FILES})
else()
    qt5_create_translation(GUI_WALLET_QM_FILES ${CMAKE_CURRENT_SOURCE_DIR} ${GUI_WALLET_TS_FILES} OPTIONS -no-obsolete)
endif()

add_executable(${CMAKE_PROJECT_NAME} MACOSX_BUNDLE WIN32
               ${GUI_WALLET_PRECOMPILED_SOURCE_FILE} # must be the first file
               ${GUI_WALLET_PRECOMPILED_HEADER_FILE}
               ${GUI_WALLET_RESOURCES}
               ${GUI_WALLET_ICON}
               ${GUI_WALLET_QM_FILES}
               browse_content_tab.cpp
               browse_content_tab.hpp
               decent_button.cpp
               decent_button.hpp
               decent_label.cpp
               decent_label.hpp
               decent_line_edit.cpp
               decent_line_edit.hpp
               decent_text_edit.cpp
               decent_text_edit.hpp
               gui_wallet_global.cpp
               gui_wallet_global.hpp
               gui_wallet_tabcontentmanager.cpp
               gui_wallet_tabcontentmanager.hpp
               main_gui_wallet.cpp
               mainwindow.cpp
               mainwindow.hpp
               mining_vote_popup.cpp
               mining_vote_popup.hpp
               mining_vote_tab.cpp
               mining_vote_tab.hpp
               overview_tab.cpp
               overview_tab.hpp
               purchased_tab.cpp
               purchased_tab.hpp
               rev_history_dlg.cpp
               rev_history_dlg.hpp
               richdialog.cpp
               richdialog.hpp
               transactions_tab.cpp
               transactions_tab.hpp
               update_prog_bar.cpp
               update_prog_bar.hpp
               upload_popup.cpp
               upload_popup.hpp
               upload_tab.cpp
               upload_tab.hpp
             )

if( APPLE OR WIN32 )
    add_subdirectory(updatemanager)
    target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE UPDATE_MANAGER)
    target_sources(${CMAKE_PROJECT_NAME} PRIVATE update_manager.cpp update_manager.hpp)
    target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE update)
endif()

if( WIN32 )
    add_custom_target(translations ALL DEPENDS ${GUI_WALLET_QM_FILES})
    add_dependencies(${CMAKE_PROJECT_NAME} translations)
endif()

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
                      graphene_wallet
                      graphene_account_history
                      graphene_transaction_history
                      decent_seeding
                      decent_elasticsearch
                      graphene_miner
                      nlohmann_json::nlohmann_json
                      Qt5::Widgets
                      ${CMAKE_DL_LIBS}
                      ${PLATFORM_SPECIFIC_LIBS}
                     )

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_BUNDLE_NAME "DECENT")
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/Info.plist.in")

if( WIN32 )
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeModules")
    include(cotire)

    set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES COTIRE_ADD_UNITY_BUILD FALSE)
    set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT ${GUI_WALLET_PRECOMPILED_HEADER_FILE})
    cotire(${CMAKE_PROJECT_NAME})
endif()

install( TARGETS ${CMAKE_PROJECT_NAME} BUNDLE DESTINATION . RUNTIME DESTINATION bin )
