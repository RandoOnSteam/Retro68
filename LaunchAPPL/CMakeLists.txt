add_subdirectory(Common)

if(CMAKE_SYSTEM_NAME MATCHES Retro.*)
    add_subdirectory(Server)
elseif(NOT WIN32)
    add_subdirectory(Client)
endif()
