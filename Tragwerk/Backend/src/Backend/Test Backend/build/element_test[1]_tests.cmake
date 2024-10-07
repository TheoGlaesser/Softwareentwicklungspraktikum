add_test( Element.variables [==[/home/stce/SEPraktikum/Local/Softwareentwicklungspraktikum/Tragwerk/Backend/src/Backend/Test Backend/build/element_test]==] [==[--gtest_filter=Element.variables]==] --gtest_also_run_disabled_tests)
set_tests_properties( Element.variables PROPERTIES WORKING_DIRECTORY [==[/home/stce/SEPraktikum/Local/Softwareentwicklungspraktikum/Tragwerk/Backend/src/Backend/Test Backend/build]==])
set( element_test_TESTS Element.variables)
