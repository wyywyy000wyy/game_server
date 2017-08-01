#include "log.h"

std::shared_ptr<spdlog::logger> glog_t = []() {
	auto sinks = spdlog::stdout_color_mt("console")->sinks();
	auto sink2 = spdlog::daily_logger_mt("files", "imm_server", 4, 0)->sinks();

	sinks.insert(sinks.end(), sink2.begin(), sink2.end());

	auto multi_sink = std::make_shared<spdlog::logger>("logs", sinks.begin(), sinks.end());
	multi_sink->set_level(spdlog::level::trace);
	return multi_sink;
}();