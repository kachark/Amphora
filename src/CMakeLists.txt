
add_executable(amphora
  amphora.cpp
  amphora_util.cpp
  crypto_util.cpp
  cli.cpp
  account.cpp
  account_controller.cpp
  user.cpp
  user_controller.cpp
  crypto.cpp
  crypto_controller.cpp
  )

target_link_libraries(amphora
  PRIVATE
    ${Boost_LIBRARIES}
    ${CRYPTOPP}
  )
