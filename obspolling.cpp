#include "obspolling.hpp"

obspolling::obspolling() {}

void obspolling::startpolling() {
	gthreadpool.enqueueTask([this] {	
		pollingclient.connect(syncdata);
		running = true;
		while (running) {
			std::string tempimage = getimagedata();
			{
				std::unique_lock lock(imgdatamtx);
				imagedata = tempimage;
			}
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
	if (returnmsg.contains("status") && returnmsg["status"].contains("ok")) {
		std::string returnstring = returnmsg["imageData"];
		return returnstring;
	}

}

obspolling obspoll;

std::string obspolling::getpollingdata() {
	std::string tempdata;
	{
		std::shared_lock lock(imgdatamtx);
		tempdata = imagedata;
	}
	return tempdata;
}
