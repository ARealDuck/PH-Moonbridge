#include "obsws.hpp"
#include "settings.hpp"
#include <iostream>
#include "cryptopp/base64.h"
#include "cryptopp/sha.h"
#include "cryptopp/filters.h"
#include "cryptopp/files.h"

using namespace CryptoPP;
// init
obsws* obsws::instance = nullptr;
obsws* obsws::obswsinit() {
	if (instance == nullptr) {
		instance = new obsws();
	}
	return instance;
}
// contructor
obsws::obsws() {
	settings = settings::settingsinit();
}
// destructor
obsws::~obsws() {

}

//auth
string obsws::auth(string& challenge, string& salt) {
	string password = settings->cache<string>("password");
	stringstream passsalt;
	passsalt << password << salt;
	string input;
	passsalt.str(input);
	SHA256 hash;
	string base64secret;
	StringSource(input, true, new HashFilter(hash, new Base64Encoder(new StringSink(base64secret))));
	stringstream b64chal;
	b64chal << base64secret << challenge;
	b64chal.str(input);
	SHA256 hash;
	string digest;
	StringSource(input, true, new HashFilter(hash, new Base64Encoder(new StringSink(digest))));
	return digest;
}
