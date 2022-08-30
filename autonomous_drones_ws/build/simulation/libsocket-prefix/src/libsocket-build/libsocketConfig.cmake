set(libsocket_INCLUDE_DIRS "/home/gotvinne/Documents/autonomous_drones_ss2022/autonomous_drones_ws/build/simulation/libsocket-prefix/src/libsocket/headers")

set(libsocket_BINARY_DIR "/home/gotvinne/Documents/autonomous_drones_ss2022/autonomous_drones_ws/build/simulation/libsocket-prefix/src/libsocket-build")

include(${libsocket_BINARY_DIR}/libsocketTargets.cmake)

set(libsocket_LIBRARIES socket++)
