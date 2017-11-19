// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once


// TODO: 在此处引用程序需要的其他头文件
#include <iostream>
#include <sstream>
#include <boost/asio.hpp>
#include <boost/unordered_set.hpp>
#include <boost/thread.hpp>
#include <boost/array.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/locale.hpp>


#define LISTEN_PORT 12333
#define TO_UTF8 boost::locale::conv::to_utf<char>