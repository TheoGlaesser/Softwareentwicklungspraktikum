if(EXISTS "/home/stce/SEPraktikum/17_10_2024/Softwareentwicklungspraktikum/Tragwerk/Test/build/TrussTest[1]_tests.cmake")
  include("/home/stce/SEPraktikum/17_10_2024/Softwareentwicklungspraktikum/Tragwerk/Test/build/TrussTest[1]_tests.cmake")
else()
  add_test(TrussTest_NOT_BUILT TrussTest_NOT_BUILT)
endif()