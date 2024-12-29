#include "Graph.h"

void create_List(Graph &G) {
    G.firstG = NULL;
}

adr_Node createN(infotypeN x) {
    adr_Node P = new elmN;
    P->info = x;
    P->next = NULL;
    P->firstE = NULL;
    return P;
}

adr_Edge createE(infotypeE a) {
    adr_Edge Q = new elmE;
    Q->info = a;
    Q->next = NULL;
    return Q;
}

void addNode(Graph &G, adr_Node P) {
        if (G.firstG == NULL) {
            G.firstG = P;
        } else {
            adr_Node Q = G.firstG;
            while (Q->next != NULL) {
                Q = Q->next;
            }
            Q->next = P;
        }
}

adr_Node findNode(Graph G, string id) {
    adr_Node P = G.firstG;
    while (P != NULL) {
        if (P->info.id == id) {
            return P;
        }
        P = P->next;
    }
    return NULL;
}

void addEdge(Graph &G, string id, adr_Edge P) {
    adr_Node Q = findNode(G, id);
    if (Q != NULL) {
        if (Q->firstE == NULL) {
            Q->firstE = P;
        } else {
            adr_Edge a = Q->firstE;
            while (a->next != NULL) {
                a = a->next;
            }
            a->next = P;
        }
    } else {
        cout << "ID lokasi tidak ditemukan";
    }
}

void connecting(Graph &G, string id, string id2, string zona) {
    adr_Node node1 = findNode(G, id);
    adr_Node node2 = findNode(G, id2);
    if (node1 != NULL && node2 != NULL) {
        infotypeE edgeInfo1;
        edgeInfo1.nama = node2->info.nama;
        edgeInfo1.id = node2->info.id;
        edgeInfo1.zona = zona;
        adr_Edge edge1 = createE(edgeInfo1);
        addEdge(G, id, edge1);
        infotypeE edgeInfo2;
        edgeInfo2.nama = node1->info.nama;
        edgeInfo2.id = node1->info.id;
        edgeInfo2.zona = zona;
        adr_Edge edge2 = createE(edgeInfo2);
        addEdge(G, id2, edge2);
    }
}

adr_Edge findEdge(adr_Node P, string id) {
    if (P != NULL) {
        adr_Edge Q = P->firstE;
        while (Q != NULL) {
            if (Q->info.id == id) {
                return Q;
            }
            Q = Q->next;
        }
    }
    return NULL;
}

void DeleteEdge(adr_Node p, string id) {
    if (p == NULL || p->firstE == NULL){
        return;
    }
    adr_Edge Q = p->firstE;
    if (Q->info.id == id) {
        p->firstE = Q->next;
        delete Q;
    } else {
        adr_Edge prev = Q;
        Q = Q->next;
        while (Q != NULL) {
            if (Q->info.id == id) {
                prev->next = Q->next;
                delete Q;
                return;
            }
            prev = Q;
            Q = Q->next;
        }
    }
}


bool findConnecting(Graph G, string id, string id2) {
    adr_Node A = findNode(G, id);
    adr_Node B = findNode(G, id2);
    if (A != NULL && B != NULL){
        if (findEdge(A, id2) != NULL && findEdge(B,id) != NULL){
            return true;
        }
    }
    return false;
}

void disconnecting(Graph &G, string id, string id2) {
    adr_Node P1 = findNode(G, id);
    adr_Node P2 = findNode(G, id2);

    if (P1 != NULL && P2 != NULL) {
        if (findConnecting(G, id, id2)){
            DeleteEdge(P1, id2);
            DeleteEdge(P2, id);
            cout << "Koneksi antara " << id << " dan " << id2 << " berhasil dihapus." << endl;
        } else {
            cout << "lokasi " << P1->info.nama << " dan lokasi " << P2->info.nama << " tidak terhubung.";
        }

    } else {
        if (P1 == NULL && P2 == NULL) {
            cout << "Lokasi dengan ID " << id << " dan " << id2 << " tidak ditemukan." << endl;
        } else if (P1 == NULL) {
            cout << "Lokasi dengan ID " << id << " tidak ditemukan." << endl;
        } else {
            cout << "Lokasi dengan ID " << id2 << " tidak ditemukan." << endl;
        }
    }
}

void deleteNode(Graph &G, string id) {
    adr_Node target = findNode(G, id);
    if (target == NULL) {
        cout << "Lokasi dengan ID " << id << " tidak ditemukan." << endl;
        return;
    }
    adr_Node current = G.firstG;
    while (current != NULL) {
        DeleteEdge(current, id);
        current = current->next;
    }
    if (G.firstG == target) {
        G.firstG = target->next;
    } else {
        adr_Node prev = G.firstG;
        while (prev->next != target) {
            prev = prev->next;
        }
        prev->next = target->next;
    }
    adr_Edge edge = target->firstE;
    while (edge != NULL) {
        adr_Edge temp = edge;
        edge = edge->next;
        delete temp;
    }
    delete target;

    cout << "Lokasi dengan ID " << id << " berhasil dihapus." << endl;
}


