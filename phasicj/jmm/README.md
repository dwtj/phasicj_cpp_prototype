# `phasicj::jmmevents`

This package is used to adapt lower-level JVM Tooling Interface (JVMTI) events
into higher-level Java Memory Model (JMM) events. The `JvmtiToJmmAdapter` class
sits at the center of this process. It is responsible for configuring a
JVMTI environment such that relevant JVMTI events are transformed into
appropriate JMM events.
