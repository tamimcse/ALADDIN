make run-trace &&
$ALADDIN_HOME/common/aladdin if-else dynamic_trace.gz example/config_example
dot -Tpdf if-else_graph.dot -o if-else_graph.pdf
