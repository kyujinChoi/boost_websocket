#
# Copyright (c) 2016-2017 Vinnie Falco (vinnie dot falco at gmail dot com)
#
# Distributed under the Boost Software License, Version 1.0. (See accompanying
# file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Official repository: https://github.com/boostorg/beast
#

# GroupSources(include/boost/beast beast)
# GroupSources(example/http/server/sync "/")

# add_executable (http-server-sync
#     ${BOOST_BEAST_FILES}
#     Jamfile
#     http_server_sync.cpp
# )

# target_link_libraries(http-server-sync
#     lib-asio
#     lib-asio-ssl
#     lib-beast)

# set_property(TARGET http-server-sync PROPERTY FOLDER "example-http-server")
find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED)
add_executable (http-server-sync
    ${BOOST_BEAST_FILES}
    http_server_sync.cpp
)
include_directories(${Boost_INCLUDE_DIR} ${OpenCV_INCLUDE_DIRS})
target_link_libraries(http-server-sync ${Boost_LIBRARIES} ${OpenCV_LIBRARIES} pthread)
