# aux_source_directory(. SRC_LIST)
set(SRC_LIST rpc_config.cpp 
             rpc_application.cpp 
             rpc_header.pb.cc 
             rpc_provider.cpp 
             rpc_channel.cpp 
             rpc_controller.cpp
             rpc_logger.cpp)
add_library(rpc ${SRC_LIST})
target_link_libraries(rpc muduo_net muduo_base pthread)