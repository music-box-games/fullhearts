file(GLOB eventsrc "./*.cc")
add_library(events ${LINK_TYPE} ${eventsrc})