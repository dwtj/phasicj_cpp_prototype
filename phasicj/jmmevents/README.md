# `phasicj/jmmevents`

This package adapts JVMTI events into more abstract JMM events. By implementing
the `phasicj::jmmevents::ActionListener` interface, a class can consume the
various kinds of events emitted by a JVM (via a JVMTI instance).
