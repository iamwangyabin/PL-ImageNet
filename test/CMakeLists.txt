add_executable( testSiftMatch testSiftMatch.cpp)
target_link_libraries( testSiftMatch SimpleSFM )

add_executable( draw3D testDraw3d.cpp)
target_link_libraries( draw3D SimpleSFM )