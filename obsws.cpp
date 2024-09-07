#include "obsws.hpp"
#include "settings.hpp"
#include <iostream>
#include "cryptopp/base64.h"
#include "cryptopp/sha.h"
#include "cryptopp/filters.h"
#include "cryptopp/files.h"

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
	CryptoPP::SHA256 hash;
	string base64secret;
	CryptoPP::StringSource(input, true, new CryptoPP::HashFilter(hash, new CryptoPP::Base64Encoder(new CryptoPP::StringSink(base64secret))));
	stringstream b64chal;
	b64chal << base64secret << challenge;
	b64chal.str(input);
	CryptoPP::SHA256 hash;
	string digest;
	CryptoPP::StringSource(input, true, new CryptoPP::HashFilter(hash, new CryptoPP::Base64Encoder(new CryptoPP::StringSink(digest))));
	return digest;
}
