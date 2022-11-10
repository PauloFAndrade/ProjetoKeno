cmake_minimum_required(VERSION 3.2)
project (KenoGame VERSION 1.0.0 LANGUAGES CXX )

#=== Main App ===

include_directories( "core" )

set ( CMAKE_CXX_FLAGS "-Wall" )

#add_executable(keno)

#target_sources(
#    keno
#    PRIVATE
#        core/keno_bet.h
#        core/keno_common.h
#        core/main.cpp
#        core/keno_bet.cpp
        #core/backup.cpp
#)

add_executable( keno
                core/main.cpp
                #core/keno_game.cpp
                core/keno_bet.cpp )

target_compile_features( keno PUBLIC cxx_std_17 )
