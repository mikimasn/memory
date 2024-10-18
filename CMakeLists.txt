cmake_minimum_required(VERSION 3.29)
project(MemoryGejanci)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)

add_executable(MemoryGejanci main.cpp
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
)
