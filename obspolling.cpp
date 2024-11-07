#include "obspolling.hpp"

obspolling::obspolling() {}

void obspolling::startpolling() {
	gthreadpool.enqueueTask([this] {	
		pollingclient.connect(syncdata);
		running = true;
		while (running) {
			imagedata = getimagedata();
			// wait for 500ms before sending request again
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
	});

}

std::string obspolling::getimagedata() {
	nlohmann::json datamsg;
	datamsg["op"] = 6;
	datamsg["d"] = {
		{"requestType", "GetSourceScreenshot"},
		{"requestId", pollingclient.createid() },
		{"requestData", {
			{"sourceName", sourcename},
			{"imageFormat", "png"},
			{"imageCompressionQuality", 100}
		}}
	};
	nlohmann::json returnmsg = pollingclient.sendmsg(datamsg);
	returnmsg.parse
}

obspolling obspoll;
