#include "filial.h"
#include <stdbool.h>
#include "glibW.h"
#include <gmodule.h>
#include <string.h>
#include <stdlib.h>

struct filiais {
    GHashTable* cliCompra;
    GHashTable* prodCompra;
};

typedef struct cliCompra {
    char* cliente;
    GHashTable* prodCli;
    int quantidade[12];
} *CliCompra;

typedef struct prodCompra {
    char* prod;
    GHashTable* quemComprou;
} *ProdCompra;

typedef struct prodCli {
    char* prod;
    char* cliente;
    int quantidade[12];
    double total;
} *ProdCli;

struct compradores {
    char** compradores[2];
    int quantidades[2];
};

int filialGetProdutosCliente(Compradores c, Tipo t, char*** array) {
    if(array)
        *array = c->compradores[t];
    return c->quantidades[t];
}

void compradoresDestroy(Compradores c) {
    int i, j;
    for(i = 0; i < 2; i++) {
        for(j = 0; j < c->quantidades[i]; j++)
            free(c->compradores[i][j]);
        free(c->compradores[i]);
    }
    free(c);
}

static ProdCli prodCliInit(char* cliente, char* produto, int quantidade, double total, int mes) {
    ProdCli pcl = malloc(sizeof(struct prodCli));
    pcl->prod = malloc(strlen(produto) + 1);
    strcpy(pcl->prod, produto);
    pcl->cliente = cliente;
    memset(pcl->quantidade, 0, 12 * sizeof(int));
    pcl->quantidade[mes - 1] += quantidade;
    pcl->total = total;
    return pcl;
}

static void prodCliUpdate(ProdCli pcl, int quantidade, int mes, double total) {
    pcl->quantidade[mes - 1] += quantidade;
    pcl->total += total;
}

static void prodCliDestroy(void* pc) {
    ProdCli pcl = (ProdCli) pc;
    free(pcl->prod);
    free(pcl);
}

static CliCompra cliCompraInit(const char* cliente) {
    CliCompra cc = malloc(sizeof(struct cliCompra));
    cc->cliente = malloc(strlen(cliente) + 1);
    strcpy(cc->cliente, cliente);
    cc->prodCli = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, prodCliDestroy);
    memset(cc->quantidade, 0, 12 * sizeof(int));
    return cc;
}

static void cliCompraUpdate(CliCompra cc, char* produto, int quantidade, double total, int mes) {
    ProdCli pcl = g_hash_table_lookup(cc->prodCli, produto);
    cc->quantidade[mes-1] += quantidade;
    if(pcl) 
        prodCliUpdate(pcl, quantidade, mes, total);
    else {
        pcl = prodCliInit(cc->cliente, produto, quantidade, total, mes);
        g_hash_table_insert(cc->prodCli, pcl->prod, pcl);
    }
} 

static void cliCompraDestroy(void* c) {
    CliCompra cc = (CliCompra) c;
    g_hash_table_destroy(cc->prodCli);
    free(cc->cliente);
    free(cc);
}

static ProdCompra prodCompraInit(const char* prod, const char* cli, const Tipo tipo) {
    ProdCompra r = malloc(sizeof(struct prodCompra));
    char* cliente = malloc(strlen(cli) + 1);
    Tipo* t = malloc(sizeof(Tipo));
    *t = tipo;
    strcpy(cliente, cli);
    r->prod = malloc(strlen(prod) + 1);
    strcpy(r->prod, prod);
    r->quemComprou = g_hash_table_new_full(g_str_hash, g_str_equal, free, free);
    g_hash_table_insert(r->quemComprou, cliente, t);
    return r;
} 

static void prodCompraUpdate(ProdCompra r, char* client, Tipo t) {
    Tipo* tipo = g_hash_table_lookup(r->quemComprou, client);
    if(tipo && *tipo != t) 
        *tipo = AL;
    else if(!tipo) {
        char* cliente = malloc(strlen(client) + 1);
        strcpy(cliente, client);
        tipo = malloc(sizeof(Tipo));
        *tipo = t;
        g_hash_table_insert(r->quemComprou, cliente, tipo);
    }
}

static void prodCompraDestroy(void* o) {
    ProdCompra r = (ProdCompra) o;
    g_hash_table_destroy(r->quemComprou);
    free(r->prod);
    free(r);
} 

static void productLetter(gpointer key, gpointer value, gpointer data) {
    Compradores c = (Compradores) data;
    Tipo t = *(Tipo*) value;
    if(t != P) {
        c->compradores[N][c->quantidades[N]] = malloc(strlen((char*) key) + 1);
        strcpy(c->compradores[N][c->quantidades[N]++], (char*) key);
    }
    if(t != N) {
        c->compradores[P][c->quantidades[P]] = malloc(strlen((char*) key) + 1);
        strcpy(c->compradores[P][c->quantidades[P]++], (char*) key);
    }
}

Compradores produtoQuemComprou(const Filiais f, const char* id) {
    ProdCompra p = g_hash_table_lookup(f->prodCompra, id);
    int size;
    Compradores c = malloc(sizeof(struct compradores));
    size = p ? g_hash_table_size(p->quemComprou) : 0;
    c->compradores[0] = malloc(size * sizeof(char*));
    c->compradores[1] = malloc(size * sizeof(char*));
    c->quantidades[0] = c->quantidades[1] = 0;
    if(p) g_hash_table_foreach(p->quemComprou, productLetter, c);
    return c;
}

