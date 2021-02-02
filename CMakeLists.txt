cmake_minimum_required (VERSION 2.6 FATAL_ERROR)

project      (Ep)

# FreeGlut 3.2.1
find_package(FreeGLUT PATHS C:/bin/freeglut-3.2.1 REQUIRED)
include_directories(${FreeGLUT_INCLUDE_DIRS})
link_directories(${FreeGLUT_LIBRARY_DIRS} "c:/bin/GLUT/lib" )
add_definitions(${FreeGLUT_DEFINITIONS})
if(NOT FreeGLUT_FOUND)
    message(ERROR " FreeGLUT not found!")
else()
    message(" FreeGLUT Found!")
    message("Include: ${FreeGLUT_INCLUDE_DIRS}")
    message("Lib: ${FreeGLUT_LIBRARY_DIRS}")
    message("Def: ${FreeGLUT_DEFINITIONS}")
    message("Include: ${GLUT_INCLUDE_DIRS}")
    message("Lib: ${GLUT_LIBRARY_DIRS}")
    message("Def: ${GLUT_DEFINITIONS}")
endif(NOT FreeGLUT_FOUND)

# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OpenGL not found!")
else()
    message(" OpenGL Found!")
endif(NOT OPENGL_FOUND)


set  (project_SOURCES 
CMakeProject1/VisOf/main.cpp 
CMakeProject1/VisOf/ColorRGBA.hpp
CMakeProject1/VisOf/Point.hpp
CMakeProject1/VisOf/point3dutils.hpp
CMakeProject1/VisOf/PrintBase.hpp
CMakeProject1/VisOf/printof.hpp
CMakeProject1/VisOf/PrintOfPart.hpp
CMakeProject1/VisOf/GL_interactor.cpp
CMakeProject1/VisOf/scrInteractor.cpp
CMakeProject1/VisOf/TrackBall.cpp
)
set  (project_HEADERS 
CMakeProject1/Of/Cores.h
GL_interactor.h
scrInteractor.h
TrackBall.h
of/ofBase.h
of/ofBinaryIO.h
of/ofBoundaryCellCIterator2D.h
of/ofBoundaryCellIterator2D.h
of/ofBoundaryCellIterator.h
of/ofCell2D.h
of/ofCell3D.h
of/ofCell.h
of/ofCellsIterator.h
of/ofCgmPointsReader.h
of/ofCgmReader.h
of/ofDelaunay2D.h
of/ofDiDo3D.h
of/ofGeometric.h
of/of.h
of/ofIterator.h
of/ofKdTree.h
of/ofList.h
of/ofMacros.h
of/ofMarkFrat.h
of/ofMesh2D.h
of/ofMesh3D.h
of/ofMesh.h
of/ofMeshNOSurface.h
of/ofMeshOper.h
of/ofMeshSurface.h
of/ofMeshWriter.h
of/ofMyCell.h
of/ofMyDelaunay2D.h
of/ofMyGeometric.h
of/ofMyMesh.h
of/ofMyOffReader.h
of/ofMyof.h
of/ofMyTraits.h
of/ofMyVertex3D.h
of/ofMyVis.h
of/ofOffPointsReader.h
of/ofOffReader.h
of/ofOffWriter.h
of/ofOfReader.h
of/ofOfWriter.h
of/ofOperators.h
of/ofParameters.h
of/ofPgReader.h
of/ofPlane.h
of/ofPoints2DReader.h
of/ofPolyDataPointsReader.h
of/ofPolyDataReader.h
of/ofPolyDataWriter.h
of/ofPolygonBoundaries.h
of/ofPolygon.h
of/ofPolyWriter.h
of/ofReader.h
of/ofRemesh.h
of/ofRuppert2D.h
of/ofSearchDIDO.h
of/ofSing.h
of/ofSingularVertex.h
of/ofTetGen3D.h
of/ofTetGen3DReader.h
of/ofTetGenReader.h
of/ofTopology.h
of/ofTraits.h
of/ofTransfSolution.h
of/ofTReader.h
of/ofVector.h
of/ofVertex2D.h
of/ofVertex3D.h
of/ofVertex.h
of/ofVertexStarIterator2D.h
of/ofVertexStarIterator3D.h
of/ofVertexStarIterator.h
of/ofVertexStarIteratorSurface.h
of/ofVertexStarIteratorSurfaceVertex.h
of/ofVerticesIterator.h
of/ofVis2D.h
of/ofVtkPointsReader.h
of/ofvtkreader.h
of/ofVtkWriter.h
of/ofWriter.h
of/ofWrlReader.h
of/ofXmlParser.h
of/pair.h
of/ShePolyWriter.h
)



include_directories( ${CMAKE_SOURCE_DIR}/CMakeProject1/VisOf )
include_directories( ${CMAKE_SOURCE_DIR}/CMakeProject1/VisOf/Utils )
include_directories( ${CMAKE_SOURCE_DIR}/CMakeProject1/VisOf/iterFunc )
include_directories( ${CMAKE_SOURCE_DIR}/CMakeProject1/of )
include_directories( ${OPENGL_INCLUDE_DIRS}  ${FreeGLUT_INCLUDE_DIRS} )
# temporario: freeglut-3.2.1
include_directories( "c:/bin/freeglut-3.2.1/include/" )

ADD_EXECUTABLE  (ep 
    CMakeProject1/main.cpp 
    CMakeProject1/scrInteractor.cpp  
    CMakeProject1/TrackBall.cpp
    )

set(CMAKE_CXX_FLAGS "-D_CRT_SECURE_NO_WARNINGS -std=c++17 ${CMAKE_CXX_FLAGS}")

target_link_libraries(ep ${OPENGL_LIBRARIES} ${GLUT_LIBRARY}
"c:/bin/GLUT/lib/Debug" "c:/bin/GLUT/lib/Release"  )





