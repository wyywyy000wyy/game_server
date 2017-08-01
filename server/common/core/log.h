#ifndef  __SERVER_LOG_H__
#define __SERVER_LOG_H__
#include <spdlog/spdlog.h>

extern std::shared_ptr<spdlog::logger> glog_t;

#define LOGDEBUG(...)	glog_t->debug(__VA_ARGS__)
#define LOGINFO(...)	glog_t->info(__VA_ARGS__)
#define LOGWARN(...)	glog_t->warn(__VA_ARGS__)
#define LOGERROR(...)	glog_t->error(__VA_ARGS__)


#endif // ! __SERVER_LOG_H__
