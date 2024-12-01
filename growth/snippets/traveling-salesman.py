import matplotlib.pyplot as plt
import networkx as nx


def mst_tsp_approximation(graph):
    """
    Approximate TSP solution using MST-based heuristic.
    :param graph: Weighted graph (NetworkX graph object)
    :return: Approximate TSP path and its cost
    """
    # Step 1: Compute the MST
    mst = nx.minimum_spanning_tree(graph, weight="weight")

    # Step 2: Perform preorder traversal of the MST
    start_node = list(mst.nodes)[0]
    visited = []

    def preorder_traversal(node):
        if node not in visited:
            visited.append(node)
            for neighbor in mst.neighbors(node):
                preorder_traversal(neighbor)

    preorder_traversal(start_node)

    # Step 3: Form the TSP path
    tsp_path = visited + [start_node]  # Complete the cycle by returning to the start
    tsp_cost = sum(
        graph[tsp_path[i]][tsp_path[i + 1]]["weight"] for i in range(len(tsp_path) - 1)
    )

    return tsp_path, tsp_cost


# Example graph
graph = nx.complete_graph(5)  # Complete graph with 5 nodes
weights = {
    (0, 1): 2,
    (0, 2): 9,
    (0, 3): 10,
    (0, 4): 3,
    (1, 2): 7,
    (1, 3): 4,
    (1, 4): 8,
    (2, 3): 1,
    (2, 4): 6,
    (3, 4): 5,
}

# Assign weights to the edges
for (u, v), w in weights.items():
    graph[u][v]["weight"] = w

# Solve TSP using MST Approximation
tsp_path, tsp_cost = mst_tsp_approximation(graph)

# Print the results
print("Approximate TSP Path:", tsp_path)
print("Approximate TSP Cost:", tsp_cost)

# Visualize the MST and the TSP path
plt.figure(figsize=(12, 6))

# Generate the layout for node positions
pos = nx.spring_layout(graph)

# Plot MST
mst = nx.minimum_spanning_tree(graph, weight="weight")
plt.subplot(1, 2, 1)
nx.draw(
    mst,
    with_labels=True,
    node_color="lightblue",
    edge_color="green",
    pos=pos,
    node_size=500,
    font_size=12,
)
edge_labels = nx.get_edge_attributes(mst, "weight")
nx.draw_networkx_edge_labels(mst, pos=pos, edge_labels=edge_labels)
plt.title("Minimum Spanning Tree")

# Plot TSP Path
plt.subplot(1, 2, 2)
tsp_edges = [(tsp_path[i], tsp_path[i + 1]) for i in range(len(tsp_path) - 1)]
tsp_graph = nx.Graph()
tsp_graph.add_edges_from(tsp_edges)
nx.draw(
    graph,
    with_labels=True,
    node_color="lightblue",
    pos=pos,
    node_size=500,
    font_size=12,
)
nx.draw_networkx_edges(graph, edgelist=tsp_edges, edge_color="red", width=2, pos=pos)

# Display weights and travel order
for i, (u, v) in enumerate(tsp_edges):
    mid_point = ((pos[u][0] + pos[v][0]) / 2, (pos[u][1] + pos[v][1]) / 2)
    plt.text(
        mid_point[0],
        mid_point[1],
        f"{i + 1} ({graph[u][v]['weight']})",
        fontsize=10,
        ha="center",
        color="black",
    )

plt.title("Approximate TSP Path with Order and Weights")
plt.show()
