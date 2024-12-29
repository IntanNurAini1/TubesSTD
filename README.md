#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <iostream>
using namespace std;

struct infotypeN {
    string nama;
    string id;
};

struct infotypeE {
    string nama;
    string id;
    string zona;
};

typedef struct elmN *adr_Node;
typedef struct elmE *adr_Edge;

struct elmN {
    infotypeN info;
    adr_Node next;
    adr_Edge firstE;
};

struct elmE {
    infotypeE info;
    adr_Edge next;
};

struct Graph {
    adr_Node firstG;
};

void create_List(Graph &G);
adr_Node createN(infotypeN x);
adr_Edge createE(infotypeE a);
void addNode(Graph &G, adr_Node P);
adr_Node findNode(Graph G, string id);
void addEdge(Graph &G, string id, adr_Edge P);
void connecting(Graph &G, string id, string id2, string zone);
adr_Edge findEdge(adr_Node P, string id);
void DeleteEdge(adr_Node p, string id);
bool findConnecting(Graph G, string id1, string id2);
void disconnecting(Graph &G, string id1, string id2);
void deleteNode(Graph &G, string id);
void showAll(Graph G);
void Pencariantetangga(Graph G, string id);
void jalurAman(Graph G, string id);
void addlokasi(Graph &G);
#endif // GRAPH_H_INCLUDED
