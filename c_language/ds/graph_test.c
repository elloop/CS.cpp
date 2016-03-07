#include "ds/graph_test.h"

#include <assert.h>
#include <stdio.h>



void create_mgraph(mgraph_t* g)
{
    assert(g);
    size_t num = 0;
    printf("how many vertex: \n");
    scanf("%d", &num);
    g->size = num;
    g->adj = (mgraph_edge_t **) malloc(sizeof(mgraph_edge_t*) * num);
    for (size_t i=0; i<num; ++i) 
    {
        g->adj[i] = (mgraph_edge_t *) malloc (sizeof (mgraph_edge_t) * num);
    }
    init_mgraph_edges(g);

    g->vertexes = (mgraph_elem_t *) malloc (sizeof (mgraph_elem_t) * num);

    // init vertexes.
    init_mgraph_vertexes(g);

    // init edges.
    create_mgraph_edges(g);

}

void delete_mgraph(mgraph_t* g)
{
    assert(g);

    if (g->vertexes) 
    {
        free(g->vertexes);
    }

    if (g->adj)
    {
        for ( size_t i = 0; i < g->size; i++ )
        {
            if (g->adj[i])
            {
                free(g->adj[i]);
            }
        }
        free(g->adj);
    }
}

void dfs_mgraph(mgraph_t* g)
{

}

void init_mgraph_vertexes(mgraph_t* g)
{
    assert(g && g->vertexes);

    for ( size_t i = 0; i < g->size; ++i )
    {
        printf("vertex %d: ", (i+1));
        scanf("%c", &(g->vertexes[i]));
    }
}

void init_mgraph_edges(mgraph_t* g)
{
    assert(g && g->adj);
    for (size_t i=0; i<g->size; ++i) 
    {
        for (size_t j = 0; j < g->size; j++)
        {
            g->adj[i][j] = 0;
        }
    }
}

void create_mgraph_edges(mgraph_t* g)
{
    assert(g && g->adj);
    size_t count = 0;
    printf("how many edges: \n");
    scanf("%d", &count);

    size_t  h;
    size_t  t;
    h = t = 0;
    for (size_t i = 0; i < count; ++i)
    {
        printf("edge %d: i j = ", (i + 1));
        scanf("%d %d %d", &h, &t);
        g->adj[h - 1][t - 1] = 1;
        g->adj[t - 1][h - 1] = 1;
    }
}
