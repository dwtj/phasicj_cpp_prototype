// Copyright 2019 David Johnston

#ifndef PHASICJ_TRACELOGGER_AGENT_H_
#define PHASICJ_TRACELOGGER_AGENT_H_

namespace phasicj::tracelogger::agent {

jint OnLoad(JavaVM&, const char* options);
jint OnAttach(JavaVM&, const char* options);
void OnUnload(JavaVM&);

}  // namespace phasicj::tracelogger::agent

#endif  // PHASICJ_TRACELOGGER_AGENT_H_
