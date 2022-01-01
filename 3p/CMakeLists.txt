add_subdirectory(./veque)

add_library(3p INTERFACE)
target_link_libraries(3p INTERFACE
	veque
)