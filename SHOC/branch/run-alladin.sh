make run-trace &&
$ALADDIN_HOME/common/aladdin br dynamic_trace.gz example/config_example
dot -Tpdf br_graph.dot -o br_graph.pdf
