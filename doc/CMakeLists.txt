set(DOXYGEN_EXTRACT_ALL YES)
set(DOXYGEN_BUILTIN_STL_SUPPORT YES)
set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "readme.md")
set(DOXYGEN_GENERATE_LATEX YES)
set(DOXYGEN_USE_PDFLATEX YES)
set(DOXYGEN_COMPACT_LATEX YES)

set(DOXYGEN_AWESOME "${CMAKE_CURRENT_SOURCE_DIR}/doxygen-awesome-css")

set(DOXYGEN_GENERATE_TREEVIEW YES) # optional. Also works without treeview
set(DOXYGEN_DISABLE_INDEX NO)
set(DOXYGEN_FULL_SIDEBAR NO)
set(DOXYGEN_HTML_EXTRA_STYLESHEET
  ${CMAKE_CURRENT_SOURCE_DIR}/doxygen-custom/custom.css
  ${DOXYGEN_AWESOME}/doxygen-awesome.css
  ${DOXYGEN_AWESOME}/doxygen-awesome-sidebar-only.css
  ${DOXYGEN_AWESOME}/doxygen-awesome-sidebar-only-darkmode-toggle.css
)

set(DOXYGEN_HTML_EXTRA_FILES
  ${DOXYGEN_AWESOME}/doxygen-awesome-darkmode-toggle.js
  ${DOXYGEN_AWESOME}/doxygen-awesome-fragment-copy-button.js
  ${DOXYGEN_AWESOME}/doxygen-awesome-paragraph-link.js
  ${DOXYGEN_AWESOME}/doxygen-awesome-interactive-toc.js
)

set(DOXYGEN_TOC_INCLUDE_HEADINGS 5)

set(DOXYGEN_HTML_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/doxygen-custom/header.html)

doxygen_add_docs(doc
                "${PROJECT_SOURCE_DIR}/README.md"
                "${CMAKE_CURRENT_SOURCE_DIR}/readme.md"
                "${PROJECT_SOURCE_DIR}/examples/readme.md"
                "${PROJECT_SOURCE_DIR}/libs/readme.md"
                "${PROJECT_SOURCE_DIR}/output/readme.md"
                "${PROJECT_SOURCE_DIR}/plan/readme.md"
                "${PROJECT_SOURCE_DIR}/tests/readme.md"
                 tracey/tracey.hpp
                 tracey/cli.hpp
                 tracey/camera.hpp
                 tracey/constants.hpp
                 tracey/reader.hpp
                 tracey/geometry/box.hpp
                 tracey/geometry/geometry_list.hpp
                 tracey/geometry/geometry.hpp
                 tracey/geometry/plane.hpp
                 tracey/geometry/sphere.hpp
                 tracey/material/material.hpp
                 tracey/ray/color.hpp
                 tracey/ray/hittable_list.hpp
                 tracey/ray/hittable.hpp
                 tracey/ray/light_source.hpp
                 tracey/ray/ray.hpp
                 tracey/ray/sphere.hpp
                 tracey/utils/file_writer.hpp
                 WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/include")

