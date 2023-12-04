import networkx as nx

# Create a Directed Acyclic Graph (DAG)
G = nx.DiGraph()

# Add nodes (tasks) and edges (dependencies)
G.add_node("Start")
G.add_node("A", duration=5)
G.add_node("B", duration=3)
G.add_node("C", duration=2)
G.add_node("D", duration=4)
G.add_node("E", duration=2)
G.add_node("End")

G.add_edge("Start", "A")
G.add_edge("Start", "B")
G.add_edge("A", "C")
G.add_edge("B", "C")
G.add_edge("C", "D")
G.add_edge("C", "E")
G.add_edge("D", "End")
G.add_edge("E", "End")

# Calculate earliest start times (ES) and earliest finish times (EF)
es = {}
ef = {}
for node in nx.topological_sort(G):
    if node == "Start":
        es[node] = 0
    else:
        es[node] = max(ef[pred] for pred in G.predecessors(node))
    ef[node] = es[node] + G.nodes[node].get("duration", 0)  # Use get() to handle missing "duration"

# Calculate latest start times (LS) and latest finish times (LF)
ls = {}
lf = {}
for node in reversed(list(nx.topological_sort(G))):
    if node == "End":
        lf[node] = ef[node]
    else:
        lf[node] = min(ls[succ] for succ in G.successors(node))
    ls[node] = lf[node] - G.nodes[node].get("duration", 0)  # Use get() to handle missing "duration"

# Calculate slack for each task
slack = {}
for node in G.nodes:
    slack[node] = ls[node] - es[node]

# Find critical path tasks
critical_path = [node for node in G.nodes if slack[node] == 0]

# Print results
print("Critical Path Tasks:", critical_path)
print("Earliest Start Times (ES):", es)
print("Earliest Finish Times (EF):", ef)
print("Latest Start Times (LS):", ls)
print("Latest Finish Times (LF):", lf)
print("Slack:", slack)
