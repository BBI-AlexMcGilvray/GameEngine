if(EXISTS "D:/Coding/VisualStudios/Application/builds/ThePlant/Product/Dependencies/luacpp/Source/testLuaTypes[1]_tests.cmake")
  include("D:/Coding/VisualStudios/Application/builds/ThePlant/Product/Dependencies/luacpp/Source/testLuaTypes[1]_tests.cmake")
else()
  add_test(testLuaTypes_NOT_BUILT testLuaTypes_NOT_BUILT)
endif()