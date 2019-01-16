// Copyright 2019 David Johnston

#include <jvmti.h>
#include "gtest/gtest.h"

#include "jvmti.h"

#include "phasicj/tracelogger/agent.h"
#include "phasicj/tracelogger/agent_static.h"

TEST(trivial_agent_test, drive_agent_lifetime_events_with_nullptrs) {
  phasicj::tracelogger::Agent agent;
  EXPECT_EQ(agent.OnLoad(nullptr, nullptr, nullptr), 0);
  EXPECT_EQ(agent.OnAttach(nullptr, nullptr, nullptr), 0);
  agent.OnUnload(nullptr);
}

TEST(trivial_agent_test, drive_dynamically_linked_agent_lifetime_events_with_nullptrs) {
  EXPECT_EQ(Agent_OnLoad(nullptr, nullptr, nullptr), 0);
  EXPECT_EQ(Agent_OnAttach(nullptr, nullptr, nullptr), 0);
  Agent_OnUnload(nullptr);
}

TEST(trivial_agent_test, drive_statically_linked_agent_test_agent_lifetime_events_with_nullptrs) {
  EXPECT_EQ(Agent_OnLoad_pjtracelogger(nullptr, nullptr, nullptr), 0);
  EXPECT_EQ(Agent_OnAttach_pjtracelogger(nullptr, nullptr, nullptr), 0);
  Agent_OnUnload_pjtracelogger(nullptr);
}
