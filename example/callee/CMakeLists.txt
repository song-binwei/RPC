set(SRC_LIST userservice.cpp ../user.pb.cc ../friend.pb.cc)
add_executable(provider ${SRC_LIST})
target_link_libraries(provider rpc protobuf)