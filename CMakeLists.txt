cmake_minimum_required(VERSION 3.17)
project(SEICert)

set(CMAKE_CXX_STANDARD 17)

add_executable(SEICert main.cpp CPPRules/Containers.h CPPRules/Declerations.h CPPRules/Strings.h CPPRules/MemoryManagement.h CRules/MemoryManagement.h)