if(EXISTS "D:/Coding/VisualStudios/Application/builds/ThePlant/Product/Dependencies/luacpp/Source/testLuaMetaObject[1]_tests.cmake")
  include("D:/Coding/VisualStudios/Application/builds/ThePlant/Product/Dependencies/luacpp/Source/testLuaMetaObject[1]_tests.cmake")
else()
  add_test(testLuaMetaObject_NOT_BUILT testLuaMetaObject_NOT_BUILT)
endif()
