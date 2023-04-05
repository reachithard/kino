set(DEBUG_SUFFIX "d")

qt5_wrap_ui(KINO_FORMS
        mainwindow.ui)

add_executable(kino main.cpp core/launcher.cpp core/launcher.h core/sandbox.cpp core/sandbox.h core/kino.cpp core/kino.h platform/win/launcher_win.cpp platform/win/launcher_win.h platform/launcher_platform.h ui/ui_config.cpp ui/ui_config.h platform/special_platform.h platform/win/special_win.cpp platform/win/special_win.h wrap/application.cpp wrap/application.h wrap/ael.cpp wrap/ael.h ui/style/core_fonts.cpp ui/style/core_fonts.h)
target_sources(kino PRIVATE ${KINO_FORMS} ./mainwindow.cpp)
target_include_directories(kino PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(kino PRIVATE Qt5::Core Qt5::Widgets)
target_include_directories(kino PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})