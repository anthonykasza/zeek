// See the file  in the main distribution directory for copyright.

#include "ConnSize.h"
#include "plugin/Plugin.h"
#include "analyzer/Component.h"

namespace zeek::plugin::detail::Zeek_ConnSize {

class Plugin : public zeek::plugin::Plugin {
public:
	zeek::plugin::Configuration Configure() override
		{
		AddComponent(new zeek::analyzer::Component("ConnSize", zeek::analyzer::conn_size::ConnSize_Analyzer::Instantiate));

		zeek::plugin::Configuration config;
		config.name = "Zeek::ConnSize";
		config.description = "Connection size analyzer";
		return config;
		}
} plugin;

} // namespace zeek::plugin::detail::Zeek_ConnSize
