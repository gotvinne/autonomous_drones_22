# Config file for the module example
# It defines the following variables:
# ${PROJECT_NAME}_INCLUDE_DIR  - Location of header files
# ${PROJECT_NAME}_INCLUDE_DIRS - All include directories needed to use ${PROJECT_NAME}
# ${PROJECT_NAME}_LIBRARY      - ${PROJECT_NAME} library
# ${PROJECT_NAME}_LIBRARIES    - ${PROJECT_NAME} library and all dependent libraries
# ${PROJECT_NAME}_DEFINITIONS  - Compiler definitions as semicolon separated list

find_library(utils_LIBRARY utils
  PATHS /home/gotvinne/Documents/autonomous_drones_ss2022/autonomous_drones_ws/devel/lib
  NO_DEFAULT_PATH
  )

set(utils_LIBRARIES ${utils_LIBRARY}
  )

find_path(utils_INCLUDE_DIR time_manager/clock.h
  PATHS /home/gotvinne/Documents/autonomous_drones_ss2022/autonomous_drones_ws/devel/include/utils
  NO_DEFAULT_PATH
  )

set(utils_INCLUDE_DIRS ${utils_INCLUDE_DIR}
  )

set(utils_DEFINITIONS "-std=c++11")
