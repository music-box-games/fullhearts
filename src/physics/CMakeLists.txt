file(GLOB physsrc "./*.cc")
add_library(physics ${LINK_TYPE} ${physsrc})