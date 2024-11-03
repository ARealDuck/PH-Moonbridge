#pragma once
#include <condition_variable>
#include <mutex>

struct clientsync {
	std::condition_variable clientcv;
	bool ready = false;
	std::mutex clientmtx;
};