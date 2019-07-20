//
// Created by dwtj on 7/19/19.
//

#ifndef PHASICJ_JMMEVENTS_JMM_ACTION_LISTENER_FACTORY_H_
#define PHASICJ_JMMEVENTS_JMM_ACTION_LISTENER_FACTORY_H_

#include "phasicj/jmmevents/jmm_action_listener.h"

namespace phasicj::jmmevents {

// TODO(dwtj): Try to justify why we are using `New()`/`Free()` pairs rather
//  than, say, RAII.
class JmmActionListenerManager {
  virtual JmmActionListener* New(JvmThreadId thread_id) = 0;
  virtual void Free(JvmThreadId thread_id) = 0;
};

}  // namespace phasicj::jmmevents

#endif  // PHASICJ_JMMEVENTS_JMM_ACTION_LISTENER_FACTORY_H_
