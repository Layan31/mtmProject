cmake_minimum_required(VERSION 3.28)
project(HW4)

set(CMAKE_CXX_STANDARD 17)

add_executable(HW4 main.cpp
        MatamStory.cpp
        Utilities.cpp
        Players/Job.h
        Players/Character.h
        Players/Character.cpp
        Players/Player.cpp
        Events/Encounter.h
        Events/SpecialEvent.h
        Events/Event.cpp
        Events/Event.cpp
        Events/Encounter.cpp
        Events/SpecialEvent.cpp
        main.cpp
        Players/PlayerFactory.cpp
        Players/PlayerFactory.h
        Events/EventFactory.cpp
        Players/Job.cpp)
