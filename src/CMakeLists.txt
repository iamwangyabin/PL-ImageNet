add_library( SimpleSFM SHARED
        Frame.cpp
        svf.cpp
#        Matches.cpp
        System.cpp
        )

target_link_libraries( SimpleSFM
        ${THIRD_PARTY_LIBS}
        )