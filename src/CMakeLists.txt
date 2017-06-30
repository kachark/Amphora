
add_executable(amphora
  amphora.cpp
  amphora_util.cpp
  crypto_util.cpp
  amphora_interface.cpp
  account.cpp
  account_manager.cpp
  user.cpp
  user_manager.cpp
  )

target_link_libraries(amphora
  PRIVATE
    ${Boost_LIBRARIES}
    cryptopp-shared
  )
