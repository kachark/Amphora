
add_executable(amphora
  amphora.cpp
  amphora_util.cpp
  amphora_interface.cpp
  amphora_backend.cpp
  account.cpp
  )

target_link_libraries(amphora
  PRIVATE
    ${Boost_LIBRARIES}
    cryptopp-shared
  )
