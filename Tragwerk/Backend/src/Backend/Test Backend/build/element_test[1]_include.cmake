if(EXISTS "/home/stce/SEPraktikum/Local/Softwareentwicklungspraktikum/Tragwerk/Backend/src/Backend/Test Backend/build/element_test[1]_tests.cmake")
  include("/home/stce/SEPraktikum/Local/Softwareentwicklungspraktikum/Tragwerk/Backend/src/Backend/Test Backend/build/element_test[1]_tests.cmake")
else()
  add_test(element_test_NOT_BUILT element_test_NOT_BUILT)
endif()