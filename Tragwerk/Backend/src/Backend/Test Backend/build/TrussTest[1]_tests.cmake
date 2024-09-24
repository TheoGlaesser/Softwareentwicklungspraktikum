add_test( TrussTest.General [==[/home/stce/SEPraktikum/Local/Softwareentwicklungspraktikum/Tragwerk/Backend/src/Backend/Test Backend/build/TrussTest]==] [==[--gtest_filter=TrussTest.General]==] --gtest_also_run_disabled_tests)
set_tests_properties( TrussTest.General PROPERTIES WORKING_DIRECTORY [==[/home/stce/SEPraktikum/Local/Softwareentwicklungspraktikum/Tragwerk/Backend/src/Backend/Test Backend/build]==])
set( TrussTest_TESTS TrussTest.General)