void showAll(Graph G) {
    adr_Node a = G.firstG;
    if (a == NULL){
        cout << "tidak ada lokasi" << endl;
        return;
    }
    while (a != NULL) {
        cout << "------------------------------------------------------------"<< endl;
        cout << "Lokasi " << a->info.nama <<" dengan ID "<< a->info.id <<  " terhubung dengan: "<< endl;
        adr_Edge b = a->firstE;
        if (b == NULL) {
            cout << "Tidak ada koneksi";
        } else {
            int i = 1;
            while (b != NULL) {
                cout << i << ". lokasi " << b->info.nama << " (ID " <<b->info.id << " zona " << b->info.zona << ")" << endl;
                b = b->next;
                i++;
            }
        }
        cout << endl;
        a = a->next;
    }
    cout << "------------------------------------------------------------"<< endl;
}

void Pencariantetangga(Graph G, string id) {
    adr_Node node = findNode(G, id);
    if (node != NULL) {
        adr_Edge edge = node->firstE;
        if (edge == NULL) {
            cout << "Tidak ada koneksi." << endl;
        } else {
            cout << "Lokasi yang bertetangga dengan " << node->info.nama << ": " << endl;
            int i = 1;
            while (edge != NULL) {
                cout << i << ". " << edge->info.nama << " (ID: " << edge->info.id << ", Zona: " << edge->info.zona << ")" << endl;
                edge = edge->next;
                i++;
            }
            cout << endl;
        }
    } else {
        cout << "Lokasi dengan ID " << id << " tidak ditemukan." << endl;
    }
}

void jalurAman(Graph G, string id) {
    adr_Node b = findNode(G, id);
    if (b != NULL){
        adr_Edge a = b->firstE;
        if (a == NULL){
            cout << "Tidak ada koneksi dari lokasi " << b->info.nama << endl;
        } else {
            cout << "Lokasi yang aman dituju dari " << b->info.nama << " :" << endl;
            bool adaZonaH = false;
            int i = 1;
            while(a!=NULL){
                if (a->info.zona == "Hijau"){
                    cout << i << ". lokasi " << a->info.nama << " , id: " << a->info.id << ", zona: " << a->info.zona << endl;
                    i++;
                    adaZonaH = true;
                }
                a = a->next;
            }
            if (!adaZonaH) {
                cout << "Tidak ada zona aman dari lokasi " << b->info.nama << endl;
            }
        }
    } else {
        cout << "Lokasi yang diinput tidak ada" << endl;
    }
}

void addlokasi(Graph &G){
    infotypeN m;
    m.nama = "Moosewood";
    m.id = "M123";
    adr_Node nodeM = createN(m);
    addNode(G, nodeM);

    infotypeN s;
    s.nama = "Sunstone";
    s.id = "S123";
    adr_Node nodeB = createN(s);
    addNode(G, nodeB);

    infotypeN r;
    r.nama = "Roslit";
    r.id = "R123";
    adr_Node nodeR = createN(r);
    addNode(G, nodeR);

    infotypeN f;
    f.nama = "Forsaken";
    f.id = "F123";
    adr_Node nodeF = createN(f);
    addNode(G, nodeF);

    infotypeN t;
    t.nama = "Terappin";
    t.id = "T123";
    adr_Node nodeT = createN(t);
    addNode(G, nodeT);

    infotypeN sn;
    sn.nama = "Snowcap";
    sn.id = "Sn123";
    adr_Node nodeSn = createN(sn);
    addNode(G, nodeSn);

    infotypeN a;
    a.nama = "Ancient";
    a.id = "A123";
    adr_Node nodeA = createN(a);
    addNode(G, nodeA);

    infotypeN ms;
    ms.nama = "Mushgrove";
    ms.id = "Ms123";
    adr_Node nodeMs = createN(ms);
    addNode(G, nodeMs);

    string zoneH = "hijau";
    string zoneO = "Oren";
    string zoneM = "Merah";

    // Moosewood
    connecting(G, m.id, s.id, zoneH);
    connecting(G, m.id, r.id, zoneH);
    connecting(G, m.id, f.id, zoneO);
    connecting(G, m.id, t.id, zoneO);
    connecting(G, m.id, sn.id, zoneH);
    connecting(G, m.id, a.id, zoneM);
    connecting(G, m.id, ms.id, zoneH);
    // Sunstone
    connecting(G, s.id, ms.id, zoneH);
    connecting(G, s.id, r.id, zoneH);
    // Roslit
    connecting(G, r.id, f.id, zoneH);
    //Forsaken
    connecting(G, f.id, t.id, zoneO);
    // Terappin
    connecting(G, t.id, sn.id, zoneH);
    //Snowcap
    connecting(G, sn.id, a.id, zoneM);
    //Ancient
    connecting(G, a.id, ms.id, zoneM);
}
