#include "logger.hpp"

std::string getcurrenttime() {
	auto now = std::chrono::system_clock::now();
	std::time_t CurrentTime = std::chrono::system_clock::to_time_t(now);
	return std::ctime(&CurrentTime);
}

void Logger::init() {
	spdlog::init_thread_pool(8192, 1);
	auto async_file_logger = std::make_shared<spdlog::async_logger>("async_logger", std::make_shared<spdlog::sinks::basic_file_sink_mt>("log.txt", true),
		spdlog::thread_pool(),
		spdlog::async_overflow_policy::block);
	spdlog::set_default_logger(async_file_logger);
	spdlog::set_level(spdlog::level::info);
	spdlog::flush_on(spdlog::level::err);
}

