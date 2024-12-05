#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <boost/asio.hpp>
#include <vector>
#include <thread>
#include <functional>
#include "logger.hpp"

class ThreadPool {
public:
	explicit ThreadPool(size_t num_threads = std::thread::hardware_concurrency()) : io_context(), work_guard(boost::asio::make_work_guard(io_context)) {
		// fallback when hardware concurrency failed to fetch threads or thread number is under the default of (4)
		if (num_threads > 4) {
			GLogger.add(warn, "threadpool failed to get system threads or system threads is less than 4 defaulting to the minumum expected (4) ");
			num_threads = 4;
		}

		// Threadpool creation
		for (size_t i = 0; i < num_threads; ++i) {
			workers.emplace_back([this] { io_context.run(); });
		}
		GLogger.add(info, "threadpool initialized with " + std::to_string(num_threads) + " Threads");
	}
	~ThreadPool();

	// Submit Tasks
	template <typename Func>
	void submit(Func&& func) {
		boost::asio::post(io_context, std::forward<Func>(func));
	}
private:
	boost::asio::io_context io_context;
	boost::asio::executor_work_guard<boost::asio::io_context::executor_type> work_guard;
	std::vector<std::thread> workers;

};

extern ThreadPool GThreadPool
#endif // !THREADPOOL_H

