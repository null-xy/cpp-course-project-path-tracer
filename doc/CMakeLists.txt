set(DOXYGEN_EXTRACT_ALL YES)
set(DOXYGEN_BUILTIN_STL_SUPPORT YES)
set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "readme.md")
set(DOXYGEN_GENERATE_LATEX YES)
set(DOXYGEN_USE_PDFLATEX YES)
set(DOXYGEN_COMPACT_LATEX YES)

doxygen_add_docs(doc
                "${CMAKE_CURRENT_SOURCE_DIR}/readme.md"
                 tracey/tracey.hpp
                 tracey/cli.hpp
                 tracey/camera.hpp
                 ALL
                 WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/include")

