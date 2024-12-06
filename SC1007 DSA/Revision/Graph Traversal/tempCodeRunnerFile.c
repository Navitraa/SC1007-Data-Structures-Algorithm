// Write your code here
void DFS_R(Graph g, int v)
{
    // Base case
    v = v - 1; //adjust for 0-based indexing
    g.visited[v] = 1;
    printf("%d", v+1);

    // Recursive case
    for (int u = 0; u < g.V; u++) {
        if ((g.matrix[v][u] == 1) && (g.visited[u] == 0)) {
            DFS_R(g, u+1); // NOTE: use u+1 to adjust back to 1-based indexing for DFS_R input
        }
    }
}