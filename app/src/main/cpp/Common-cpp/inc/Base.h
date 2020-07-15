/* Exit Games Common - C++ Client Lib
 * Copyright (C) 2004-2020 by Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#pragma once

#include "Logger.h"
#include "MemoryManagement/Allocate.h"

namespace ExitGames
{
	namespace Common
	{
		class Base : public ToString
		{
		public:
			virtual ~Base(void);
			static void setListener(const BaseListener* baseListener);
			static int getDebugOutputLevel(void);
			static bool setDebugOutputLevel(int debugLevel);
			static const LogFormatOptions& getLogFormatOptions(void);
			static void setLogFormatOptions(const LogFormatOptions& options);
		protected:
			static Logger mLogger;
		};
	}
}