Filiais filialInit() {
    Filiais f = malloc(sizeof(struct filiais));
    f->prodCompra = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, prodCompraDestroy);
    f->cliCompra = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, cliCompraDestroy);
    return f;
}

void filialUpdate(Filiais f, Venda v) {
    char* cliente = getClientSale(v);
    char* produto = getProductSale(v);
    ProdCompra pc = g_hash_table_lookup(f->prodCompra, produto);
    CliCompra cc = g_hash_table_lookup(f->cliCompra, cliente);
    if(cc)
        cliCompraUpdate(cc, produto, getQuantSale(v), getTotalSale(v), getMesSale(v));
    else {
        cc = cliCompraInit(cliente);
        cliCompraUpdate(cc, produto, getQuantSale(v), getTotalSale(v), getMesSale(v));
        g_hash_table_insert(f->cliCompra, cc->cliente, cc);
    }
    if(pc)
        prodCompraUpdate(pc, cliente, getTipoSale(v));
    else {
        pc = prodCompraInit(produto, cliente, getTipoSale(v));
        g_hash_table_insert(f->prodCompra, pc->prod, pc);
    }
}

int getClientQuant(const char* id, int mes, const Filiais f) {
    CliCompra p = g_hash_table_lookup(f->cliCompra, id);
    return p ? p->quantidade[mes] : 0;
}

int produtosQuantosCompraram(const char* id, Filiais f) {
    ProdCompra p = g_hash_table_lookup(f->prodCompra, id);
    return p ? g_hash_table_size(p->quemComprou) : 0;
}

static int prodCliCmp(const void* a, const void* b) {
    ProdCli aa = *(ProdCli*) a;
    ProdCli bb = *(ProdCli*) b;
    return bb->total - aa->total;
}

static int prodCliCmpQuant(const void* a, const void* b, void* c) {
    ProdCli aa = *(ProdCli*) a;
    ProdCli bb = *(ProdCli*) b;
    int mes = *(int*) c;
    return bb->quantidade[mes - 1] - aa->quantidade[mes - 1];
}

void mergeUpdate(void* key, void* value, void* data) {
    char* ke = (char*) key;
    ProdCli valu = (ProdCli) value;
    GHashTable* dat = (GHashTable*) data;
    ProdCli tmp = g_hash_table_lookup(dat, ke);
    int quants = 0, i;
    for(i = 0; i < 12; i++)
        quants += valu->quantidade[i];
    if(tmp) tmp->total += valu->total; 
    else g_hash_table_insert(dat, key, prodCliInit(valu->cliente, valu->prod, quants, valu->total, 1));
}

int getMaisVendidosCliente(const Filiais f[], const char* id, int N, char*** rrr) {
    GHashTable* merge = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, NULL);
    GHashTableIter r;
    ProdCli prod;
    char* lixo;
    int i, size;
    for(i = 0; i < N; i++) {
        CliCompra cliCompra = g_hash_table_lookup(f[i]->cliCompra, id);
        if(cliCompra)
            g_hash_table_foreach(cliCompra->prodCli, mergeUpdate, merge);
    }
    g_hash_table_iter_init(&r, merge);
    i=0;
    size = g_hash_table_size(merge);
    ProdCli array[size];
    *rrr = malloc(sizeof(char*) * 3);
    while(g_hash_table_iter_next(&r, (void*) &lixo, (void*) &prod))
        array[i++] = prod;
    qsort(array, size, sizeof(ProdCli), prodCliCmp);
    for(i = 0; i < 3 && i < size; i++) {
        (*rrr)[i] = malloc(strlen(array[i]->prod) + 1);
        strcpy((*rrr)[i], array[i]->prod);
    }
    g_hash_table_destroy(merge);
    return i;
}

int getMaisCompradosCliente(const Filiais f[], const char* id, char*** rrr, int mes) {
    GHashTable* merge = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, NULL);
    GHashTableIter r;
    ProdCli prod;
    char* lixo;
    int i, size;
    for(i = 0; i < N; i++) {
        CliCompra cliCompra = g_hash_table_lookup(f[i]->cliCompra, id);
        if(cliCompra)
            g_hash_table_foreach(cliCompra->prodCli, mergeUpdate, merge);
    }
    g_hash_table_iter_init(&r, merge);
    i=0;
    size = g_hash_table_size(merge);
    ProdCli array[size];
    *rrr = malloc(sizeof(char*) * size);
    while(g_hash_table_iter_next(&r, (void*) &lixo, (void*) &prod))
        array[i++] = prod;
    qsort_r(array, size, sizeof(ProdCli), prodCliCmpQuant, &mes);
    for(i = 0; i < size; i++) {
        (*rrr)[i] = malloc(strlen(array[i]->prod) + 1);
        strcpy((*rrr)[i], array[i]->prod);
    }
    g_hash_table_destroy(merge);
    return i;
}

void destroyFilial(Filiais f) {
    g_hash_table_destroy(f->cliCompra);
    g_hash_table_destroy(f->prodCompra);
    free(f);
}

