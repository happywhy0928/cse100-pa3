test_HC_tree_exe = executable('test_HCTree.cpp.executable',
sources: ['test_HCTree.cpp'],
dependencies: [HC_tree_dep, input_stream_dep, output_stream_dep, gtest_dep])
test('my HCTree test', test_HC_tree_exe)

test_bitinput_exe = executable('test_BitInputStream.cpp.executable',
sources: ['test_BitInputStream.cpp'],
dependencies: [HC_tree_dep, input_stream_dep, output_stream_dep, gtest_dep])
test('my bitinput test', test_bitinput_exe)

test_bitoutput_exe = executable('test_BitOutputStream.cpp.executable',
sources: ['test_BitOutputStream.cpp'],
dependencies: [HC_tree_dep, input_stream_dep, output_stream_dep, gtest_dep])
test('my bitoutput test', test_bitoutput_exe)