file(GLOB_RECURSE sources CONFIGURE_DEPENDS
    src/*.c
    src/*.h
    include/*.h
)

add_executable(image-transformer ${sources}
        include/image.h
        include/bmp.h
        include/transfo.h
        src/image.c
        src/bmp.c
        src/transf.c)
target_include_directories(image-transformer PRIVATE src include)
