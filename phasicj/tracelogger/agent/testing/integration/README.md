This package holds all integration tests for the PhasicJ TraceLogger JVMTI
native agent. We are testing to see whether the agent performs properly when
running within various JVMs running various Java programs.

[The JNI Invocation API](https://docs.oracle.com/en/java/javase/11/docs/specs/jni/invocation.html)
is used to start a JVM with the TraceLogger agent.
