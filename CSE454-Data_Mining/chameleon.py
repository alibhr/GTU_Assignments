from numpy.core.fromnumeric import partition
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import networkx as nx
import metis
import itertools

k = 7
knn = 20
m = 80
alpha = 2.0

# http://cs.joensuu.fi/sipu/datasets/
df = pd.read_csv('Datasets/aggregation.csv', sep=',',header=None)
# df = pd.read_csv('Datasets/compound.csv', sep=',',header=None)
# df = pd.read_csv('Datasets/flame.csv', sep=',',header=None)
# df = pd.read_csv('Datasets/jain.csv', sep=',',header=None)
# df = pd.read_csv('Datasets/pathbased.csv', sep=',',header=None)
# df = pd.read_csv('Datasets/r15.csv', sep=',',header=None)
# df = pd.read_csv('Datasets/smileface.csv', sep=',',header=None)
# df = pd.read_csv('Datasets/spiral.csv', sep=',',header=None)

def get_distance(a, b):
    return np.linalg.norm(np.array(a) - np.array(b))

def get_distances(p, points):
    distances = []

    for x in points:
        distances.append(get_distance(p, x))
    
    return distances

def create_knn_graph(df, k):
    points = [p[1:] for p in df.itertuples()]
    
    g = nx.Graph()
    
    for i in range(0, len(points)):
        g.add_node(i)

    for i, p in enumerate(points):
        distances = get_distances(p, points)

        closests = np.argsort(distances)[1:k+1]

        for c in closests:
            if(distances[c] != 0):
                g.add_edge(i, c, weight=1.0 / distances[c], similarity=int(1.0 / distances[c] * 1e4))
        
        g.nodes[i]['pos'] = p
    
    g.graph['edge_weight_attr'] = 'similarity'

    return g

def initial_set_of_sub_clusters(graph, k, df=None):
    clusters = 0
    
    for p in graph.nodes():
        graph.nodes[p]['cluster'] = 0
    
    cluster_frequency = {}
    cluster_frequency[0] = len(graph.nodes())

    while clusters < k - 1:
        max_cluster = -1
        max_val = 0
    
        for key, val in cluster_frequency.items():
            if val > max_val:
                max_val = val
                max_cluster = key
    
        s_nodes = [n for n in graph.nodes if graph.nodes[n]['cluster'] == max_cluster]
        s_graph = graph.subgraph(s_nodes)
        _, parts = metis.part_graph(s_graph, 2, objtype='cut', ufactor=250)
        
        new_part_cnt = 0
        for i, p in enumerate(s_graph.nodes()):
            if parts[i] == 1:
                graph.nodes[p]['cluster'] = clusters + 1
                new_part_cnt = new_part_cnt + 1
        
        cluster_frequency[max_cluster] = cluster_frequency[max_cluster] - new_part_cnt
        cluster_frequency[clusters + 1] = new_part_cnt
        clusters = clusters + 1

    _, parts = metis.part_graph(graph, k)
    
    if df is not None:
        df['cluster'] = nx.get_node_attributes(graph, 'cluster').values()
    
    return graph

def get_connected_edges(part1, part2, graph):
    result = []

    for x in part1:
        for y in part2:
            if x in graph and y in graph[x]:
                result.append((x, y))

    return result

def get_cluster(graph, clusters):
    nodes = [n for n in graph.nodes if graph.nodes[n]['cluster'] in clusters]

    return nodes

def part_graph(graph, k, df=None):
    _, parts = metis.part_graph(graph, 2, objtype='cut', ufactor=250)

    for i, p in enumerate(graph.nodes()):
        graph.nodes[p]['cluster'] = parts[i]

    if df is not None:
        df['cluster'] = nx.get_node_attributes(graph, 'cluster').values()

    return graph

def get_weights(graph, edges):
    return [graph[edge[0]][edge[1]]['weight'] for edge in edges]

def calculate_score(graph, gi, gj, edges, a):
    ci_cluster = graph.subgraph(gi)
    cj_cluster = graph.subgraph(gj)

    copy_graph_i = ci_cluster.copy()
    copy_graph_i = part_graph(copy_graph_i, 2)
    min_cut_i = get_connected_edges(get_cluster(copy_graph_i, [0]), get_cluster(copy_graph_i, [1]), copy_graph_i)

    copy_graph_j = cj_cluster.copy()
    copy_graph_j = part_graph(copy_graph_j, 2)
    min_cut_j = get_connected_edges(get_cluster(copy_graph_j, [0]), get_cluster(copy_graph_j, [1]), copy_graph_j)
    
    bw_i = get_weights(ci_cluster, min_cut_i)
    bw_j = get_weights(cj_cluster, min_cut_j)

    EC = np.sum(get_weights(graph, edges))
    ECci = np.sum(bw_i)
    ECcj = np.sum(bw_j)
    r_i = EC / ((ECci + ECcj) / 2.0)

    SEC = np.mean(get_weights(graph, edges))

    Ci = np.sum(get_weights(ci_cluster, ci_cluster.edges()))
    Cj = np.sum(get_weights(cj_cluster, cj_cluster.edges()))

    SECci = 0
    if bw_i != []:
        SECci = np.mean(bw_i)
    
    SECcj = 0
    if bw_j != []:
        SECcj = np.mean(bw_j)

    r_c =  SEC / ((Ci / (Ci + Cj) * SECci) + (Cj / (Ci + Cj) * SECcj))

    return r_i * np.power(r_c, a)

def merge_sub_clusters(graph, df, a, k):
    clusters = np.unique(df['cluster'])

    max_score = 0
    ci, cj = -1, -1

    if len(clusters) <= k:
        return False

    for combination in itertools.combinations(clusters, 2):
        i, j = combination
        if i != j:
            gi = get_cluster(graph, [i])
            gj = get_cluster(graph, [j])

            edges = get_connected_edges(gi, gj, graph)

            if not edges:
                continue

            ms = calculate_score(graph, gi, gj, edges, a)

            if ms > max_score:
                max_score = ms
                ci, cj = i, j

    if max_score > 0:
        df.loc[df['cluster'] == cj, 'cluster'] = ci
        for i, p in enumerate(graph.nodes()):
            if graph.nodes[p]['cluster'] == cj:
                graph.nodes[p]['cluster'] = ci
    return max_score > 0

def rebuild_labels(df):
    ans = df.copy()
    clusters = list(pd.DataFrame(df['cluster'].value_counts()).index)
    c = 1
    
    for i in clusters:
        ans.loc[df['cluster'] == i, 'cluster'] = c
        c = c + 1
    
    return ans

if __name__ == "__main__":

    # PHASE 1
    graph = create_knn_graph(df, knn)
    graph = initial_set_of_sub_clusters(graph, m, df)

    # PHASE 2
    for i in enumerate(range(m - k)):
        merge_sub_clusters(graph, df, alpha, k)

    # SHOW RESULTS
    res = rebuild_labels(df)
    print(res)

    df.plot(kind='scatter', c=df['cluster'], cmap='gist_rainbow', x=1, y=0)
    plt.show()
