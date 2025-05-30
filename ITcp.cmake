cacheToIncludes(${CMAKE_CURRENT_LIST_DIR})

cacheToSources(
    ${CMAKE_CURRENT_LIST_DIR}/tcp/ITcpConnection.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/tcp/ITcpConnectionData.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/tcp/ITcpManage.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/tcp/ITcpServer.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/tcp/ITcpSocket.cpp
)