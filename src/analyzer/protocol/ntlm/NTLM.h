// See the file "COPYING" in the main distribution directory for copyright.

#pragma once

#include "events.bif.h"
#include "analyzer/protocol/tcp/TCP.h"

#include "ntlm_pac.h"

namespace zeek::analyzer::ntlm {

class NTLM_Analyzer final : public zeek::analyzer::tcp::TCP_ApplicationAnalyzer {

public:
	explicit NTLM_Analyzer(zeek::Connection* conn);
	~NTLM_Analyzer() override;

	// Overriden from Analyzer.
	void Done() override;

	void DeliverStream(int len, const u_char* data, bool orig) override;
	void Undelivered(uint64_t seq, int len, bool orig) override;

	// Overriden from zeek::analyzer::tcp::TCP_ApplicationAnalyzer.
	void EndpointEOF(bool is_orig) override;

	static zeek::analyzer::Analyzer* Instantiate(zeek::Connection* conn)
		{ return new NTLM_Analyzer(conn); }

protected:
	binpac::NTLM::NTLM_Conn* interp;
};

} // namespace zeek::analyzer::ntlm

namespace analyzer::ntlm {

using NTLM_Analyzer [[deprecated("Remove in v4.1. Use zeek::analyzer::ntlm::NTLM_Analyzer.")]] = zeek::analyzer::ntlm::NTLM_Analyzer;

} // namespace analyzer::ntlm
