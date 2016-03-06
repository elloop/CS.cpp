#pragma once

#include <stdlib.h>

typedef char mgraph_elem_t;

typedef int mgraph_edge_t;

typedef struct 
{
    mgraph_edge_t  **adj;
    mgraph_elem_t  *vertexes;
    size_t  size;
} mgraph_t;

void create_mgraph(mgraph_t* g);

void delete_mgraph(mgraph_t* g);

void dfs_mgraph(mgraph_t* g);

void init_mgraph_edges(mgraph_t* g);

void init_mgraph_vertexes(mgraph_t* g);

