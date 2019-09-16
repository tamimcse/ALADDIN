make run-trace &&
$ALADDIN_HOME/common/aladdin poptrie dynamic_trace.gz example/config_example
dot -Tpdf poptrie_graph.dot -o poptrie_graph.pdf
