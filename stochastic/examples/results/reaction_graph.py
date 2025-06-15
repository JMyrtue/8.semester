import networkx as nx
import matplotlib.pyplot as plt
import re

def parse_reaction_line(line):
    """Parses a reaction line like '(A + DA) >> 0.5 >>= D_A'."""
    match = re.match(r"\((.*?)\) >> ([\d\.eE+-]+) >>= (.*)", line.strip())
    if not match:
        return None, None, None

    inputs = [x.strip() for x in match.group(1).split('+')]
    rate = match.group(2)
    outputs = [x.strip() for x in match.group(3).split('+')]

    return inputs, rate, outputs

def build_graph_from_file(filename):
    G = nx.DiGraph()

    with open(filename) as f:
        for line in f:
            inputs, rate, outputs = parse_reaction_line(line)
            if not inputs or not outputs:
                continue

            rate_node = f"{rate}"

            # Add rate node
            G.add_node(rate_node, type='rate')

            # Connect inputs to rate
            for inp in inputs:
                G.add_node(inp, type='agent')
                G.add_edge(inp, rate_node)

            # Connect rate to outputs
            for out in outputs:
                G.add_node(out, type='agent')
                G.add_edge(rate_node, out)

    return G

def draw_graph(G):
    plt.figure(figsize=(6, 6))
    pos = nx.spring_layout(G, k=1.5, seed=42)
    agent_nodes = [n for n, d in G.nodes(data=True) if d['type'] == 'agent']
    rate_nodes = [n for n, d in G.nodes(data=True) if d['type'] == 'rate']

    nx.draw_networkx_nodes(G, pos, node_size=1000, nodelist=agent_nodes, node_color='lightblue', node_shape='o', label='Agent')
    nx.draw_networkx_nodes(G, pos, node_size=500, nodelist=rate_nodes, node_color='lightgreen', node_shape='s', label='Rate')
    nx.draw_networkx_edges(G, pos, min_target_margin=15)
    nx.draw_networkx_labels(G, pos, labels={n: n for n in agent_nodes})
    nx.draw_networkx_labels(G, pos, labels={n: n for n in rate_nodes},
                            font_size=8,  # smaller font
                            font_color='black')

    plt.title("Reaction Graph")
    plt.legend(loc='upper right', fontsize=20, frameon=True, fancybox=True, shadow=True)
    plt.axis('off')
    plt.show()

if __name__ == "__main__":
    graph = build_graph_from_file("ReactionNetwork-3.txt")
    draw_graph(graph)
