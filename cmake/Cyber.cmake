set(CYBER_ROOT "../opt/" CACHE PATH "CYBER_ROOT")
set(CYBER_INCLUDE_DIR "${CYBER_ROOT}/include")
set(CYBER_LIB_DIR "${CYBER_ROOT}/lib")

include_directories(${CYBER_INCLUDE_DIR}/cyber)
include_directories(${CYBER_INCLUDE_DIR}/cyber/proto)
include_directories(${CYBER_INCLUDE_DIR}/cyber/class_loader)
include_directories(${CYBER_INCLUDE_DIR}/cyber/class_loader/utility)

link_directories(${CYBER_LIB_DIR})
