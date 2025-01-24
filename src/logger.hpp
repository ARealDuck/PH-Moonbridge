#include <spdlog/spdlog.h>
#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>


class Logger {
public:
	static std::shared_ptr<spdlog::logger> get() {
		return spdlog::default_logger();
	}
	static void init() {
			spdlog::init_thread_pool(8192, 1);
			auto async_file_logger = std::make_shared<spdlog::async_logger>("async_logger", std::make_shared<spdlog::sinks::basic_file_sink_mt>("log.txt", true),
				spdlog::thread_pool(),
				spdlog::async_overflow_policy::block);
			spdlog::set_pattern("[%m-%d %H:%M:%S]");
			spdlog::set_default_logger(async_file_logger);
			spdlog::set_level(spdlog::level::info);
			spdlog::flush_on(spdlog::level::err);
	}
};