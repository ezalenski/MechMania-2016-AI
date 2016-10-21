project(decisiontree)

set(HEADER_FILES
        Action.h
        Character.h
        DecisionTree.h
        GameMap.h
        State.h
        json.hpp
        )

set(SOURCE_FILES
        Action.cpp
        Character.cpp
        DecisionTree.cpp
        GameMap.cpp
        State.cpp
        )

add_library(decisiontree STATIC ${SOURCE_FILES} ${HEADER_FILES})