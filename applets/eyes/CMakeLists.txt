install(FILES eyes.svg
        DESTINATION ${PLASMA_DATA_INSTALL_DIR}/desktoptheme/default/widgets/)

kde4_install_icons(${ICON_INSTALL_DIR})

plasma_install_package(package org.kde.plasma.eyes)
