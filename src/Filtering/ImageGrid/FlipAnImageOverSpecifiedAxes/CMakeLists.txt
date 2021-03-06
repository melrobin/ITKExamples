cmake_minimum_required(VERSION 3.10.2)

project( FlipAnImageOverSpecifiedAxes )

find_package( ITK REQUIRED )
include( ${ITK_USE_FILE} )

add_executable( FlipAnImageOverSpecifiedAxes Code.cxx )
target_link_libraries( FlipAnImageOverSpecifiedAxes ${ITK_LIBRARIES} )

install( TARGETS FlipAnImageOverSpecifiedAxes
  DESTINATION bin/ITKSphinxExamples/Filtering/ImageGrid
  COMPONENT Runtime
)

install( FILES Code.cxx CMakeLists.txt Code.py
  DESTINATION share/ITKSphinxExamples/Code/Filtering/ImageGrid/FlipAnImageOverSpecifiedAxes
  COMPONENT Code
)

enable_testing()

set( input_image ${CMAKE_CURRENT_BINARY_DIR}/Yinyang.png )
set( output_image Output.png )

add_test( NAME FlipAnImageOverSpecifiedAxesTest
  COMMAND ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/FlipAnImageOverSpecifiedAxes
    ${input_image}
    ${output_image}
    0
  )

if( ITK_WRAP_PYTHON )
  string( REPLACE . "Python." output_image "${output_image}" )
  add_test( NAME FlipAnImageOverSpecifiedAxesTestPython
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Code.py
      ${input_image}
      ${output_image}
      0
    )
endif()
