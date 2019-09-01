// Copyright 2019 David Johnston

#include "TraceEnhancer.h"

namespace phasicj::jmm::vectorclocks {

using ::std::unique_ptr;

TraceEnhancer::TraceEnhancer(unique_ptr<VcJmmTrace> enhanced) :
  enhanced_{enhanced} {}

}  // namespace phasicj::jmm::vectorclocks
