add_test([=[testMean.simpleTest]=]  /home/logan/Desktop/CS/Programming-Abstractions-In-Cpp/Chapter-5/Collections/build/collections [==[--gtest_filter=testMean.simpleTest]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[testMean.simpleTest]=]  PROPERTIES WORKING_DIRECTORY /home/logan/Desktop/CS/Programming-Abstractions-In-Cpp/Chapter-5/Collections/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  collections_TESTS testMean.simpleTest)
