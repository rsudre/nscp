#pragma once

#include "error_handler_interface.hpp"
#include "metrics_handler.hpp"
#include "token_store.hpp"
#include "metrics_handler.hpp"

#include <StreamResponse.h>
#include <Request.h>

#include <socket/socket_helpers.hpp>

#include <string>
#include <list>

struct session_manager_interface {

private:
	error_handler_interface* log_data;
	std::string password_;

	metrics_handler metrics_store;
	token_store tokens;
	socket_helpers::allowed_hosts_manager allowed_hosts;
public:
	session_manager_interface();

	bool is_loggedin(Mongoose::Request &request, Mongoose::StreamResponse &response, bool respond = true);

	bool is_allowed(std::string ip);

	bool validate_token(std::string token);
	void revoke_token(std::string token);
	std::string generate_token();

	std::string get_metrics();
	void set_metrics(std::string metrics);

	void add_log_message(bool is_error, error_handler_interface::log_entry entry);
	error_handler_interface* get_log_data();
	void reset_log();

	void set_allowed_hosts(std::string host);
	void set_allowed_hosts_cache(bool value);
	void set_password(std::string password);

	std::list<std::string> boot();
	bool validate_password(string password);
	bool validate_user(const std::string user, const std::string &password);
	void setup_token(Mongoose::StreamResponse & response);
};
