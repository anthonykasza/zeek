// See the file "COPYING" in the main distribution directory for copyright.

#pragma once

#include "analyzer/protocol/tcp/TCP.h"

#include "xmpp_pac.h"

namespace zeek::analyzer::xmpp {

class XMPP_Analyzer final : public zeek::analyzer::tcp::TCP_ApplicationAnalyzer {
public:
	explicit XMPP_Analyzer(zeek::Connection* conn);
	~XMPP_Analyzer() override;

	void Done() override;
	void DeliverStream(int len, const u_char* data, bool orig) override;
	void Undelivered(uint64_t seq, int len, bool orig) override;

	// Overriden from zeek::analyzer::tcp::TCP_ApplicationAnalyzer.
	void EndpointEOF(bool is_orig) override;

	void StartTLS();

	static zeek::analyzer::Analyzer* Instantiate(zeek::Connection* conn)
		{ return new XMPP_Analyzer(conn); }

protected:
	std::unique_ptr<binpac::XMPP::XMPP_Conn> interp;
	bool had_gap;

	bool tls_active;
};

} // namespace zeek::analyzer::xmpp

namespace analyzer::xmpp {

using XMPP_Analyzer [[deprecated("Remove in v4.1. Use zeek::analyzer::xmpp::XMPP_Analyzer.")]] = zeek::analyzer::xmpp::XMPP_Analyzer;

} // namespace analyzer::xmpp
