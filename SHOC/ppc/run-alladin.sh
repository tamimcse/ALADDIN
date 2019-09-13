make run-trace &&
$ALADDIN_HOME/common/aladdin ppc dynamic_trace.gz example/config_example
dot -Tpdf ppc_graph.dot -o ppc_graph.pdf
