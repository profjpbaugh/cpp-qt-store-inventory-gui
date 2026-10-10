cmake_minimum_required(VERSION 3.19)
project(StoreInventoryApp LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(StoreInventoryApp
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    Product.h Product.cpp
    ProductDialog.h ProductDialog.cpp ProductDialog.ui
)

target_link_libraries(StoreInventoryApp
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS StoreInventoryApp
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET StoreInventoryApp
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
