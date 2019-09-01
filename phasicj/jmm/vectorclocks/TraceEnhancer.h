// Copyright 2019 David Johnston

#ifndef PHASICJ_JMM_VECTORCLOCKS_VCJMMTRACEENHANCER_H_
#define PHASICJ_JMM_VECTORCLOCKS_VCJMMTRACEENHANCER_H_

#include "phasicj/jmm/JmmTrace.h"
#include "phasicj/jmm/vectorclocks/VcJmmTrace.h"

namespace phasicj::jmm::vectorclocks {

class TraceEnhancer : public ::phasicj::jmm::JmmTrace {
 public:
  explicit TraceEnhancer(::std::unique_ptr<VcJmmTrace> enhanced) noexcept;

 private:
  ::std::unique_ptr<VcJmmTrace> enhanced_;
};

}  // namespace phasicj::jmm::vectorclocks

#endif  // PHASICJ_JMM_VECTORCLOCKS_VCJMMTRACEENHANCER_H_
