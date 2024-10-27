cmake_minimum_required(VERSION 3.28)
project(Memory)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -pthread -Wall -Werror")
set(CMAKE_DEBUG_FLAGS "${CMAKE_DEBUG_FLAGS} -g")
set(CMAKE_RELEASE_FLAGS "${CMAKE_RELEASE_FLAGS} -O2")
set(CMAKE_BUILD_TYPE Debug)

add_executable(Memory main.cpp
        tui/TerminalHelper.cpp
        tui/TerminalHelper.h
        tui/UI/Element.cpp
        tui/UI/Element.h
        tui/Functional/Input.h
        tui/UI/Window.cpp
        tui/UI/Window.h
        tui/UI/Window.h
        tui/Functional/Input.cpp
        tui/Functional/Interupts.cpp
        tui/Functional/Interupts.h
        tui/MaterialDesign/FramedElement.h
        tui/MaterialDesign/Button.h
        tui/MaterialDesign/Button.cpp
        tui/MaterialDesign/FramedElement.cpp
        tui/MaterialDesign/Positioner.h
        tui/MaterialDesign/Positioner.cpp
        tui/MaterialDesign/Text.cpp
        tui/MaterialDesign/Text.h
        tui/MaterialDesign/MemoryText.cpp
        tui/MaterialDesign/MemoryText.h
        tui/Screens/StartScreen.cpp
        tui/Screens/StartScreen.h
        tui/MaterialDesign/Group.h
        tui/MaterialDesign/InputBox.cpp
        tui/MaterialDesign/InputBox.h
        game/Application.cpp
        game/Application.h
        tui/Screens/SetupScreen.cpp
        tui/Screens/SetupScreen.h
        tui/Screens/ErrorScreen.cpp
        tui/Screens/ErrorScreen.h
        game/Game.cpp
        game/Game.h
        tui/Screens/GameScreen.cpp
        tui/Screens/GameScreen.h
        tui/MaterialDesign/Card.cpp
        tui/MaterialDesign/Card.h
        tui/Screens/ResultScreen.cpp
        tui/Screens/ResultScreen.h
        tui/Screens/SaveScreen.cpp
        tui/Screens/SaveScreen.h
        tui/Screens/LoadScreen.cpp
        tui/Screens/LoadScreen.h
)
