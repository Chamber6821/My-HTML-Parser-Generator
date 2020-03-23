#include "ParserConfig.h"

namespace Core {
	ParserConfig::ParserConfig() {}
	ParserConfig::~ParserConfig() {}

	ParserConfig ParserConfig::defoult() {
		static ParserConfig def;
		static bool f = false;
		if (!f) {
			f = true;
			// init
		}
		return def;
	}
};
