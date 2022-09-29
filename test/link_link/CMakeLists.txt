add_executable(test_game_logic game_logic.cpp)
add_test(NAME test_game_logic COMMAND test_game_logic)
target_link_libraries(test_game_logic PUBLIC Qt6::Test)